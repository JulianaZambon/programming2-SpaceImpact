#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>

// Inclusão de bibliotecas locais
#include "configuracoes.h"
#include "jogador.h"
#include "inimigos.h"

/*-----------------------------------------------------------------------------------------*/
/* DEFINIÇÕES */
#define TELA_INICIAL "assets/cenarios/tela_inicial.png"
#define PATH_CENARIO_2 "assets/cenarios/cenario2.png"

/*-----------------------------------------------------------------------------------------*/
/* FUNÇÕES AUXILIARES */

unsigned char verifica_morte(jogador *jogador_1, inimigo *inimigo_1)
{
    projetil *previous = NULL;
    for (projetil *index = jogador_1->arma->shots; index != NULL; index = index->proximo)
    {
        // Verifica colisão do projétil com a vítima
        if ((index->x >= inimigo_1->x - inimigo_1->tam_lateral / 2) && (index->x <= inimigo_1->x + inimigo_1->tam_lateral / 2) &&
            (index->y >= inimigo_1->y - inimigo_1->tam_lateral / 2) && (index->y <= inimigo_1->y + inimigo_1->tam_lateral / 2))
        {
            inimigo_1->hp--; // Diminui o HP da vítima

            // Verifica se a vítima ainda tem HP
            if (inimigo_1->hp > 0)
            {
                // Se não for o primeiro projétil, atualiza o ponteiro anterior
                if (previous)
                {
                    previous->proximo = index->proximo; // Remove o projétil da lista
                    destruir_projetil(index);            // Destroi o projétil
                    index = previous->proximo;          // Atualiza para o próximo projétil
                }
                else
                {
                    // Se for o primeiro projétil da lista, atualiza a cabeça da lista
                    jogador_1->arma->shots = index->proximo; // Atualiza a lista de projéteis
                    destruir_projetil(index);                // Destroi o projétil
                    index = jogador_1->arma->shots;          // Atualiza para o próximo
                }
            }
            else
            {
                // A vítima morreu
                destruir_projetil(index); // Destroi o projétil
                return 1;                // A vítima morreu
            }
        }
        previous = index; // Atualiza o projétil anterior
    }
    return 0; // Nenhum projétil acertou a vítima
}

// Atualiza a posição e ações do jogador
void atualiza_posicao(jogador *jogador_1)
{
    // Movimentação do jogador
    if (jogador_1->controle->esquerda)
        mover_jogador(jogador_1, 1, 0, X_SCREEN, Y_SCREEN);
    if (jogador_1->controle->direita)
        mover_jogador(jogador_1, 1, 1, X_SCREEN, Y_SCREEN);
    if (jogador_1->controle->cima)
        mover_jogador(jogador_1, 1, 2, X_SCREEN, Y_SCREEN);
    if (jogador_1->controle->baixo)
        mover_jogador(jogador_1, 1, 3, X_SCREEN, Y_SCREEN);

    // Disparo de projétil
    if (jogador_1->controle->fogo && !jogador_1->arma->timer)
    {
        jogador_atira(jogador_1);               // Realiza o disparo
        jogador_1->arma->timer = ARMA_COOLDOWN; // Define o tempo de cooldown da arma
    }

    // Atualiza a posição/movimentação dos projéteis
    mover_projetil(&jogador_1->arma->shots);
}

/*-----------------------------------------------------------------------------------------*/
/* MAIN */
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
    ALLEGRO_BITMAP *background = al_load_bitmap(PATH_CENARIO_2);

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_start_timer(timer);

    // Após a tela inicial, o jogo começa
    // Inicialização do jogador
    jogador *jogador_1 = criar_jogador(20, 60, 80, Y_SCREEN / 2, X_SCREEN, Y_SCREEN);
    jogador_1->sprite = al_load_bitmap(PATH_JOGADOR);
    if (!jogador_1)
        return 1;

    // Inicialização do inimigo
    inimigo *inimigo_1 = criar_inimigo(20, 60, X_SCREEN - 50, Y_SCREEN / 2, 2, X_SCREEN, Y_SCREEN);
    if (!inimigo_1)
        return 1;

    unsigned char trajetoria = 0; // Inicializa o controle de trajetória

    // Variáveis de controle de animação
    unsigned int animation_counter_jogador = 0;
    unsigned int animation_counter_inimigo = 0;
    unsigned int animation_counter_fundo = 0;

    float background_x = 0;

    /*-----------------------------------------------------------------------------------------*/
    /* LOOP PRINCIPAL DO JOGO */
    while (1)
    {
        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);

        if (event.type == ALLEGRO_EVENT_TIMER)
        {
            al_clear_to_color(al_map_rgb(0, 0, 0));

            // Atualiza o fundo
            background_x -= VELOCIDADE_BACKGROUND;
            if (background_x <= -al_get_bitmap_width(background))
                background_x = 0;

            al_draw_bitmap(background, background_x, 0, 0);
            al_draw_bitmap(background, background_x + al_get_bitmap_width(background), 0, 0);

            // Atualiza animação do jogador e do inimigo
            atualizar_animacao_jogador(jogador_1, &animation_counter_jogador, ANIMATION_DELAY_JOGADOR);
            atualizar_animacao_inimigo(inimigo_1, &animation_counter_inimigo, ANIMATION_DELAY_INIMIGO);

            // Atualiza o jogador e projéteis
            atualiza_posicao(jogador_1);

            // Atualiza o inimigo
            mover_inimigo(inimigo_1, 2, &trajetoria, X_SCREEN, Y_SCREEN);

            // Desenha o jogador
            desenhar_jogador(jogador_1);

            // Desenha os corações de HP
            desenhar_hp(jogador_1, 15, 15);

            // Desenha o inimigo
            desenhar_inimigo(inimigo_1);

            // Desenha os projéteis do jogador
            for (projetil *p = jogador_1->arma->shots; p != NULL; p = (projetil *)p->proximo)
            {
                if (verificar_colisao_projetil(p, inimigo_1->x, inimigo_1->y, inimigo_1->tam_lateral))
                {
                    inimigo_1->hp--;
                    projetil *proximo = p->proximo;
                    destruir_projetil(p);
                    p = proximo;
                }
                else
                    desenhar_projetil(p);
            }

            // Atualiza a arma do jogador
            if (jogador_1->arma->timer)
                atualiza_arma(jogador_1->arma);

            for (projetil *p = inimigo_1->arma->shots; p != NULL; p = p->proximo)
            {
                if (verificar_colisao_projetil(p, jogador_1->x, jogador_1->y, jogador_1->tam_lateral))
                {
                    jogador_1->hp--;

                    // Armazena o próximo projétil antes de destruir o atual
                    projetil *proximo = p->proximo;

                    // Destrói o projétil
                    destruir_projetil(p);

                    // Atualiza o ponteiro p para o próximo projétil
                    p = proximo;
                }
                else
                {
                    // Desenha o projétil se não houver colisão
                    desenhar_projetil(p);
                }
            }

            al_flip_display();
        }
        /*-----------------------------------------------------------------------------------------*/
        /* EVENTOS DO JOGADOR */
        else if (event.type == ALLEGRO_EVENT_KEY_DOWN || event.type == ALLEGRO_EVENT_KEY_UP)
        {
            switch (event.keyboard.keycode)
            {
            case ALLEGRO_KEY_LEFT:
                joystick_esquerda(jogador_1->controle);
                break;
            case ALLEGRO_KEY_RIGHT:
                joystick_direita(jogador_1->controle);
                break;
            case ALLEGRO_KEY_UP:
                joystick_cima(jogador_1->controle);
                break;
            case ALLEGRO_KEY_DOWN:
                joystick_baixo(jogador_1->controle);
                break;
            case ALLEGRO_KEY_SPACE:
                joystick_fogo(jogador_1->controle);
                break;
            }
        }
        else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            break;
        }
    }
    /*-----------------------------------------------------------------------------------------*/
    /* LIBERAÇÃO DE RECURSOS */
    al_destroy_bitmap(jogador_1->sprite);
    al_destroy_bitmap(background);
    al_destroy_display(disp);
    al_destroy_font(font);
    al_destroy_event_queue(queue);
    al_destroy_timer(timer);
    destroi_jogador(jogador_1);

    return 0;
}
