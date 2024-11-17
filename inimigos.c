#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>

#include "inimigos.h"

enemy *enemy_create(unsigned char side, unsigned char face, short x, unsigned short y, unsigned short max_x, unsigned short max_y);
void enemy_move(enemy *element, unsigned char steps, unsigned char trajectory, unsigned short max_x, unsigned short max_y);
void enemy_draw(enemy *element);	  
void enemy_shot(enemy *element);
void enemy_destroy(enemy *element);
