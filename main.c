// Compilação: gcc main.c jogador.c joystick.c -o SpaceImpact $(pkg-config allegro-5 allegro_main-5 allegro_font-5 allegro_image-5 allegro_primitives-5 --libs --cflags)

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>

#include "jogador.h"

#define X_SCREEN 1140
#define Y_SCREEN 640
#define ANIMATION_DELAY_PLAYER 3 // Ajuste a velocidade da animação (quanto maior, mais lento)

// // Função para verificar a colisão entre o jogador e os inimigos
// unsigned char collision_2D(player *element_first, enemy *element_second);

// // função que verifica se um projétil acertou um inimigo ou chefe
// unsigned char check_kill(player *killer, enemy *victim);

// // função que atualiza o posicionamento de projéteis conforme o movimento dos mesmos
// void update_projeteis(player *player_1);

// // Função para atualizar a posição do jogador conforme os comandos do controle e conforme colisões
// void update_position(player *player_1, enemy *enemy_1, enemy *enemy_2, boss *boss_1);

/*----------------------------------------------------------------------------------*/

// Função para atualizar a posição do jogador conforme os comandos do controle
void update_position(player *player_1)
{
    if (player_1->control->left)
    {
        player_move(player_1, 1, 0, X_SCREEN, Y_SCREEN);
    }
    if (player_1->control->right)
    {
        player_move(player_1, 1, 1, X_SCREEN, Y_SCREEN);
    }
    if (player_1->control->up)
    {
        player_move(player_1, 1, 2, X_SCREEN, Y_SCREEN);
    }
    if (player_1->control->down)
    {
        player_move(player_1, 1, 3, X_SCREEN, Y_SCREEN);
    }
}

int main()
{
    // Inicializa os addons do Allegro
    al_init();
    al_init_image_addon();
    al_install_keyboard();
    al_install_joystick();
    al_init_primitives_addon();

    ALLEGRO_TIMER *timer = al_create_timer(1.0 / 30.0); // Timer de 30 FPS
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    ALLEGRO_FONT *font = al_create_builtin_font();
    ALLEGRO_DISPLAY *disp = al_create_display(X_SCREEN, Y_SCREEN);
    ALLEGRO_BITMAP *background = al_load_bitmap("assets/cenarios/cenario2.png");

    float background_x = 0; // Posição inicial da imagem de fundo

    // Registra as fontes de eventos
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_joystick_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    // Cria o jogador
    player *player_1 = player_create(20, 60, 80, Y_SCREEN / 2, X_SCREEN, Y_SCREEN);
    if (!player_1 || !(player_1->sprite = al_load_bitmap("assets/jogador/sprite_jogador.png")))
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
            background_x -= 3; //(quanto maior o valor, mais rápido o fundo se moverá)

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
            if (animation_counter >= ANIMATION_DELAY_PLAYER)
            {
                // Atualiza o quadro do jogador a cada N ciclos do timer
                player_1->current_frame = (player_1->current_frame + 1) % 72; // Cicla entre 0 e 71
                animation_counter = 0;                                        // Reseta o contador
            }

            // Atualiza a posição do jogador com base nas entradas do teclado e joystick
            update_position(player_1);

            // Chama a função para desenhar o jogador
            player_draw(player_1);

            al_flip_display();
        }
        // Eventos de teclado para mover o jogador
        else if (event.type == ALLEGRO_EVENT_KEY_UP || event.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch (event.keyboard.keycode)
            {
            case ALLEGRO_KEY_LEFT:
                player_1->control->left = (event.type == ALLEGRO_EVENT_KEY_DOWN);
                break;
            case ALLEGRO_KEY_RIGHT:
                player_1->control->right = (event.type == ALLEGRO_EVENT_KEY_DOWN);
                break;
            case ALLEGRO_KEY_UP:
                player_1->control->up = (event.type == ALLEGRO_EVENT_KEY_DOWN);
                break;
            case ALLEGRO_KEY_DOWN:
                player_1->control->down = (event.type == ALLEGRO_EVENT_KEY_DOWN);
                break;
            }
        }
        else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            break;
        }
    }

    // Limpeza dos recursos
    al_destroy_bitmap(player_1->sprite);
    al_destroy_bitmap(background);
    al_destroy_display(disp);
    al_destroy_font(font);
    al_destroy_event_queue(queue);
    al_destroy_timer(timer);
    player_destroy(player_1);

    return 0;
}
