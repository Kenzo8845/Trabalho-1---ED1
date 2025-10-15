#include "formas.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    TIPO_CIRCULO,
    TIPO_RETANGULO,
    TIPO_LINHA,
    TIPO_TEXTO
} TipoForma;

typedef struct {
    double x, y, r;
    char *corb, *corp;
    double area;
} EstruturaCirculo;

typedef struct {
    double x, y, w, h;
    char *corb, *corp;
    double area;
} EstruturaRetangulo;

typedef struct {
    double x1, y1, x2, y2;
    char *cor;
    double area;
} EstruturaLinha;

typedef struct {
    double x, y;
    char *corb, *corp;
    char a;
    char *txto;
    double area;
} EstruturaTexto;

typedef struct {
    TipoForma tipo;
    int id; // ID unico de cada forma
    union {
        EstruturaCirculo circulo;
        EstruturaRetangulo retangulo;
        EstruturaLinha linha;
        EstruturaTexto texto;
    } dados;
} EstruturaForma;

Forma circulo_cria(int i, double x, double y, double r, char *corb, char *corp) {
    EstruturaForma *NovoCirculo = (EstruturaForma*) malloc(sizeof(EstruturaForma));
    if (NovoCirculo == NULL) {
        printf("erro de alocação ao criar novo circulo em circulo_cria");
        return NULL;
    }

    NovoCirculo->tipo = TIPO_CIRCULO;

    NovoCirculo->id = i;
    NovoCirculo->dados.circulo.r = r;
    NovoCirculo->dados.circulo.x = x;
    NovoCirculo->dados.circulo.y = y;
    NovoCirculo->dados.circulo.corb = strdup(corb);
    NovoCirculo->dados.circulo.corp = strdup(corp);
    NovoCirculo->dados.circulo.area = 3.1415926 * (r*r);
    return (Forma)NovoCirculo;
}

Forma retangulo_cria(int i, double x, double y, double w, double h, char *corb, char *corp) {
    EstruturaForma *NovoRetangulo = (EstruturaForma*) malloc(sizeof(EstruturaForma));
    if (NovoRetangulo == NULL) {
        printf("erro de alocação ao criar novo retangulo em retangulo_cria");
        return NULL;
    }

    NovoRetangulo->tipo = TIPO_RETANGULO;

    NovoRetangulo->id = i;
    NovoRetangulo->dados.retangulo.x = x;
    NovoRetangulo->dados.retangulo.y = y;
    NovoRetangulo->dados.retangulo.w = w;
    NovoRetangulo->dados.retangulo.h = h;
    NovoRetangulo->dados.retangulo.corb = strdup(corb);
    NovoRetangulo->dados.retangulo.corp = strdup(corp);
    NovoRetangulo->dados.retangulo.area = w*h;

    return (Forma)NovoRetangulo;
}

Forma linha_cria(int i, double x1, double y1, double x2, double y2, char *cor) {
    EstruturaForma *NovaLinha = (EstruturaForma*) malloc(sizeof(EstruturaForma));
    if (NovaLinha == NULL) {
        printf("erro de alocação ao criar nova Linha em linha_cria");
        return NULL;
    }

    NovaLinha->tipo = TIPO_LINHA;

    NovaLinha->id = i;
    NovaLinha->dados.linha.x1 = x1;
    NovaLinha->dados.linha.x2 = x2;
    NovaLinha->dados.linha.y1 = y1;
    NovaLinha->dados.linha.y2 = y2;
    NovaLinha->dados.linha.cor = strdup(cor);
    NovaLinha->dados.linha.area = forma_getArea(NovaLinha);

    return (Forma)NovaLinha;
}

Forma texto_cria(int i, double x, double y, char* corb, char *corp, char a, char *txto) {
    EstruturaForma *NovoTexto = (EstruturaForma*) malloc(sizeof(EstruturaForma));
    if (NovoTexto == NULL) {
        printf("erro de alocação ao criar novo texto em texto_cria");
        return NULL;
    }

    NovoTexto->tipo = TIPO_TEXTO;

    NovoTexto->id = i;
    NovoTexto->dados.texto.x = x;
    NovoTexto->dados.texto.y = y;
    NovoTexto->dados.texto.corb = strdup(corb);
    NovoTexto->dados.texto.corp = strdup(corp);
    NovoTexto->dados.texto.a = a;
    NovoTexto->dados.texto.txto = strdup(txto);
    NovoTexto->dados.texto.area = 20 * strlen(txto);

    return (Forma)NovoTexto;
}

void forma_destruir(Forma f) {

    EstruturaForma *forma = (EstruturaForma *)f;
    if (f == NULL) { 
    return;
    }

    switch (forma->tipo) {
        case TIPO_CIRCULO:
            free(forma->dados.circulo.corb);
            free(forma->dados.circulo.corp);
            break;

        case TIPO_RETANGULO:
            free(forma->dados.retangulo.corb);
            free(forma->dados.retangulo.corp);
            break;
            
        case TIPO_LINHA:
            free(forma->dados.linha.cor); 
            break;
            
        case TIPO_TEXTO:
            free(forma->dados.texto.corb);
            free(forma->dados.texto.corp);
            free(forma->dados.texto.txto); 
            break;
    }

    free(forma); 
}

int forma_getId(Forma f) {
    EstruturaForma *forma = (EstruturaForma *)f;
    if (f == NULL) { 
    return -1;
    }

    return forma->id;
}

double forma_getArea(Forma f) {
    EstruturaForma *forma = (EstruturaForma *)f;
    if (f == NULL) { 
    return -1;
    }

    double area;

    switch (forma->tipo) {
        case TIPO_CIRCULO:
        area = 3.1415926 * (forma->dados.circulo.r * forma->dados.circulo.r);
        return area;

        case TIPO_RETANGULO:
        area = forma->dados.retangulo.w * forma->dados.retangulo.h;
        return area;

        case TIPO_LINHA:
        double dx = forma->dados.linha.x2 - forma->dados.linha.x1;
        double dy = forma->dados.linha.y2 - forma->dados.linha.y1;

        double comprimento = sqrt(dx * dx + dy * dy); 

        area = 2.0 * comprimento;
        return area;

        case TIPO_TEXTO:
        area = 20 * strlen(forma->dados.texto.txto);
        return area;
    }

    // Return para caso de tipo desconhecido.
    return -1;
}

char* forma_getCorComplementar(char* cor) {
     if (cor == NULL || cor[0] != '#') {
        // Tratar erro ou cor invalida
        return NULL;
    }
    unsigned int r, g, b;
    sscanf(cor, "#%2x%2x%2x", &r, &g, &b); 

    unsigned int r_comp = 255 - r;
    unsigned int g_comp = 255 - g;
    unsigned int b_comp = 255 - b;

    char *corComp = (char *)malloc(sizeof(char) * 8); 
    if (corComp == NULL) 
    return NULL; // Verifica alocação

sprintf(corComp, "#%02X%02X%02X", r_comp, g_comp, b_comp);

return corComp;
}

Forma forma_clonar(Forma original, int novoId) {
    EstruturaForma *forma = (EstruturaForma *)original;
    if (original == NULL) { 
    return NULL;
    }

    switch (forma->tipo) {
        case TIPO_CIRCULO:
        return (Forma)circulo_cria(novoId, forma->dados.circulo.x, forma->dados.circulo.y, forma->dados.circulo.r, forma->dados.circulo.corp, forma->dados.circulo.corb);

        case TIPO_RETANGULO:
        return(Forma)retangulo_cria(novoId, forma->dados.retangulo.x, forma->dados.retangulo.y, forma->dados.retangulo.w, forma->dados.retangulo.h, forma->dados.retangulo.corp, forma->dados.retangulo.corb);

        case TIPO_LINHA:
        return (Forma)linha_cria(novoId, forma->dados.linha.x1, forma->dados.linha.y1, forma->dados.linha.x2, forma->dados.linha.y2, forma_getCorComplementar(forma->dados.linha.cor));

        case TIPO_TEXTO:
        return (Forma)texto_cria(novoId, forma->dados.texto.x, forma->dados.texto.y, forma->dados.texto.corp, forma->dados.texto.corb, forma->dados.texto.a, forma->dados.texto.txto);
    }

    // Return para caso de tipo desconhecido.
    return NULL;
}


