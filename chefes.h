#ifndef __CHEFES__ // Guardas de inclusão
#define __CHEFES__ // Guardas de inclusão

#include <allegro5/allegro.h> // Inclusão necessária para usar ALLEGRO_BITMAP
#include "arma.h"             // Inclusão necessária para usar a estrutura arma

#define NUM_BOSSES 2

typedef struct
{
    unsigned char side;           // Tamanho da lateral de um chefe
    unsigned char face;           // A face principal do chefe, algo como a sua "frente"
    unsigned char hp;             // Quantidade de vida do chefe (HP maior que dos inimigos)
    unsigned short x;             // Posição X do centro do chefe
    unsigned short y;             // Posição Y do centro do chefe
    int type;                     // Tipo de chefe (diferencia os 2 chefes)
    ALLEGRO_BITMAP *boss_sprite;  // Sprite do chefe
    unsigned short current_frame; // Quadro atual (índice no sprite sheet)
    arma *arma;                   // Elemento para realizar disparos no jogo
} boss;

// função de criação de um chefe
boss *boss_create(unsigned char side, unsigned char face, short x, unsigned short y, unsigned short max_x, unsigned short max_y);
// função de movimentação do chefe
void boss_move(boss *element, unsigned char steps, unsigned char trajectory, unsigned short max_x, unsigned short max_y);
// função de desenho do chefe
void boss_draw(boss *element);
// funcao de disparo do chefe
void boss_shot(boss *element);
// função de destruição do chefe
void boss_destroy(boss *element);

#endif // Guardas de inclusão
