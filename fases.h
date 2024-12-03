#ifndef __FASES__ // Guardas de inclusão
#define __FASES__ // Guardas de inclusão

#include <allegro5/allegro.h> // Inclusão necessária para usar ALLEGRO_BITMAP

// Inclusões de bibliotecas locais
#include "inimigos.h"
#include "chefes.h"
#include "jogador.h"
#include "background.h"
#include "configuracoes.h"

/*-----------------------------------------------------------------------------------------*/
/* DEFINIÇÕES */
#define PATH_CENARIO_FASE1 "assets/cenarios/cenario3.png"
#define PATH_CENARIO_FASE2 "assets/cenarios/cenario4.png"

/*-----------------------------------------------------------------------------------------*/
/* ESTRUTURAS */

// Estrutura que representa uma fase do jogo
typedef struct
{
    inimigo inimigos[NUM_INIMIGOS]; // Vetor de inimigos
    chefe chefes[NUM_CHEFES];       // Vetor de chefes
    ALLEGRO_BITMAP *background;     // Imagem de fundo da fase
} fase;

/*-----------------------------------------------------------------------------------------*/
/* VARIÁVEIS EXTERNAS */

extern unsigned short fase_atual; // Variável externa para a fase atual
extern unsigned char jk;          // Controle de dano do jogador pelo inimigo
extern unsigned char ik;          // Controle de dano causado pelo jogador ao inimigo
extern unsigned char ck;          // Controle de dano causado ao chefe
extern unsigned char jk_chefe;    // Controle de dano do jogador pelo chefe
extern unsigned int score;        // Variável de pontuação

/*-----------------------------------------------------------------------------------------*/
/* PROTÓTIPO DE FUNÇÕES AUXILIARES */

// Implementação da função que verifica se um projétil acertou um inimigo, a cada acerto o jogador ganha 10 pontos
unsigned char check_kill_inimigo(jogador *killer, inimigo *victim, unsigned int *score);

// Implementação da função que verifica se um projétil acertou um chefe, a cada acerto o jogador ganha 10 pontos
unsigned char check_kill_chefe(jogador *killer, chefe *victim, unsigned int *score);

// Implementação da função que verifica se um projetil inimigo acertou o jogador, cada acerto reduz 1 ponto de vida
unsigned char check_player(inimigo **killer, jogador *victim);

// Implementação da função que verifica se um projétil de chefe acertou o jogador, cada acerto reduz 2 pontos de vida
unsigned char check_player_chefe(chefe *killer, jogador *victim);

/*-----------------------------------------------------------------------------------------*/
/* PROTÓTIPOS DE FUNÇÕES */

// Funções de inicialização, atualização e finalização de cada fase
void inicializa_fase(ALLEGRO_BITMAP **background, jogador **jogador_1, inimigo **lista_inimigos, chefe **chefe_1,
                chefe **chefe_2, int fase);
void atualiza_fase(ALLEGRO_BITMAP *background, jogador *jogador_1, inimigo **lista_inimigos, chefe *chefe_1,
                chefe *chefe_2, int fase);
void finaliza_fase(ALLEGRO_BITMAP *background, jogador *jogador_1, inimigo *lista_inimigos, chefe *chefe_1,
                chefe *chefe_2, int fase);

#endif
