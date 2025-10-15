#ifndef FILA_H
#define FILA_H

/*
*TAD de fila generica, com a logica de primeiro a entrar sera o primeiro a sair.
*Este arquivo contem as funções básicas para manipulação das filas.
*/

#include <stdbool.h>

/*
* Declaração opaca da fila.
*/
typedef struct fila* Fila;

/*
* Cria uma fila vazia.
* Retorna: um ponteiro para a fila criada.
*/
Fila fila_cria();

/*
* Enfilera um elemento no final da fila.
* Parametros:
* - f: uma fila ja existente 
* - e: um elemento que sera alocado no fim.
*/
void fila_adicionaAoFim(Fila f, void* e);

/*
* Retira um elemento do inicio da fila.
* Parametros: uma fila 'f' na qual se quer retirar o elemento.
* Retorna: um ponteiro para o elemento retirado, ou NULL, caso a fila esteja vazia.
*/
void* fila_retiraDoInicio(Fila f);

/*
* Mostra o numero de elementos da fila.
* Parametros: a fila 'f' qual sera retornado o tamanho.
* Retorna: o tamanho da fila.
*/
int fila_tamanho(Fila f);

/*
* Verifica se a fila esta vazia.
* Parametros: a fila a ser verificada.
* Retorna:  
* True: caso ela esteja vazia.
* False: caso haja qualquer elemento nela.
*/
bool fila_vazia(Fila f);

/*
* Libera toda a memória usada pela fila.
* Parametros: a fila 'f' a ser destruida.
* IMPORTANTE: não libera a memória dos elementos apontados.
*/
void fila_destruir(Fila f);



#endif