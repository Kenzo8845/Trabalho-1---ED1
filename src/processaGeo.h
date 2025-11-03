#ifndef PROCESSAGEO_H
#define PROCESSAGEO_H

#include "chao.h"
#include "disparador.h"
#include "fila.h"
#include "svg.h"

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Abre o arquivo .geo em formato de leitura.
 * Cria as formas e vai adicionando-as na ordem de leitura ao chão.
 * @param geo_path Nome do arquivo .geo.
 * @param path_svg_geo Nome do arquivo svg com as formas no chão depois do processamento do arquivo geo.
 * @return Chao O TAD Chao preenchido com as formas, ou NULL em caso de erro.
 */
Chao processaGeo(const char* geo_path, const char *path_svg_geo);

#endif