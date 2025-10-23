#include "pilha.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct No {
    void *elemento;
    struct No* prox;
} NoPilha;

typedef struct Pilha {
    NoPilha* topo;
    int tamanho;
} EstruturaPilha;


/*
* Cria uma nova pilha vazia.
*/
Pilha pilha_cria() {
    EstruturaPilha *PilhaNova = (EstruturaPilha*) malloc(sizeof(EstruturaPilha));
    if (PilhaNova == NULL) {
        printf("erro ao criar pilha nova");
        return NULL;
        // Caso haja erro de alocação.
    }
    PilhaNova->topo = NULL;
    PilhaNova->tamanho = 0;

    return(Pilha) PilhaNova;
}

void pilha_adicionaAoTopo(Pilha p, void* elemento) {
     EstruturaPilha *pilha = (EstruturaPilha *) p;

    if (pilha == NULL || elemento == NULL) {
        // A pilha nao foi criada ou o elemento e invalido.
        return;
    }
    
    NoPilha *NovoTopo = (NoPilha*) malloc(sizeof(NoPilha));

    if (NovoTopo == NULL) {
        return;
        //Falha na alocação.
    }
    
    NovoTopo->elemento = elemento;
    NovoTopo->prox = pilha->topo;
    pilha->topo = NovoTopo;
}

void* pilha_retiraDoTopo(Pilha p) {
    EstruturaPilha *pilha = (EstruturaPilha*) p;
    if(pilha == NULL) {
        return;
        // A pilha não foi criada.
    }

    // NoRetirado é o topo atual da pilha.
    NoPilha *NoRetirado = pilha->topo;
    
    // Salva o elemento do item retirado em uma variável.
    void *ItemRetorno = NoRetirado->elemento;

    // Atualiza o topo.
    pilha->topo = pilha->topo->prox;

    // Libera o item retirado, mas não no conteudo.
    free(NoRetirado);

    // Atualiza o tamanho.
    pilha->tamanho--;

    return ItemRetorno;
}

int pilha_tamanho(Pilha p) {
    EstruturaPilha *pilha = (EstruturaPilha*) p;
    if(pilha == NULL) {
        return;
        // A pilha não foi criada.
    }

    return pilha->tamanho;
}

bool pilha_vazia(Pilha p) {
    EstruturaPilha *pilha = (EstruturaPilha*) p;
    if(pilha == NULL) {
        return;
        // A pilha não foi criada.
    }
    
    if (pilha->tamanho == 0) {
        return true;
    }
    
    else {
        return false;
    }
}

void pilha_destruir(Pilha p) {
    EstruturaPilha* pilha = (EstruturaPilha*) p;
    if (pilha == NULL) {
        printf("nao foi possivel criar a pilha em: pilha_destruir");
        // Erro ao criar a pilha.
        return;
    }

    NoPilha *atual = pilha->topo;
    while (atual != NULL) {
        NoPilha *prox = atual->prox;
        free(atual);
        atual = prox;
    }

    free(pilha);
}



