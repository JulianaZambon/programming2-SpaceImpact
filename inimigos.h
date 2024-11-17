#ifndef __INIMIGOS__ // Guardas de inclusão
#define __INIMIGOS__ // Guardas de inclusão

#include <allegro5/allegro.h> // Inclusão necessária para usar ALLEGRO_BITMAP
#include "arma.h"             // Inclusão necessária para usar a estrutura arma

#define NUM_INIMIGOS 4

typedef struct
{
    unsigned char side;           // Tamanho da lateral de um inimigo
    unsigned char face;           // A face principal do inimigo, algo como a sua "frente"
    unsigned char hp;             // Quantidade de vida do inimigo, em unidades
    unsigned short x;             // Posição X do centro do inimigo
    unsigned short y;             // Posição Y do centro do inimigo                        
    int type;                     // Tipo de inimigo (diferencia os 4 inimigos)
    ALLEGRO_BITMAP *enemy_sprite; // Sprite do inimigo
    int can_shoot;                // Para determinar se o inimigo pode atirar
    arma *arma;                   // Elemento para realizar disparos no jogo
} enemy;

// função de criação de um inimigo
enemy *enemy_create(unsigned char side, unsigned char face, short x, unsigned short y, unsigned short max_x, unsigned short max_y);
// função de movimentação do inimigo
void enemy_move(enemy *element, unsigned char steps, unsigned char trajectory, unsigned short max_x, unsigned short max_y);
// função de desenho do inimigo
void enemy_draw(enemy *element);	  
// funcao de disparo do inimigo
void enemy_shot(enemy *element);
// função de destruição do inimigo
void enemy_destroy(enemy *element); 

#endif // Guardas de inclusão
