#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>

#include "chefes.h"

boss *boss_create(unsigned char side, unsigned char face, short x, unsigned short y, unsigned short max_x, unsigned short max_y);
void boss_move(boss *element, unsigned char steps, unsigned char trajectory, unsigned short max_x, unsigned short max_y);
void boss_draw(boss *element);
void boss_shot(boss *element);
void boss_destroy(boss *element);
