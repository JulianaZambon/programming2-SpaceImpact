#ifndef __JOGADOR__ // Guardas de inclusão
#define __JOGADOR__ // Guardas de inclusão

#include <allegro5/allegro.h> // Inclusão necessária para usar ALLEGRO_BITMAP

#include "joystick.h" // Inclusão necessária para usar a estrutura joystick
#include "arma.h"	  // Inclusão necessária para usar a estrutura arma

// Quantidade de pixels que um jogador se move por passo
#define JOGADOR_STEP 20

typedef struct
{
	unsigned char tam_lateral;	// Tamanho da lateral de um jogador
	unsigned char face;			// A face principal do jogador, algo como a sua "frente"
	unsigned char hp;			// Quantidade de vida do jogador, em unidades
	unsigned short x;			// Posição X do centro do jogador
	unsigned short y;			// Posição Y do centro do jogador
	unsigned short frame_atual; // Quadro atual (índice no sprite sheet)
	joystick *controle;			// elemento de controle da nave no jogo
	arma *arma;					// elemento para realizar disparos no jogo
	ALLEGRO_BITMAP *sprite;		// ponteiro para o sprite do jogador

} jogador;

// função de criação de um jogador
jogador *criar_jogador(unsigned char side, unsigned char face, short x, unsigned short y, unsigned short max_x, unsigned short max_y);
// função de movimentação do jogador
void mover_jogador(jogador *elemento, char steps, unsigned char trajetoria, unsigned short max_x, unsigned short max_y);
// função de desenho do jogador
void desenhar_jogador(jogador *elemento);
// função de atualização da animação do jogador
void atualizar_animacao_jogador(jogador *elemento, unsigned int *animation_counter, unsigned int delay);
// funcao de disparo do jogador
void jogador_atira(jogador *elemento);
// função de destruição do jogador
void destroi_jogador(jogador *elemento);

#endif // Guardas de inclusão
