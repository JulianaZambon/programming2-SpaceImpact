#ifndef __INIMIGOS__ // Guardas de inclusão
#define __INIMIGOS__ // Guardas de inclusão

#include <allegro5/allegro.h> // Inclusão necessária para usar ALLEGRO_BITMAP

// Inclusões de bibliotecas locais
#include "arma.h"             

/*-----------------------------------------------------------------------------------------*/
/* DEFINIÇÕES */
#define NUM_INIMIGOS 4 // Número de tipos de inimigos
#define ANIMATION_DELAY_INIMIGO 3 // Velocidade da animação (quanto maior, mais lento)

// Definições de inimigos
#define INIMIGO_STEP 5
#define INIMIGO1_STEP 3
#define INIMIGO2_STEP 1
#define INIMIGO3_STEP 4

// Paths dos sprites dos inimigos
#define PATH_INIMIGO_0 "assets/inimigos/fase1/enemy2.png"
#define PATH_INIMIGO_1 "assets/inimigos/fase1/enemy4.png"
#define PATH_INIMIGO_2 "assets/inimigos/fase2/enemy.png"
#define PATH_INIMIGO_3 "assets/inimigos/fase2/enemy3.png"

/*-----------------------------------------------------------------------------------------*/
/* ESTRUTURAS */

// Estrutura para informações do sprite do inimigo
typedef struct
{
    int largura;            // Largura do quadro do sprite
    int altura;             // Altura do quadro do sprite
    int num_frames;         // Número total de quadros no sprite
    ALLEGRO_BITMAP *sprite; // Imagem do sprite
} inimigo_sprite;

// Estrutura para o inimigo
typedef struct
{
    unsigned char tam_lateral;   // Tamanho da lateral de um inimigo
    unsigned char face;          // A face principal do inimigo, algo como a sua "frente"
    unsigned char hp;            // Quantidade de vida do inimigo, em unidades
    unsigned short x;            // Posição X do centro do inimigo
    unsigned short y;            // Posição Y do centro do inimigo
    unsigned short tipo;         // Tipo de inimigo (diferencia os 4 inimigos)
    unsigned int frame_atual;    // Quadro atual (índice no sprite)
    int pode_atirar;             // Para determinar se o inimigo pode atirar
    arma *arma;                  // Elemento para realizar disparos no jogo
    inimigo_sprite *sprite_info; // Informações sobre o sprite do inimigo
} inimigo;

// Estrutura para controlar a onda de inimigos
// typedef struct
// {
//     unsigned short num_inimigos;           // Número de inimigos na onda
//     unsigned short max_x;                  // Largura máxima da tela
//     unsigned short max_y;                  // Altura máxima da tela
//     inimigo *lista_inimigos[MAX_INIMIGOS]; // Lista de inimigos na onda
//     double proximo_tempo;                  // Próximo tempo de aparição de inimigo
// } OndaInimigos;

/*-----------------------------------------------------------------------------------------*/
/* /* PROTÓTIPOS DE FUNÇÕES DO INIMIGO */

// Função de criação de um inimigo
inimigo *criar_inimigo(unsigned char side, unsigned char face, short x, unsigned short y, unsigned short type, unsigned short max_x, unsigned short max_y);

// Função de movimentação do inimigo
void mover_inimigo(inimigo *elemento, unsigned char steps, unsigned char *trajetoria, unsigned short max_x, unsigned short max_y);

// Função de desenho do inimigo
void desenhar_inimigo(inimigo *element);

// Função de atualização da animação do inimigo
void atualizar_animacao_inimigo(inimigo *elemento, unsigned int *animation_counter, unsigned int delay);

// Função de disparo do inimigo
void inimigo_atira(inimigo *element);

// Função de destruição do inimigo
void destroi_inimigo(inimigo *element);

/*-----------------------------------------------------------------------------------------*/
/* FUNÇÕES ONDA DE INIMIGOS */

// // Função de criação de uma nova onda de inimigos
// OndaInimigos *criar_onda_inimigos(unsigned short max_x, unsigned short max_y);

// // Função de desenho da onda de inimigos
// void desenhar_onda_inimigos(OndaInimigos *onda);

// // Função de atualização da onda de inimigos
// void atualizar_onda_inimigos(OndaInimigos *onda);

// // Função de atualização da animação dos inimigos na onda
// void atualizar_animacao_onda_inimigos(OndaInimigos *onda, unsigned int *animation_counter, unsigned int delay);

// // Função de destruição da onda de inimigos
// void destruir_onda_inimigos(OndaInimigos *onda);

#endif // __INIMIGOS__
