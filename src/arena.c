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