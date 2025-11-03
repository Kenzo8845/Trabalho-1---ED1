#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "chao.h"
#include "arena.h"
#include "processaGeo.h"
#include "processaQry.h"

/*
* Função auxiliar para extrair o nome base de um path.
* Ex: "entrada/t1.geo" -> "t1"
*/
void get_nome_base(const char* path_completo, char* nome_saida) {
    const char* barra = strrchr(path_completo, '/');
    if (barra) {
        strcpy(nome_saida, barra + 1);
    } else {
        strcpy(nome_saida, path_completo);
    }
    
    char* ponto = strrchr(nome_saida, '.');
    if (ponto) {
        *ponto = '\0';
    }
}

/*
* Função auxiliar para juntar diretório e nome de arquivo.
* Ex: ("saida", "t1.svg") -> "saida/t1.svg"
*/
void build_path(const char* dir, const char* nome_arq, char* path_final) {
    sprintf(path_final, "%s/%s", dir, nome_arq);
}


int main(int argc, char *argv[]) {

    char* path_entrada = NULL;
    char* path_geo_nome = NULL;
    char* path_saida = NULL;
    char* path_qry_nome = NULL;

    // Leitura do argumentos.
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) {
            path_geo_nome = argv[++i];
        } else if (strcmp(argv[i], "-q") == 0 && i + 1 < argc) {
            path_qry_nome = argv[++i];
        } else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            path_saida = argv[++i];
        } else if (strcmp(argv[i], "-e") == 0 && i + 1 < argc) {
            path_entrada = argv[++i];
        }
    }

    // Validação
    if (path_geo_nome == NULL || path_saida == NULL) {
        printf("Erro: Argumentos obrigatorios -f e -o nao fornecidos.\n");
        printf("Uso: ./programa -f <arq.geo> -o <dir_saida> [-q <arq.qry>] [-e <dir_entrada>]\n");
        return 1;
    }

    // Montagem dos paths de entrada.
    char path_geo_completo[1024];
    char path_qry_completo[1024];
    
    if (path_entrada) {
        build_path(path_entrada, path_geo_nome, path_geo_completo);
        if (path_qry_nome) {
            build_path(path_entrada, path_qry_nome, path_qry_completo);
        }
    } else {
        strcpy(path_geo_completo, path_geo_nome);
        if (path_qry_nome) {
            strcpy(path_qry_completo, path_qry_nome);
        }
    }

    // Extrai nomes base
    char nome_base_geo[256];
    char nome_base_qry[256];
    get_nome_base(path_geo_nome, nome_base_geo);
    if (path_qry_nome) {
        get_nome_base(path_qry_nome, nome_base_qry);
    }
    
    // Montagem dos paths de saida.
    char path_svg_geo[1024];
    char path_svg_qry[1024];
    char path_log_txt[1024];

    sprintf(path_svg_geo, "%s/%s.svg", path_saida, nome_base_geo);
    
    if (path_qry_nome) {
        sprintf(path_svg_qry, "%s/%s-%s.svg", path_saida, nome_base_geo, nome_base_qry);
        sprintf(path_log_txt, "%s/%s-%s.txt", path_saida, nome_base_geo, nome_base_qry);
    }

    printf("=== BOCHA GEOMETRICA ===\n");
    printf("Arquivo GEO: %s\n", path_geo_completo);
    printf("SVG de saida (GEO): %s\n", path_svg_geo);
    if (path_qry_nome) {
        printf("Arquivo QRY: %s\n", path_qry_completo);
        printf("SVG de saida (QRY): %s\n", path_svg_qry);
        printf("TXT de saida: %s\n", path_log_txt);
    }
    printf("========================\n\n");

    // Processamento do geo.
    printf("Processando GEO...\n");
    Chao chao = processaGeo(path_geo_completo, path_svg_geo);
    if (chao == NULL) {
        printf("Erro fatal ao processar arquivo GEO.\n");
        return 1;
    }
    printf("GEO processado. SVG gerado em: %s\n\n", path_svg_geo);
    
    // Criação da arena.
    Arena arena = arena_cria();
    if (arena == NULL) {
        printf("Erro fatal ao criar a Arena.\n");
        chao_destruir(chao);
        return 1;
    }
    
    // Processamento do QRY.
    if (path_qry_nome) {
        printf("Processando QRY: %s\n", path_qry_completo);
        
        FILE* log_txt = fopen(path_log_txt, "w");
        if (log_txt == NULL) {
            printf("Erro: Nao foi possivel criar o arquivo de LOG: %s\n", path_log_txt);
            chao_destruir(chao);
            arena_destroi(arena);
            return 1;
        }

        fprintf(log_txt, "=== LOG DO PROCESSAMENTO QRY ===\n");
        fprintf(log_txt, "Arquivo: %s\n\n", path_qry_completo);

        processaQry(path_qry_completo, path_svg_qry, chao, arena, log_txt);

        fclose(log_txt);
        printf("Log gerado em: %s\n", path_log_txt);
    }

    // Limpeza de memoria
    printf("\nExecucao concluida. Limpando memoria...\n");
    arena_destroi(arena);
    chao_destruir(chao);
    
    printf("Programa finalizado com sucesso!\n");
    return 0;
}