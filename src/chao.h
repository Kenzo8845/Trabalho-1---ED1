#ifndef CHAO_H
#define CHAO_H

#include "fila.h"
#include "formas.h"
#include <stdio.h>
#include <stdlib.h>

/*
* TAD de chão.
* O chão é um tipo de fila, com logica de primerio a entrar sera o primeiro a sair.
* Todos os elementos armazenados no chão serão formas.
* O chão serve de como "inventario" das formas utilizadas no jogo da bocha.
*
* Quando o chão é usado:
* Ao iniciar o jogo, todas as formas lidas no arquivo .geo são adicionadas em ordem de leitura ao chão.
* Quando uma forma é colocada de um carregador ela é pega do chão.
* Ao sair da arena, a forma ou é destruida, ou retorna ao chão.
*
* Este arquivo contem todas as funções responsaveis pela manipulação do chão.
*/

typedef struct chao* Chao;



/*=====================*/
/* Constructor do chão */
/*=====================*/
/**
 * @brief Cria um chão novo.
 * @param geo_formas Uma fila com os as formas retiradas do arquivo geo.
 * @return O chao criado, ou NULL em caso de erro.
 */
Chao chao_cria(Fila geo_formas);



/*====================*/
/* Destructor do chão */
/*====================*/
/**
 * @brief Destroi e libera a memoria de um chão.
 * @param c O chão qual sera destruido.
 */
void chao_destruir(Chao c);




/*====================*/
/* Operações do chão  */
/*====================*/
/**
 * @brief Retira-se uma forma do inicio do chão.
 * @param c O chão de qual a forma sera retirda.
 * @return Forma, A forma retirada, ou NULL em caso de erro.
 */
Forma chao_retiraForma(Chao c);

/**
 * @brief Adiciona uma forma ao final do chão.
 * @param c O chão no qual sera adicionada a forma.
 * @param f A forma na qual sera adicionada ao chão.
 */
void chao_adicionaAoChao(Chao c, Forma f);



/*====================*/
/*  Getters do chão   */
/*====================*/
/**
 * @brief Pega a quantidade de Formas no chao.
 * @param c O chão qual se quer saber o tamanho.
 * @return int O numero de formas no chão, ou -1, em caso de erro.
 */
int chao_getTamanho(Chao c);

/**
 * @brief Retorna a Fila do chão selecionado.
 * @param c O chão qual se quer a fila.
 * @return Fila A fila do chão selecionado, ou NULL, em caso de erro.
 */
Fila chao_getFila(Chao c);



/*====================*/
/* Funções de Desenho */
/*====================*/
/**
 * @brief Desenha todas as formas do Chão em um arquivo SVG.
 * @param c O Chão.
 * @param svg_file O ponteiro do arquivo SVG.
 */
void chao_desenhaSvg(Chao c, FILE* svg_file);


#endif