#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "fases.h"

// Controle de dano e score
unsigned char jk = 0;
unsigned char ik = 0;
unsigned char ck = 0;
unsigned char jk_chefe = 0;
unsigned int score = 0;

/*--------------------------------------------------------------------------------------*/
/* FUNÇÕES AUXILIARES */
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

// Implementação da função que verifica se um projetil inimigo acertou o jogador, cada acerto reduz 1 ponto de vida
unsigned char check_player(inimigo **killer, jogador *victim)
{
    projetil *anterior = NULL;
    projetil *index = (*killer)->arma->shots;

    // Itera sobre todos os projéteis disparados pelo inimigo
    while (index != NULL)
    {
        // Verifica se o projétil colidiu com o jogador no eixo X e Y
        if ((index->x >= victim->x - victim->face / 2) &&
            (index->x <= victim->x + victim->face / 2) &&
            (index->y >= victim->y - QUADRADO_SPRITE_JOGADOR / 2) &&
            (index->y <= victim->y + QUADRADO_SPRITE_JOGADOR / 2))
        {
            victim->hp--; // Reduz o HP do jogador

            // Remove o projétil da lista
            if (anterior)
            {
                anterior->proximo = index->proximo; // Se não for o primeiro, ajusta o ponteiro do anterior
            }
            else
            {
                (*killer)->arma->shots = (projetil *)index->proximo; // Se for o primeiro, ajusta o início da lista
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
}

// Implementação da função que verifica se um projétil de chefe acertou o jogador, cada acerto reduz 2 pontos de vida
unsigned char check_player_chefe(chefe *killer, jogador *victim)
{
    projetil *anterior = NULL;
    projetil *index = killer->arma1->shots;

    // Itera sobre todos os projéteis disparados pelo chefe
    while (index != NULL)
    {
        // Verifica se o projétil colidiu com o jogador no eixo X e Y
        if ((index->x >= victim->x - victim->face / 2) &&
            (index->x <= victim->x + victim->face / 2) &&
            (index->y >= victim->y - QUADRADO_SPRITE_JOGADOR / 2) &&
            (index->y <= victim->y + QUADRADO_SPRITE_JOGADOR / 2))
        {
            victim->hp -= 2; // Reduz o HP do jogador

            // Remove o projétil da lista
            if (anterior)
            {
                anterior->proximo = index->proximo; // Se não for o primeiro, ajusta o ponteiro do anterior
            }
            else
            {
                killer->arma1->shots = (projetil *)index->proximo; // Se for o primeiro, ajusta o início da lista
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

/*--------------------------------------------------------------------------------------*/
/* Funções de inicialização, atualização e finalização de cada fase */

// Função de inicialização de fase
void inicializa_fase(ALLEGRO_BITMAP **background, jogador **jogador_1, inimigo **lista_inimigos, chefe **chefe_1,
                     chefe **chefe_2, int fase)
{
    if (fase == 1)
    {
        *background = al_load_bitmap(PATH_CENARIO_FASE1);
        if (!*background)
            return;

        *jogador_1 = criar_jogador(20, 60, 80, Y_SCREEN / 2, X_SCREEN, Y_SCREEN);
        if (!*jogador_1)
            return;

        (*jogador_1)->sprite = al_load_bitmap(PATH_JOGADOR);
        if (!(*jogador_1)->sprite)
            return;

        *lista_inimigos = NULL;

        *chefe_1 = criar_chefe(20, 60, X_SCREEN - 100, Y_SCREEN / 2, 0, X_SCREEN, Y_SCREEN);
        if (!*chefe_1)
            return;
    }
    else if (fase == 2)
    {
        *background = al_load_bitmap(PATH_CENARIO_FASE2);
        if (!*background)
            return;

        *jogador_1 = criar_jogador(20, 60, 80, Y_SCREEN / 2, X_SCREEN, Y_SCREEN);
        if (!*jogador_1)
            return;

        (*jogador_1)->sprite = al_load_bitmap(PATH_JOGADOR);
        if (!(*jogador_1)->sprite)
            return;

        *chefe_2 = criar_chefe(20, 60, X_SCREEN - 100, Y_SCREEN / 2, 1, X_SCREEN, Y_SCREEN);
        if (!*chefe_2)
            return;

        *lista_inimigos = NULL;
    }
}

void atualiza_fase(ALLEGRO_BITMAP *background, jogador *jogador_1, inimigo **lista_inimigos, chefe *chefe_1,
                   chefe *chefe_2, int fase)
{
    static float background_x = 0;                 // Posição de rolagem do fundo
    ALLEGRO_FONT *font = al_create_builtin_font(); // Fonte para exibir o score

    // Atualiza e desenha o fundo
    atualiza_e_desenha_background(background, &background_x, VELOCIDADE_BACKGROUND);

    // Atualiza e desenha o jogador
    atualizar_animacao_jogador(jogador_1, &jogador_1->animation_counter, ANIMATION_DELAY_JOGADOR);
    atualiza_posicao(jogador_1);
    desenhar_jogador(jogador_1);
    desenhar_hp(jogador_1, 15, 15);

    // Exibe o score
    al_draw_textf(font, al_map_rgb(255, 255, 255), X_SCREEN - 150, 40, 0, "Score: %05d", score);

    // Desenha os projéteis do jogador
    for (projetil *p = jogador_1->arma->shots; p != NULL; p = (projetil *)p->proximo)
        desenhar_projetil_jogador(p);

    if (jogador_1->arma->timer)
        atualiza_arma(jogador_1->arma);

    atualizar_criacao_inimigo(lista_inimigos);

    // Controle do score
    jk = check_player(lista_inimigos, jogador_1);

    inimigo *anterior = NULL;
    inimigo *atual = *lista_inimigos;
    while (atual != NULL)
    {
        atualizar_animacao_inimigo(atual, ANIMATION_DELAY_INIMIGO);
        mover_inimigo(atual, 1, NULL, X_SCREEN, Y_SCREEN_MOVIMENTO);
        desenhar_inimigo(atual);

        for (projetil *p = atual->arma->shots; p != NULL; p = (projetil *)p->proximo)
            desenhar_projetil_inimigo_fase_1(p);

        // Verifica se o inimigo foi destruído
    }

        // Se o score for maior que X, o chefe aparece, pois significa que todos os inimigos foram derrotados
        // Se o score for menor que X, o chefe não aparece, algum inimigo não foi derrotado, portanto o jogador perdeu!

        unsigned int animation_counter_chefe = 0;
        // 10 pontos por cada tiro no inimigo
        // Inimigo do tipo 0 tem hp == 2 (mais hp pq não atira)
        // Inimigo do tipo 1 tem hp == 1 (menso hp pq atira)
        if (score >= 10 * (2 * (QNTD_INIM_TIPO_0) + (QNTD_INIM_TIPO_0)))
        {
            if (fase == 1)
            {
                atualizar_animacao_chefe(chefe_1, &animation_counter_chefe, ANIMATION_DELAY_CHEFE);
                mover_chefe(chefe_1, CHEFE0_STEP, 0, X_SCREEN, Y_SCREEN_MOVIMENTO);
                desenhar_chefe(chefe_1);

                for (projetil *p = chefe_1->arma1->shots; p != NULL; p = (projetil *)p->proximo)
                    desenhar_projetil_chefe_0(p);

                if (chefe_1->arma1->timer)
                    atualiza_arma(chefe_1->arma1);

                for (projetil *p = chefe_1->arma2->shots; p != NULL; p = (projetil *)p->proximo)
                    desenhar_projetil2_chefe_0(p);

                if (chefe_1->arma2->timer)
                    atualiza_arma(chefe_1->arma2);

                // Controle do score
                // jk_chefe = check_player_chefe(chefe_1, jogador_1);
                // ck = check_kill_chefe(jogador_1, chefe_1, &score);
                // se o jogador matar o chefe, ele avanca para a próxima fase
            }
        }
        // else{
        //     // Tela de Game Over
        //     al_clear_to_color(al_map_rgb(0, 0, 0));
        //     al_draw_text(font, al_map_rgb(255, 255, 255), X_SCREEN / 2 - 40, Y_SCREEN / 2 - 15, 0, "GAME OVER!");
        // }

        al_flip_display();

        al_destroy_font(font); // Libera a memória da fonte
    }

    void finaliza_fase(ALLEGRO_BITMAP * background, jogador * jogador_1, inimigo * lista_inimigos, chefe * chefe_1,
                       chefe * chefe_2, int fase)
    {
        if (fase == 1)
        {
            al_destroy_bitmap(background);
            destroi_jogador(jogador_1);
            destroi_chefe(chefe_1);
            for (inimigo *atual = lista_inimigos; atual != NULL; atual = atual->proximo)
                destroi_inimigo(atual);
        }
        else if (fase == 2)
        {
            al_destroy_bitmap(background);
            destroi_jogador(jogador_1);
            destroi_chefe(chefe_2);
            for (inimigo *atual = lista_inimigos; atual != NULL; atual = atual->proximo)
                destroi_inimigo(atual);
        }
    }
