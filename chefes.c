#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>

#include "chefes.h"

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
        new_boss->boss_sprite = al_load_bitmap("assets/chefes/fase1/.png");
        break;
    case 1:
        new_boss->boss_sprite = al_load_bitmap("assets/chefes/fase2/.png");
        break;
    default:
        break;
    }

    return new_boss;
}
void boss_move(boss *element, unsigned char steps, unsigned char trajectory, unsigned short max_x, unsigned short max_y)
{
}
void boss_draw(boss *element)
{
}
void boss_shot(boss *element)
{
}
void boss_destroy(boss *element)
{
}
