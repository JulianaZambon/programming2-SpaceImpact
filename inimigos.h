#ifndef __INIMIGOS__ // Guardas de inclusão
#define __INIMIGOS__ // Guardas de inclusão

#include <allegro5/allegro.h> 

// Inclusões de bibliotecas locais
#include "arma.h"
#include "chefes.h"

/*-------------------------------------------------------------------*/
/* DEFINIÇÕES */
#define NUM_INIMIGOS 4            // Número de tipos de inimigos
#define ANIMATION_DELAY_INIMIGO 3 // Velocidade da animação (quanto maior, mais lento)
#define STEPS_INIMIGO 2           // Velocidade de movimento do inimigo

#define INIMIGO_STEP 2  // Velocidade de movimento do inimigo 0
#define INIMIGO1_STEP 1 // Velocidade de movimento do inimigo 1
#define INIMIGO2_STEP 1 // Velocidade de movimento do inimigo 2
#define INIMIGO3_STEP 2 // Velocidade de movimento do inimigo 3

#define PATH_INIMIGO_0 "assets/inimigos/fase1/inimigo1.png" // Caminho para o sprite do inimigo 0
#define PATH_INIMIGO_1 "assets/inimigos/fase1/inimigo2.png" // Caminho para o sprite do inimigo 1
#define PATH_INIMIGO_2 "assets/inimigos/fase2/inimigo3.png" // Caminho para o sprite do inimigo 2
#define PATH_INIMIGO_3 "assets/inimigos/fase2/inimigo4.png" // Caminho para o sprite do inimigo 3

#define QUADRADO_SPRITE_INIMIGO_0 100 // Tamanho do quadro do sprite do inimigo 0
#define QUADRADO_SPRITE_INIMIGO_1 110 // Tamanho do quadro do sprite do inimigo 1
#define QUADRADO_SPRITE_INIMIGO_2 110 // Tamanho do quadro do sprite do inimigo 2
#define QUADRADO_SPRITE_INIMIGO_3 118 // Tamanho do quadro do sprite do inimigo 3

#define COLUNAS_SPRITE_INIMIGO_0 5 // Número de colunas do sprite do inimigo 0
#define COLUNAS_SPRITE_INIMIGO_1 4 // Número de colunas do sprite do inimigo 1
#define COLUNAS_SPRITE_INIMIGO_2 4 // Número de colunas do sprite do inimigo 2
#define COLUNAS_SPRITE_INIMIGO_3 6 // Número de colunas do sprite do inimigo 3

#define ATIRA 1           // Atira
#define NAO_ATIRA 0       // Não atira
#define CONTADOR_ZERADO 0 // Contador zerado

#define HP_INIMIGO_0 2 // Vida do inimigo 0
#define HP_INIMIGO_1 1 // Vida do inimigo 1
#define HP_INIMIGO_2 2 // Vida do inimigo 2
#define HP_INIMIGO_3 1 // Vida do inimigo 3

#define QNTD_INIM_TIPO_0 10 // Quantidade de inimigos do tipo 0
#define QNTD_INIM_TIPO_1 10 // Quantidade de inimigos do tipo 1
#define QNTD_INIM_TIPO_2 10 // Quantidade de inimigos do tipo 2
#define QNTD_INIM_TIPO_3 10 // Quantidade de inimigos do tipo 3

// Intervalo de criação de inimigos na fase 1 e 2
// rand() % MIN_INTERVALO_FASE01 + MAX_INTERVALO_FASE01;
#define MIN_INTERVALO_FASE01 150 // Intervalo mínimo entre a criação de inimigos na fase 1
#define MAX_INTERVALO_FASE01 100 // Intervalo máximo entre a criação de inimigos na fase 1
#define MIN_INTERVALO_FASE02 150 // Intervalo mínimo entre a criação de inimigos na fase 2
#define MAX_INTERVALO_FASE02 200 // Intervalo máximo entre a criação de inimigos na fase 2

/*-------------------------------------------------------------------*/
/* ESTRUTURAS */

// Estrutura para informações do sprite do inimigo
typedef struct
{
    int largura;            // Largura do quadro do sprite
    int altura;             // Altura do quadro do sprite
    int num_frames;         // Número total de colunas no sprite sheet
    ALLEGRO_BITMAP *sprite; // Imagem do sprite
} inimigo_sprite;

// Estrutura para o inimigo
typedef struct inimigo
{
    unsigned char tam_lateral;      // Tamanho da lateral de um inimigo
    unsigned char face;             // A face principal do inimigo, algo como a sua "frente"
    unsigned char hp;               // Quantidade de vida do inimigo, em unidades
    unsigned short x;               // Posição X do centro do inimigo
    unsigned short y;               // Posição Y do centro do inimigo
    unsigned short tipo;            // Tipo de inimigo (diferencia os 4 inimigos)
    unsigned int frame_atual;       // Quadro atual (índice no sprite)
    unsigned int contador_animacao; // Contador para controlar a animação do inimigo
    int pode_atirar;                // Para determinar se o inimigo pode atirar (1) ou não (0)
    arma *arma;                     // Elemento para realizar disparos no jogo
    inimigo_sprite *sprite_info;    // Informações sobre o sprite do inimigo
    struct inimigo *proximo;        // Ponteiro para o próximo inimigo na lista encadeada
} inimigo;

/*-------------------------------------------------------------------*/
/* PROTÓTIPOS DE FUNÇÕES DO INIMIGO */

// Função de criação de um inimigo
inimigo *criar_inimigo(unsigned char side, unsigned char face, short x, unsigned short y, unsigned short type, unsigned short max_x, unsigned short max_y);

// Função de movimentação do inimigo
void mover_inimigo(inimigo *elemento, unsigned char steps, unsigned char *trajetoria, unsigned short max_x, unsigned short max_y);

// Função de desenho do inimigo
void desenhar_inimigo(inimigo *element);

// Função de atualização da animação do inimigo
void atualizar_animacao_inimigo(inimigo *elemento, unsigned int delay);

// Função para adicionar um inimigo à lista
void adicionar_inimigo_lista(inimigo **lista, unsigned char sprite, unsigned short tipo);

// Funções de atualização da criação de inimigos
void atualizar_criacao_inimigo_fase1(inimigo **lista);
void atualizar_criacao_inimigo_fase2(inimigo **lista);

// Função de disparo do inimigo
void inimigo_atira(inimigo *element);

// Função de destruição do inimigo
void destroi_inimigo(inimigo *element);

#endif // __INIMIGOS__
