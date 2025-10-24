#ifndef ARENA_H
#define ARENA_H

#include "fila.h"
#include "formas.h"
#include <stdio.h>
#include <stdlib.h>

/*
* TAD de Arena.
* A arena é um tipo de fila, com lógica de primeira entrar sera o primerio a sair.
* Todos os elementos armazenados na Arena serão formas, e o numero maximo de formas na arena é 3. Para calculos de sobreposição.
* A arena é o local onde as formas disparadas vão parar, e apos 2 formas estarem na arena,
* é calculado sobreposição, talvez a forma lançada primeiro é clonada,
* e adicionada ao fim da arena, e as formas são então, retiradas da arena.
*
* Quando a arena é usada:
* Quando um disparador dispara, a forma vai parar na arena.
*
* Este arquivo contem todas as funções responsaveis pela manipulação da arena.
*/

typedef struct arena* Arena;



/*======================*/
/* Constructor da Arena */
/*======================*/
/**
 * @brief Cria uma nova Arena.
 * @return Arena, a arena criada, ou NULL, em caso de erro.
 */
Arena arena_cria();



/*=====================*/
/* Destructor da Arena */
/*=====================*/
/**
 * @brief libera a memoria da arena, e das formas dentro dela.
 * @param a A arena a ser destruida.
 */
void arena_destroi(Arena a);



/*=====================*/
/*  Getters da Arena   */
/*=====================*/
/**
 * @brief Retorna o numero de formas presentes na Arena.
 * @param a A arena onde se quer saber o numero de formas.
 * @return int o numero de formas.
 */
int arena_getNumeroDeFormas(Arena a);

/**
 * @brief Retorna a Fila da arena selecionada.
 * @param c A arena qual se quer a fila.
 * @return Fila A fila da arena selecionada, ou NULL, em caso de erro.
 */
Fila arena_getFila(Arena a);



/*=====================*/
/* Operações da Arena  */
/*=====================*/
/**
 * @brief Adiciona uma forma ao fim da Arena.
 * @param a A arena onde a forma será adicionada.
 * @param f A forma a ser adicionada a Arena.
 */
void arena_adicionaForma(Arena a, Forma f);

/**
 * @brief Remove uma forma do inicio da arena.
 * @param a A arena onde a forma sera removida. 
 * @return Forma um ponteiro para a forma retirada.
 */
Forma arena_removeForma(Arena a);

#endif