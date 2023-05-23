# Universidade Federal da Paraíba - UFPB
## Curso: Ciência de Dados e Inteligência Artificial
## Disciplina: Programação Estruturada
## Projeto: Implementação do algoritmo K-means na linguagem C

---

Equipe:
- DAVI NASIASENE AMORIM (20220056987)
- FRANCELINO TEOTONIO JUNIOR (20190035175)
- GUILHERME BARBOZA DE SOUSA (20220007418)
- IGÓ FERREIRA MELO SILVA (20220155214)

---

O que é o K-means?

O algoritmo K-means é um método de aprendizado não supervisionado usado para agrupar dados em clusters. Ele busca dividir um conjunto de dados em grupos (clusters) com base em suas características ou similaridades.
O algoritmo K-means funciona da seguinte maneira:
1. Inicialização: O algoritmo seleciona aleatoriamente K pontos de dados como "centroides" iniciais. Esses centroides representam os pontos centrais de cada cluster.
2. Associação: Cada ponto de dados é atribuído ao centroide mais próximo com base em uma medida de distância, geralmente a distância euclidiana.
3. Atualização: Os centroides dos clusters são atualizados recalculando-se as médias dos pontos atribuídos a cada cluster. Isso envolve mover o centroide para o centro dos pontos que estão atualmente associados a ele.
4. Repetição: Os passos 2 e 3 são repetidos até que ocorra uma condição de parada. A condição de parada pode ser um número máximo de iterações, quando não ocorrem mais alterações significativas nos centroides ou quando os clusters convergem para uma configuração estável.


O resultado final do algoritmo K-means é um conjunto de K clusters, cada um contendo pontos de dados semelhantes. Os centroides finais podem ser usados para classificar novos pontos de dados em clusters existentes.
O K-means é amplamente utilizado em várias áreas, como análise de dados, mineração de dados, reconhecimento de padrões e aprendizado de máquina. Ele pode ajudar a identificar padrões, segmentar clientes, agrupar documentos e muito mais. No entanto, é importante lembrar que o K-means requer que o número de clusters (K) seja especificado antecipadamente e que pode haver sensibilidade à inicialização dos centroides.

---

Download Gnuplot:

[Mirror 1](https://sourceforge.net/projects/gnuplot/files/gnuplot/)

[Mirror 2](https://fossies.org/windows/misc/gp547-win64-mingw.exe/)

---

Exemplos:

![gif 1](https://github.com/IgoSilvaUFPB/projeto_PE/blob/40d4afc8bc30212fbc869098c8006489fdf95684/gif_1.gif)
![gif 2](https://github.com/IgoSilvaUFPB/projeto_PE/blob/40d4afc8bc30212fbc869098c8006489fdf95684/gif_2.gif)
![gif 3](https://github.com/IgoSilvaUFPB/projeto_PE/blob/40d4afc8bc30212fbc869098c8006489fdf95684/gif_3.gif)
