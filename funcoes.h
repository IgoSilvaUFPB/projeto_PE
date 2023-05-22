#ifndef _FUNCOES_H_
#define _FUNCOES_H_ 

#define MAX_LINE_LENGTH 100

// Plota o gráfico
void plotagem(int iteration) {
    FILE *points = fopen(ARQUIVO_PONTOS, "r");
    FILE *centroids = fopen(ARQUIVO_CENTROIDES, "r");

    if (points == NULL || centroids == NULL) {
        printf("Erro ao abrir os arquivos.\n");
        return;
    }

    // Prepara o comando para chamar o gnuplot
    FILE *gnuplotPipe = popen("gnuplot -persist", "w");
    if (gnuplotPipe == NULL) {
        printf("Erro ao abrir o pipe do gnuplot.\n");
        return;
    }

    fprintf(gnuplotPipe, "set title 'Rodada %d'\n", iteration);
    fprintf(gnuplotPipe, "set xlabel 'X'\n");
    fprintf(gnuplotPipe, "set ylabel 'Y'\n");
    fprintf(gnuplotPipe, "plot '-' using 1:2:3 with points lc variable pt 7 title 'Pontos', '-' using 1:2:3 with points lc variable pt 9 ps 4 title 'Centroides'\n");

    // Lê e plota os pontos
    fprintf(gnuplotPipe, "# Pontos\n");
    float x, y;
    int id, clu;
    while (fscanf(points, "%d,%f,%f,%d", &id, &x, &y, &clu) == 4) {
        fprintf(gnuplotPipe, "%f %f %d\n", x, y, clu);
    }
    fprintf(gnuplotPipe, "e\n");

    // Lê e plota os centroides
    fprintf(gnuplotPipe, "# Centroides\n");
    while (fscanf(centroids, "%d,%f,%f", &id, &x, &y) == 3) {
        fprintf(gnuplotPipe, "%f %f %d\n", x, y, id);
    }
    fprintf(gnuplotPipe, "e\n");

    // Exibe o gráfico
    fprintf(gnuplotPipe, "set terminal png\n");
    fprintf(gnuplotPipe, "set palette defined (0 'red', 1 'blue', 2 'green', 3 'black' )\n");
    fprintf(gnuplotPipe, "replot\n");

    // Fecha os arquivos e o pipe do gnuplot
    fclose(points);
    fclose(centroids);
    pclose(gnuplotPipe);
}

// Calcula a distância entre os pontos e os centroides
double distancia(Point points, Centroid centroids) {
    return sqrt(pow(points.x - centroids.x, 2) + pow(points.y - centroids.y, 2));
}

// Carrega dados dos arquivos csv
void carregaDados(Point points[], Centroid centroids[]) {    
    // Carrega dados dos pontos
    FILE *pontos = fopen(ARQUIVO_PONTOS, "r");
    if (pontos == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }
    char line[100];
    for (int i = 0; i < NUM_POINTS; i++) {
        fgets(line, sizeof(line), pontos);
        sscanf(line, "%d,%lf,%lf,%d", &points[i].id, &points[i].x, &points[i].y, &points[i].cluster);
    }
    fclose(pontos);

    // Carrega dados dos centroides
    FILE *centroides = fopen(ARQUIVO_CENTROIDES, "r");
    if (centroides == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }    
    char line2[100];
    for (int i = 0; i < NUM_CLUSTERS; i++) {
        fgets(line2, sizeof(line2), centroides);
        sscanf(line2, "%d,%lf,%lf", &centroids[i].id, &centroids[i].x, &centroids[i].y);
    }    
    fclose(centroides);    
}

// Associa os pontos aos centroides mais próximos
void associaPontosaosCentroides(Point points[], Centroid centroids[]) {
    for (int i = 0; i < NUM_POINTS; i++) {
        double minDistance = INFINITY;
        int closestCentroid = 0;

        for (int j = 0; j < NUM_CLUSTERS; j++) {
            double d = distancia(points[i], centroids[j]);
            if (d < minDistance) {
                minDistance = d;
                closestCentroid = j;
            }
        }
        points[i].cluster = closestCentroid; // Altera o centroide associado ao ponto
    }
}

// Atualiza a posição dos centroides
void atualizaPosicaoCentroides(Point points[], Centroid centroids[]) {
    // Zera as posições dos centroides
    for (int k = 0; k < NUM_CLUSTERS; k++) {        
        centroids[k].sumx = 0;
        centroids[k].sumy = 0;
        centroids[k].count = 0;
    }

    // Soma as posições dos pontos associados a cada centroide    
    for (int i = 0; i < NUM_POINTS; i++) {
        int cluster = points[i].cluster;
        centroids[cluster].sumx = centroids[cluster].sumx + points[i].x;
        centroids[cluster].sumy = centroids[cluster].sumy + points[i].y;
        centroids[cluster].count++;
    }

    // Calcula a média das posições dos pontos associados a cada centroide
    for (int j = 0; j < NUM_CLUSTERS; j++) {
        if (centroids[j].count > 0) {
            centroids[j].x = centroids[j].sumx / centroids[j].count;
            centroids[j].y = centroids[j].sumy / centroids[j].count;
        }
    }
}

// Pausa para visualização
void pausa(){
    printf("\nPressione ENTER para continuar...\n");
    while(getchar() != '\n');
}

// Atualiza o arquivo dos pontos
void atualizaPontos (Point points[]){
    FILE *pontos = fopen(ARQUIVO_PONTOS, "w");
    if (pontos == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }     

    for (int i = 0; i < NUM_POINTS; i++) {
        fprintf(pontos, "%d,%lf,%lf,%d\n", points[i].id, points[i].x, points[i].y, points[i].cluster);
    }
    fclose(pontos);
}

// Atualiza o arquivo dos centroides
void atualizaCentroides (Centroid centroids[]){
    FILE *centroides = fopen(ARQUIVO_CENTROIDES, "w");
    if (centroides == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    for (int j = 0; j < NUM_CLUSTERS; j++) {
        fprintf(centroides, "%d,%lf,%lf\n", centroids[j].id, centroids[j].x, centroids[j].y);
    }
    fclose(centroides);
}

void resetaArquivos(Point points[], Centroid centroids[]) {    
    // Carrega dados dos pontos de teste
    FILE *pontosteste = fopen("df_test.csv", "r");    
    if (pontosteste == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }
    char line[100];
    for (int i = 0; i < NUM_POINTS; i++) {
        fgets(line, sizeof(line), pontosteste);
        sscanf(line, "%d,%lf,%lf,%d", &points[i].id, &points[i].x, &points[i].y, &points[i].cluster);
    }
    fclose(pontosteste);

    // Recupera os pontos de teste
    FILE *pontos = fopen(ARQUIVO_PONTOS, "w");
    if (pontos == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }
    for (int i = 0; i < NUM_POINTS; i++) {
        fprintf(pontos, "%d,%lf,%lf,%d\n", points[i].id, points[i].x, points[i].y, points[i].cluster);
    }
    fclose(pontos);

    // Carrega dados dos centroides de teste
    FILE *centroidesteste = fopen("centroide_test.csv", "r");    
    if (centroidesteste == NULL || pontos == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }
    char line2[100];
    for (int i = 0; i < NUM_CLUSTERS; i++) {
        fgets(line2, sizeof(line2), centroidesteste);
        sscanf(line2, "%d,%lf,%lf", &centroids[i].id, &centroids[i].x, &centroids[i].y);
    }
    fclose(centroidesteste);

    // Recupera os centroides de teste
    FILE *centroides = fopen(ARQUIVO_CENTROIDES, "w");
    if (centroides == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }
    for (int j = 0; j < NUM_CLUSTERS; j++) {
        fprintf(centroides, "%d,%lf,%lf\n", centroids[j].id, centroids[j].x, centroids[j].y);
    }
    fclose(centroides); 
}

#endif