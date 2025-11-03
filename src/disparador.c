#include "disparador.h"
#include "carregador.h"
#include "arena.h"
#include "formas.h"
#include "fila.h" 
#include <stdlib.h>
#include <stdio.h>

/*=================================*/
/* Estrutura Interna do Disparador */
/*=================================*/
typedef struct disparador {
    int id;
    double x, y;
    Carregador esquerdo;
    Carregador direito;
    Forma forma_em_disparo;
} EstruturaDisparador;


/*===========================*/
/* Constructor do Disparador */
/*===========================*/
Disparador disparador_cria(int id, double x, double y) {
    EstruturaDisparador *novoDisparador = (EstruturaDisparador*) malloc(sizeof(EstruturaDisparador));
    if (novoDisparador == NULL) {
        printf("Erro(0) em disparador_cria: falha na alocacao da estrutura.\n");
        return NULL;
    }

    novoDisparador->esquerdo = NULL;
    novoDisparador->direito = NULL;

    novoDisparador->id = id;
    novoDisparador->x = x;
    novoDisparador->y = y;
    novoDisparador->forma_em_disparo = NULL;

    return (Disparador)novoDisparador;
}


/*===========================*/
/* Destructor do Disparador  */
/*===========================*/
void disparador_destroi(Disparador d) {
    EstruturaDisparador *disparador = (EstruturaDisparador*) d;
    if (disparador == NULL) {
        printf("Erro(0) em disparador_destroi: Disparador invalido.\n");
        return;
    }

    if (disparador->esquerdo != NULL) {
        carregador_destroi(disparador->esquerdo);
    }
    if (disparador->direito != NULL) {
        carregador_destroi(disparador->direito);
    }

    if (disparador->forma_em_disparo != NULL) {
        forma_destruir(disparador->forma_em_disparo);
    }

    free(disparador);
}


/*=============================*/
/* Operações de Carregamento   */
/*=============================*/

void disparador_attach(Disparador d, Carregador ce, Carregador cd) {
    EstruturaDisparador *disparador = (EstruturaDisparador*) d;
    if (disparador == NULL || ce == NULL || cd == NULL) {
        printf("Erro(0) em disparador_attach: Disparador ou Carregadores invalidos.\n");
        return;
    }

    disparador->esquerdo = ce;
    disparador->direito = cd;
}


Forma disparador_shift(Disparador d, char lado, int n) {
    EstruturaDisparador *disparador = (EstruturaDisparador*) d;
    if (disparador == NULL) {
        printf("Erro(0) em disparador_shift: Disparador invalido.\n");
        return NULL;
    }
    if (lado != 'e' && lado != 'd') {
        printf("Erro(1) em disparador_shift: Lado invalido ('%c').\n", lado);
        return NULL;
    }
    if (disparador->esquerdo == NULL || disparador->direito == NULL) {
        printf("Erro(2) em disparador_shift: Carregadores nao foram encaixados.\n");
        return NULL;
    }
    if (n <= 0) {
        return disparador->forma_em_disparo;
    }

    Carregador origem_nova_forma, destino_forma_atual;

    for (int i = 0; i < n; i++) {
        if (lado == 'e') {
            destino_forma_atual = disparador->esquerdo;
            origem_nova_forma = disparador->direito; 
        } else {
            destino_forma_atual = disparador->direito;  
            origem_nova_forma = disparador->esquerdo; 
        }

        if (disparador->forma_em_disparo != NULL) {
            carregador_carregaForma(destino_forma_atual, disparador->forma_em_disparo);
            disparador->forma_em_disparo = NULL;
        }

        if (!carregador_estaVazio(origem_nova_forma)) {
            disparador->forma_em_disparo = carregador_descarregaForma(origem_nova_forma);
        } else {
            printf("Aviso em disparador_shift: Carregador origem vazio (shift %d/%d).\n", i + 1, n);
        }
    }
    
    return disparador->forma_em_disparo;
}



/*=============================*/
/* Operação de Disparo         */
/*=============================*/
Forma disparador_dispara(Disparador d, double dx, double dy, Arena a, FILE* svg_file, int desenha_trajetoria) {
    EstruturaDisparador *disparador = (EstruturaDisparador*) d;
    if (disparador == NULL || a == NULL) {
        printf("Erro(0) em disparador_dispara: Disparador ou Arena invalida.\n");
        return NULL;
    }

    if (disparador->forma_em_disparo == NULL) {
        printf("Aviso em disparador_dispara: Nao ha forma engatilhada para disparo.\n");
        return NULL;
    }
    
    Forma formaDisparada = disparador->forma_em_disparo;
    
    double x_inicial = disparador->x;
    double y_inicial = disparador->y;
    
    double novoX = disparador->x + dx;
    double novoY = disparador->y + dy;
    
    forma_setX(formaDisparada, novoX);
    forma_setY(formaDisparada, novoY);

     if (desenha_trajetoria && svg_file != NULL) {
        svg_desenha_trajetoria(svg_file, x_inicial, y_inicial, novoX, novoY);
    }
    
    arena_adicionaForma(a, formaDisparada);
    
    disparador->forma_em_disparo = NULL;
    
    return formaDisparada;
}


Fila disparador_rajada(Disparador d, char lado, double dx, double dy, double ix, double iy, Arena a) {
    EstruturaDisparador *disparador = (EstruturaDisparador*) d;
    if (disparador == NULL || a == NULL) {
        printf("Erro(0) em disparador_rajada: Disparador ou Arena invalida.\n");
        return NULL;
    }
    if (lado != 'e' && lado != 'd') {
        printf("Erro(1) em disparador_rajada: Lado invalido ('%c').\n", lado);
        return NULL;
    }

    Fila formas_disparadas = fila_cria();
    if (formas_disparadas == NULL) {
        printf("Erro(2) em disparador_rajada: Falha ao criar a Fila de resultados.\n");
        return NULL;
    }

    Forma forma_disparada;
    int i = 0;

    Carregador origem = (lado == 'e') ? disparador->direito : disparador->esquerdo;

    while (!carregador_estaVazio(origem) || disparador->forma_em_disparo != NULL) {

        Forma forma_engatilhada = disparador_shift(d, lado, 1);
        
        if (forma_engatilhada == NULL && disparador->forma_em_disparo == NULL) {
            break; 
        }

        double novo_dx = dx + (ix * i);
        double novo_dy = dy + (iy * i);
        i++;

        forma_disparada = disparador_dispara(d, novo_dx, novo_dy, a, NULL, 0);

        if (forma_disparada != NULL) {
            fila_adicionaAoFim(formas_disparadas, forma_disparada);
        } else {
            break;
        }
    }

    return formas_disparadas;
}


/*=============================*/
/* Getters/Setters Auxiliares  */
/*=============================*/

int disparador_getId(Disparador d) {
    EstruturaDisparador *disparador = (EstruturaDisparador*) d;
    if (disparador == NULL) {
        printf("Erro(0) em disparador_getId.\n");
        return -1;
    }
    return disparador->id;
}

double disparador_getX(Disparador d) {
    EstruturaDisparador *disparador = (EstruturaDisparador*) d;
    if (disparador == NULL) {
        printf("Erro(0) em disparador_getX.\n");
        return 0.0;
    }
    return disparador->x;
}

double disparador_getY(Disparador d) {
    EstruturaDisparador *disparador = (EstruturaDisparador*) d;
    if (disparador == NULL) {
        printf("Erro(0) em disparador_getY.\n");
        return 0.0;
    }
    return disparador->y;
}

Carregador disparador_getCarregadorEsquerdo(Disparador d) {
    EstruturaDisparador *disparador = (EstruturaDisparador*) d;
    if (disparador == NULL) {
        printf("Erro(0) em disparador_getCarregadorEsquerdo.\n");
        return NULL;
    }
    return disparador->esquerdo;
}

Carregador disparador_getCarregadorDireito(Disparador d) {
    EstruturaDisparador *disparador = (EstruturaDisparador*) d;
    if (disparador == NULL) {
        printf("Erro(0) em disparador_getCarregadorDireito.\n");
        return NULL;
    }
    return disparador->direito;
}

Forma disparador_getFormaEmDisparo(Disparador d) {
    EstruturaDisparador *disparador = (EstruturaDisparador*) d;
    if (disparador == NULL) {
        printf("Erro(0) em disparador_getFormaEmDisparo.\n");
        return NULL;
    }
    return disparador->forma_em_disparo;
}