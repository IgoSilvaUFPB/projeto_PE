/*---------------------------------------------------------*/
//Universidade Federal da Paraíba - UFPB
//Curso: Ciência de Dados e Inteligência Artificial
//Disciplina: Programação Estruturada
//Projeto: Implementação do algoritmo K-Means na linguagem C
//Equipe:
// - DAVI NASIASENE AMORI (20220056987)
// - FRANCELINO TEOTONIO JUNIOR (20190035175)
// - GUILHERME BARBOZA DE SOUSA (20220007418)
// - IGÓ FERREIRA MELO SILVA (20220155214)
/*---------------------------------------------------------*/
#include <stdio.h>
#include "davi.h"
#include "francelino.h"
#include "guilherme.h"
#include "igo.h"
#include <stdlib.h>
#include <math.h>

#define MAX_ITERATIONS 5
#define NUM_POINTS 200
#define NUM_CLUSTERS 3
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

    /*
    Função que gera pontos iniciais
    ??????
    */

    /*
    Função que gera centroides iniciais
    ?????
    */

    Point points[NUM_POINTS];
    Centroid centroids[NUM_CLUSTERS];

    // Reseta os arquivos de teste
    resetaArquivos(points, centroids);

    int iteration;

    // Plota o gráfico na condição inicial
    plotagem(0);

    // Pausa para visualização
    pausa();

    for (iteration = 0; iteration < MAX_ITERATIONS; iteration++) {       
        
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