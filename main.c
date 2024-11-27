#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>

#include "configuracoes.h"
#include "jogador.h"
#include "inimigos.h"

// Função auxiliar para remover projétil da lista
void remove_projetil(player *player_1, projetil *current, projetil *previous)
{
    if (previous)
    {
        previous->next = current->next;  // Atualiza o ponteiro do projétil anterior
    }
    else
    {
        player_1->arma->shots = current->next;  // Remove o primeiro projétil da lista
    }
    projetil_destroy(current);  // Libera a memória alocada para o projétil
}

// Atualiza o posicionamento de projéteis conforme o movimento
void update_projeteis(player *player_1)
{
    projetil *previous = NULL;
    projetil *current = player_1->arma->shots;

    while (current != NULL)
    {
        // Verifica se o projétil está indo para a esquerda
        if (!current->trajectory)  
        {
            if (current->x - PROJETIL_MOVE >= 0)
            {
                current->x -= PROJETIL_MOVE;  // Move o projétil para a esquerda
            }
            else  // Se o projétil sair da tela
            {
                remove_projetil(player_1, current, previous);
                current = (previous) ? previous->next : player_1->arma->shots;
                continue;  // Retorna ao início do loop para verificar o próximo projétil
            }
        }
        // Verifica se o projétil está indo para a direita
        else if (current->trajectory == 1)  
        {
            if (current->x + PROJETIL_MOVE <= X_SCREEN)
            {
                current->x += PROJETIL_MOVE;  // Move o projétil para a direita
            }
            else  // Se o projétil sair da tela
            {
                remove_projetil(player_1, current, previous);
                current = (previous) ? previous->next : player_1->arma->shots;
                continue;  // Retorna ao início do loop para verificar o próximo projétil
            }
        }

        // Avança para o próximo projétil
        previous = current;
        current = current->next;
    }
}

// Atualiza a posição e ações do jogador
void update_position(player *player_1)
{
    if (player_1->control->left)
        player_move(player_1, 1, 0, X_SCREEN, Y_SCREEN);
    if (player_1->control->right)
        player_move(player_1, 1, 1, X_SCREEN, Y_SCREEN);
    if (player_1->control->up)
        player_move(player_1, 1, 2, X_SCREEN, Y_SCREEN);
    if (player_1->control->down)
        player_move(player_1, 1, 3, X_SCREEN, Y_SCREEN);

    if (player_1->control->fire && !player_1->arma->timer)
    { 
        player_shot(player_1); // Realiza o disparo
        player_1->arma->timer = ARMA_COOLDOWN;
    }
    update_projeteis(player_1); // Atualiza a posição dos projéteis
}

int main()
{
    // Inicialização do Allegro
    al_init();
    al_init_primitives_addon();
    al_init_image_addon();
    al_install_keyboard();

    ALLEGRO_TIMER *timer = al_create_timer(1.0 / 30.0);
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    ALLEGRO_FONT *font = al_create_builtin_font();
    ALLEGRO_DISPLAY *disp = al_create_display(X_SCREEN, Y_SCREEN);
    ALLEGRO_BITMAP *background = al_load_bitmap("assets/cenarios/cenario2.png");

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    al_start_timer(timer);

    // Inicialização do jogador
    player *player_1 = player_create(20, 60, 80, Y_SCREEN / 2, X_SCREEN, Y_SCREEN);
    player_1->sprite = al_load_bitmap("assets/jogador/sprite_jogador.png");
    if (!player_1)
        return 1;

    int animation_counter = 0;
    player_1->current_frame = 0;
    float background_x = 0;

    while (1)
    {
        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);

        if (event.type == ALLEGRO_EVENT_TIMER)
        {
            al_clear_to_color(al_map_rgb(0, 0, 0));

            // Atualiza o fundo
            background_x -= BACKGROUND_SPEED;
            if (background_x <= -al_get_bitmap_width(background))
                background_x = 0;

            al_draw_bitmap(background, background_x, 0, 0);
            al_draw_bitmap(background, background_x + al_get_bitmap_width(background), 0, 0);

            // Atualiza animação do jogador
            if (++animation_counter >= ANIMATION_DELAY_PLAYER)
            {
                player_1->current_frame = (player_1->current_frame + 1) % 72;
                animation_counter = 0;
            }

            // Atualiza o jogador e projéteis
            update_position(player_1);

            // Desenha o jogador
            player_draw(player_1);

            // Desenha os projéteis
            for (projetil *index = player_1->arma->shots; index != NULL; index = (projetil *)index->next)
            {
                al_draw_filled_circle(index->x, index->y, 10, al_map_rgb(255, 0, 0));
            }

            if (player_1->arma->timer)
                update_arma(player_1->arma); 

            al_flip_display();
        }
        else if (event.type == ALLEGRO_EVENT_KEY_DOWN || event.type == ALLEGRO_EVENT_KEY_UP)
        {
            switch (event.keyboard.keycode)
            {
            case ALLEGRO_KEY_LEFT: joystick_left(player_1->control); break;
            case ALLEGRO_KEY_RIGHT: joystick_right(player_1->control); break;
            case ALLEGRO_KEY_UP: joystick_up(player_1->control); break;
            case ALLEGRO_KEY_DOWN: joystick_down(player_1->control); break;
            case ALLEGRO_KEY_SPACE: joystick_fire(player_1->control); break;
            }
        }
        else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            break;
        }
    }

    // Libera recursos
    al_destroy_bitmap(player_1->sprite);
    al_destroy_bitmap(background);
    al_destroy_display(disp);
    al_destroy_font(font);
    al_destroy_event_queue(queue);
    al_destroy_timer(timer);
    player_destroy(player_1);

    return 0;
}
