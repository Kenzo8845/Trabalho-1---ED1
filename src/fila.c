#include "fila.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct No {
    void *Elemento;
    struct No* prox;
} NoFila;

typedef struct fila {
    NoFila *Inicio;
    NoFila* fim;
    int tamanho;
} EstruturaFila;

Fila fila_cria() {
    EstruturaFila * FilaNova = (EstruturaFila*) malloc(sizeof(EstruturaFila));
    if(FilaNova == NULL) {
        printf("erro de alocação ao criar fila nova");
        return NULL;
    }

    FilaNova->fim = NULL;
    FilaNova->Inicio = NULL;
    FilaNova->tamanho = 0;

    return (Fila) FilaNova;
}

void fila_adicionaAoFim(Fila f, void* elemento) {
    EstruturaFila *fila = (EstruturaFila*) f;
    
    if (fila == NULL || elemento == NULL) {
        printf("erro ao adicionar ao fim, fila nao criada ou elemento invalido");
        return;
        // Erro de alocação
    }

    NoFila *NovoFim = (NoFila*) malloc(sizeof(NoFila));

    if (NovoFim == NULL) {
        printf("erro ao criar novo fim");
        return;
    }

    if(fila->tamanho == 0) {
    // O prox do fim é NULL.
    NovoFim->prox = NULL;

    NovoFim->Elemento = elemento;

    // Como a fila estava vazia, o fim tambem é o inicio.
    fila->Inicio = NovoFim;

    fila->tamanho++;
    
    return;
    }

    fila->fim->prox = NovoFim;
    fila->fim = NovoFim;

    return;
}

void* fila_retiraDoInicio(Fila f) {
    EstruturaFila* fila = (EstruturaFila*) f;
    if (fila == NULL) {
        // Erro ao criar a fila.
        print("nao foi possivel criar a fila em: fila_retiraDoInicio");
        return;
    }

    if(fila->Inicio == NULL) {
        printf("nao foi possivel retirar da fila, ela esta vazia");
        return;
    }

    // Cria uma variável temporária para o Node a ser retirado.
    NoFila* ItemRetirado = fila->Inicio;

    void* ItemRetorno = fila->Inicio->Elemento;

    fila->Inicio = fila->Inicio->prox;

    free(ItemRetirado);

    fila->tamanho--;

    return ItemRetorno;
}

int fila_tamanho(Fila f) {
    EstruturaFila* fila = (EstruturaFila*) f;
    if (fila == NULL) {
        printf("nao foi possivel criar a fila em: fila_tamanho");
        // Erro ao criar a fila.
        return 0;
    }

    return fila->tamanho;
}

bool fila_vazia(Fila f) {
 EstruturaFila* fila = (EstruturaFila*) f;
    if (fila == NULL) {
        printf("nao foi possivel criar a fila em: fila_vazia");
        // Erro ao criar a fila.
        return;
    }
    if (fila->tamanho == 0) {
        return true;
    }

    return false;
}

void fila_destruir(Fila f) {
    EstruturaFila* fila = (EstruturaFila*) f;
    if (fila == NULL) {
        printf("nao foi possivel criar a fila em: fila_destruir");
        // Erro ao criar a fila.
        return;
    }

    NoFila *atual = fila->Inicio;
    while (atual != NULL) {
        NoFila *prox = atual->prox;
        free(atual);
        atual = prox;
    }

    free(fila);
}