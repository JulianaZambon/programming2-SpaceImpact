#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>

#include "fases.h"
#include "inimigos.h"
#include "chefes.h"
#include "jogador.h"
#include "arma.h"
#include "configuracoes.h"

// 02 inimigos
// 01 chefe
fase *criar_fase1()
{
    fase *fase1 = (fase *)malloc(sizeof(fase));
    if (!fase1)
        return NULL;

    // Carrega a imagem de fundo
    fase1->background = al_load_bitmap("assets/cenarios/cenario1.png");
    if (!fase1->background)
    {
        al_destroy_bitmap(fase1->background);
        free(fase1);
        return NULL;
    }

    // Cria os inimigos
    fase1->enemies[0] = *enemy_create(20, 60, 80, Y_SCREEN / 2, 0, X_SCREEN, Y_SCREEN);
    fase1->enemies[1] = *enemy_create(20, 60, X_SCREEN / 4, Y_SCREEN / 2, 1, X_SCREEN, Y_SCREEN);

    // Cria o chefe
    fase1->bosses[0] = *boss_create(270, 270, X_SCREEN - 100, Y_SCREEN / 2, X_SCREEN, Y_SCREEN);

    return fase1;
}

void fase_destroy(fase *element)
{
    if (element)
    {
        if (element->background)
            al_destroy_bitmap(element->background);
        free(element);
    }
}