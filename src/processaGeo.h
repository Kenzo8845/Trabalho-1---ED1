#ifndef PROCESSAGEO_H
#define PROCESSAGEO_H

#include "chao.h"
#include "disparador.h"
#include "fila.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Abre o arquivo .geo em formato de leitura.
 * Cria as formas e vai adicionando-as na ordem de leitura ao chão.
 * @param geo_path Nome do arquivo .geo.
 * @return Chao O TAD Chao preenchido com as formas, ou NULL em caso de erro.
 */
Chao processa_geo(const char* geo_path);

#endif