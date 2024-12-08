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
#include "narrativa.h"
#include "background.h"
#include "jogador.h"
#include "inimigos.h"
#include "chefes.h"
#include "fases.h"

/*-------------------------------------------------------------------*/
/* DEFINIÇÕES */
#define X_SCREEN 1140
#define Y_SCREEN 640

/*-------------------------------------------------------------------*/
/* FUNÇÕES DE INICIALIZAÇÃO */

void exibir_mensagem(ALLEGRO_FONT *font, const char *mensagens[],
                     int num_mensagens, float duracao_por_mensagem,
                     bool com_efeito, float velocidade_efeito)
{
    for (int i = 0; i < num_mensagens; i++)
    {
        const char *mensagem = mensagens[i];
        if (com_efeito)
        {
            // Exibe com efeito de digitação
            size_t tamanho = strlen(mensagem);
            for (size_t j = 0; j <= tamanho; j++)
            {
                al_clear_to_color(al_map_rgb(0, 0, 0));
                al_draw_textf(font, al_map_rgb(255, 255, 255), X_SCREEN / 2, Y_SCREEN / 2,
                              ALLEGRO_ALIGN_CENTER, "%.*s", (int)j, mensagem);
                al_flip_display();
                al_rest(velocidade_efeito);
            }
        }
        else
        {
            // Exibe diretamente
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_text(font, al_map_rgb(255, 255, 255), X_SCREEN / 2, Y_SCREEN / 2,
                         ALLEGRO_ALIGN_CENTER, mensagem);
            al_flip_display();
            al_rest(duracao_por_mensagem);
        }
    }
}

bool inicializa_allegro()
{
    if (!al_init())
        return false;
    if (!al_init_primitives_addon() || !al_init_image_addon() ||
        !al_init_font_addon() || !al_init_ttf_addon())
        return false;
    if (!al_install_keyboard())
        return false;
    return true;
}

void inicializa_jogo(ALLEGRO_EVENT_QUEUE **queue, ALLEGRO_TIMER **timer,
                     ALLEGRO_DISPLAY **disp, ALLEGRO_FONT **font)
{
    *timer = al_create_timer(1.0 / 30.0); // 30 FPS
    *queue = al_create_event_queue();
    *font = al_create_builtin_font();
    *disp = al_create_display(X_SCREEN, Y_SCREEN);

    if (!*timer || !*queue || !*font || !*disp)
        exit(1);

    al_register_event_source(*queue, al_get_keyboard_event_source());
    al_register_event_source(*queue, al_get_display_event_source(*disp));
    al_register_event_source(*queue, al_get_timer_event_source(*timer));
    al_start_timer(*timer);
}

/*-------------------------------------------------------------------*/
/* MAIN */
int main()
{
    if (!inicializa_allegro())
        return -1;

    srand(time(NULL));

    ALLEGRO_EVENT_QUEUE *queue;
    ALLEGRO_TIMER *timer;
    ALLEGRO_FONT *font;
    ALLEGRO_DISPLAY *disp;

    inicializa_jogo(&queue, &timer, &disp, &font);

    /* INICIALIZAÇÃO DE RECURSOS */
    jogador *jogador_1 = malloc(sizeof(jogador));
    inimigo *lista_inimigos_fase1 = malloc(sizeof(inimigo) * NUM_INIMIGOS);
    inimigo *lista_inimigos_fase2 = malloc(sizeof(inimigo) * NUM_INIMIGOS);
    chefe *chefe_1 = malloc(sizeof(chefe));
    chefe *chefe_2 = malloc(sizeof(chefe));

    ALLEGRO_BITMAP *background;

    /* INICIALIZAÇÃO DA TELA INCIAL DO JOGO */
    tela_inicial_sprite *tela_inicial = criar_tela_inicial();
    if (!tela_inicial)
        return 1;

    /* INICIALIZAÇÃO DAS NARRATIVAS */
    tela_nave_ligando *nave_ligando = criar_tela_nave_ligando();
    tela_velocidade_luz *velocidade_luz = criar_tela_velocidade_luz();

    /* VARIÁVEIS DE CONTROLE */
    bool jogo_rodando = true;
    bool tela_inicial_ativa = true;
    ALLEGRO_EVENT event;
    unsigned int animation_tela_inicial = 0;
    int fase_atual = 1; /* Inicia na Fase 1 */

    /*-------------------------------------------------------------------*/
    while (jogo_rodando)
    {
        al_wait_for_event(queue, &event);

        if (tela_inicial_ativa)
        {
            if (event.type == ALLEGRO_EVENT_TIMER)
            {
                al_clear_to_color(al_map_rgb(0, 0, 0));
                atualizar_animacao_tela_inicial(tela_inicial, &animation_tela_inicial,
                                                VELOCIDADE_TELA_INICIAL);

                desenhar_tela_inicial(tela_inicial);

                al_draw_textf(font, al_map_rgb(255, 255, 255), X_SCREEN / 2 - 60,
                              Y_SCREEN / 2 - 200, 0, "PRESS 'S' TO START");
                al_flip_display();
            }
            else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            {
                jogo_rodando = false;
            }
            else if (event.type == ALLEGRO_EVENT_KEY_DOWN)
            {
                if (event.keyboard.keycode == ALLEGRO_KEY_S)
                {
                    tela_inicial_ativa = false;

                    const char *mensagens[] = {
                        "SPACE IMPACT: Maxive Galaxy",
                        "explore, trade, fight!",
                        "Pressione as setas para mover a nave e a barra de espaço para atirar."};
                    exibir_mensagem(font, mensagens, 3, 1.5, true, 0.1);

                    const char *prologo[] = {
                        "PRÓLOGO"};
                    exibir_mensagem(font, prologo, 1, 1.5, true, 0.2);

                    // Narrativa
                    const char *narrativa_fase_1[] = {
                        "Kai Takeda, um piloto de 28 anos e mecânico, sonha em se juntar às forças de defesa da cidade,",
                        "onde sua amiga de infância, Haruka, é comandante. Quando criaturas misteriosas chamadas Espectros",
                        "começam a atacar a cidade, Kai se vê no meio da luta para protegê-la. Determinado a cumprir sua",
                        "promessa a Haruka, Kai deve confrontar os Espectros enquanto lida com a crescente ameaça que pode",
                        "destruir a cidade e tudo o que ele ama."};
                    exibir_mensagem(font, narrativa_fase_1, 5, 1.5, true, 0.1);

                    while (!al_is_event_queue_empty(queue))
                    {
                        ALLEGRO_EVENT unused_event;
                        al_get_next_event(queue, &unused_event);
                    }

                    bool animacao_ativa = true;
                    while (animacao_ativa)
                    {
                        al_clear_to_color(al_map_rgb(0, 0, 0));
                        atualizar_animacao_tela_nave_ligando(nave_ligando, &nave_ligando->animation_counter,
                                                             1);
                        desenhar_tela_nave_ligando(nave_ligando);
                        al_flip_display();
                        al_rest(0.05);
                        // Finaliza após exibir todos os quadros
                        if (nave_ligando->frame_atual == 95 - 1)
                            animacao_ativa = false; // Sai do loop
                    }

                    /* Inicializa a Fase 1 */
                    inicializa_fase(&background, &jogador_1, &lista_inimigos_fase1,
                                    NULL, &chefe_1, &chefe_2, fase_atual);
                }
            }
        }
        /*-------------------------------------------------------------------*/
        /* JOGO */
        else
        {
            if (event.type == ALLEGRO_EVENT_TIMER)
            {
                /* Atualiza a fase */
                while (!al_is_event_queue_empty(queue))
                {
                    ALLEGRO_EVENT unused_event;
                    al_get_next_event(queue, &unused_event);
                }
                atualiza_fase(background, jogador_1, &lista_inimigos_fase1,
                              &lista_inimigos_fase2, chefe_1, chefe_2, fase_atual);

                /* Verifica se o jogador venceu a fase */
                if (venceu_fase) // Se venceu a fase atual
                {
                    if (fase_atual == 1) /* Se estava na Fase 1 */
                    {
                        /* MENSAGEM DE VITÓRIA - FASE 1 */
                        const char *mensagem_vitoria_fase_1[] = {
                            "VITÓRIA ! Fase 1 concluída.",
                            "Você derrotou o Espectro do Fogo e salvou a cidade por agora.",
                            "Mas a batalha está longe de terminar...",
                            "A ameaça dos Espectros cresce cada vez mais.",
                            "Prepare-se para o próximo desafio, piloto!"};
                        exibir_mensagem(font, mensagem_vitoria_fase_1, 5, 1.5, true, 0.1);

                        /* Avança para a fase 2 */
                        fase_atual = 2;
                        venceu_fase = false; /* Reseta a variável para a nova fase */

                        /* NARRATIVA FASE 2 */
                        const char *narrativa_fase_2[] = {
                            "Após a vitória contra o Espectro do Fogo, novas ameaças surgem.",
                            "Kai Takeda se prepara para enfrentar o Espectro do Vento, mais rápido e imprevisível.",
                            "Rumores dizem que ele é um inimigo ainda mais perigoso, desafiando até os melhores pilotos.",
                            "A cidade está em alerta máximo, e Kai será testado como nunca antes.",
                            "A luta pela sobrevivência continua e Kai deve proteger a cidade a todo custo."};
                        exibir_mensagem(font, narrativa_fase_2, 5, 1.5, true, 0.1);

                        bool animacao_ativa_2 = true;
                        while (animacao_ativa_2)
                        {
                            al_clear_to_color(al_map_rgb(0, 0, 0)); // Limpa a tela

                            atualizar_animacao_tela_velocidade_luz(velocidade_luz, &velocidade_luz->animation_counter,
                                                                   5);
                            desenhar_tela_velocidade_luz(velocidade_luz);
                            al_flip_display();
                            al_rest(0.05);
                            // Finaliza após exibir todos os quadros
                            if ((velocidade_luz->frame_atual == 14 - 1))
                            {
                                animacao_ativa_2 = false; // Sai do loop
                            }
                        }

                        while (!al_is_event_queue_empty(queue))
                        {
                            ALLEGRO_EVENT unused_event;
                            al_get_next_event(queue, &unused_event);
                        }
                        inicializa_fase(&background, &jogador_1, NULL, &lista_inimigos_fase2,
                                        &chefe_1, &chefe_2, fase_atual);
                        atualiza_fase(background, jogador_1, NULL, &lista_inimigos_fase2,
                                      chefe_1, chefe_2, fase_atual);
                    }
                    else if (fase_atual == 2) /* Se estava na Fase 2 */
                    {
                        /* Se o jogador venceu a Fase 2 exibe a mensagem de vitória */
                        /* MENSAGEM DE VITÓRIA */
                        const char *mensagem_vitoria[] = {
                            "VITÓRIA! Parabéns, Kai Takeda!",
                            "Você derrotou os Espectros e salvou a cidade!",
                            "Sua coragem foi essencial para proteger todos.",
                            "A cidade está segura, mas o preço foi alto.",
                            "Este é apenas o começo de uma nova era de esperança!"};
                        exibir_mensagem(font, mensagem_vitoria, 5, 1.5, true, 0.2);

                        jogo_rodando = false; /* Encerra o jogo */
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

    /*-------------------------------------------------------------------*/
    /* LIBERAÇÃO DE RECURSOS */
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    al_destroy_font(font);
    free(jogador_1);
    free(lista_inimigos_fase1);
    free(lista_inimigos_fase2);
    free(chefe_1);
    free(chefe_2);

    return 0;
}
