#ifndef __JOGADOR__ // Guardas de inclusão
#define __JOGADOR__ // Guardas de inclusão

#include <allegro5/allegro.h> // Inclusão necessária para usar ALLEGRO_BITMAP
#include "joystick.h"		  // Inclusão necessária para usar a estrutura joystick

// Quantidade de pixels que um jogador se move por passo
#define PLAYER_STEP 20 

typedef struct
{
	unsigned char side;			  // Tamanho da lateral de um jogador
	unsigned short x;			  // Posição X do centro do jogador
	unsigned short y;			  // Posição Y do centro do jogador
	ALLEGRO_BITMAP *sprite;		  // Adicionado: ponteiro para o sprite do jogador
	unsigned short current_frame; // Quadro atual (índice no sprite sheet)
	joystick *control;			  // Elemento de controle da nave no jogo
} player;

// Protótipos das funções relacionadas ao jogador
player *player_create(unsigned char side, unsigned short x, unsigned short y, unsigned short max_x, unsigned short max_y);
void player_move(player *element, unsigned char steps, unsigned char trajectory, unsigned short max_x, unsigned short max_y);
void player_draw(player *element);	  // Protótipo da função de desenho do sprite do jogador
void player_update(player *element);  // Protótipo da função de atualização do sprite do jogador
void player_destroy(player *element); // Protótipo da função de destruição de um jogador, agora também liberando o sprite

#endif // Guardas de inclusão
