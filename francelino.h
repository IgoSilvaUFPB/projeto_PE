#ifndef _francelino_H_
#define _francelino_H_ 

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_ITERATIONS 100
#define NUM_POINTS 200
#define NUM_CLUSTERS 3

typedef struct {
    double x;
    double y;
    int cluster;
} Point;

typedef struct {
    double x;
    double y;
    int count;
} Centroid;

double distance(Point point, Centroid centroid) {
    return sqrt(pow(point.x - centroid.x, 2) + pow(point.y - centroid.y, 2));
}

int main() {
    Point points[NUM_POINTS];
    Centroid centroids[NUM_CLUSTERS];
    
    // Inicialização: Selecionar centroides aleatórios
    centroids[0].x = 1.0;
    centroids[0].y = 1.0;
    centroids[0].count = 0;
    centroids[1].x = -1.0;
    centroids[1].y = -1.0;
    centroids[1].count = 0;
    centroids[2].x = 0.0;
    centroids[2].y = 0.0;
    centroids[2].count = 0;
    
    // Leitura dos pontos de dados
    FILE *file = fopen("df_test.csv", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }
    
    char line[100];
    fgets(line, sizeof(line), file);  // Ignorar o cabeçalho do arquivo
    
    for (int i = 0; i < NUM_POINTS; i++) {
        fgets(line, sizeof(line), file);
        sscanf(line, "%*d,%lf,%lf", &points[i].x, &points[i].y);
        points[i].cluster = 0;
    }
    
    fclose(file);
    
    // Execução do algoritmo K-means
    int iteration;
    for (iteration = 0; iteration < MAX_ITERATIONS; iteration++) {
        // Associação: Atribuir pontos aos centroides mais próximos
        for (int i = 0; i < NUM_POINTS; i++) {
            double minDistance = INFINITY;
            int closestCentroid;
            
            for (int j = 0; j < NUM_CLUSTERS; j++) {
                double d = distance(points[i], centroids[j]);
                if (d < minDistance) {
                    minDistance = d;
                    closestCentroid = j;
                }
            }
            
            points[i].cluster = closestCentroid;
            centroids[closestCentroid].count++;
            centroids[closestCentroid].x += points[i].x;
            centroids[closestCentroid].y += points[i].y;
        }
        
        // Atualização: Recalcular as posições dos centroides
        for (int j = 0; j < NUM_CLUSTERS; j++) {
            centroids[j].x /= centroids[j].count;
            centroids[j].y /= centroids[j].count;
            centroids[j].count = 0;
        }
    }
    
    // Imprimir os resultados
    printf("Resultado do K-means:\n");
    for (int i = 0; i < NUM_POINTS; i++) {
        printf("Ponto (%lf, %lf) pertence ao cluster %d\n", points[i].x, points[i].y, points[i].cluster);
    }
    
    return 0;
}
