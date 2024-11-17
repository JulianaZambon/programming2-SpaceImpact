#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>

#include "inimigos.h"

// Define o passo de movimentação dos inimigos
// fase 1
#define ENEMY_STEP 20
#define ENEMY1_STEP 30
// fase 2
#define ENEMY2_STEP 35
#define ENEMY3_STEP 45

enemy *enemy_create(unsigned char side, unsigned char face, short x, unsigned short y, unsigned short type, unsigned short max_x, unsigned short max_y)
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
    new_enemy->type = type;          // Insere o tipo de inimigo
    new_enemy->arma = arma_create(); // Insere o elemento de disparos do inimigo

    // Carrega o sprite para o inimigo
    switch (new_enemy->type)
    {
    case 0:
        new_enemy->enemy_sprite = al_load_bitmap("assets/inimigos/fase1/sprite-enemy2.png");
        break;
    case 1:
        new_enemy->enemy_sprite = al_load_bitmap("assets/inimigos/fase1/sprite-enemy4.png");
        break;
    case 2:
        new_enemy->enemy_sprite = al_load_bitmap("assets/inimigos/fase2/sprite-enemy.png");
        break;
    case 3:
        new_enemy->enemy_sprite = al_load_bitmap("assets/inimigos/fase2/sprite-enemy3.png");
        break;
    default:
        break;
    }

    if (!new_enemy->enemy_sprite)
    {
        free(new_enemy); // Libera a memória caso o carregamento do sprite falhe
        return NULL;
    }

    return new_enemy;
}

// devem ter algum padrão de movimentação
void enemy_move(enemy *element, unsigned char steps, unsigned char trajectory, unsigned short max_x, unsigned short max_y)
{
    if (!element)
        return;

    switch (element->type)
    {
    case 0: // Tipo 0 de inimigo
        // Padrão de movimentação: mover para a esquerda
        if ((element->x - steps * ENEMY_STEP) - element->side / 2 >= 0)
            element->x = element->x - steps * ENEMY_STEP;
        break;

    case 1: // Tipo 1 de inimigo
        // Padrão de movimentação: mover para a esquerda
        if ((element->x - steps * ENEMY1_STEP) - element->side / 2 >= 0)
            element->x = element->x - steps * ENEMY1_STEP;
        break;

        // FASE 02

    case 2: // Tipo 2 de inimigo
        // Padrão de movimentação: mover para cima e para baixo em direção ao jogador (esquerda)
        if ((element->x - steps * ENEMY2_STEP) - element->side / 2 >= 0)
            element->x = element->x - steps * ENEMY2_STEP;
        if ((element->y - steps * ENEMY2_STEP) - element->side / 2 >= 0)
            element->y = element->y - steps * ENEMY2_STEP;
        break;

    case 3: // Tipo 3 de inimigo
        // Padrão de movimentação: mover para a esquerda
        if ((element->x - steps * ENEMY3_STEP) - element->side / 2 >= 0)
            element->x = element->x - steps * ENEMY3_STEP;
        break;

    default:
        break;
    }
}

void enemy_draw(enemy *element)
{
    if (element && element->enemy_sprite)
    {
        al_draw_bitmap(element->enemy_sprite, element->x - element->side / 2, element->y - element->side / 2, 0);
    }
}

void enemy_shot(enemy *element)
{
    if (element && element->arma)
    {
        arma_shot(element->arma, element->x, element->y, element->face);
    }
}

void enemy_destroy(enemy *element)
{
    if (element)
    {
        al_destroy_bitmap(element->enemy_sprite); // Libera a imagem do inimigo
        arma_destroy(element->arma);              // Libera a arma do inimigo
        free(element);                            // Libera a memória alocada para o inimigo
    }
}
