#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <math.h>

#include "inimigos.h"

// Define o passo de movimentação dos inimigos
// fase 1
#define ENEMY_STEP 2
#define ENEMY1_STEP 30
// fase 2
#define ENEMY2_STEP 35
#define ENEMY3_STEP 45

enemy *enemy_create(unsigned char side, unsigned char face, short x, unsigned short y, unsigned short type, unsigned short max_x, unsigned short max_y)
{
    if ((x - side / 2 < 0) || (x + side / 2 > max_x) || (y - side / 2 < 0) || (y + side / 2 > max_y))
        return NULL; // Verifica se a posição inicial é válida

    enemy *new_enemy = (enemy *)malloc(sizeof(enemy)); // Aloca memória na heap para um novo inimigo
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
        al_destroy_bitmap(new_enemy->enemy_sprite); // Libera a memória alocada para o sprite
        arma_destroy(new_enemy->arma);              // Libera a memória alocada para a arma
        free(new_enemy);                            // Libera a memória alocada para o inimigo
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
    case 0: // Tipo 0 de inimigo (movimento simples para a esquerda)
        if ((element->x - steps * ENEMY_STEP) - element->side / 2 >= 0)
            element->x -= steps * ENEMY_STEP;
        if ((element->x + element->side / 2) > max_x)
            element->x = max_x - element->side / 2;
        break;

    case 1: // Tipo 1 de inimigo (movimento de vai-e-vem horizontal)
        if (trajectory % 2 == 0)
        {
            // Movendo para a direita
            element->x += steps * ENEMY1_STEP;
            if ((element->x + element->side / 2) > max_x)
            {
                element->x = max_x - element->side / 2;
                trajectory++; // Muda a direção
            }
        }
        else
        {
            // Movendo para a esquerda
            element->x -= steps * ENEMY1_STEP;
            if ((element->x - element->side / 2) <= 0)
            {
                element->x = element->side / 2;
                trajectory++; // Muda a direção
            }
        }
        break;

    case 2: // Tipo 2 de inimigo (movimento sinusoidal)
        element->x += steps * ENEMY2_STEP;
        element->y = (unsigned short)(max_y / 2 + 50 * sin(element->x * 0.1)); // Movimento em onda

        if ((element->x + element->side / 2) > max_x)
            element->x = max_x - element->side / 2;
        break;

    case 3: // Tipo 3 de inimigo (movimento aleatório ou zig-zag)
        if (rand() % 2 == 0)
            element->x += steps * ENEMY3_STEP;
        else
            element->x -= steps * ENEMY3_STEP;

        // Limites horizontais
        if ((element->x - element->side / 2) < 0)
            element->x = element->side / 2;
        if ((element->x + element->side / 2) > max_x)
            element->x = max_x - element->side / 2;
        break;

    default:
        break;
    }
}

// Função para desenhar o inimigo na tela com o recorte correto do sprite
void enemy_draw(enemy *element)
{
    // FASE 01
    //  INIMIGO 01 DA FASE 01
    // Definições do tamanho de cada quadro no sprite sheet
    int sprite_width = 100;  // Largura do quadro no sprite sheet
    int sprite_height = 100; // Altura do quadro no sprite sheet

    // Calcula a posição do quadro no sprite sheet
    int frame_x = (element->current_frame % 5) * sprite_width;  // Coluna
    int frame_y = (element->current_frame / 5) * sprite_height; // Linha

    //  INIMIGO 02 DA FASE 01
    int sprite1_width = 110;
    int sprite1_height = 110;

    int frame1_x = (element->current_frame % 4) * sprite_width;
    int frame1_y = (element->current_frame / 4) * sprite_height;
    /*------------------------------------------------------------------------------*/
    // FASE 02
    //  INIMIGO 01 DA FASE 02
    int sprite2_width = 118;
    int sprite2_height = 118;

    int frame2_x = (element->current_frame % 6) * sprite_width;
    int frame2_y = (element->current_frame / 6) * sprite_height;

    //  INIMIGO 02 DA FASE 02
    int sprite3_width = 110;
    int sprite3_height = 110;

    int frame3_x = (element->current_frame % 4) * sprite_width;
    int frame3_y = (element->current_frame / 4) * sprite_height;
    /*------------------------------------------------------------------------------*/

    switch (element->type)
    {
    case 0:
        al_draw_bitmap_region(element->enemy_sprite, frame_x, frame_y, sprite_width, sprite_height,
                       element->x - sprite_width / 2, element->y - sprite_height / 2, 0);
        break;
    case 1:
        al_draw_bitmap_region(element->enemy_sprite, frame1_x, frame1_y, sprite1_width, sprite1_height,
                       element->x - sprite1_width / 2, element->y - sprite1_height / 2, 0);
        break;
    case 2:
        al_draw_bitmap_region(element->enemy_sprite, frame2_x, frame2_y, sprite2_width, sprite2_height,
                       element->x - sprite2_width / 2, element->y - sprite2_height / 2, 0);
        break;
    case 3:
        al_draw_bitmap_region(element->enemy_sprite, frame3_x, frame3_y, sprite3_width, sprite3_height,
                       element->x - sprite3_width / 2, element->y - sprite3_height / 2, 0);
        break;
    default:
        break;
    }
}

void enemy_shot(enemy *element)
{
    if (!element)
        return;

    arma_shot(element->x, element->y, element->face, element->arma);
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
