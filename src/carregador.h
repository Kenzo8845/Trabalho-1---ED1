#ifndef CARREGADOR_H
#define CARREGADOR_D

#include "formas.h"
#include "pilha.h"
#include "chao.h"

/*
* TAD de carregador.
* O carregador é um contenier de formas.
* O carregador pode ser carregado com formas, ele as armazena em formato de pilha, primeiro a entrar sera o ultimo a sair.
* O carregador é acoplado a um disparador, 1 disparador contem 2 carregadores, um na esquerda e um na direita.
* O carregador é carregado com formas provenientes do chão.
* Este arquivo contem todas as funções responsaveis pela manipulação dos carregadores.
*/

typedef struct carregador* Carregador;


/*==========================*/
/* Constructor do Carregador */
/*==========================*/
/**
 * @brief Cria e aloca um novo TAD Carregador com um ID e uma Pilha interna.
 * @param id O identificador unico do carregador (e.g., 1 ou 2).
 * @return Carregador O carregador criado, ou NULL em caso de erro.
 */
Carregador carregador_cria(int id);


/*==========================*/
/* Destructor do Carregador */
/*==========================*/
/**
 * @brief Libera a memória alocada para o carregador e para as Formas dentro dele.
 * @param c O carregador a ser destruído.
 */
void carregador_destroi(Carregador c);


/*==========================*/
/* Operações do Carregador  */
/*==========================*/
/**
 * @brief Adiciona (empilha) uma Forma no topo do carregador.
 * @param c O carregador onde a forma será colocada.
 * @param f A Forma a ser carregada.
 */
void carregador_carregaForma(Carregador c, Forma f);

/**
 * @brief Carrega N formas do TAD Chao para a Pilha do carregador.
 * As formas são retiradas do Chao na ordem FIFO e empilhadas, de forma que a 
 * primeira forma retirada do Chao fique na base da Pilha do carregador.
 * @param c O carregador onde as formas serão colocadas.
 * @param ch O TAD Chao de onde as formas serão retiradas.
 * @param n O número de formas a serem retiradas do Chao.
 */
void carregador_carregaNFormas(Carregador c, Chao ch, int n);

/**
 * @brief Remove (desempilha) e retorna a Forma que está no topo do carregador.
 * @param c O carregador de onde a forma será retirada.
 * @return Forma A forma do topo, ou NULL se o carregador estiver vazio ou for inválido.
 */
Forma carregador_descarregaForma(Carregador c);


/*==========================*/
/* Getters do Carregador   */
/*==========================*/
/**
 * @brief Retorna o ID do carregador.
 * @param c O carregador.
 * @return int O ID do carregador, ou -1 em caso de erro.
 */
int carregador_getId(Carregador c);

/**
 * @brief Verifica se o carregador está vazio.
 * @param c O carregador a ser verificado.
 * @return int 1 se estiver vazio, 0 se contiver formas, ou 1 em caso de erro.
 */
int carregador_estaVazio(Carregador c);

#endif