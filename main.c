/*------------------------------------------------------------*/
/*          Universidade Federal da Paraíba - UFPB            */
/*      Curso: Ciência de Dados e Inteligência Artificial     */
/*            Disciplina: Programação Estruturada             */
/* Projeto: Implementação do algoritmo K-Means na linguagem C */
/* Equipe:                                                    */
/* - DAVI NASIASENE AMORIM (20220056987)                      */
/* - FRANCELINO TEOTONIO JUNIOR (20190035175)                 */
/* - GUILHERME BARBOZA DE SOUSA (20220007418)                 */
/* - IGÓ FERREIRA MELO SILVA (20220155214)                    */
/*------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAX_ITERATIONS 30
#define NUM_POINTS 300
#define NUM_CLUSTERS 5
#define ESPALHAMENTO 19
#define ARQUIVO_PONTOS "pontos.csv"
#define ARQUIVO_CENTROIDES "centroides.csv"

typedef struct {
    int id;
    double x;
    double y;
    int cluster;
} Point;

typedef struct {
    int id;
    double x;
    double y;
    int count;
    double sumx;
    double sumy;
} Centroid;

#include "funcoes.h"

int main() {

    printf("\n** K-MEANS COM PONTOS E CENTROIDES GERADOS ALEATORIAMENTE **\n\nAbertura - ");

    // Definindo arrays de pontos e centroides
    Point points[NUM_POINTS];
    Centroid centroids[NUM_CLUSTERS];

    // Semente para geração de pontos e centroides
    srand(time(NULL));    

    //Gera pontos
    criaPontos();

    //Gera centroides
    criaCentroides();

    // Plota o gráfico na condição inicial
    plotagem(0);

    // Pausa para visualização
    pausa();

    for (int iteration = 0; iteration < MAX_ITERATIONS; iteration++) {       
        printf("\nRodada %d - ", iteration+1);

        // Carrega dados dos arquivos csv
        carregaDados(points, centroids);

        // Associa os pontos aos centroides mais próximos
        associaPontosaosCentroides(points, centroids);

        // Atualiza a posição dos centroides
        atualizaPosicaoCentroides(points, centroids);

        // Atualiza o arquivo dos pontos
        atualizaPontos (points);

        // Atualiza o arquivo dos centroides
        atualizaCentroides (centroids);

        // Plota o gráfico
        plotagem(iteration+1);

        // Pausa para visualização
        pausa();
    }
    return 0;
}