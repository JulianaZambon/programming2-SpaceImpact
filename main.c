#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>

#include "configuracoes.h"
#include "jogador.h"
#include "inimigos.h"

// Função que atualiza o posicionamento de projéteis conforme o movimento dos mesmos
void update_projeteis(player *player_1)
{
    projetil *previous = NULL; // Variável auxiliar para salvar a posição imediatamente anterior na fila
    for (projetil *index = player_1->arma->shots; index != NULL;)
    { // Para cada projétil presente na lista de projéteis disparados
        if (!index->trajectory)
            index->x -= PROJETIL_MOVE; // Se a trajetória for para a esquerda, atualiza a posição para a esquerda
        else if (index->trajectory == 1)
            index->x += PROJETIL_MOVE; // Se a trajetória for para a direita, atualiza a posição para a esquerda

        if ((index->x < 0) || (index->x > X_SCREEN))
        { // Verifica se o projétil saiu das bordas da janela
            if (previous)
            {                                       // Verifica se não é o primeiro elemento da lista de projéteis
                previous->next = index->next;       // Se não for, salva o próximo projétil
                projetil_destroy(index);            // Chama o destrutor para o projétil atual
                index = (projetil *)previous->next; // Atualiza para o próximo projétil
            }
            else
            {                                                    // Se for o primeiro projétil da lista
                player_1->arma->shots = (projetil *)index->next; // Atualiza o projétil no início da lista
                projetil_destroy(index);                         // Chama o destrutor para o projétil atual
                index = player_1->arma->shots;                   // Atualiza para o próximo projétil
            }
        }
        else
        {                                    // Se não saiu da tela
            previous = index;                // Atualiza o projétil anterior (para a próxima iteração)
            index = (projetil *)index->next; // Atualiza para o próximo projétil
        }
    }
}

// Função que atualiza a posição do jogador conforme os comandos do controle
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
    if (player_1->control->fire) // Verifica se o jogador está atirando
    { 
        if (!player_1->arma->timer) // Verifica se a arma do jogador não está em cooldown
        {                                          
            player_shot(player_1);                 // Se não estiver, faz um disparo
            player_1->arma->timer = ARMA_COOLDOWN; // Inicia o cooldown da arma
        }
    }
    update_projeteis(player_1); // Atualiza os disparos do jogador
}

int main()
{
    // Inicializa os addons do Allegro
    al_init();
    al_init_primitives_addon();

    al_init_image_addon();
    al_install_keyboard();
    al_install_joystick();

    ALLEGRO_TIMER *timer = al_create_timer(1.0 / 30.0); // Timer de 30 FPS
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    ALLEGRO_FONT *font = al_create_builtin_font();
    ALLEGRO_DISPLAY *disp = al_create_display(X_SCREEN, Y_SCREEN);
    ALLEGRO_BITMAP *background = al_load_bitmap("assets/cenarios/cenario2.png");

    // Registra as fontes de eventos
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_joystick_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    // Inicializa o timer e a fila de eventos
    ALLEGRO_EVENT event;
    al_start_timer(timer);

    float background_x = 0; // Posição inicial da imagem de fundo;

    // Criar o jogador
    player *player_1 = player_create(20, 60, 80, Y_SCREEN / 2, X_SCREEN, Y_SCREEN);
    player_1->sprite = al_load_bitmap("assets/jogador/sprite_jogador.png");
    if (!player_1)
        return 1;

    // Variáveis de controle da animação do sprite do jogador
    int animation_counter = 0;
    player_1->current_frame = 0;

    /*--------------------------------------------------------------------------------*/

    // Loop principal do jogo
    while (1)
    {
        al_wait_for_event(queue, &event);

        if (event.type == ALLEGRO_EVENT_TIMER)
        {
            al_clear_to_color(al_map_rgb(0, 0, 0)); // Limpa a tela com a cor preta
            background_x -= BACKGROUND_SPEED;       // Ajuste a velocidade do background
            // Reseta a posição quando a imagem sair da tela
            if (background_x <= -al_get_bitmap_width(background))
            {
                background_x = 0;
            }
            // Desenha a imagem de fundo duas vezes para o looping contínuo
            al_draw_bitmap(background, background_x, 0, 0);
            al_draw_bitmap(background, background_x + al_get_bitmap_width(background), 0, 0);

            // Atualiza o quadro atual do sprite (simulação de animação)
            animation_counter++;
            if (animation_counter >= ANIMATION_DELAY_PLAYER)
            {
                player_1->current_frame = (player_1->current_frame + 1) % 72; // Cicla entre 0 e 71
                animation_counter = 0;                                        // Reseta o contador
            }

            update_position(player_1); // Atualiza a posição do jogador

            player_draw(player_1); // Desenha o jogador na tela

            // Desenha os projéteis na tela
            for (projetil *index = player_1->arma->shots; index != NULL; index = (projetil *)index->next)
            {
                al_draw_filled_circle(index->x, index->y, 2, al_map_rgb(255, 0, 0)); // Desenha o projétil
            }

            update_projeteis(player_1);

            al_flip_display(); // Insere as modificações realizadas nos buffers de tela
        }

        /*--------------------------------------------------------------------------------*/

        // else if (event.type == ALLEGRO_EVENT_TIMER) // O evento tipo 30 indica um evento de relógio, ou seja, verificação se a tela deve ser atualizada (conceito de FPS)
        // {
        //     for (projetil *index = player_1->arma->shots; index != NULL; index = (projetil *)index->next)
        //         al_draw_filled_circle(index->x, index->y, 2, al_map_rgb(255, 0, 0)); // Insere as balas existentes disparadas pelo primeiro jogador na tela
        //     if (player_1->arma->timer)
        //         player_1->arma->timer--; // Atualiza o cooldown da arma do primeiro jogador
        // }

        // Eventos de teclado para mover o jogador
        else if (event.type == ALLEGRO_EVENT_KEY_UP || event.type == ALLEGRO_EVENT_KEY_DOWN) // Verifica se o evento é de botão do teclado abaixado ou levantado
        {
            switch (event.keyboard.keycode)
            {
            case ALLEGRO_KEY_LEFT:
                joystick_left(player_1->control);
                break;
            case ALLEGRO_KEY_RIGHT:
                joystick_right(player_1->control);
                break;
            case ALLEGRO_KEY_UP:
                joystick_up(player_1->control);
                break;
            case ALLEGRO_KEY_DOWN:
                joystick_down(player_1->control);
                break;
            case ALLEGRO_KEY_0:
                joystick_fire(player_1->control);
                break;
            }
        }
        else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) // Evento de clique no "X" de fechamento da tela
            break;
    }

    /*--------------------------------------------------------------------------------*/

    // Libera os recursos alocados na heap
    al_destroy_bitmap(player_1->sprite);
    al_destroy_bitmap(background);
    al_destroy_display(disp);
    al_destroy_font(font);
    al_destroy_event_queue(queue);
    al_destroy_timer(timer);
    player_destroy(player_1);

    return 0;
}
