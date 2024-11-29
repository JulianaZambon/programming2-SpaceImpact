#ifndef __INIMIGOS__ // Guardas de inclusão
#define __INIMIGOS__ // Guardas de inclusão

#include <allegro5/allegro.h> // Inclusão necessária para usar ALLEGRO_BITMAP
#include "arma.h"             // Inclusão necessária para usar a estrutura arma

/*-----------------------------------------------------------------------------------------*/

#define ANIMATION_DELAY_INIMIGO 3  // velocidade da animação (quanto maior, mais lento)

#define INIMIGO_STEP 5
#define INIMIGO1_STEP 3
#define INIMIGO2_STEP 1
#define INIMIGO3_STEP 4

#define NUM_INIMIGOS 4 // Número de tipos de inimigos

#define PATH_INIMIGO_0 "assets/inimigos/fase1/enemy2.png"
#define PATH_INIMIGO_1 "assets/inimigos/fase1/enemy4.png"
#define PATH_INIMIGO_2 "assets/inimigos/fase2/enemy.png"
#define PATH_INIMIGO_3 "assets/inimigos/fase2/enemy3.png"

#define NUM_INIMIGOS_ORDA 15 // Número de inimigos em uma onda

/*-----------------------------------------------------------------------------------------*/

typedef struct
{
    int largura;            // Largura do quadro do sprite
    int altura;             // Altura do quadro do sprite
    int num_frames;         // Número total de quadros no sprite
    ALLEGRO_BITMAP *sprite; // Imagem do sprite
} inimigo_sprite;

typedef struct
{
    unsigned char tam_lateral;   // Tamanho da lateral de um inimigo
    unsigned char face;          // A face principal do inimigo, algo como a sua "frente"
    unsigned char hp;            // Quantidade de vida do inimigo, em unidades
    unsigned short x;            // Posição X do centro do inimigo
    unsigned short y;            // Posição Y do centro do inimigo
    unsigned short tipo;         // Tipo de inimigo (diferencia os 4 inimigos)
    unsigned short frame_atual;  // Quadro atual (índice no sprite)
    int pode_atirar;             // Para determinar se o inimigo pode atirar
    arma *arma;                  // Elemento para realizar disparos no jogo
    inimigo_sprite *sprite_info; // Informações sobre o sprite do inimigo
} inimigo;

// função de criação de um inimigo
inimigo *criar_inimigo(unsigned char side, unsigned char face, short x, unsigned short y, unsigned short type, unsigned short max_x, unsigned short max_y);
// função de movimentação do inimigo
void mover_inimigo(inimigo *elemento, unsigned char steps, unsigned char *trajetoria, unsigned short max_x, unsigned short max_y);
// função de desenho do inimigo
void desenhar_inimigo(inimigo *element);
// função de atualização da animação do inimigo
void atualizar_animacao_inimigo(inimigo *elemento, unsigned int *animation_counter, unsigned int delay);
// função de criação da onda de inimigos
void criar_onda_inimigos(inimigo **lista_inimigos, unsigned short max_x, unsigned short max_y, unsigned short tipo);
// função de desenho da onda de inimigos
void desenhar_onda_inimigos(inimigo **lista_inimigos, unsigned short max_x, unsigned short max_y);
// função de movimentação da onda de inimigos
void atualizar_onda_inimigos(inimigo **lista_inimigos, unsigned short max_x, unsigned short max_y, int *animation_counter);
// funcao de disparo do inimigo
void inimigo_atira(inimigo *element);
// função de destruição do inimigo
void destroi_inimigo(inimigo *element);

#endif // Guardas de inclusão
