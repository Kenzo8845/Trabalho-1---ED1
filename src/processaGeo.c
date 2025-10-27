#include "chao.h"
#include "processaGeo.h"
#include "fila.h" 
#include "formas.h" 
#include "estilo.h" 
#include "svg.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Chao processaGeo(const char *path_geo, const char *path_svg_geo) {
    FILE *arquivo_geo = fopen(path_geo, "r");
    if (arquivo_geo == NULL) {
        printf("erro ao abrir arquivo geo\n");
        return NULL;
    }

    FILE *svg_file = svg_inicia(path_svg_geo);
    if (svg_file == NULL) {
        printf("Erro: Nao foi possivel criar o SVG 1 (geo) em %s\n", path_svg_geo);
    }


    Fila formas_chao = fila_cria();
    if (formas_chao == NULL) {
        fclose(arquivo_geo);
        if (svg_file) svg_finaliza(svg_file);
        return NULL;
    }

    Chao chao = chao_cria(formas_chao);
    if (chao == NULL) {
        fclose(arquivo_geo);
        if (svg_file) svg_finaliza(svg_file);
        return NULL;
    }

    char buffer[256];
    char comando[16];

    char fFamily[32] = "sans";
    char fWeight[8] = "n";
    double fSize = 10;


    while (fgets(buffer, sizeof(buffer), arquivo_geo) != NULL) {
        if (buffer[0] == '\n' || buffer[0] == '#') {
            continue;
        }

        comando[0] = '\0';
        sscanf(buffer, "%s", comando);

        if (strcmp(comando, "c") == 0) {
            int id; 
            double x, y, r; 
            char corb[32] = "", corp[32] = "";
            int n_lidos = sscanf(buffer, "c %i %lf %lf %lf %s %s", &id, &x, &y, &r, corb, corp);

            if (n_lidos < 4) continue;

            Forma f = circulo_cria(id, x, y, r, corb, corp);

            if (f && svg_file) {
                forma_desenhaSvg(f, svg_file);
            }

            chao_adicionaAoChao(chao, f);
        }

        else if (strcmp(comando, "r") == 0) {
            int id;
            double x, y, w, h;
            char corb[32] = "", corp[32] = "";
            int n_lidos = sscanf(buffer, "r %i %lf %lf %lf %lf %s %s", &id, &x, &y, &w, &h, corb, corp);

            if (n_lidos < 5) continue;

            Forma f = retangulo_cria(id, x, y, w, h, corb, corp);

            if (f && svg_file) {
                forma_desenhaSvg(f, svg_file);
            }

            chao_adicionaAoChao(chao, f);
        }

        else if (strcmp(comando, "l") == 0) {
            int id; double x1, y1, x2, y2; char cor[64] = "";
            int n_lidos = sscanf(buffer, "l %i %lf %lf %lf %lf %s", &id, &x1, &y1, &x2, &y2, cor);

            if (n_lidos < 5) continue;

            Forma f = linha_cria(id, x1, y1, x2, y2, cor);

            if (f && svg_file) {
                forma_desenhaSvg(f, svg_file);
            }

            chao_adicionaAoChao(chao, f);
        }

        else if (strcmp(comando, "t") == 0) {
            int id;
            double x, y;
            char corp[32] = "", corb[32] = "";
            char a = 'i';
            char txto[128] = "";
            int offset = 0;

            sscanf(buffer, "t %i %lf %lf %s %s %c %n", &id, &x, &y, corb, corp, &a, &offset);

            if (offset > 0) {
                const char *inicio_texto = buffer + offset;
                while (*inicio_texto && (*inicio_texto == ' ' || *inicio_texto == '\t')) {
                    inicio_texto++;
                }
                strncpy(txto, inicio_texto, sizeof(txto) - 1);
                txto[sizeof(txto) - 1] = '\0';
                txto[strcspn(txto, "\r\n")] = 0;
            }


            Estilo estilo_temp = estilo_cria(fFamily, fWeight, fSize);
            
            Forma f = texto_cria(id, x, y, corb, corp, a, txto, estilo_temp);

            estilo_destroi(estilo_temp);

            if (f && svg_file) {
                forma_desenhaSvg(f, svg_file);

                chao_adicionaAoChao(chao, f);
            }
        }

        else if (strcmp(comando, "ts") == 0) {
            char family[32], weight[8];
            double size;
            int n_lidos = sscanf(buffer, "ts %s %s %lf", family, weight, &size);

            if (n_lidos == 3) {
                strcpy(fFamily, family);
                strcpy(fWeight, weight);
                fSize = size;
            }
        }
    }

        if (svg_file) {
        svg_finaliza(svg_file);
        }

        
        fclose(arquivo_geo);
        return chao;
}