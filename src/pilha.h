#ifndef PILHA_H
#define PILHA_H

/*
*TAD de pilha generica, com a logica de ultimo a entrar na pilha sera o primeiro a sair.
*Este arquivo contem as funções básicas para manipulação das pilhas.
*/

#include <stdbool.h>

/*
* Declaração opaca da pilha.
*/
typedef struct pilha* Pilha;

/*
* Cria uma pilha vazia.
* Retorna: um ponteiro para a pilha criada.
*/
Pilha pilha_cria();

/*
* Empilha um elemento no topo da pilha.
* Parametros:
* - p: uma pilha ja existente 
* - e: um elemento que sera alocado no topo.
*/
void pilha_adicionaAoTopo(Pilha p, void* e);

/*
* Retira o elemento do topo da pilha.
* Parametros: a pilha em qual vai ser retirado o elemento.
* Retorna:
* - Um ponteiro para o elemento retirado, ou NULL, caso a pilha esteja vazia.
*/
void* pilha_retiraDoTopo(Pilha p);

/*
* Mostra o numero de elementos da pilha.
* Parametros: a pilha qual sera retornado o tamanho.
* Retorna: o tamanho da pilha.
*/
int pilha_tamanho(Pilha p);

/*
* Verifica se a pilha esta vazia.
* Parametros: a pilha a ser verificada.
* Retorna:  
* True: caso ela esteja vazia.
* False: caso haja qualquer elemento nela.
*/
bool pilha_vazia(Pilha p);

/*
* Libera toda a memória usada pela pilha.
* Parametros: a pilha 'p' a ser destruida.
* IMPORTANTE: não libera a memória dos elementos apontados.
*/
void pilha_destruir(Pilha p);


#endif
