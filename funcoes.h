#ifndef _FUNCOES_H_
#define _FUNCOES_H_

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

    // Define parâmetros de plotagem do gnuplot
    fprintf(gnuplotPipe, "set title 'Rodada %d'\n", iteration);
    fprintf(gnuplotPipe, "set xlabel 'X'\n");
    fprintf(gnuplotPipe, "set ylabel 'Y'\n");
    fprintf(gnuplotPipe, "set key box linestyle 1 width 2 height 2 horizontal outside bottom center\n");
    fprintf(gnuplotPipe, "plot '-' using 1:2:3 with points lc variable pt 7 title 'Pontos', \
                                '-' using 1:2:3 with points lc variable pt 9 ps 5 title 'Centroides', \
                                '-' using 1:2:3:4 with labels textcolor rgb 'black' notitle\n");

    // Lê e plota os pontos
    fprintf(gnuplotPipe, "# Pontos\n");
    float x, y;
    int id, clu, count;
    while (fscanf(points, "%d,%f,%f,%d", &id, &x, &y, &clu) == 4) {
        fprintf(gnuplotPipe, "%f %f %d\n", x, y, clu);
    }
    fprintf(gnuplotPipe, "e\n");

    // Lê e plota os centroides
    fprintf(gnuplotPipe, "# Centroides\n");
    while (fscanf(centroids, "%d,%f,%f,%d", &id, &x, &y, &count) == 4) {
        fprintf(gnuplotPipe, "%f %f %d\n", x, y, id);
    }
    fprintf(gnuplotPipe, "e\n");

    // Lê e plota os rótulos dos centroides
    fprintf(gnuplotPipe, "# Rótulos dos Centroides\n");
    rewind(centroids);  // Volta ao início do arquivo de centroides
    while (fscanf(centroids, "%d,%f,%f,%d", &id, &x, &y, &count) == 4) {
        fprintf(gnuplotPipe, "%f %f %d %d\n", x, y, count, count);
    }
    fprintf(gnuplotPipe, "e\n");    

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
        sscanf(line2, "%d,%lf,%lf,%d", &centroids[i].id, &centroids[i].x, &centroids[i].y, &centroids[i].count);
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
        if(points[i].cluster != closestCentroid){
            printf(".");
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
    printf("\n\nPressione ENTER para continuar...\n");
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
        fprintf(centroides, "%d,%lf,%lf,%d\n", centroids[j].id, centroids[j].x, centroids[j].y, centroids[j].count);
    }
    fclose(centroides);
}

// Gera pontos
void criaPontos() {
    FILE *pontos = fopen(ARQUIVO_PONTOS, "w");
    if (pontos == NULL) {
        printf("Erro ao abrir os arquivo.\n");
        return;
    }    

    // Gera centros de agrupamentos
    Point centroids[NUM_CLUSTERS];
    for (int i = 0; i < NUM_CLUSTERS; i++) {
        centroids[i].id = i + 1;
        centroids[i].x = (float)(rand() % 1000) / 10.0;  // Coordenadas de referência - x entre 0 e 100
        centroids[i].y = (float)(rand() % 1000) / 10.0;  // Coordenadas de referência - y entre 0 e 100
    }

    // Gera pontos aleatóriamente
    Point points[NUM_POINTS];
    for (int i = 0; i < NUM_POINTS; i++) {
        int cluster = i % NUM_CLUSTERS;
        points[i].id = i;
        float radius = (float)(rand() % ESPALHAMENTO);  // Ajustar o raio para controlar o espalhamento
        float angle = (float)(rand() % 360) * 3.1415 / 180.0;  // Ângulo aleatório em radianos        
        points[i].x = centroids[cluster].x + radius * cos(angle);
        points[i].y = centroids[cluster].y + radius * sin(angle);
        points[i].cluster = 0;  // Centroide associado inicializa em 0
    }

    // Salva pontos no CSV
    for (int i = 0; i < NUM_POINTS; i++) {
        fprintf(pontos, "%d,%.2f,%.2f,%d\n", points[i].id, points[i].x, points[i].y, points[i].cluster);
    }

    fclose(pontos);
}

// Gera centroides
void criaCentroides() {
    FILE *centroides = fopen(ARQUIVO_CENTROIDES, "w");
    if (centroides == NULL) {
        printf("Erro ao abrir os arquivo.\n");
        return;
    }

    // Gera centroides aleatoriamente
    Centroid centroids[NUM_CLUSTERS];
    for (int i = 0; i < NUM_CLUSTERS; i++) {
        centroids[i].id = i + 1;
        centroids[i].x = (float)(rand() % 1000) / 10.0;  // Coordenadas x dos centroides entre 0 e 100
        centroids[i].y = (float)(rand() % 1000) / 10.0;  // Coordenadas y dos centroides entre 0 e 100
        centroids[i].count = 0;
    }   

    // Salva centroides no CSV
    for (int i = 0; i < NUM_CLUSTERS; i++) {
        fprintf(centroides, "%d,%.2f,%.2f,%d\n", centroids[i].id, centroids[i].x, centroids[i].y, centroids[i].count);
    }

    fclose(centroides);
}

#endif