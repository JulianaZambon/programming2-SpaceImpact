#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>

#include "jogador.h"

#define X_SCREEN 1140
#define Y_SCREEN 640
#define ANIMATION_DELAY 10 // Ajuste a velocidade da animação (quanto maior, mais lento)

int main()
{
    // Inicializa os addons do Allegro e verifica se foram carregados corretamente
    if (!al_init())
    {
        fprintf(stderr, "Falha ao inicializar o Allegro.\n");
        return -1;
    }

    if (!al_init_image_addon())
    {
        fprintf(stderr, "Falha ao inicializar o addon de imagens.\n");
        return -1;
    }

    if (!al_install_keyboard())
    {
        fprintf(stderr, "Falha ao instalar o teclado.\n");
        return -1;
    }

    if (!al_init_primitives_addon())
    {
        fprintf(stderr, "Falha ao inicializar o addon de primitivas.\n");
        return -1;
    }

    ALLEGRO_TIMER *timer = al_create_timer(1.0 / 30.0); // Timer de 30 FPS
    if (!timer)
    {
        fprintf(stderr, "Falha ao criar o timer.\n");
        return -1;
    }

    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    if (!queue)
    {
        fprintf(stderr, "Falha ao criar a fila de eventos.\n");
        al_destroy_timer(timer);
        return -1;
    }

    ALLEGRO_FONT *font = al_create_builtin_font();
    if (!font)
    {
        fprintf(stderr, "Falha ao criar a fonte.\n");
        al_destroy_event_queue(queue);
        al_destroy_timer(timer);
        return -1;
    }

    ALLEGRO_DISPLAY *disp = al_create_display(X_SCREEN, Y_SCREEN);
    if (!disp)
    {
        fprintf(stderr, "Falha ao criar a tela.\n");
        al_destroy_font(font);
        al_destroy_event_queue(queue);
        al_destroy_timer(timer);
        return -1;
    }

    ALLEGRO_BITMAP *background = al_load_bitmap("assets/cenarios/cenario2.png");
    if (!background)
    {
        fprintf(stderr, "Erro ao carregar a imagem de fundo.\n");
        al_destroy_display(disp);
        al_destroy_font(font);
        al_destroy_event_queue(queue);
        al_destroy_timer(timer);
        return -1;
    }

    float background_x = 0; // Posição inicial da imagem de fundo

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    player *player_1 = player_create(1, 1, (Y_SCREEN - 512) / 2, X_SCREEN, Y_SCREEN);
    if (!player_1 || !(player_1->sprite = al_load_bitmap("assets/jogador/sprite-player2.png")))
    {
        fprintf(stderr, "Erro ao criar o jogador 1 ou carregar o sprite.\n");
        al_destroy_bitmap(background);
        al_destroy_display(disp);
        al_destroy_font(font);
        al_destroy_event_queue(queue);
        al_destroy_timer(timer);
        return -1;
    }

    ALLEGRO_EVENT event;
    al_start_timer(timer);

    // Variável de controle da animação
    int animation_counter = 0;
    player_1->current_frame = 0;

    // Loop principal do jogo
    while (1)
    {
        al_wait_for_event(queue, &event);

        if (event.type == ALLEGRO_EVENT_TIMER)
        {
            // Limpa a tela antes de desenhar
            al_clear_to_color(al_map_rgb(0, 0, 0));

            // Atualiza a posição da imagem de fundo
            background_x -= 2; // Valor negativo para mover para a esquerda; ajuste conforme necessário

            // Reseta a posição quando a imagem sair da tela
            if (background_x <= -al_get_bitmap_width(background))
            {
                background_x = 0;
            }

            // Desenha a imagem de fundo duas vezes para o looping contínuo
            al_draw_bitmap(background, background_x, 0, 0);
            al_draw_bitmap(background, background_x + al_get_bitmap_width(background), 0, 0);

            // Atualiza o contador para animar o jogador
            animation_counter++;
            if (animation_counter >= ANIMATION_DELAY)
            {
                // Atualiza o quadro do jogador a cada N ciclos do timer
                player_1->current_frame = (player_1->current_frame + 1) % 72; // Cicla entre 0 e 71
                animation_counter = 0;                                        // Reseta o contador
            }

            // Chama a função para desenhar o jogador
            player_draw(player_1);

            al_flip_display();
        }
        else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            break;
        }
    }

    // Libera recursos
    al_destroy_bitmap(background);
    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    player_destroy(player_1); // Libera o jogador corretamente

    return 0;
}
