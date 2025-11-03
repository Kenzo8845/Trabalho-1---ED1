#include "carregador.h"
#include "pilha.h"
#include "formas.h" 
#include "chao.h"
#include <stdlib.h>
#include <stdio.h>


/*================================*/
/* Estrutura Interna do Carregador */
/*================================*/
typedef struct carregador {
    int id;
    Pilha formas; 
} EstruturaCarregador;


/*==========================*/
/* Constructor do Carregador */
/*==========================*/
Carregador carregador_cria(int id) {
    EstruturaCarregador *novoCarregador = (EstruturaCarregador*) malloc(sizeof(EstruturaCarregador));
    if(novoCarregador == NULL) {
        printf("Erro(0) em carregador_cria: falha na alocacao da estrutura.\n");
        return NULL;
    }

    novoCarregador->formas = pilha_cria(); 
    if (novoCarregador->formas == NULL) {
        printf("Erro(1) em carregador_cria: falha na alocacao da Pilha.\n");
        free(novoCarregador);
        return NULL;
    }

    novoCarregador->id = id;

    return (Carregador)novoCarregador;
}

/*==========================*/
/* Destructor do Carregador */
/*==========================*/
void carregador_destroi(Carregador c) {
    EstruturaCarregador *carregador = (EstruturaCarregador*) c;
    if(carregador == NULL) {
        printf("Erro(0) em carregador_destroi: Carregador invalido.\n");
        return;
    }
    
    while (!carregador_estaVazio(c)) {
        Forma forma_generica = carregador_descarregaForma(c); 
        if (forma_generica != NULL) {
            forma_destruir(forma_generica); 
        }
    }
    
    pilha_destruir(carregador->formas);
    free(carregador);
}


/*==========================*/
/* Operações do Carregador  */
/*==========================*/
void carregador_carregaForma(Carregador c, Forma f) {
    EstruturaCarregador *carregador = (EstruturaCarregador*) c;
    if(carregador == NULL || f == NULL) {
        printf("Erro(0) em carregador_carregaForma: Carregador ou Forma invalida.\n");
        return;
    }
    
    pilha_adicionaAoTopo(carregador->formas, (void*)f); 
}

void carregador_carregaNFormas(Carregador c, Chao ch, int n) {
    EstruturaCarregador *carregador = (EstruturaCarregador*) c;
    if(carregador == NULL || ch == NULL || n <= 0) {
        printf("Erro(0) em carregador_carregaNFormas: Parametros invalidos.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        Forma f = chao_retiraForma(ch); 
        
        if (f == NULL) {
            printf("Aviso em carregador_carregaNFormas: Chao vazio antes de carregar %d formas.\n", n);
            break;
        }
        
        carregador_carregaForma(c, f); 
    }
}


Forma carregador_descarregaForma(Carregador c) {
    EstruturaCarregador *carregador = (EstruturaCarregador*) c;
    if(carregador == NULL) {
        printf("Erro(0) em carregador_descarregaForma: Carregador invalido.\n");
        return NULL;
    }
    
    return (Forma)pilha_retiraDoTopo(carregador->formas); 
}


/*==========================*/
/* Getters do Carregador   */
/*==========================*/
int carregador_getId(Carregador c) {
    EstruturaCarregador *carregador = (EstruturaCarregador*) c;
    if(carregador == NULL) {
        printf("Erro(0) em carregador_getId: Carregador invalido.\n");
        return -1;
    }
    
    return carregador->id;
}


int carregador_estaVazio(Carregador c) {
    EstruturaCarregador *carregador = (EstruturaCarregador*) c;
    if(carregador == NULL) {
        printf("Erro(1) em carregador_estaVazio: Carregador invalido.\n");
        return 1; 
    }
    
    return pilha_vazia(carregador->formas);
}