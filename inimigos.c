#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>

#include "inimigos.h"

enemy *create_enemy(float x, float y, float speed, int hp, int type, const char *sprite_path) {
    enemy *new_enemy = (enemy *)malloc(sizeof(enemy));
    if (!new_enemy) {
        fprintf(stderr, "Erro ao alocar memória para o inimigo.\n");
        return NULL;
    }

    new_enemy->x = x;
    new_enemy->y = y;
    new_enemy->speed = speed;
    new_enemy->hp = hp;
    new_enemy->type = type;
    
    // sprites dos inimigos de acordo com o tipo
    switch (type) {
        // fase 1
        case 0:
            new_enemy->sprite = al_load_bitmap("assets/inimigos/fase1/sprite-enemy2.png");
            break;
        case 1:
            new_enemy->sprite = al_load_bitmap("assets/inimigos/fase1/sprite-enemy4.png");
            break;
        // fase 2
        case 2:
            new_enemy->sprite = al_load_bitmap("assets/inimigos/fase2/sprite-enemy.png");
            break;
        case 3:
            new_enemy->sprite = al_load_bitmap("assets/inimigos/fase2/sprite-enemy3.png");
            break;
        default:
            fprintf(stderr, "Tipo de inimigo desconhecido.\n");
            free(new_enemy);
            return NULL;
    }

    if (!new_enemy->sprite) {
        fprintf(stderr, "Erro ao carregar o sprite do inimigo do tipo %d.\n", type);
        free(new_enemy);
        return NULL;
    }

    return new_enemy;
}

void draw_enemy(const enemy *enemies) {
    if (enemies) {
        al_draw_bitmap(enemies->sprite, enemies->x, enemies->y, 0);
    }
}

void move_enemy(enemy *enemies, unsigned char steps, unsigned char trajectory, unsigned short max_x, unsigned short max_y) {
    if (enemies) {
        switch (trajectory) {
        case 0:
            enemies->x -= steps * enemies->speed;
            if (enemies->x <= 0) {
                enemies->x = max_x;
            }
            break;
        case 1:
            enemies->x += steps * enemies->speed;
            if (enemies->x >= max_x) {
                enemies->x = 0;
            }
            break;
        case 2:
            enemies->y -= steps * enemies->speed;
            if (enemies->y <= 0) {
                enemies->y = max_y;
            }
            break;
        case 3:
            enemies->y += steps * enemies->speed;
            if (enemies->y >= max_y) {
                enemies->y = 0;
            }
            break;
        }
    }
}

void destroy_enemy(enemy *enemies) {
    if (enemies) {
        if (enemies->sprite) {
            al_destroy_bitmap(enemies->sprite);
        }
        free(enemies);
    }
}
