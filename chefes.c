#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>

#include "chefes.h"

void create_boss(boss *new_boss, float x, float y, float speed, int hp, int damage, const char *sprite_path){
    new_boss = (boss *)malloc(sizeof(boss));
    if (!new_boss) {
        fprintf(stderr, "Erro ao alocar memória para o chefe.\n");
        return;
    }

    new_boss->x = x;
    new_boss->y = y;
    new_boss->speed = speed;
    new_boss->hp = hp;
    new_boss->damage = damage;
    new_boss->sprite = al_load_bitmap(sprite_path);
    new_boss->phase = 1;

    switch (new_boss->phase) {
        case 1:
            new_boss->sprite = al_load_bitmap("assets/chefes/boss2.png");
            break;
        case 2:
            new_boss->sprite = al_load_bitmap("assets/chefes/boss3.png");
            break;
        default:
            fprintf(stderr, "Fase do chefe desconhecida.\n");
            free(new_boss);
            return;
    }

    return new_boss;
}

void draw_boss(const boss *new_boss) {
    if (new_boss) {
        al_draw_bitmap(new_boss->sprite, new_boss->x, new_boss->y, 0);
    }
}

void move_boss(boss *new_boss) {
    if (new_boss) {
        new_boss->x -= new_boss->speed;
    }
}

void destroy_boss(boss *new_boss) {
    if (new_boss) {
        al_destroy_bitmap(new_boss->sprite);
        free(new_boss);
    }
}
