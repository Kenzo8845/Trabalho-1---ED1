#ifndef FORMAS_H
#define FORMAS_H

#include <stdio.h>

/*
* TAD de formas geometricas básicas, como triângulo, circulo e retangulo,
* Alem da linha, e do texto, tratados como formas também.
* Este arquivo contém funções básicas para manipulação dessas formas.
*/


typedef void* Forma;

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
Forma criarCirculo(int i, double x, double y, double r, char *corb, char *corp);

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
Forma criarRetangulo(int i, double x, double y, double w, double h, char *corb, char *corp);

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
Forma criarLinha(int i, double x1, double y1, double x2, double y2, char *cor);

/**
 * @brief Cria um novo texto.
 * @param i Identificdor do texto.
 * @param x Coordenada x da âncora do texto.
 * @param y Coordenada y da âncora do texto.
 * @param corb Cor da borda.
 * @param corp Cord do preenchimento.
 * @param a Posição da âncora (i: inicio, m: meio, f: fim)
 * @param txto Texto do texto, pode incluir espaços em branco.
 * @return Forma O ponteiro para a nova forma (Texto) ou NULL em caso de erro.
 */
Forma criarTexto(int i, double x, double y, char* corb, char *corp, char a, char *txto);

/**
 * @brief Libera a memória alocada para uma forma.
 * @param f A forma a ser destruída.
 */
void destruirForma(Forma f);

/**
 * @brief Retorna o identificador único da forma.
 * @param f A forma.
 * @return int O identificador
 */
int getFormaId(Forma f);

/**
 * @brief Calcula e retorna a área da forma.
 * @param f A forma.
 * @return double A área calculada.
 */
double getFormaArea(Forma f);

/**
 * @brief Cria e retorna um clone da forma, trocando as cores de borda e preenchimento.
 * Normalmente utilizado quando uma forma é esmagada.
 * @param original A forma original a ser clonada.
 * @param novoId O novo identificador único a ser atribuído ao clone.
 * @return Forma O ponteiro para a nova forma clonada.
 */
Forma clonarForma(Forma original, int novoId);

/**
 * @brief Modifica a cor da borda de uma forma.
 * @param f A forma a ser modificada.
 * @param novaCorBorda A nova cor da borda (cor de preenchimento de I).
 */
void setFormaCorBorda(Forma f, char *novaCorBorda);

/**
 * @brief Verifica se duas formas se sobrepõem (intersectam).
 * @param f1 Primeira forma.
 * @param f2 Segunda forma.
 * @return int 1 se houver sobreposição, 0 caso contrário.
 */
int verificaSobreposicao(Forma f1, Forma f2);

/**
 * @brief Escreve a representação SVG da forma em um arquivo.
 * * @param f A forma.
 * @param svgFile O ponteiro para o arquivo SVG aberto.
 */
void escreverFormaSVG(Forma f, void *svgFile);


#endif