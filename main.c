#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Inclusão de bibliotecas locais
#include "configuracoes.h"
#include "telaInicial.h"
#include "background.h"
#include "jogador.h"
#include "inimigos.h"
#include "chefes.h"
#include "fases.h"

/*-----------------------------------------------------------------------------------------*/
/* DEFINIÇÕES */
#define X_SCREEN 1140 // Dimensões da tela
#define Y_SCREEN 640  // Dimensões da tela

/*-----------------------------------------------------------------------------------------*/
/* FUNÇÕES DE INICIALIZAÇÃO */
bool inicializa_allegro()
{
    if (!al_init())
    {
        fprintf(stderr, "Falha ao inicializar a Allegro.\n");
        return false;
    }
    if (!al_init_primitives_addon() || !al_init_image_addon() || !al_init_font_addon() || !al_init_ttf_addon())
    {
        fprintf(stderr, "Falha ao inicializar os addons da Allegro.\n");
        return false;
    }
    if (!al_install_keyboard())
    {
        fprintf(stderr, "Falha ao inicializar o teclado.\n");
        return false;
    }
    return true;
}

void inicializa_jogo(ALLEGRO_EVENT_QUEUE **queue, ALLEGRO_TIMER **timer, ALLEGRO_DISPLAY **disp, ALLEGRO_FONT **font)
{
    *timer = al_create_timer(1.0 / 30.0); // 30 FPS
    *queue = al_create_event_queue();
    *font = al_create_builtin_font();
    *disp = al_create_display(X_SCREEN, Y_SCREEN);

    if (!*timer || !*queue || !*font || !*disp)
    {
        fprintf(stderr, "Falha ao criar componentes do jogo.\n");
        exit(1);
    }

    al_register_event_source(*queue, al_get_keyboard_event_source());
    al_register_event_source(*queue, al_get_display_event_source(*disp));
    al_register_event_source(*queue, al_get_timer_event_source(*timer));
    al_start_timer(*timer);
}

/*-----------------------------------------------------------------------------------------*/
/* MAIN */
int main()
{
    if (!inicializa_allegro())
    {
        return -1; // Se a inicialização falhar, retorna erro
    }

    srand(time(NULL)); // Inicializa a semente do gerador de números aleatórios

    ALLEGRO_EVENT_QUEUE *queue;
    ALLEGRO_TIMER *timer;
    ALLEGRO_FONT *font;
    ALLEGRO_DISPLAY *disp;

    inicializa_jogo(&queue, &timer, &disp, &font);

    // Inicialização dos elementos do jogo
    jogador *jogador_1 = malloc(sizeof(jogador));
    inimigo *lista_inimigos = malloc(sizeof(inimigo) * NUM_INIMIGOS); // Exemplo
    chefe *chefe_1 = malloc(sizeof(chefe));
    chefe *chefe_2 = malloc(sizeof(chefe));

    ALLEGRO_BITMAP *background;

    // Inicialização da tela inicial
    tela_inicial_sprite *tela_inicial = criar_tela_inicial();
    if (!tela_inicial)
    {
        return 1; // Retorna erro se não conseguir criar a tela inicial
    }

    bool jogo_rodando = true;
    bool tela_inicial_ativa = true;
    ALLEGRO_EVENT event;
    unsigned int animation_tela_inicial = 0;
    int fase_atual = 1; // Variável que controla a fase atual


    /*-----------------------------------------------------------------------------------------*/
    while (jogo_rodando)
    {
        al_wait_for_event(queue, &event);

        if (tela_inicial_ativa)
        {
            if (event.type == ALLEGRO_EVENT_TIMER)
            {
                al_clear_to_color(al_map_rgb(0, 0, 0));
                atualizar_animacao_tela_inicial(tela_inicial, &animation_tela_inicial, VELOCIDADE_TELA_INICIAL);
                desenhar_tela_inicial(tela_inicial);
                al_draw_textf(font, al_map_rgb(255, 255, 255), X_SCREEN / 2 - 60, Y_SCREEN / 2 - 200, 0, "PRESS 'S' TO START");
                al_flip_display();
            }
            else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            {
                jogo_rodando = false;
            }
            else if (event.type == ALLEGRO_EVENT_KEY_DOWN)
            {
                if (event.keyboard.keycode == ALLEGRO_KEY_S) // Inicia o jogo ao pressionar a tecla 'S'
                {
                    tela_inicial_ativa = false;
                    inicializa_fase(&background, &jogador_1, &lista_inimigos, &chefe_1, &chefe_2, fase_atual);
                }
            }
        }
        /*-----------------------------------------------------------------------------------------*/
        /* JOGO */
        else
        {
            if (event.type == ALLEGRO_EVENT_TIMER)
            {
                // Atualiza a fase com base na fase atual
                atualiza_fase(background, jogador_1, &lista_inimigos, chefe_1, chefe_2, fase_atual);

                // Verifica se a fase foi concluída
                if (venceu_fase) // Se venceu a fase atual
                {
                    if (fase_atual == 1) // Se estava na fase 1
                    {
                        // Exibe mensagem de conclusão
                        al_clear_to_color(al_map_rgb(0, 0, 0));
                        al_draw_textf(font, al_map_rgb(255, 255, 255), X_SCREEN / 2 - 60, Y_SCREEN / 2, 0, "Fase 1 concluída!");
                        al_flip_display();
                        al_rest(3.0); // Aguarda 3 segundos

                        // Avança para a fase 2
                        fase_atual = 2;
                        venceu_fase = false; // Reseta a variável para a nova fase
                        inicializa_fase(&background, &jogador_1, &lista_inimigos, &chefe_1, &chefe_2, fase_atual);
                    }
                    else if (fase_atual == 2)
                    {
                        // Se venceu a fase 2, exibe mensagem final
                        al_clear_to_color(al_map_rgb(0, 0, 0));
                        al_draw_textf(font, al_map_rgb(255, 255, 255), X_SCREEN / 2 - 60, Y_SCREEN / 2, 0, "Você venceu o jogo!");
                        al_flip_display();
                        al_rest(3.0); // Aguarda 3 segundos
                        jogo_rodando = false; // Encerra o jogo
                    }
                }
            }
            else if (event.type == ALLEGRO_EVENT_KEY_DOWN || event.type == ALLEGRO_EVENT_KEY_UP)
            {
                processa_evento_teclado(event, jogador_1);
            }
            else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            {
                jogo_rodando = false;
            }
        }
    }

    /*-----------------------------------------------------------------------------------------*/
    /* LIBERAÇÃO DE RECURSOS */
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    // Libera memória alocada
    free(jogador_1);
    free(lista_inimigos);
    free(chefe_1);
    free(chefe_2);

    return 0;
}
