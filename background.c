#include <allegro5/allegro5.h>
#include "background.h"

void atualiza_e_desenha_background(ALLEGRO_BITMAP *background, float *background_x, float velocidade)
{
    // Limpa a tela com cor preta
    al_clear_to_color(al_map_rgb(0, 0, 0));

    // Atualiza a posição do fundo
    *background_x -= velocidade;
    if (*background_x <= -al_get_bitmap_width(background))
        *background_x = 0;

    // Desenha o fundo duas vezes para criar um efeito de loop contínuo
    al_draw_bitmap(background, *background_x, 0, 0);
    al_draw_bitmap(background, *background_x + al_get_bitmap_width(background), 0, 0);
}