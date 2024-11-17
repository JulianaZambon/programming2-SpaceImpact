#ifndef __CONFIG__ // Guardas de inclusão
#define __CONFIG__ // Guardas de inclusão

#define X_SCREEN 1140
#define Y_SCREEN 640
#define ANIMATION_DELAY_PLAYER 3 // Ajuste a velocidade da animação (quanto maior, mais lento)

// função de criação do loop do background
void draw_moving_background(ALLEGRO_BITMAP *background, float *offset, float speed, int screen_width);

#endif
