#ifndef PROCESSAQRY_H
#define PROCESSAQRY_H

#include <stdio.h>  
#include <stdlib.h>
#include "chao.h"
#include "arena.h"

/*
* Módulo de Processamento de Consultas (.qry).
*
* Este módulo é responsável por ler o arquivo de consultas (.qry),
* interpretar os comandos e chamar as funções apropriadas dos
* TADs (Disparador, Carregador, Arena, Chao) para executar as
* ações do jogo "Bocha Geométrica".
*
* Ele também gerencia a criação dos arquivos de saída SVG
* em momentos específicos (comandos 'dsp' e 'calc').
*/

/**
 * @brief Processa um arquivo de consultas .qry.
 * @param path_qry O caminho para o arquivo .qry.
 * @param path_svg_pos_calc O caminho onde o SVG Pós-Calc deve ser salvo.
 * @param chao O TAD Chao, já preenchido com as formas do .geo.
 * @param arena O TAD Arena, inicialmente vazio.
 * @param log_txt O ponteiro para o arquivo .txt de log.
 */
void processaQry(const char *path_qry, const char *path_svg_pos_calc, Chao chao, Arena arena, FILE* log_txt);

#endif