#include <stdio.h>
#include <stdlib.h>
#include "fila.h"
#include "formas.h"
#include "arena.h"

typedef struct arena {
    Fila formas;
} EstruturaArena;

Arena arena_cria() {
    EstruturaArena* arenaNova =(EstruturaArena*) malloc(sizeof(EstruturaArena));
    if(arenaNova == NULL) {
        printf("Erro(0) em arena_cria");
        return NULL;
    }

    arenaNova->formas == NULL;

    return (Arena)arenaNova;
}

void arena_destroi(Arena a) {
    EstruturaArena* arena = (EstruturaArena*) a;
    if(arena == NULL) {
        printf("Erro(0) em arena_destroi");
        return;
    }
    
    while (!fila_vazia(arena->formas)) {
        void *forma_generica = fila_retiraDoInicio(arena->formas);
        if (forma_generica != NULL) {
            forma_destruir((Forma)forma_generica); 
        }
    }
}

int arena_getNumeroDeFormas(Arena a) {
    EstruturaArena* arena = (EstruturaArena*) a;
    if(arena == NULL) {
        printf("Erro(0) em arena_getNumeroFormas");
        return -1;
    }

    return fila_tamanho(arena->formas);
}

Fila arena_getFila(Arena a) {
    EstruturaArena* arena = (EstruturaArena*) a;
    if(arena == NULL) {
        printf("Erro(0) em arena_getFila");
        return NULL;
    }

    return arena->formas;
}

void arena_adicionaForma(Arena a, Forma f) {
    EstruturaArena* arena = (EstruturaArena*) a;
    if(arena == NULL || arena->formas == NULL || f == NULL) {
        printf("Erro(0) em arena_adicionaForma");
        return;
    }

    return fila_adicionaAoFim(arena->formas, (void*) f);
}

Forma arena_removeForma(Arena a) {
    EstruturaArena* arena = (EstruturaArena*) a;
    if(arena == NULL) {
        printf("Erro(0) em arena_removeForma");
        return NULL;
    }

    void* formaRetirada = fila_retiraDoInicio(arena->formas);
    if(formaRetirada == NULL) {
        printf("Erro(1) em arena_removeForma");
        return NULL;
    }

    return (Forma)formaRetirada;
}

void arena_processa(Arena a, Chao ch, FILE *txt_fp, FILE *svg_fp, double *area_total_esmagada) {
    EstruturaArena* arena = (EstruturaArena*) a;
    if (arena == NULL || ch == NULL || txt_fp == NULL || area_total_esmagada == NULL) {
        printf("Erro(0) em arena_processa: Parametros invalidos.\\n");
        return;
    }
    
    double area_esmagada_round = 0.0;
    fprintf(txt_fp, "\n=== Comando CALC: Processando Arena ===\n");

    while (arena_getNumeroDeFormas(a) >= 2) {
        
        Forma i = (Forma)fila_retiraDoInicio(arena->formas); 
        Forma j = (Forma)fila_retiraDoInicio(arena->formas); 

        int sobreposicao = forma_verificaSobreposicao(i, j);

        if (sobreposicao) {
            
            fprintf(txt_fp, "\nVERIFICAÇÃO: Sobreposição entre I (ID %d, A=%.2lf) e J (ID %d, A=%.2lf).\n", 
                    forma_getId(i), forma_getArea(i), forma_getId(j), forma_getArea(j));

            double area_i = forma_getArea(i);
            double area_j = forma_getArea(j);

            if (area_i < area_j) {
                fprintf(txt_fp, "RESULTADO: I (menor) ESMAGADA!. J volta ao Chao.\n");
                
                double area_destruida = forma_getArea(i);
                area_esmagada_round += area_destruida;
                *area_total_esmagada += area_destruida;

                forma_destruir(i); 
                chao_adicionaAoChao(ch, j); 
            } 
            
            else  {                
                fprintf(txt_fp, "RESULTADO: I (maior) troca cor de J. Ambas voltam ao Chao. Clone de I volta ao Chao.\n");
                forma_setCorBorda(j, forma_getCorPreenchimento(i));
                Forma clone = forma_clonar(i);
                chao_adicionaAoChao(ch, i);
                chao_adicionaAoChao(ch, j);
                chao_adicionaAoChao(ch, clone);
            }
        } 
        
        else {
            fprintf(txt_fp, "VERIFICAÇÃO: Sem sobreposição. Ambas voltam ao Chao.\n");
            chao_adicionaAoChao(ch, i);
            chao_adicionaAoChao(ch, j);
        }
    }

    if (arena_getNumeroDeFormas(a) == 1) {
        Forma f_restante = (Forma)fila_retiraDoInicio(arena->formas);
        fprintf(txt_fp, "\nAVISO CALC: Arena com elemento impar. Forma ID %d volta para o Chao.\n", forma_getId(f_restante));
        chao_adicionaAoChao(ch, f_restante);
    }

    fprintf(txt_fp, "\n[RESUMO CALC]\n");
    fprintf(txt_fp, "Area total esmagada NESTE round: %.2lf\n", area_esmagada_round);
    fprintf(txt_fp, "Area total esmagada no JOGO: %.2lf\n", *area_total_esmagada);
}