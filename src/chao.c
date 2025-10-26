#include "chao.h"
#include "fila.h"
#include "formas.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct chao {
    Fila formas; 
} EstruturaChao;

Chao chao_cria(Fila geo_formas) {
    EstruturaChao *c = (EstruturaChao*) malloc(sizeof(EstruturaChao));
    if (c == NULL) {
        printf("Erro(0) em chao_cria");
        return NULL;
    }

    c->formas = geo_formas; 

    return (Chao)c;
}

void chao_destruir(Chao c) {
    EstruturaChao *chao = (EstruturaChao*) c;
    if (chao == NULL) {
        printf("Erro(0) em chao_destruir");
        return;
    }

    while (!fila_vazia(chao->formas)) {
        void *forma_generica = fila_retiraDoInicio(chao->formas);
        if (forma_generica != NULL) {
            forma_destruir((Forma)forma_generica); 
        }
    }

    fila_destruir(chao->formas);

    free(chao);
}

Forma chao_retiraForma(Chao c){
    EstruturaChao *chao = (EstruturaChao*) c;
    if (chao == NULL || fila_vazia(chao->formas)) {
        printf("Erro(0) em chao_retiraForma");
        return NULL;
    }

    void* formaRetirada = fila_retiraDoInicio(chao->formas);
    if(formaRetirada == NULL) {
        printf("Erro(1) em chao_retiraForma");
        return NULL;
    }

    return (Forma)formaRetirada;
}

void chao_adicionaAoChao(Chao c, Forma f) {
    EstruturaChao *chao = (EstruturaChao*) c;
    if (chao == NULL || chao->formas == NULL || f == NULL) {
        printf("Erro(0) em chao_adicionaAoChao");
        return;
    }

    fila_adicionaAoFim(chao->formas, (void*)f);
}

int chao_getTamanho(Chao c) {
    EstruturaChao *chao = (EstruturaChao*) c;
    if (chao == NULL || chao->formas == NULL) {
        printf("Erro(0) em chao_getTamanho");
        return -1;
    }
    
    return fila_tamanho(chao->formas);
}

Fila chao_getFila(Chao c) {
    EstruturaChao *chao = (EstruturaChao*) c;
    if (chao == NULL || chao->formas == NULL) {
        printf("Erro(0) em chao_getFila");
        return NULL;
    }

    return chao->formas;
}