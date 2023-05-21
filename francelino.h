#ifndef _FRANCELINO_H_
#define _FRANCELINO_H_ 
/*
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <unistd.h>

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

void readData(Point points[], Centroid centroids[]) {
    FILE *file = fopen("df_test.csv", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    char line[100];
    fgets(line, sizeof(line), file);  // Ignorar o cabeçalho do arquivo

    for (int i = 0; i < NUM_POINTS; i++) {
        fgets(line, sizeof(line), file);
        sscanf(line, "%*d,%lf,%lf", &points[i].x, &points[i].y);
        points[i].cluster = 0;
    }

    fclose(file);
}

void assignPointsToClosestCentroids(Point points[], Centroid centroids[]) {
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
}

bool updateCentroids(Point points[], Centroid centroids[]) {
    bool positionChanged = false;

    for (int j = 0; j < NUM_CLUSTERS; j++) {
        if (centroids[j].count > 0) {
            double newX = centroids[j].x / centroids[j].count;
            double newY = centroids[j].y / centroids[j].count;

            if (newX != centroids[j].x || newY != centroids[j].y) {
                positionChanged = true;
            }

            centroids[j].x = newX;
            centroids[j].y = newY;
            centroids[j].count = 0;
        }
    }

    return positionChanged;
}

void performKMeans(Point points[], Centroid centroids[]) {
    int iteration;
    bool positionChanged = true;

    for (iteration = 0; iteration < MAX_ITERATIONS && positionChanged; iteration++) {
        assignPointsToClosestCentroids(points, centroids);
        positionChanged = updateCentroids(points, centroids);

        // Mostrar o estado atual dos centroides e pontos atribuídos
        printf("Iteração %d:\n", iteration + 1);
        for (int j = 0; j < NUM_CLUSTERS; j++) {
            printf("Centroide %d: (%lf, %lf)\n", j + 1, centroids[j].x, centroids[j].y);
        }
        printf("\n");
        for (int i = 0; i < NUM_POINTS; i++) {
            printf("Ponto (%lf, %lf) pertence ao cluster %d\n", points[i].x, points[i].y, points[i].cluster);
        }
        printf("\n");

        usleep(1000000);  // Pausa de 1 segundo (requer a biblioteca <unistd.h>)
    }

    printf("Número de iterações: %d\n", iteration);
}

void writeCentroidResults(Centroid centroids[]) {
    FILE *file = fopen("centroid_resultado.csv", "w");
    if (file == NULL) {
        printf("Erro ao criar o arquivo.\n");
        return;
    }

    fprintf(file, "id,x,y\n");
    for (int j = 0; j < NUM_CLUSTERS; j++) {
        fprintf(file, "%d,%lf,%lf\n", j + 1, centroids[j].x, centroids[j].y);
    }

    fclose(file);
}

int main() {
    Point points[NUM_POINTS];
    Centroid centroids[NUM_CLUSTERS];

    readData(points, centroids);

    performKMeans(points, centroids);

    writeCentroidResults(centroids);

    return 0;
}
*/

#endif