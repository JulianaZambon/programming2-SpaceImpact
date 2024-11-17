#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>

#include "inimigos.h"

enemy *enemy_create(unsigned char side, unsigned char face, short x, unsigned short y, unsigned short max_x, unsigned short max_y)
{
    if ((x - side / 2 < 0) || (x + side / 2 > max_x) || (y - side / 2 < 0) || (y + side / 2 > max_y))
        return NULL; // Verifica se a posição inicial é válida

    enemy *new_enemy = (enemy *)malloc(sizeof(*new_enemy)); // Aloca memória na heap para um novo inimigo
    if (!new_enemy)
        return NULL;

    new_enemy->side = side;          // Insere o tamanho do lado do inimigo
    new_enemy->face = face;          // Insere a indicação da face principal do inimigo
    new_enemy->x = x;                // Insere a posição inicial central de X
    new_enemy->y = y;                // Insere a posição inicial central de Y
    new_enemy->arma = arma_create(); // Insere o elemento de disparos do inimigo

    // Carrega o sprite para o inimigo
    switch (new_enemy->type)
    {
    case 0:
        new_enemy->enemy_sprite = al_load_bitmap("assets/inimigos/fase1/.png");
        break;
    case 1:
        new_enemy->enemy_sprite = al_load_bitmap("assets/inimigos/fase1/.png");
        break;
    case 2:
        new_enemy->enemy_sprite = al_load_bitmap("assets/inimigos/fase2/.png");
        break;
    case 3:
        new_enemy->enemy_sprite = al_load_bitmap("assets/inimigos/fase2/.png");
        break;
    default:
        break;
    }
}
void enemy_move(enemy *element, unsigned char steps, unsigned char trajectory, unsigned short max_x, unsigned short max_y)
{
}
void enemy_draw(enemy *element)
{
}
void enemy_shot(enemy *element)
{
}
void enemy_destroy(enemy *element)
{
}
