#ifndef __FASES__ // Guardas de inclusão
#define __FASES__ // Guardas de inclusão

#include <allegro5/allegro.h> 

// Inclusões de bibliotecas locais
#include "inimigos.h"
#include "chefes.h"
#include "jogador.h"
#include "background.h"
#include "configuracoes.h"

/*-------------------------------------------------------------------*/
/* DEFINIÇÕES */
#define PATH_CENARIO_FASE1 "assets/cenarios/cenario3.png"
#define PATH_CENARIO_FASE2 "assets/cenarios/cenario4.png"

/*-------------------------------------------------------------------*/
/* VARIÁVEIS EXTERNAS */

extern unsigned short fase_atual; // Fase atual do jogo
extern unsigned int score;        // Variável de pontuação
extern unsigned char game_over;   // Flag que sinaliza o fim do jogo
extern bool venceu_fase;          // Flag de vitória

/*-------------------------------------------------------------------*/
/* PROTÓTIPOS DE FUNÇÕES AUXILIARES */

// Função que verifica se um projétil acertou um inimigo, a cada acerto o jogador ganha 10 pontos
unsigned char verifica_acerto_no_inimigo(jogador *killer, inimigo *victim, unsigned int *score);

// Função que verifica se um projétil acertou um chefe, a cada acerto o jogador ganha 10 pontos
unsigned char verifica_acerto_no_chefe(jogador *killer, chefe *victim, unsigned int *score);

// Função que verifica se um projétil inimigo acertou o jogador, cada acerto reduz 1 ponto de vida
unsigned char verifica_acerto_no_jogador(inimigo **killer, jogador *victim);

// Função que verifica se um projétil de chefe acertou o jogador, cada acerto reduz 2 pontos de vida
unsigned char verifica_acerto_do_chefe_no_jogador(chefe *killer, jogador *victim);

// Função que contem a lógica de ataque especial do jogador
void logica_ataque_especial_fase1(jogador *jogador, simbolo_ataque_especial **simbolo_ptr, unsigned int delay,
                            unsigned short max_x, unsigned short max_y);

void logica_ataque_especial_fase2(jogador *jogador, simbolo_ataque_especial **simbolo_ptr, unsigned int delay,
                            unsigned short max_x, unsigned short max_y);

/*-------------------------------------------------------------------*/
/* PROTÓTIPOS DE FUNÇÕES PRINCIPAIS */

// Funções para inicialização, atualização e finalização de cada fase
void inicializa_fase(ALLEGRO_BITMAP **background, jogador **jogador_1, inimigo **lista_inimigos_fase1,
                     inimigo **lista_inimigos_fase2, chefe **chefe_1, chefe **chefe_2, int fase);

void atualiza_fase(ALLEGRO_BITMAP *background, jogador *jogador_1, inimigo **lista_inimigos_fase1,
                   inimigo **lista_inimigos_fase2, chefe *chefe_1, chefe *chefe_2, int fase);

void finaliza_fase(ALLEGRO_BITMAP *background, jogador *jogador_1, inimigo *lista_inimigos_fase1,
                   inimigo *lista_inimigos_fase2, chefe *chefe_1, chefe *chefe_2, int fase);

#endif
