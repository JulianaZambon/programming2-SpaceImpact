#ifndef __FASES__ // Guardas de inclusão
#define __FASES__ // Guardas de inclusão

#include <allegro5/allegro.h> // Inclusão necessária para usar ALLEGRO_BITMAP
#include "inimigos.h"
#include "chefes.h"
#include "jogador.h"

typedef struct
{
    enemy enemies[NUM_INIMIGOS]; // Vetor de inimigos
    boss bosses[NUM_BOSSES];     // Vetor de chefes
    ALLEGRO_BITMAP *background;  // Imagem de fundo
} fase;

// função de criação da fase 1
fase *criar_fase1();
// função de criação da fase 2
fase *criar_fase2();

// Função de criação do loop do background
void draw_moving_background(ALLEGRO_BITMAP *background, float *offset, float speed, int screen_width);

// Função para verificar a colisão entre o jogador e os inimigos
unsigned char collision_2D(player *player_1, enemy *enemy_1, enemy *enemy_2, boss *boss_1);

// função que verifica se um projétil acertou um inimigo ou chefe
unsigned char check_kill(player *killer, enemy *victim);

// função que atualiza o posicionamento de projéteis conforme o movimento dos mesmos
void update_projeteis(player *player_1);

// Função para atualizar a posição do jogador conforme os comandos do controle e conforme colisões
void update_position(player *player_1, enemy *enemy_1, enemy *enemy_2, boss *boss_1);

// função de destruição de uma fase
void fase_destroy(fase *element);

#endif