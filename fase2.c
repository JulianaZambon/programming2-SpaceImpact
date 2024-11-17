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
fase *criar_fase2()
{
    fase *fase2 = (fase *)malloc(sizeof(fase));
    if (!fase2)
        return NULL;

    // Carrega a imagem de fundo
    fase2->background = al_load_bitmap("assets/cenarios/cenario2.png");
    if (!fase2->background)
    {
        al_destroy_bitmap(fase2->background);
        free(fase2);
        return NULL;
    }

    // Cria os inimigos
    fase2->enemies[2] = *enemy_create(20, 60, 80, Y_SCREEN / 2, 2, X_SCREEN, Y_SCREEN);
    fase2->enemies[3] = *enemy_create(20, 60, X_SCREEN / 4, Y_SCREEN / 2, 3, X_SCREEN, Y_SCREEN);

    // Cria o chefe
    fase2->bosses[1] = *boss_create(270, 270, X_SCREEN - 100, Y_SCREEN / 2, X_SCREEN, Y_SCREEN);

    return fase2;
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
