#ifndef __CONFIG__ // Guardas de inclusão
#define __CONFIG__ // Guardas de inclusão

#include <allegro5/allegro.h> // Inclusão necessária para usar ALLEGRO_EVENT
#include "jogador.h"          // Inclusão necessária para usar a estrutura jogador

/*-------------------------------------------------------------------*/
/* DEFINIÇÕES */

#define X_SCREEN 1140        // Dimensões da tela
#define Y_SCREEN 640         // Dimensões da tela
#define ESPACO_INTERFACE 100 // Espaço ocupado pela interface superior 

#define Y_SCREEN_MOVIMENTO 520    // Limite de movimento do jogador no eixo Y
#define VELOCIDADE_BACKGROUND 3   // Velocidade do background (quanto maior, mais rápido)
#define VELOCIDADE_TELA_INICIAL 1 // Velocidade da animação da tela inicial (quanto maior, mais rápido)

#define ANIMATION_DELAY_FUNDO 3 // Velocidade da animação do fundo (quanto maior, mais lento)

/*-------------------------------------------------------------------*/
/* PROTÓTIPO DE FUNÇÕES DA MAIN */

void atualiza_posicao(jogador *jogador_1);
void processa_evento_teclado(ALLEGRO_EVENT event, jogador *jogador_1);

#endif
