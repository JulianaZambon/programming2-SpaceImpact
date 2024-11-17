#ifndef __JOGADOR__ // Guardas de inclusão
#define __JOGADOR__ // Guardas de inclusão

#include <allegro5/allegro.h> // Inclusão necessária para usar ALLEGRO_BITMAP
#include "joystick.h"		  // Inclusão necessária para usar a estrutura joystick
#include "arma.h"			  // Inclusão necessária para usar a estrutura arma

// Quantidade de pixels que um jogador se move por passo
#define PLAYER_STEP 20

typedef struct
{
	unsigned char side;			  // Tamanho da lateral de um jogador
	unsigned char face;			  // A face principal do jogador, algo como a sua "frente"
	unsigned char hp;			  // Quantidade de vida do jogador, em unidades 
	unsigned short x;			  // Posição X do centro do jogador
	unsigned short y;			  // Posição Y do centro do jogador
	ALLEGRO_BITMAP *sprite;		  // Adicionado: ponteiro para o sprite do jogador
	unsigned short current_frame; // Quadro atual (índice no sprite sheet)
	joystick *control;			  // Elemento de controle da nave no jogo
	arma *arma;					  // Elemento para realizar disparos no jogo
} player;

// função de criação de um jogador
player *player_create(unsigned char side, unsigned char face, short x, unsigned short y, unsigned short max_x, unsigned short max_y);
// função de movimentação do jogador
void player_move(player *element, unsigned char steps, unsigned char trajectory, unsigned short max_x, unsigned short max_y);
// função de desenho do jogador
void player_draw(player *element);	  
// funcao de disparo do jogador
void player_shot(player *element);
// função de destruição do jogador
void player_destroy(player *element); 

#endif // Guardas de inclusão
