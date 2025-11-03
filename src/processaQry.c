#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "processaQry.h"
#include "fila.h"       
#include "pilha.h"
#include "chao.h"
#include "arena.h"
#include "carregador.h"
#include "disparador.h"
#include "formas.h"
#include "svg.h"

/* ================================================================== */
/* FUNÇÕES AUXILIARES                                                  */
/* ================================================================== */

static Disparador buscar_disparador(Fila lista_disparadores, int id) {
    if (lista_disparadores == NULL || fila_vazia(lista_disparadores)) return NULL;
    int n = fila_tamanho(lista_disparadores);
    Disparador d = NULL, encontrado = NULL;
    for (int i = 0; i < n; i++) {
        d = (Disparador) fila_retiraDoInicio(lista_disparadores);
        if (d == NULL) continue;
        
        if (disparador_getId(d) == id) {
            encontrado = d;
        }
        fila_adicionaAoFim(lista_disparadores, d); 
    }
    return encontrado;
}

// ✅ Nova função: busca E REMOVE da lista
static Carregador buscar_e_remover_carregador(Fila lista_carregadores, int id) {
    if (lista_carregadores == NULL || fila_vazia(lista_carregadores)) return NULL;
    
    int n = fila_tamanho(lista_carregadores);
    Carregador encontrado = NULL;
    
    for (int i = 0; i < n; i++) {
        Carregador c = (Carregador) fila_retiraDoInicio(lista_carregadores);
        if (c == NULL) continue;
        
        if (carregador_getId(c) == id) {
            encontrado = c;
            // NÃO adiciona de volta - remove da lista!
        } else {
            fila_adicionaAoFim(lista_carregadores, c);
        }
    }
    
    return encontrado;
}

/* ================================================================== */
/* FUNÇÃO PRINCIPAL (processaQry)                                     */
/* ================================================================== */

void processaQry(const char *path_qry, const char *path_svg_pos_calc, Chao chao, Arena arena, FILE* log_txt) {
    
    FILE *arquivo_qry = fopen(path_qry, "r");
    if (arquivo_qry == NULL) { 
        printf("Erro: Nao foi possivel abrir o arquivo QRY: %s\n", path_qry);
        return; 
    }

    FILE* svg_file = svg_inicia(path_svg_pos_calc);
    if (svg_file == NULL) {
        printf("Erro: Nao foi possivel criar o SVG final em %s\n", path_svg_pos_calc);
        // Mesmo com erro, tentamos continuar sem o SVG
    }

    Fila lista_disparadores = fila_cria();
    Fila lista_carregadores = fila_cria();

    char buffer[256], comando[16];
    double area_total_esmagada = 0.0;
    int num_disparos = 0;
    int num_instrucoes = 0;

    fprintf(log_txt, "Iniciando processamento do QRY...\n\n");

    while (fgets(buffer, sizeof(buffer), arquivo_qry) != NULL) {
        if (buffer[0] == '\n' || buffer[0] == '#') continue;
        
        comando[0] = '\0';
        sscanf(buffer, "%s", comando);
        num_instrucoes++;

        fprintf(log_txt, "[%d] %s", num_instrucoes, buffer);

        /* ========== COMANDO: pd ========== */
        if (strcmp(comando, "pd") == 0) {
            int id; 
            double x, y;
            sscanf(buffer, "pd %d %lf %lf", &id, &x, &y);
            
            Disparador d = disparador_cria(id, x, y); 
            if (d) {
                fila_adicionaAoFim(lista_disparadores, d);
                fprintf(log_txt, "  -> Disparador %d criado em (%.2lf, %.2lf)\n", id, x, y);
            }
        } 
        
        /* ========== COMANDO: lc ========== */
        else if (strcmp(comando, "lc") == 0) {
            int id, n;
            sscanf(buffer, "lc %d %d", &id, &n);
            
            Carregador c = carregador_cria(id); 
            if (c) {
                carregador_carregaNFormas(c, chao, n); 
                fila_adicionaAoFim(lista_carregadores, c);
                fprintf(log_txt, "  -> Carregador %d criado e carregado\n", id);
            }
        }
        
        /* ========== COMANDO: atch ========== */
        else if (strcmp(comando, "atch") == 0) {
            int id_disp, id_carr_e, id_carr_d;
            sscanf(buffer, "atch %d %d %d", &id_disp, &id_carr_e, &id_carr_d);

            Disparador d = buscar_disparador(lista_disparadores, id_disp);
            if (d == NULL) {
                fprintf(log_txt, "  -> ERRO: Disparador %d nao encontrado!\n", id_disp);
                continue;
            }

            Carregador ce = buscar_e_remover_carregador(lista_carregadores, id_carr_e);
            Carregador cd = buscar_e_remover_carregador(lista_carregadores, id_carr_d);

            if (ce == NULL) {
                ce = carregador_cria(id_carr_e);
                fprintf(log_txt, "  -> Carregador esquerdo %d criado vazio\n", id_carr_e);
            }

            if (cd == NULL) {
                cd = carregador_cria(id_carr_d);
                fprintf(log_txt, "  -> Carregador direito %d criado vazio\n", id_carr_d);
            }

            disparador_attach(d, ce, cd);
            fprintf(log_txt, "  -> Disparador %d anexado com carregadores %d e %d\n", 
                    id_disp, id_carr_e, id_carr_d);
        }
        
        /* ========== COMANDO: shft ========== */
        else if (strcmp(comando, "shft") == 0) {
            int id_disp, n; 
            char direcao;
            sscanf(buffer, "shft %d %c %d", &id_disp, &direcao, &n);
            
            Disparador d = buscar_disparador(lista_disparadores, id_disp);
            if (d) {
                Forma forma_final = disparador_shift(d, direcao, n);
                if (forma_final) {
                    fprintf(log_txt, "  -> Forma ID=%d em posicao de disparo\n", forma_getId(forma_final));
                } else {
                    fprintf(log_txt, "  -> Nenhuma forma em posicao\n");
                }
            }
        }
        
        /* ========== COMANDO: dsp ========== */
        else if (strcmp(comando, "dsp") == 0) {
            int id_disp; 
            double dx, dy; 
            char modo = 'i';
            
            int n_lidos = sscanf(buffer, "dsp %d %lf %lf %c", &id_disp, &dx, &dy, &modo);
            if (n_lidos < 3) continue;

            Disparador d = buscar_disparador(lista_disparadores, id_disp);
            if (!d) continue;

            int desenha_trajetoria = (modo == 'v') ? 1 : 0;
            Forma forma_disparada = disparador_dispara(d, dx, dy, arena, svg_file, desenha_trajetoria);
            
            if (forma_disparada) {
                num_disparos++;
                double fx = forma_getX(forma_disparada);
                double fy = forma_getY(forma_disparada);
                fprintf(log_txt, "  -> Forma ID=%d -> (%.2lf, %.2lf). Arena=%d formas %s\n", forma_getId(forma_disparada), fx, fy, 
                    arena_getNumeroDeFormas(arena), (modo == 'v' ? " [trajetoria desenhada]" : ""));
            }
        }

        /* ========== COMANDO: rjd ========== */
        else if (strcmp(comando, "rjd") == 0) {
            int id_disp; 
            char lado; 
            double dx, dy, ix, iy;
            
            sscanf(buffer, "rjd %d %c %lf %lf %lf %lf", &id_disp, &lado, &dx, &dy, &ix, &iy);

            Disparador d = buscar_disparador(lista_disparadores, id_disp);
            if (d) {
                Fila formas_disparadas = disparador_rajada(d, lado, dx, dy, ix, iy, arena);
                
                if (formas_disparadas != NULL) {
                    int n_disparadas = fila_tamanho(formas_disparadas);
                    num_disparos += n_disparadas;
                    fprintf(log_txt, "  -> Rajada: %d formas. Arena=%d\n", 
                            n_disparadas, arena_getNumeroDeFormas(arena));
                    fila_destruir(formas_disparadas); 
                }
            }
        }

        /* ========== COMANDO: calc ========== */
        else if (strcmp(comando, "calc") == 0) {
            fprintf(log_txt, "\n===== CALC =====\n");
            fprintf(log_txt, "Arena: %d formas\n", arena_getNumeroDeFormas(arena));
            
            arena_processa(arena, chao, log_txt, svg_file, &area_total_esmagada);
            
            fprintf(log_txt, "Pos-calc: Chao=%d, Arena=%d\n", chao_getTamanho(chao), arena_getNumeroDeFormas(arena));
            fprintf(log_txt, "Area esmagada acumulada: %.2lf\n\n", area_total_esmagada);
        }
    }
    
    fclose(arquivo_qry);

    /* ========== SVG FINAL ========== */
    //FILE* svg_file = svg_inicia(path_svg_pos_calc);
    if (svg_file) {
        chao_desenhaSvg(chao, svg_file);
        svg_finaliza(svg_file);
        printf("SVG final gerado em: %s\n", path_svg_pos_calc);
    }

    /* ========== ESTATÍSTICAS ========== */
    fprintf(log_txt, "\n===== ESTATISTICAS =====\n");
    fprintf(log_txt, "Pontuacao: %.2lf\n", area_total_esmagada);
    fprintf(log_txt, "Instrucoes: %d\n", num_instrucoes);
    fprintf(log_txt, "Disparos: %d\n", num_disparos);

    /* ========== LIMPEZA ========== */
    while (!fila_vazia(lista_disparadores)) {
        Disparador d = (Disparador) fila_retiraDoInicio(lista_disparadores);
        disparador_destroi(d); 
    }
    fila_destruir(lista_disparadores);

    while (!fila_vazia(lista_carregadores)) {
        Carregador c = (Carregador) fila_retiraDoInicio(lista_carregadores);
        carregador_destroi(c);
    }
    fila_destruir(lista_carregadores);
}