#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>

#include "chefes.h"

// Define o passo de movimentação dos chefes
// fase 1
#define BOSS_STEP 15
#define BOSS1_STEP 15

boss *boss_create(unsigned char side, unsigned char face, short x, unsigned short y, unsigned short max_x, unsigned short max_y)
{
    if ((x - side / 2 < 0) || (x + side / 2 > max_x) || (y - side / 2 < 0) || (y + side / 2 > max_y))
        return NULL; // Verifica se a posição inicial é válida

    boss *new_boss = (boss *)malloc(sizeof(*new_boss)); // Aloca memória na heap para um novo chefe
    if (!new_boss)
        return NULL;

    new_boss->side = side;          // Insere o tamanho do lado do chefe
    new_boss->face = face;          // Insere a indicação da face principal do chefe
    new_boss->x = x;                // Insere a posição inicial central de X
    new_boss->y = y;                // Insere a posição inicial central de Y
    new_boss->arma = arma_create(); // Insere o elemento de disparos do chefe

    // Carrega o sprite para o chefe
    switch (new_boss->type)
    {
    case 0:
        new_boss->boss_sprite = al_load_bitmap("assets/chefes/fase1/boss3.png");
        break;
    case 1:
        new_boss->boss_sprite = al_load_bitmap("assets/chefes/fase2/boss2.png");
        break;
    default:
        break;
    }

    if (!new_boss->boss_sprite)
    {
        al_destroy_bitmap(new_boss->boss_sprite); // Libera a memória alocada para o sprite
        arma_destroy(new_boss->arma);             // Libera a memória alocada para a arma
        free(new_boss);                           // Libera a memória alocada para o chefe
        return NULL;
    }

    return new_boss;
}
void boss_move(boss *element, unsigned char steps, unsigned char trajectory, unsigned short max_x, unsigned short max_y)
{
    if (!element)
        return;

    switch (element->type)
    {
    case 0: // Tipo 0 de chefe
        // Verifica movimento para a esquerda
        if ((element->x - steps * BOSS_STEP) - element->side / 2 >= 0)
            element->x -= steps * BOSS_STEP;
        break;

    case 1: // Tipo 1 de chefe
        // Verifica movimento para a esquerda
        if ((element->x - steps * BOSS1_STEP) - element->side / 2 >= 0)
            element->x -= steps * BOSS1_STEP;
        break;
    default:
        break;
    }
}

void boss_draw(boss *element)
{
    // FASE 01
    int sprite_width = 270;  // Largura do quadro no sprite sheet (ajustar caso nao fique harmonico)
    int sprite_height = 270; // Altura do quadro no sprite sheet

    // Calcula a posição do quadro no sprite sheet
    int frame_x = (element->current_frame % 17) * sprite_width;  // Coluna
    int frame_y = (element->current_frame / 17) * sprite_height; // Linha

    // FASE 02
    int sprite1_width = 250;
    int sprite1_height = 250;

    int frame1_x = (element->current_frame % 8) * sprite_width;
    int frame1_y = (element->current_frame / 8) * sprite_height;

    switch (element->type)
    {
    case 0:
        al_draw_bitmap_region(element->boss_sprite, frame_x, frame_y, sprite_width, sprite_height,
                              element->x - sprite_width / 2, element->y - sprite_height / 2, 0);
        break;
    case 1:
        al_draw_bitmap_region(element->boss_sprite, frame1_x, frame1_y, sprite1_width, sprite1_height,
                              element->x - sprite1_width / 2, element->y - sprite1_height / 2, 0);
        break;
    default:
        break;
    }
}

void boss_shot(boss *element)
{
    if (!element)
        return;

    arma_shot(element->x, element->y, element->face, element->arma);
}

void boss_destroy(boss *element)
{
    if (element)
    {
        if (element->boss_sprite)
            al_destroy_bitmap(element->boss_sprite);
        arma_destroy(element->arma);
        free(element);
    }
}
