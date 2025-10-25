#include "formas.h"
#include "estilo.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



/*======================*/
/*  Structs das formas  */ 
/*======================*/
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
    Estilo estilo;
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





/*==========================*/
/*  Constructors das formas */
/*==========================*/
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

Forma texto_cria(int i, double x, double y, char* corb, char *corp, char a, char *txto, Estilo e) {
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
    NovoTexto->dados.texto.estilo = e;

    return (Forma)NovoTexto;
}





/*==========================*/
/*  Destructor das formas   */
/*==========================*/
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
            estilo_destroi(forma->dados.texto.estilo);
            break;
    }

    free(forma); 
}





/*====================*/
/* Getters das formas */
/*====================*/
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

static char* forma_getCorComplementar(char* cor) {
     if (cor == NULL || cor[0] != '#') {
        printf("Erro(0) em getCorComplementar!");
        // Tratar erro ou cor invalida
        return NULL;
    }
    unsigned int r, g, b;
    sscanf(cor, "#%2x%2x%2x", &r, &g, &b); 

    unsigned int r_comp = 255 - r;
    unsigned int g_comp = 255 - g;
    unsigned int b_comp = 255 - b;

    char *corComp = (char *)malloc(sizeof(char) * 8); 
    if (corComp == NULL) {
        printf("Erro(1) em getCorComplementar!");
        return NULL; // Verifica alocação
    }

sprintf(corComp, "#%02X%02X%02X", r_comp, g_comp, b_comp);

return corComp;
}

char* forma_getCorPreenchimento(Forma f) {
    EstruturaForma* forma = (EstruturaForma*) f;
    if (f == NULL) {
        printf("Erro(0) em getCorPreenchimento!") ;
        return NULL;
    }

     switch (forma->tipo) {
        case TIPO_CIRCULO:
            return forma->dados.circulo.corp;
       
        case TIPO_RETANGULO:
            return forma->dados.retangulo.corp;

        case TIPO_LINHA:
            return forma->dados.linha.cor;

        case TIPO_TEXTO:
            return forma->dados.texto.corp;
    }

    printf("Erro(1) em getCorPreenchimento");
    return NULL;
}

char* forma_getCorBorda(Forma f) {
    EstruturaForma* forma = (EstruturaForma*) f;
    if (f == NULL) {
        printf("Erro(0) em getCorBorda!") ;
        return NULL;
    }

     switch (forma->tipo) {
        case TIPO_CIRCULO:
            return forma->dados.circulo.corb;
       
        case TIPO_RETANGULO:
            return forma->dados.retangulo.corb;

        case TIPO_LINHA:
            return forma->dados.linha.cor;

        case TIPO_TEXTO:
            return forma->dados.texto.corb;
    }

    printf("Erro(1) em getCorBorda");
    return NULL;
}





/*==================================*/
/*  Setters e operações das formas  */
/*==================================*/
void forma_setCorBorda(Forma f, char* novaCorBorda) {
    if (novaCorBorda == NULL || novaCorBorda[0] != '#') {
        printf("Erro(0) em setCorBorda!");
        // Tratar erro ou cor invalida
        return;
    }

    EstruturaForma* forma = (EstruturaForma*) f;
    if (f == NULL) {
        printf("Erro(1) em setCorBorda!") ;
        return;
    }

    char *novaCorAlocada = strdup(novaCorBorda);
    if (novaCorAlocada == NULL) {
        printf("Erro(2) em setCorBorda");
        return;
    } 


      switch (forma->tipo) {
        case TIPO_CIRCULO:
            free(forma->dados.circulo.corb);
            forma->dados.circulo.corb = novaCorAlocada;
            return;

        case TIPO_RETANGULO:
            free(forma->dados.retangulo.corb);
            forma->dados.retangulo.corb = novaCorAlocada;
            return;

        case TIPO_LINHA:
            free(forma->dados.linha.cor);
            forma->dados.linha.cor = novaCorAlocada;
            return;
        
        case TIPO_TEXTO:
            free(forma->dados.texto.corb);
            forma->dados.texto.corb = novaCorAlocada;
            return;
    }
    printf("Erro(3) em setCorBorda");
    return;
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
            return (Forma)texto_cria(novoId, forma->dados.texto.x, forma->dados.texto.y, forma->dados.texto.corp, forma->dados.texto.corb, forma->dados.texto.a, forma->dados.texto.txto, estilo_clona(forma->dados.texto.estilo));
    }

    // Return para caso de tipo desconhecido.
    return NULL;
}

/*
 * Funcoes utilizadas para otimização de verifica sobreposição.
 */

static int verifica_retangulo_retangulo(EstruturaForma* f1, EstruturaForma* f2) {
    if (f1->dados.retangulo.x + f1->dados.retangulo.w <= f2->dados.retangulo.x || 
        f2->dados.retangulo.x + f2->dados.retangulo.w <= f1->dados.retangulo.x ||
        f1->dados.retangulo.y + f1->dados.retangulo.h <= f2->dados.retangulo.y || 
        f2->dados.retangulo.y + f2->dados.retangulo.h <= f1->dados.retangulo.y) { 
        return 0; // Não sobrepõe.
    }
    return 1; // Sobrepõe.
}

static int verifica_circulo_circulo(EstruturaForma* f1, EstruturaForma* f2) {
    double distanciaAoQuadrado = pow((f1->dados.circulo.x - f2->dados.circulo.x), 2) + pow((f1->dados.circulo.y - f2->dados.circulo.y), 2);
    if(distanciaAoQuadrado <= pow(f1->dados.circulo.r + f2->dados.circulo.r, 2)) {
        return 1; // Sobrepõe.
    }

    return 0; // Não sorepõe.
}

static int verifica_retangulo_circulo(EstruturaForma* retangulo, EstruturaForma* circulo) {
    // Encontrar o ponto dentro do retangulo, mais proximo ao centro do circulo:
    // Pega o x min entre a quina do retangulo e o circulo, depois pega o x maximo entre o minimo anterior e o comeco do retangulo.
    double px = fmax(retangulo->dados.retangulo.x, (fmin(circulo->dados.circulo.x, retangulo->dados.retangulo.x + retangulo->dados.retangulo.w)));

    // Faz o mesmo com y, funcional independente se o circulo se encontra antes, durante ou depois do retangulo.
    double py = fmax(retangulo->dados.retangulo.y, (fmin(circulo->dados.circulo.y, retangulo->dados.retangulo.y + retangulo->dados.retangulo.h)));

    double dx = circulo->dados.circulo.x - px;
    double dy = circulo->dados.circulo.y - py;

    // Distância do centro do círculo ao ponto mais próximo no retângulo
    double distanciaAoQuadrado = dx * dx + dy * dy;

    if (distanciaAoQuadrado <= circulo->dados.circulo.r * circulo->dados.circulo.r) {
        return 1; // Sobrepõe.
    }

    return 0; // Não sobrepõe.
}

// Funcao que lida com coordenadas de retangulos, Bounding Boxes basicamente, vai ser principalmente utilizado para otimizar codigos complexos de logica com linhas.
static int verifica_bboxes(double x1, double y1, double w1, double h1, double x2, double y2, double w2, double h2) {
    
    // Testa se NÃO há sobreposição em X
    if (x1 + w1 <= x2 || x2 + w2 <= x1) {
        return 0; 
    }

    // Testa se NÃO há sobreposição em Y
    if (y1 + h1 <= y2 || y2 + h2 <= y1) {
        return 0; 
    }

    return 1;
}

static int verifica_linha_circulo(EstruturaForma *f1, EstruturaForma *f2) {
    
    // Dados da Linha (Segmento A)
    double x1 = f1->dados.linha.x1; // Ponto A (x1, y1)
    double y1 = f1->dados.linha.y1;
    double x2 = f1->dados.linha.x2; // Ponto B (x2, y2)
    double y2 = f1->dados.linha.y2;
    
    // Dados do Círculo
    double cx = f2->dados.circulo.x; // Centro C
    double cy = f2->dados.circulo.y;
    double r = f2->dados.circulo.r;


    // BB da Linha (R1): Calcula x, y, w, h
    double bbox_lx = fmin(x1, x2);
    double bbox_ly = fmin(y1, y2);
    double bbox_lw = fmax(x1, x2) - bbox_lx;
    double bbox_lh = fmax(y1, y2) - bbox_ly;
    
    // BB do Círculo (R2): Quadrado de 2r x 2r
    double bbox_cx = cx - r;
    double bbox_cy = cy - r;
    double bbox_cw = 2.0 * r;
    double bbox_ch = 2.0 * r;

    // Se as Bounding Boxes NÃO se cruzam, não há colisão. Retorno rápido.
    if (!verifica_bboxes(bbox_lx, bbox_ly, bbox_lw, bbox_lh, bbox_cx, bbox_cy, bbox_cw, bbox_ch)) {
        return 0; 
    }
  
    /*=========================================/
    * Metodo: Distancia Ponto-Segmento de Reta /
    * ========================================*/

    double ab_x = x2 - x1;
    double ab_y = y2 - y1;
    
    double ac_x = cx - x1;
    double ac_y = cy - y1;

    double ab_len_sq = ab_x * ab_x + ab_y * ab_y;

    // Se a linha tem comprimento zero (é um ponto), tratado como um circulo de raio 0.
    if (ab_len_sq == 0.0) {
        double dist_sq = ac_x * ac_x + ac_y * ac_y; // Distância do ponto (x1,y1) ao centro
        return (dist_sq <= r * r);
    }

    double t = (ac_x * ab_x + ac_y * ab_y) / ab_len_sq;

    double t_clamped = fmax(0.0, fmin(1.0, t));

    // Encontra o ponto mais proximo P no segmento.
    double px = x1 + t_clamped * ab_x;
    double py = y1 + t_clamped * ab_y;

    double final_dx = cx - px;
    double final_dy = cy - py;
    double dist_sq = final_dx * final_dx + final_dy * final_dy;

    return (dist_sq <= r * r);
}

static int is_ponto_dentro_retangulo(double px, double py, EstruturaForma *f_retangulo) {
    double rx = f_retangulo->dados.retangulo.x;
    double ry = f_retangulo->dados.retangulo.y;
    double rw = f_retangulo->dados.retangulo.w;
    double rh = f_retangulo->dados.retangulo.h;

    // Condição: O ponto está entre as coordenadas X do retângulo E as coordenadas Y
    if (px >= rx && px <= (rx + rw) && py >= ry && py <= (ry + rh)) 
    {
        return 1; // O ponto esta dentro do retangulo.
    }
    
    return 0; // Ponto nao esta dentro do retangulo.
}

// O EPSILON é crucial para evitar problemas com ponto flutuante na comparação com zero.
#define EPSILON 1e-9 
// ...

static int intersecta_segmento_segmento(double x1a, double y1a, double x2a, double y2a, double x1b, double y1b, double x2b, double y2b) {

    double dxA = x2a - x1a; 
    double dyA = y2a - y1a;
    double dxB = x2b - x1b; 
    double dyB = y2b - y1b;
    
    // Denominador (Determinante do sistema)
    double denominador = dxA * dyB - dyA * dxB;

    // Se o determinante for próximo de zero, as linhas são paralelas/colineares.
    // Para simplificacao, tratamos como nao colidindo (o teste colinear e complexo).
    if (fabs(denominador) < EPSILON) {
        return 0; 
    }
    
    // Vetor de diferenca entre os pontos iniciais (A1 - B1)
    double dx_start = x1a - x1b;
    double dy_start = y1a - y1b;
    
    // Calcula t (para o Segmento A)
    double num_t = dxB * dy_start - dyB * dx_start;
    double t = num_t / denominador;

    // Calcula u (para o Segmento B)
    double num_u = dxA * dy_start - dyA * dx_start;
    double u = num_u / denominador;

    // Teste Final: t e u devem estar no intervalo [0, 1] para intersecção em ambos os SEGMENTOS
    if (t >= 0.0 - EPSILON && t <= 1.0 + EPSILON && u >= 0.0 - EPSILON && u <= 1.0 + EPSILON) {
        // Usamos EPSILON na comparacao para maior robustez do float
        return 1; 
    }

    return 0; 
}

static int verifica_linha_retangulo(EstruturaForma *f_linha, EstruturaForma *f_retangulo) {
    
    double x1 = f_linha->dados.linha.x1;
    double y1 = f_linha->dados.linha.y1;
    double x2 = f_linha->dados.linha.x2;
    double y2 = f_linha->dados.linha.y2;

    double rx = f_retangulo->dados.retangulo.x;
    double ry = f_retangulo->dados.retangulo.y;
    double rw = f_retangulo->dados.retangulo.w;
    double rh = f_retangulo->dados.retangulo.h;

    // Coordenadas das 4 bordas do Retângulo (Bordas sao Segmentos)
    double x_fim = rx + rw;
    double y_fim = ry + rh;

    double bbox_lx = fmin(x1, x2);
    double bbox_ly = fmin(y1, y2);
    double bbox_lw = fmax(x1, x2) - bbox_lx;
    double bbox_lh = fmax(y1, y2) - bbox_ly;

    if (!verifica_bboxes(bbox_lx, bbox_ly, bbox_lw, bbox_lh, rx, ry, rw, rh)) {
        return 0;
    }

    // Teste preciso, caso passe do teste das BB.

    // Teste para ver se a linnha intersecta alguma das 4 bordas do retangulo.
    if (intersecta_segmento_segmento(x1, y1, x2, y2, rx, ry, x_fim, ry) ||    // Borda Superior
        intersecta_segmento_segmento(x1, y1, x2, y2, x_fim, ry, x_fim, y_fim) || // Borda Direita
        intersecta_segmento_segmento(x1, y1, x2, y2, x_fim, y_fim, rx, y_fim) || // Borda Inferior
        intersecta_segmento_segmento(x1, y1, x2, y2, rx, y_fim, rx, ry))     // Borda Esquerda
    {
        return 1; // Colidiu com uma das bordas
    }

    // Caso nao esteja nas bordas, testa se esta contida dentro do retangulo.
    if (is_ponto_dentro_retangulo(x1, y1, f_retangulo)) {
        return 1; // Linha está contida
    }

    return 0; // Nao esta contida e nem tem colisão.
}

static int verifica_linha_linha(EstruturaForma *f1_linha, EstruturaForma *f2_linha) {

    double x1a = f1_linha->dados.linha.x1;
    double y1a = f1_linha->dados.linha.y1;
    double x2a = f1_linha->dados.linha.x2;
    double y2a = f1_linha->dados.linha.y2;
    
    double x1b = f2_linha->dados.linha.x1;
    double y1b = f2_linha->dados.linha.y1;
    double x2b = f2_linha->dados.linha.x2;
    double y2b = f2_linha->dados.linha.y2;

    // BB da Linha A
    double bbox_lx_a = fmin(x1a, x2a);
    double bbox_ly_a = fmin(y1a, y2a);
    double bbox_lw_a = fmax(x1a, x2a) - bbox_lx_a;
    double bbox_lh_a = fmax(y1a, y2a) - bbox_ly_a;
    
    // BB da Linha B
    double bbox_lx_b = fmin(x1b, x2b);
    double bbox_ly_b = fmin(y1b, y2b);
    double bbox_lw_b = fmax(x1b, x2b) - bbox_lx_b;
    double bbox_lh_b = fmax(y1b, y2b) - bbox_ly_b;

    if (!verifica_bboxes(bbox_lx_a, bbox_ly_a, bbox_lw_a, bbox_lh_a, bbox_lx_b, bbox_ly_b, bbox_lw_b, bbox_lh_b)) {
        return 0;
    }

    // Caso ele passe no texte da BB, roda o teste preciso.
    return intersecta_segmento_segmento(x1a, y1a, x2a, y2a, x1b, y1b, x2b, y2b);
}

// Estrutura temporária para retornar os 4 pontos, utilizada na função para converter texto ara linha.
typedef struct {
    double x1, y1, x2, y2;
} SegmentoCoords;

static SegmentoCoords get_texto_segmento(EstruturaTexto *texto) {
    SegmentoCoords seg;
    double xt = texto->x;
    double yt = texto->y;
    int t = strlen(texto->txto); // |t|: numero de caracteres
    
    double comprimento_total = 10.0 * (double)t;
    double comprimento_metade = comprimento_total / 2.0;

    switch (texto->a) {
        case 'i': // Inicial (x1, y1) -> (x1 + L, y1)
            seg.x1 = xt;
            seg.y1 = yt;
            seg.x2 = xt + comprimento_total;
            seg.y2 = yt; 
            break;
        case 'f': // Final (x1 - L, y1) -> (x1, y1)
            seg.x1 = xt - comprimento_total;
            seg.y1 = yt;
            seg.x2 = xt;
            seg.y2 = yt;
            break;
        case 'm': // Médio (x1 - L/2, y1) -> (x1 + L/2, y1)
            seg.x1 = xt - comprimento_metade;
            seg.y1 = yt;
            seg.x2 = xt + comprimento_metade;
            seg.y2 = yt;
            break;
        default:
            // Caso padrao ou erro
            seg.x1 = xt; seg.y1 = yt;
            seg.x2 = xt + comprimento_total; seg.y2 = yt;
            break;
    }
    return seg;
}

// Cria um linha temporaria com dados de um texto, possibilitando reutilizar as funções de linha.
static Forma texto_para_linha_temporaria(EstruturaForma *f_texto) {
    EstruturaTexto *texto = &f_texto->dados.texto;
    SegmentoCoords seg = get_texto_segmento(texto);
    
    // O ID temp da linha, é o id do texto, porem negativo.
    int id_temp = -(f_texto->id); 
    
    // A cor da linha temporária é a cor de borda do texto.
    return linha_cria(id_temp, seg.x1, seg.y1, seg.x2, seg.y2, texto->corb);
}

int verificaSobreposicao(Forma f1, Forma f2){
    EstruturaForma* forma1 = (EstruturaForma*) f1;
    EstruturaForma* forma2 = (EstruturaForma*) f2;
    int resultado = 0; // Resultado padrao: Nao sobrepoe

    if (forma1 == NULL || forma2 == NULL) {
        printf("Erro(0) em verificaSobreposicao");
        return -1; 
    }

    // Garante que forma1 tenha a forma de maior prioridade (menor valor de enum)
    if(forma2->tipo < forma1->tipo) { 
        return verificaSobreposicao(forma2, forma1);
    }
    
    switch (forma1->tipo) {
        
        case TIPO_CIRCULO:
            switch (forma2->tipo) {
                case TIPO_CIRCULO:
                    return verifica_circulo_circulo(forma1, forma2);
                case TIPO_RETANGULO:
                    return verifica_retangulo_circulo(forma2, forma1);
                case TIPO_LINHA:
                    return verifica_linha_circulo(forma2, forma1);
                case TIPO_TEXTO:
                    {
                        Forma linha_temp = texto_para_linha_temporaria(forma2);
                        resultado = verifica_linha_circulo(linha_temp, forma1);
                        forma_destruir(linha_temp); // Libera a linha temporaria.
                        return resultado;
                    }
            }
            break;
            
        case TIPO_RETANGULO:
            switch (forma2->tipo) {
                case TIPO_RETANGULO:
                    return verifica_retangulo_retangulo(forma1, forma2);
                case TIPO_LINHA:
                    return verifica_linha_retangulo(forma2, forma1);
                case TIPO_TEXTO:
                    {
                        Forma linha_temp = texto_para_linha_temporaria(forma2);
                        resultado = verifica_linha_retangulo(linha_temp, forma1);
                        forma_destruir(linha_temp); // Libera a linha temporaria.
                        return resultado;
                    }
            }
            break;
            
        case TIPO_LINHA:
            switch (forma2->tipo) {
                case TIPO_LINHA:
                    return verifica_linha_linha(forma1, forma2);
                case TIPO_TEXTO:
                    {
                        Forma linha_temp = texto_para_linha_temporaria(forma2);
                        resultado = verifica_linha_linha(forma1, linha_temp);
                        forma_destruir(linha_temp); // Libera a linha temporaria.
                        return resultado;
                    }
            }
            break;

        case TIPO_TEXTO:
            if (forma2->tipo == TIPO_TEXTO) {
                Forma linha1_temp = texto_para_linha_temporaria(forma1);
                Forma linha2_temp = texto_para_linha_temporaria(forma2);
                
                resultado = verifica_linha_linha(linha1_temp, linha2_temp);
                
                forma_destruir(linha1_temp); // Libera a linha temporaria.
                forma_destruir(linha2_temp); // Libera a linha temporaria.
                return resultado;
            }
            break;
    }
    printf("Erro(1) em verificaSobreposicao");
    return 0; // Se chegar tipo nao existente, retorna nao sobrepoe.
}