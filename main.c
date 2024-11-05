#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <stdio.h>

int main(void)
{
    al_init();             // Inicializa a biblioteca Allegro
    al_install_keyboard(); // Inicializa o teclado

    // Inicializa addons (componentes adicionais)
    al_init_primitives_addon(); // Para desenhar formas geométricas
    al_init_image_addon();      // Para carregar imagens
    al_init_font_addon();       // Para usar fontes básicas
    al_init_ttf_addon();        // Para fontes TTF

    ALLEGRO_TIMER *timer = al_create_timer(1.0 / 60);     // Cria um timer de 60 FPS
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue(); // Cria uma fila de eventos
    ALLEGRO_FONT *font = al_create_builtin_font();        // Cria uma fonte padrão
    ALLEGRO_DISPLAY *disp = al_create_display(800, 600);  // Cria uma janela de 800x600 pixels

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    ALLEGRO_EVENT event;
    al_start_timer(timer);
    while (1)
    {
        al_wait_for_event(queue, &event);

        if (event.type == 30)
        {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_flip_display();
        }
        else if (event.type == 42)
            break;
    }

    al_destroy_display(font);
    al_destroy_display(disp); // Destroi a janela
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}