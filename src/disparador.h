#ifndef DISPARADOR_H
#define DISPARADOR_H

#include "carregador.h"
#include "arena.h"
#include "formas.h"
#include "fila.h"

#include <stdio.h>

/*
* TAD de Disparador.
* O disparador é a unidade central do jogo, responsável por manipular formas, disparando-as na Arena.
* Ele possui um ID, coordenadas (x, y), dois carregadores (esquerdo e direito) e 
* uma posição temporária para a forma pronta para disparo.
*/

typedef struct disparador* Disparador;


/*===========================*/
/* Constructor do Disparador */
/*===========================*/
/**
 * @brief Cria e aloca um novo Disparador.
 * @param id O identificador unico do disparador.
 * @param x Coordenada X na arena.
 * @param y Coordenada Y na arena.
 * @return Disparador O disparador criado, ou NULL em caso de erro.
 */
Disparador disparador_cria(int id, double x, double y);


/*===========================*/
/* Destructor do Disparador  */
/*===========================*/
/**
 * @brief Libera a memória alocada para o disparador, seus carregadores e a forma em disparo.
 * @param d O disparador a ser destruído.
 */
void disparador_destroi(Disparador d);


/*=============================*/
/* Operações de Carregamento   */
/*=============================*/

/**
 * @brief Engatilha uma forma na posição de disparo, movendo a forma atual (se existir) 
 * para o carregador oposto, e repetindo a operação 'n' vezes.
 * * Se lado == 'e':
 * 1. Forma em disparo vai para o topo do carregador esquerdo.
 * 2. Forma do topo do carregador direito vai para a posição de disparo.
 * * Se lado == 'd':
 * 1. Forma em disparo vai para o topo do carregador direito.
 * 2. Forma do topo do carregador esquerdo vai para a posição de disparo.
 * @param d O disparador.
 * @param lado Indica qual carregador a forma em posição de disparo vai, ('e' para esquerdo, 'd' para direito).
 * @param n O número de vezes que a operação de seleção/troca deve ser repetida.
 * @return Forma, Um ponteiro para a forma que ficou na posição de disparo, ou NULL caso o botão tenha sido apertado vezes o suficiente
 * para acabar com o tanto de formas do carregador oposto ao do parametro 'lado'.
 */
Forma disparador_shift(Disparador d, char lado, int n);

/**
 * @brief Encaixa dois carregadores mo Disparadr desejado.
 * @param d O disparador que em que os carregadores vao ser encaixados.
 * @param ce O carregador que vai ser encaixado na esquerda.
 * @param cd O carregador que vai ser encaixado na direita.
 */
void disparador_attach(Disparador d, Carregador ce, Carregador cd);

/*=============================*/
/* Operação de Disparo         */
/*=============================*/

/**
 * @brief Dispara a forma em posição de disparo para a Arena.
 * A forma recebe as coordenadas (x, y) do disparador antes de ser enviada para a Arena.
 * @param dx O quao longe a forma será disparada em relação ao eixo x, a posição final da forma no eixo x sera: dx + posição x do disparador.
 * @param dy O quao longe a forma será disparada em relação ao eixo y, a posição final da forma no eixo y sera: dy + posição y do disparador.
 * @param d O disparador.
 * @param a A Arena de destino.
 * @param svg_file Ponteiro para o arquivo svg onde a trajetoria seja desenhada, caso necessario.
 * @param desenha_trajetoria Consiste em basicamente um 'bool', por padrão vale 0, mas caso leia um 'v' no final do comando de dsp no qry, vale 1, e desenha a trajetoria de disparo da forma.
 * @return Retorna um ponteiro para a forma disparada.
 */
Forma disparador_dispara(Disparador d, double dx, double dy, Arena a, FILE* svg_file, int desenha_trajetoria);

/**
 * @brief Equivale a uma sequencia de disparo de maneira:
 * 1. disparador_shift(d, lado([e/d]), 1) 
 * 2. disparador_dispara(d, (dx + (ix * i)), (dy + (iy * i), a)
 * 3. voltar ao passo 1 se o carregador ainda tiver formas.
 * i == numero do disparo, i = 1 se for o primeiro disparo, i = 2 se for o segundo, etc.
 * Exemplo de rajada disparador_rajada(d1, e, 40.5, 50.7, 10, 15, arena):
 * o disparador "d1" tem coordenadas(x: 100. y: 30), e 2 formas no carregador da direita, e nenhuma em posição de disparo.
 * 1. Ele pega a forma no topo do carregador direito e coloca na posição de disparo.
 * 2. Ele faz o disparo 1, a forma para no eixo x em: 
 * (100 + 40.5 + (10 * 1)) == 150.5 => 
 * 100 = x de d1. 40.5 é o dx (tanto que d1 empurra a forma). 10 = ix, tanto a mais que o disparador empurra por tiro na rajada. 1 = numero do tiro.
 * e no eixo y em: (30 + 50.7 + (15 * 1)) == 95.7.
 * 3. Ele pega outra forma do topo do carregador direito e coloca na posição de disparo.
 * 4. Ele faz o disparo 2, e a forma vai parar em:
 * x: (100 + 40.5 + (10 * 2)) == 160.5.
 * y: (30 + 50.7 + (15 * 2)) == 110.7.
 * 5. Ele ve que acaba as formas no carregador direito e acaba a rajada.
 * @param d O disparador qual sera usado nos disparos.
 * @param lado o lado oposto de onde as formas virão, ja que a rajada usa disparador_shift para colocar as formas em posição de disparo.
 * @param dx O valor no eixo x que o disparador vai "empurrar" a forma.
 * @param dy O valor no eixo y que o disparador vai "empurrar" a forma.
 * @param ix o fator multiplicativo x por disparo na rajada.
 * @param iy o fator multiplicativo y por disparo na rajada.
 * @param a A arena de destino.
 * @return Fila, uma fila com as formas disparadas.
 */
Fila disparador_rajada(Disparador d, char lado, double dx, double dy, double ix, double iy, Arena a);




/*=============================*/
/* Getters/Setters Auxiliares  */
/*=============================*/

/**
 * @brief Retorna o ID do Disparador.
 */
int disparador_getId(Disparador d);

/**
 * @brief Retorna a coordenada X do Disparador.
 */
double disparador_getX(Disparador d);

/**
 * @brief Retorna a coordenada Y do Disparador.
 */
double disparador_getY(Disparador d);

/**
 * @brief Retorna o Carregador esquerdo do Disparador.
 */
Carregador disparador_getCarregadorEsquerdo(Disparador d);

/**
 * @brief Retorna o Carregador direito do Disparador.
 */
Carregador disparador_getCarregadorDireito(Disparador d);

/**
 * @brief Retorna a Forma atualmente em posição de disparo.
 */
Forma disparador_getFormaEmDisparo(Disparador d);

#endif