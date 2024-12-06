#ifndef __CHEFES__ // Guardas de inclusão
#define __CHEFES__ // Guardas de inclusão

#include <allegro5/allegro.h> // Inclusão necessária para usar ALLEGRO_BITMAP

// Inclusões de bibliotecas locais
#include "arma.h"

/*-----------------------------------------------------------------------------------------*/
/* DEFINIÇÕES */

#define NUM_CHEFES 2            // Número de chefes
#define ANIMATION_DELAY_CHEFE 3 // Velocidade da animação do chefe (quanto maior, mais lento)

#define CHEFE0_STEP 2 // Número de passos do chefe
#define CHEFE1_STEP 2 // Número de passos do chefe

#define PATH_CHEFE_0 "assets/chefes/fase1/chefe1.png" // Caminho para o sprite do chefe 0
#define PATH_CHEFE_1 "assets/chefes/fase2/chefe2.png" // Caminho para o sprite do chefe 1
#define QUADRADO_SPRITE_SHEET 250                     // Tamanho do quadro no sprite sheet

#define COLUNAS_SPRITE_SHEET_CHEFE_0 11 // Número de colunas no sprite do chefe 0
#define SPRITE_SHEET_CHEFE_0 22         // Número total de quadros no sprite

#define COLUNAS_SPRITE_SHEET_CHEFE_1 8 // Número de colunas no sprite do chefe 1
#define SPRITE_SHEET_CHEFE_1 16        // Número total de quadros no sprite

#define HP_CHEFE_0 5 // Vida do chefe 0
#define HP_CHEFE_1 60 // Vida do chefe 1

#define ARMA1_COOLDOWN_CHEFE 40  // Tempo de cooldown da arma do chefe (quanto maior, mais lento)
#define ARMA2_COOLDOWN_CHEFE 140 // Tempo de cooldown da segunda arma do chefe (quanto maior, mais lento)

/*-----------------------------------------------------------------------------------------*/
/* ESTRUTURAS */

// Estrutura para o sprite do chefe
typedef struct
{
    int largura;            // Largura do quadro do sprite
    int altura;             // Altura do quadro do sprite
    int num_frames;         // Número total de colunas no sprite
    int num_frames_total;   // Número total de quadros no sprite
    ALLEGRO_BITMAP *sprite; // Imagem do sprite
} chefe_sprite;

// Estrutura para o chefe
typedef struct
{
    unsigned char tam_lateral;    // Tamanho da lateral de um chefe
    unsigned char face;           // A face principal do chefe, algo como a sua "frente"
    unsigned char hp;             // Quantidade de vida do chefe (HP maior que dos inimigos)
    unsigned short x;             // Posição X do centro do chefe
    unsigned short y;             // Posição Y do centro do chefe
    int tipo;                     // Tipo de chefe (diferencia os 2 chefes)
    unsigned int animation_counter; // Contador de animação
    arma *arma1;                  // Elemento para realizar disparos no jogo
    arma *arma2;                  // Elemento para realizar disparos no jogo
    unsigned short frame_atual;   // Quadro atual (índice no sprite sheet)
    ALLEGRO_BITMAP *chefe_sprite; // Sprite do chefe
    chefe_sprite *sprite_info;    // Informações sobre o sprite do chefe
} chefe;

/*-----------------------------------------------------------------------------------------*/
/* PROTÓTIPOS DE FUNÇÕES */

// Função de criação de um chefe
chefe *criar_chefe(unsigned char side, unsigned char face, short x, unsigned short y, unsigned short type, unsigned short max_x, unsigned short max_y);
// Função de movimentação do chefe
void mover_chefe(chefe *element, unsigned char steps, unsigned char trajetoria, unsigned short max_x, unsigned short max_y);
// Função de desenho do chefe
void desenhar_chefe(chefe *element);
// Função de atualização da animação do chefe
void atualizar_animacao_chefe(chefe *elemento, unsigned int *animation_counter, unsigned int delay);
// Função de disparo do chefe
void chefe_atira(chefe *element);
// Função de destruição do chefe
void destroi_chefe(chefe *element);

#endif // Guardas de inclusão
