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

// função de criação do loop do background
void draw_moving_background(ALLEGRO_BITMAP *background, float *offset, float speed, int screen_width);
// função de criação da fase 1
fase *criar_fase1();
// função de criação da fase 2
fase *criar_fase2();
// função de destruição de uma fase
void fase_destroy(fase *element);

#endif
