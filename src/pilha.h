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
* Parametrtos:
* - p: uma pilha ja existente 
* - e: um elemento que sera olocado no topo.
*/

void pilha_adicionaAoTopo(Pilha p, void* e);

/*
* Retira o elemento do topo da pilha.
* Paramentros: a pilha em qual vai ser retirado o elemento.
* Retorna:
* - Um ponteiro para o elemento retirado,ou NULL, caso a pilha esteja vazia.
*/

void* pilha_retiraDoTopo(Pilha p);

/*
* Mostra o numero de elementos da pilha.
* Parametros: a pilha qual sera retornado o tamanho.
* Retorna: o tamanho da pilha.
*/

int pilha_tamanho(Pilha p);

/*
* Libera toda a memória usada pela pilha.
* IMPORTANTE: não libera a memória dos elementos apontados.
*/
void pilha_destruir(Pilha p);


#endif
