#ifndef _francelino_H_
#define _francelino_H_ 

//Sua área de trabalho

/*
Sugiro criar uma cópia dos arquivos com as coordenadas iniciais dos pontos e centroides
 para fazer seus testes sem atrapalhar os demais. Pois você precisará sobreescrevê-lo
 muitas vezes.
*/

/*
Função que lê os dados dos arquivos com as coordenadas dos pontos e centroides
e faz o cálculo as distâncias entre os pontos e os centroides 
atribuindo cada ponto ao centroide mais próximo e armazenando esta informação
*/

/*
Função que recalcula a posição dos centroides
utilizando a média das distâncias dos pontos atribuídos a ele.
E também verifica se houve alteração na posição do centroide,
pois esta será a condição de parada. 
É bom também limitar o número de iterações para evitar um loop infinito
nos casos em que o centróide fica alternando entre duas posições muito próximas.
*/

/*
Função para repetir todo o processo até que a condição de parada seja alcançada.
*/