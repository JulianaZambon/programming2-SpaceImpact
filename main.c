#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>

// Inclusão de bibliotecas locais
#include "configuracoes.h"
#include "telaInicial.h"
#include "background.h"
#include "jogador.h"
#include "inimigos.h"
#include "chefes.h"

/*-----------------------------------------------------------------------------------------*/
/* DEFINIÇÕES */
#define PATH_CENARIO_2 "assets/cenarios/cenario3.png"

/*-----------------------------------------------------------------------------------------*/
/* FUNÇÕES AUXILIARES */

// Implementação da função que verifica se um projétil acertou um inimigo, a cada acerto o jogador ganha 10 pontos
unsigned char check_kill_inimigo(jogador *killer, inimigo *victim, unsigned int *score)
{
    projetil *anterior = NULL;
    projetil *index = killer->arma->shots;

    // Itera sobre todos os projéteis disparados pelo jogador
    while (index != NULL)
    {
        // Verifica se o projétil colidiu com o inimigo no eixo X e Y
        if ((index->x >= victim->x - victim->sprite_info->largura / 2) &&
            (index->x <= victim->x + victim->sprite_info->largura / 2) &&
            (index->y >= victim->y - victim->sprite_info->altura / 2) &&
            (index->y <= victim->y + victim->sprite_info->altura / 2))
        {
            victim->hp--; // Reduz o HP do inimigo
            *score += 10; // Aumenta a pontuação do jogador

            // Remove o projétil da lista
            if (anterior)
            {
                anterior->proximo = index->proximo; // Se não for o primeiro, ajusta o ponteiro do anterior
            }
            else
            {
                killer->arma->shots = (projetil *)index->proximo; // Se for o primeiro, ajusta o início da lista
            }

            destruir_projetil(index); // Destrói o projétil que colidiu

            // Verifica se o inimigo ainda está vivo
            if (victim->hp > 0)
            {
                return 0; // Inimigo sofreu dano, mas ainda não morreu
            }
            else
            {
                destroi_inimigo(victim); // Destroi o inimigo
                return 1;                // Inimigo morreu
            }
        }

        // Atualiza o controle para o próximo projétil
        anterior = index;
        index = (projetil *)index->proximo;
    }

    return 0; // Não houve colisão com nenhum projétil
}

// Implementação da função que verifica se um projétil acertou um chefe, a cada acerto o jogador ganha 10 pontos
unsigned char check_kill_chefe(jogador *killer, chefe *victim, unsigned int *score)
{
    projetil *anterior = NULL;
    projetil *index = killer->arma->shots;

    // Itera sobre todos os projéteis disparados pelo jogador
    while (index != NULL)
    {
        // Verifica se o projétil colidiu com o chefe no eixo X e Y
        if ((index->x >= victim->x - victim->sprite_info->largura / 2) &&
            (index->x <= victim->x + victim->sprite_info->largura / 2) &&
            (index->y >= victim->y - victim->sprite_info->altura / 2) &&
            (index->y <= victim->y + victim->sprite_info->altura / 2))
        {
            victim->hp--; // Reduz o HP do chefe
            *score += 10; // Aumenta a pontuação do jogador

            // Remove o projétil da lista
            if (anterior)
            {
                anterior->proximo = index->proximo; // Se não for o primeiro, ajusta o ponteiro do anterior
            }
            else
            {
                killer->arma->shots = (projetil *)index->proximo; // Se for o primeiro, ajusta o início da lista
            }

            destruir_projetil(index); // Destrói o projétil que colidiu

            // Verifica se o chefe ainda está vivo
            if (victim->hp > 0)
            {
                return 0; // Chefe sofreu dano, mas ainda não morreu
            }
            else
            {
                destroi_chefe(victim); // Destroi o chefe
                return 1;              // Chefe morreu
            }
        }

        // Atualiza o controle para o próximo projétil
        anterior = index;
        index = (projetil *)index->proximo;
    }

    return 0; // Não houve colisão com nenhum projétil
}

// Implementação da função que verifica se um projetil inimigo acertou o jogador
unsigned char check_player(inimigo *killer, jogador *victim)
{
    projetil *anterior = NULL;
    projetil *index = killer->arma->shots;

    // Itera sobre todos os projéteis disparados pelo inimigo
    while (index != NULL)
    {
        // Verifica se o projétil colidiu com o jogador no eixo X e Y
        if ((index->x >= victim->x - victim->face / 2) &&
            (index->x <= victim->x + victim->face / 2) &&
            (index->y >= victim->y - TAM_JOGADOR / 2) &&
            (index->y <= victim->y + TAM_JOGADOR / 2))
        {
            victim->hp--; // Reduz o HP do jogador

            // Remove o projétil da lista
            if (anterior)
            {
                anterior->proximo = index->proximo; // Se não for o primeiro, ajusta o ponteiro do anterior
            }
            else
            {
                killer->arma->shots = (projetil *)index->proximo; // Se for o primeiro, ajusta o início da lista
            }

            destruir_projetil(index); // Destrói o projétil que colidiu

            // Verifica se o jogador ainda está vivo
            if (victim->hp > 0)
            {
                return 0; // Jogador sofreu dano, mas ainda não morreu
            }
            else
            {
                destroi_jogador(victim); // Destroi o jogador
                return 1;                // Jogador morreu
            }
        }

        // Atualiza o controle para o próximo projétil
        anterior = index;
        index = (projetil *)index->proximo;
    }

    return 0; // Não houve colisão com nenhum projétil
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

    al_init();                  // Inicializa a biblioteca Allegro
    al_init_primitives_addon(); // Inicializa o addon de primitivas
    al_init_image_addon();      // Inicializa o addon de imagens
    al_init_font_addon();       // Inicializa o addon de fontes
    al_init_ttf_addon();        // Inicializa o addon de fontes TrueType
    al_install_keyboard();      // Habilita a entrada via teclado

    ALLEGRO_TIMER *timer = al_create_timer(1.0 / 30.0); // 30 FPS
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    ALLEGRO_FONT *font = al_create_builtin_font();
    ALLEGRO_DISPLAY *disp = al_create_display(X_SCREEN, Y_SCREEN);
    ALLEGRO_BITMAP *background = al_load_bitmap(PATH_CENARIO_2);

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_start_timer(timer);

    // Inicialização do jogador
    jogador *jogador_1 = criar_jogador(20, 60, 80, Y_SCREEN / 2, X_SCREEN, Y_SCREEN);
    if (!jogador_1)
        return 1;

    // Inicialização do sprite do jogador
    jogador_1->sprite = al_load_bitmap(PATH_JOGADOR);
    if (!jogador_1->sprite)
        return 1;

    unsigned char trajetoria = 0; // Inicializa o controle de trajetória
    unsigned int animation_counter_jogador = 0;
    float background_x = 0;

    // Inicialização da tela inicial
    tela_inicial_sprite *tela_inicial = criar_tela_inicial();
    if (!tela_inicial)
        return 1;

    // Inicialização do inimigo
    // inimigo *inimigo_1 = criar_inimigo(20, 60, X_SCREEN - 50, Y_SCREEN / 2, 1, X_SCREEN, Y_SCREEN);
    // if (!inimigo_1)
    //     return 1;

    // Inicialização do chefe
    chefe *chefe_1 = criar_chefe(20, 60, X_SCREEN - 100, Y_SCREEN / 2, 0, X_SCREEN, Y_SCREEN);
    if (!chefe_1)
        return 1;

    unsigned char jk = 0;       // Controle de dano do jogador pelo inimigo
    unsigned char ik = 0;       // Controle de dano causado pelo jogador ao inimigo
    unsigned char ck = 0;       // Controle de dano causado ao chefe
    unsigned char jk_arma1 = 0; // Controle de dano do jogador pela arma 1 do chefe
    unsigned char jk_arma2 = 0; // Controle de dano do jogador pela arma 2 do chefe
    unsigned int score = 0;     // Variável de pontuação

    /*-----------------------------------------------------------------------------------------*/
    /* TELA INICIAL */
    bool tela_inicial_ativa = true;
    ALLEGRO_EVENT event;

    while (true)
    {
        al_wait_for_event(queue, &event);

        if (tela_inicial_ativa)
        {
            if (event.type == ALLEGRO_EVENT_TIMER)
            {
                al_clear_to_color(al_map_rgb(0, 0, 0));
                atualizar_animacao_tela_inicial(tela_inicial, &animation_counter_jogador, VELOCIDADE_TELA_INICIAL);
                desenhar_tela_inicial(tela_inicial);
                al_flip_display();
            }
            else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            {
                break;
            }
            else if (event.type == ALLEGRO_EVENT_KEY_DOWN)
            {
                if (event.keyboard.keycode == ALLEGRO_KEY_S)
                {
                    tela_inicial_ativa = false;
                }
            }
        }
        else
        {
            if (event.type == ALLEGRO_EVENT_TIMER)
            {
                // Atualiza e desenha o background
                atualiza_e_desenha_background(background, &background_x, VELOCIDADE_BACKGROUND);

                // ik = check_kill_inimigo(jogador_1, inimigo_1, &score);
                // jk = check_player (inimigo_1, jogador_1);                

                // Atualiza animação do jogador
                atualizar_animacao_jogador(jogador_1, &animation_counter_jogador, ANIMATION_DELAY_JOGADOR);

                // Atualiza animação do inimigo
                // atualizar_animacao_inimigo(inimigo_1, &animation_counter_jogador, ANIMATION_DELAY_INIMIGO);
                atualizar_animacao_chefe(chefe_1, &animation_counter_jogador, ANIMATION_DELAY_CHEFE);

                // Atualiza o jogador e projéteis
                atualiza_posicao(jogador_1);

                // Desenha o jogador
                desenhar_jogador(jogador_1);

                // Desenha o iniimigo
                // desenhar_inimigo(inimigo_1);
                desenhar_chefe(chefe_1);

                // Movimentação do inimigo
                // mover_inimigo(inimigo_1, 1, &trajetoria, X_SCREEN, Y_SCREEN);
                mover_chefe(chefe_1, 1, trajetoria, X_SCREEN, Y_SCREEN);

                // Desenha os corações de HP
                desenhar_hp(jogador_1, 15, 15);

                // Desenha o score do jogador
                al_draw_textf(font, al_map_rgb(255, 255, 255), X_SCREEN - 150, 40, 0, "Score: %05d", score);

                // Desenha os projéteis do jogador
                for (projetil *p = jogador_1->arma->shots; p != NULL; p = (projetil *)p->proximo)
                    desenhar_projetil_jogador(p);

                // Atualiza a arma do jogador
                if (jogador_1->arma->timer)
                    atualiza_arma(jogador_1->arma);

                // Desenha os projeteis do chefe
                for (projetil *p = chefe_1->arma1->shots; p != NULL; p = (projetil *)p->proximo)
                {
                    desenhar_projetil_chefe_0(p); // Função para desenhar projétil da arma 1
                }

                // Desenha os projéteis disparados pela segunda arma do chefe
                for (projetil *p = chefe_1->arma2->shots; p != NULL; p = (projetil *)p->proximo)
                {
                    desenhar_projetil2_chefe_0(p); // Função para desenhar projétil da arma 2
                }

                al_flip_display();
            }
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
