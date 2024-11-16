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
    new_enemy->sprite = al_load_bitmap(sprite_path);

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
