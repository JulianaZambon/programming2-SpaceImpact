#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>

#define X_SCREEN 1200
#define Y_SCREEN 650

int main() {
    al_init();
    al_install_keyboard();
    al_init_image_addon();

    ALLEGRO_TIMER *timer = al_create_timer(1.0 / 30.0);
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    ALLEGRO_FONT *font = al_create_builtin_font();
    ALLEGRO_DISPLAY *disp = al_create_display(X_SCREEN, Y_SCREEN);

    ALLEGRO_BITMAP *background = al_load_bitmap("cenario1.png");
    if (!background) {
        fprintf(stderr, "Erro ao carregar a imagem de fundo.\n");
        return -1;
    }

    float background_x = 0; // Posição inicial da imagem de fundo

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    ALLEGRO_EVENT event;
    al_start_timer(timer);

    while (1) {
        al_wait_for_event(queue, &event);

        if (event.type == ALLEGRO_EVENT_TIMER) {
            // Atualiza a posição da imagem de fundo
            background_x -= 2; // Valor negativo para mover para a esquerda; ajuste conforme necessário

            // Reseta a posição quando a imagem sair da tela
            if (background_x <= -al_get_bitmap_width(background)) {
                background_x = 0;
            }

            // Desenha a imagem de fundo duas vezes para o looping contínuo
            al_draw_bitmap(background, background_x, 0, 0);
            al_draw_bitmap(background, background_x + al_get_bitmap_width(background), 0, 0);

            al_flip_display();
            al_clear_to_color(al_map_rgb(0, 0, 0)); // Limpa a tela antes do próximo desenho
        } else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }
    }

    al_destroy_bitmap(background);
    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}
