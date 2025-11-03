#ifndef FORMAS_H
#define FORMAS_H

#include "estilo.h" // Necessario para a criação e manipulação de textos.

#include <stdio.h>

/*
* TAD de formas geometricas básicas, como circulo e retangulo,
* Alem da linha, e do texto, tratados como formas também.
* As formas são utilizadas como aspecto principal no jogo da bocha.
* Com elas poderemos checar sobreposição entre uma e outra, a partir de suas coordenadas.
* Com isso teremos o calculo de pontuação total do jogo.
*
* Este arquivo contém funções básicas para manipulação dessas formas e do estilo dos textos.
*/


typedef void* Forma;



/*==========================*/
/*  Constructors das formas */
/*==========================*/
/**
 * @brief Cria um novo Círculo.
 * @param i Identificador do círculo.
 * @param x Coordenada X do centro.
 * @param y Coordenada Y do centro.
 * @param r Raio do círculo.
 * @param corb Cor da borda.
 * @param corp Cor do preenchimento .
 * @return Forma O ponteiro para a nova forma (Círculo) ou NULL em caso de erro.
 */
Forma circulo_cria(int i, double x, double y, double r, char *corb, char *corp);

/**
 * @brief Cria um novo Retângulo.
 * @param i Identificador do retângulo.
 * @param x Coordenada X da âncora (canto inferior esquerdo).
 * @param y Coordenada Y da âncora (canto inferior esquerdo).
 * @param w Largura do retângulo.
 * @param h Altura do retângulo.
 * @param corb Cor da borda.
 * @param corp Cor do preenchimento.
 * @return Forma O ponteiro para a nova forma (Retângulo) ou NULL em caso de erro.
 */
Forma retangulo_cria(int i, double x, double y, double w, double h, char *corb, char *corp);

/**
 * @brief Cria uma nova linha.
 * @param i Identificador da linha.
 * @param x1 Coordenada x do inicio da linha.
 * @param y1 Coordenada y do inicio da linha.
 * @param x2 Coordenada x do fim da linha.
 * @param y2 Coordenada y do fim da linha.
 * @param cor Cor da linha
 * @return Forma O ponteiro para a nova forma (Linha) ou NULL em caso de erro.
 */
Forma linha_cria(int i, double x1, double y1, double x2, double y2, char *cor);

/**
 * @brief Cria um novo texto.
 * @param i Identificdor do texto.
 * @param x Coordenada x da âncora do texto.
 * @param y Coordenada y da âncora do texto.
 * @param corb Cor da borda.
 * @param corp Cord do preenchimento.
 * @param a Posição da âncora (i: inicio, m: meio, f: fim)
 * @param txto Texto do texto, pode incluir espaços em branco.
 * @param e Estilo do texto, familia grossura e tamanho da fonte.
 * @return Forma O ponteiro para a nova forma (Texto) ou NULL em caso de erro.
 */
Forma texto_cria(int i, double x, double y, char* corb, char *corp, char a, char *txto, Estilo e);



/*==========================*/
/*  Destructor das formas   */
/*==========================*/
/**
 * @brief Libera a memória alocada para uma forma.
 * @param f A forma a ser destruída.
 */
void forma_destruir(Forma f);



/*====================*/
/* Getters das formas */
/*====================*/
/**
 * @brief Retorna o identificador único da forma.
 * @param f A forma.
 * @return int O identificador, ou -1 em caso de erro.
 */
int forma_getId(Forma f);


/**
 * @brief Calcula e retorna a área da forma.
 * @param f A forma.
 * @return double A área calculada, ou -1 em caso de erro.
 */
double forma_getArea(Forma f);

/**
 * @brief Mostra qual a cor de preenchimento atual de uma forma.
 * @param f A forma.
 * @return char* A cor de preenchimento dessa forma, ou NULL em caso de erro.
 */
char* forma_getCorPreenchimento(Forma f);

/**
 * @brief Mostra qual a cor de borda atual de uma forma.
 * @param f a forma.
 * @return char* A cor de borda dessa forma, ou NULL em caso de erro.
 */
char* forma_getCorBorda(Forma f);

/**
 * @brief Pega a coordenada x da ancora de uma forma f.
 */
double forma_getX(Forma f);

/**
 * @brief Pega a coordenada Y da ancora de uma forma f.
 */
double forma_getY(Forma f);



/*==================================*/
/*  Setters e operações das formas  */
/*==================================*/
/**
 * @brief Modifica a cor da borda de uma forma.
 * @param f A forma a ser modificada.
 * @param novaCorBorda A nova cor da borda (cor de preenchimento de I).
 */
void forma_setCorBorda(Forma f, char *novaCorBorda);

/**
 * @brief Muda as coordenadas X de uma forma.
 * @param f A Forma a ser alterada.
 * @param novoX As novas coordenadas X da forma.
 */
void forma_setX(Forma f, double novoX);

/**
 * @brief Muda as coordenadas Y de uma forma.
 * @param f A Forma a ser alterada.
 * @param novoX As novas coordenadas Y da forma.
 */
void forma_setY(Forma f, double novoY);

/**
 * @brief Cria e retorna um clone da forma, invertendo as cores de borda e preenchimento.
 * @param original A forma original a ser clonada.
 * @return Forma O ponteiro para a nova forma clonada, ou NULL em caso de erro.
 */
Forma forma_clonar(Forma original);

/**
 * @brief Verifica se duas formas se sobrepõem (intersectam).
 * @param f1 Primeira forma.
 * @param f2 Segunda forma.
 * @return int 1 se houver sobreposição, 0 caso contrário.
 */
int verificaSobreposicao(Forma f1, Forma f2);

/*=========================*/
/* Função de Desenho em SVG*/
/*=========================*/
/**
 * @brief Desenha uma forma em um arquivo SVG.
 * @param f A forma a ser desenhada.
 * @param svg_file O ponteiro do arquivo SVG onde desenhar.
 */
void forma_desenhaSvg(Forma f, FILE* svg_file);

#endif