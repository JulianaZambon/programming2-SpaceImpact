#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "fases.h"

/*-------------------------------------------------------------------*/
/* VARIAVEIS E FLAGS */
unsigned int score = 0;      // Variável de pontuação
unsigned char game_over = 0; // Flag que sinaliza o fim do jogo
bool venceu_fase = false;    // Flag que sinaliza a vitória na fase

/*-------------------------------------------------------------------*/
/* FUNÇÕES AUXILIARES */

// Implementação da função que verifica se um projétil da nave do jogador
// acertou um inimigo,a cada acerto o jogador ganha 10 pontos
unsigned char verifica_acerto_em_inimigo(jogador *killer, inimigo *victim, unsigned int *score)
{
    projetil *anterior = NULL;
    projetil *index = killer->arma->shots;
    projetil *temp = NULL; // Ponteiro temporário para remoção segura

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

            // Remove o projétil da lista de forma segura
            temp = index;
            if (anterior)
            {
                anterior->proximo = index->proximo;
            }
            else
            {
                killer->arma->shots = index->proximo;
            }

            index = index->proximo;  // Atualiza o índice antes de destruir o projétil
            destruir_projetil(temp); // Destrói o projétil que colidiu

            // Verifica se o inimigo ainda está vivo
            if (victim->hp > 0)
            {
                return 0; // Inimigo sofreu dano, mas ainda está vivo
            }
            else
            {
                return 1; // Inimigo morreu, sinalizar destruição
            }
        }

        // Atualiza o controle para o próximo projétil
        anterior = index;
        index = index->proximo;
    }

    return 0; // Nenhum projétil acertou o inimigo
}

// Implementação da função que verifica se um projétil acertou um chefe,
// a cada acerto o jogador ganha 10 pontos
unsigned char verifica_acerto_em_chefe(jogador *killer, chefe *victim, unsigned int *score)
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
                return 1; // Chefe morreu, mas não destrói imediatamente
            }
        }

        // Atualiza o controle para o próximo projétil
        anterior = index;
        index = (projetil *)index->proximo;
    }

    return 0; // Não houve colisão com nenhum projétil
}

// Implementação da função que verifica se um projétil inimigo acertou o jogador,
// cada acerto reduz 1 ponto de vida
unsigned char verifica_acerto_no_jogador(inimigo **killer, jogador *victim)
{
    if (*killer == NULL || (*killer)->arma == NULL)
    {
        return 0; // Retorna 0 se o inimigo ou a arma forem NULL
    }

    projetil *anterior = NULL;
    projetil *index = (*killer)->arma->shots;

    // Itera sobre todos os projéteis disparados pelo inimigo
    while (index != NULL)
    {
        projetil *proximo = index->proximo; // Armazena o próximo antes da possível remoção

        // Verifica se o projétil colidiu com o jogador no eixo X e Y
        if ((index->x >= victim->x - victim->face / 2) &&
            (index->x <= victim->x + victim->face / 2) &&
            (index->y >= victim->y - QUADRADO_SPRITE_JOGADOR / 2) &&
            (index->y <= victim->y + QUADRADO_SPRITE_JOGADOR / 2))
        {
            victim->hp--; // Reduz o HP do jogador

            // Remove o projétil da lista de forma segura
            if (anterior)
            {
                anterior->proximo = proximo;
            }
            else
            {
                (*killer)->arma->shots = proximo; // Ajusta o início da lista se necessário
            }

            destruir_projetil(index); // Destrói o projétil que colidiu

            // Verifica se o jogador morreu após o dano
            if (victim->hp <= 0)
            {
                return 1; // Jogador morreu
            }
        }

        // Atualiza o controle para o próximo projétil
        anterior = index;
        index = proximo;
    }

    return 0; // Retorna 0 se nenhum projétil acertou o jogador
}

// Implementação da função que verifica se um projétil de chefe acertou o jogador,
// cada acerto reduz 1 ponto de vida
// O chefe possui 2 armas, cada uma com seu próprio tipo de projétil e movimentação
unsigned char verifica_acerto_do_chefe_no_jogador(chefe *killer, jogador *victim)
{
    projetil *anterior = NULL;
    projetil *atual = NULL;
    unsigned char jogador_morto = 0;

    // Define as áreas de colisão do jogador
    int jogador_min_x = victim->x - victim->face / 2;
    int jogador_max_x = victim->x + victim->face / 2;
    int jogador_min_y = victim->y - QUADRADO_SPRITE_JOGADOR / 2;
    int jogador_max_y = victim->y + QUADRADO_SPRITE_JOGADOR / 2;

    // Verificar projéteis da arma 1
    anterior = NULL;
    atual = killer->arma1->shots;
    while (atual != NULL)
    {
        if ((atual->x >= jogador_min_x) && (atual->x <= jogador_max_x) &&
            (atual->y >= jogador_min_y) && (atual->y <= jogador_max_y))
        {
            victim->hp -= 1;

            // Remove o projetil da lista
            if (anterior != NULL)
            {
                anterior->proximo = atual->proximo;
            }
            else
            {
                killer->arma1->shots = atual->proximo;
            }

            projetil *temp = atual;  // Armazena o projetil atual antes de destruí-lo
            atual = atual->proximo;  // Avança o ponteiro para o próximo projetil
            destruir_projetil(temp); // Destrói o projetil

            // Verifica se o jogador morreu
            if (victim->hp <= 0)
            {
                jogador_morto = 1;
                break; // Encerra a busca após a morte do jogador
            }
        }
        else
        {
            anterior = atual;
            atual = atual->proximo;
        }
    }

    // Verificar projéteis da arma 2
    anterior = NULL;
    atual = killer->arma2->shots;
    while (atual != NULL)
    {
        if ((atual->x >= jogador_min_x) && (atual->x <= jogador_max_x) &&
            (atual->y >= jogador_min_y) && (atual->y <= jogador_max_y))
        {
            victim->hp -= 1;

            // Remove o projetil da lista
            if (anterior != NULL)
            {
                anterior->proximo = atual->proximo;
            }
            else
            {
                killer->arma2->shots = atual->proximo;
            }

            projetil *temp = atual;  // Armazena o projetil atual antes de destruí-lo
            atual = atual->proximo;  // Avança o ponteiro para o próximo projetil
            destruir_projetil(temp); // Destrói o projetil

            // Verifica se o jogador morreu
            if (victim->hp <= 0)
            {
                jogador_morto = 1;
                break; // Encerra a busca após a morte do jogador
            }
        }
        else
        {
            anterior = atual;
            atual = atual->proximo;
        }
    }

    // Retorna 1 se o jogador morreu, 0 caso contrário
    return jogador_morto;
}

// Função principal da lógica do ataque especial
void logica_ataque_especial(jogador *jogador, simbolo_ataque_especial **simbolo_ptr, unsigned int delay,
                            unsigned short max_x, unsigned short max_y)
{
    if (!jogador || !simbolo_ptr || !*simbolo_ptr)
        return;

    /*-------------------------------------------------------------------*/
    /* DESENHO E MOVIMENTAÇÃO DO SÍMBOLO DO ATAQUE ESPECIAL */

    simbolo_ataque_especial *simbolo = *simbolo_ptr;

    // Atualiza a animação do símbolo do ataque especial
    atualizar_animacao_simbolo_ataque_especial(simbolo, delay);

    // Move o símbolo do ataque especial para a esquerda
    if (simbolo->x > 0)
    {
        simbolo->x -= 2;
    }
    else if (simbolo->x <= 0)
    {
        destruir_simbolo_ataque_especial(simbolo);
        *simbolo_ptr = NULL; // Reseta o ponteiro do símbolo
    }

    desenhar_simbolo_ataque_especial(simbolo);

    /*-------------------------------------------------------------------*/
    /* LÓGICA DE ATIVAÇÃO DO ATAQUE ESPECIAL */
    /*
    RESUMO: 1.Verifica se houve colisão do jogador com o símbolo do ataque especial
            2.Se houve colisão, os próximos projéteis disparados pelo jogador serão do ataque especial
            3.Desenha os projéteis do ataque especial
            4.Atualiza o tempo do ataque especial, que é de no máximo 5s
    */
}

/*---------------------------------------------------------------------------*/
/* Funções de inicialização, atualização e finalização de cada fase */

// Função de inicialização de fase
void inicializa_fase(ALLEGRO_BITMAP **background, jogador **jogador_1, inimigo **lista_inimigos_fase1,
                     inimigo **lista_inimigos_fase2, chefe **chefe_1, chefe **chefe_2, int fase)
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

        // Inicializa o ataque especial do jogador na fase 1
        (*jogador_1)->especial = criar_ataque_especial();
        if (!(*jogador_1)->especial)
            return;

        // Inicializa o símbolo do ataque especial
        (*jogador_1)->especial->simbolo = criar_simbolo_ataque_especial(X_SCREEN - 100, Y_SCREEN / 2, PATH_SIMBOLO_ATAQUE_ESPECIAL);
        if (!(*jogador_1)->especial->simbolo)
        {
            free((*jogador_1)->especial); // Libera a memória caso a criação falhe
            return;
        }

        // Inicializa a lista de inimigos da fase 1
        *lista_inimigos_fase1 = NULL;

        // Inicializa o chefe tipo 0
        *chefe_1 = criar_chefe(20, 60, X_SCREEN - 100, Y_SCREEN / 2, 0, X_SCREEN, Y_SCREEN);
        if (!*chefe_1)
            return;
    }
    else if (fase == 2)
    {
        *background = al_load_bitmap(PATH_CENARIO_FASE2);
        if (!*background)
            return;

        *jogador_1 = criar_jogador(20, 60, 80, Y_SCREEN / 2, X_SCREEN, Y_SCREEN_MOVIMENTO);
        if (!*jogador_1)
            return;

        (*jogador_1)->sprite = al_load_bitmap(PATH_JOGADOR);
        if (!(*jogador_1)->sprite)
            return;

        // Inicializa o ataque especial do jogador na fase 2

        // Inicializa a lista de inimigos da fase 2
        *lista_inimigos_fase2 = NULL;

        // Inicializa o chefe tipo 1
        *chefe_2 = criar_chefe(20, 60, X_SCREEN - 100, Y_SCREEN / 2, 1, X_SCREEN, Y_SCREEN_MOVIMENTO);
        if (!*chefe_2)
            return;
    }
}

// Função de atualização de fase
void atualiza_fase(ALLEGRO_BITMAP *background, jogador *jogador_1, inimigo **lista_inimigos_fase1,
                   inimigo **lista_inimigos_fase2, chefe *chefe_1, chefe *chefe_2, int fase)
{
    static float background_x = 0; // Posição de rolagem do fundo
    ALLEGRO_FONT *font = al_create_builtin_font();

    // Atualiza e desenha o fundo
    atualiza_e_desenha_background(background, &background_x, VELOCIDADE_BACKGROUND);

    /* JOGADOR */
    atualizar_animacao_jogador(jogador_1, &jogador_1->animation_counter, ANIMATION_DELAY_JOGADOR);
    atualiza_posicao(jogador_1);
    desenhar_jogador(jogador_1);
    desenhar_hp(jogador_1, 15, 15);

    /* SCORE */
    al_draw_textf(font, al_map_rgb(255, 255, 255), X_SCREEN - 150, 40, 0, "Score: %05d", score);

    // Desenha os projéteis do jogador
    for (projetil *p = jogador_1->arma->shots; p != NULL; p = (projetil *)p->proximo)
        desenhar_projetil_jogador(p);

    if (jogador_1->arma->timer)
        atualiza_arma(jogador_1->arma);

    /*---------------------------------------------------------------------------*/
    /* LÓGICA DA FASE 01 */
    if (fase == 1)
    {
        /* INIMIGOS*/
        atualizar_criacao_inimigo_fase1(lista_inimigos_fase1);
        inimigo *anterior = NULL;               // Inicializa o ponteiro para o inimigo anterior como NULL
        inimigo *atual = *lista_inimigos_fase1; // Ponteiro para o início da lista
        int jogador_morto = 0;                  // Flag para verificar se o jogador morreu

        // Loop principal para atualizar, mover e desenhar inimigos da fase 01
        while (atual != NULL)
        {
            inimigo *proximo = atual->proximo; // Armazena o próximo inimigo
            // Atualiza a animação e movimentação do inimigo
            atualizar_animacao_inimigo(atual, ANIMATION_DELAY_INIMIGO);
            mover_inimigo(atual, 1, NULL, X_SCREEN, Y_SCREEN_MOVIMENTO);
            desenhar_inimigo(atual);

            // Desenha os projéteis do inimigo
            for (projetil *p = atual->arma->shots; p != NULL; p = (projetil *)p->proximo)
                desenhar_projetil_inimigo_fase_1(p);

            // Verifica se o projétil do inimigo acertou o jogador
            if (verifica_acerto_no_jogador(&atual, jogador_1))
            {
                if (jogador_1->hp <= 0)
                {
                    destroi_jogador(jogador_1); // Destrói o jogador
                    game_over = 1;
                    jogador_morto = 1;
                }
            }
            if (jogador_morto)
            {
                break; // Sai do loop se o jogador morreu
            }
            // Verifica se o projétil do jogador acertou o inimigo
            if (verifica_acerto_em_inimigo(jogador_1, atual, &score))
            {
                // Remove o inimigo da lista
                if (anterior)
                {
                    anterior->proximo = proximo; // Atualiza a referência do próximo
                }
                else
                {
                    *lista_inimigos_fase1 = proximo; // Atualiza a cabeça da lista
                }
                destroi_inimigo(atual); // Destrói o inimigo
            }
            else
            {
                anterior = atual; // Atualiza o anterior se o inimigo não foi destruído
            }
            atual = proximo; // Avança para o próximo inimigo
        }


        /* LÓGICA DO CHEFE - FASE 01 */
        // Verifica se todos os inimigos foram derrotados para então o chefe aparecer
        if (score >= (10 * (HP_INIMIGO_0 * (QNTD_INIM_TIPO_0) +  HP_INIMIGO_1 * (QNTD_INIM_TIPO_1))))
        {
            if (chefe_1 != NULL && chefe_1->hp > 0)
            {
                /* LÓGICA DO ATAQUE ESPECIAL ADQUIRIDO NO MAPA PELO JOGADOR */
                /* para ajudar na luta contra o chefe */
                logica_ataque_especial(jogador_1, &jogador_1->especial->simbolo, ANIMATION_DELAY_SIMBOLO_ATAQUE_ESPECIAL, X_SCREEN, Y_SCREEN);

                atualizar_animacao_chefe(chefe_1, &chefe_1->animation_counter, ANIMATION_DELAY_CHEFE);
                mover_chefe(chefe_1, CHEFE0_STEP, 0, X_SCREEN, Y_SCREEN_MOVIMENTO);
                desenhar_chefe(chefe_1);

                // Desenha os projéteis das armas do chefe
                for (projetil *p = chefe_1->arma1->shots; p != NULL; p = (projetil *)p->proximo)
                    desenhar_projetil_chefe_0(p);

                for (projetil *p = chefe_1->arma2->shots; p != NULL; p = (projetil *)p->proximo)
                    desenhar_projetil2_chefe_0(p);

                // Verifica se o projétil do jogador acertou o chefe
                if (verifica_acerto_em_chefe(jogador_1, chefe_1, &score))
                {
                    if (chefe_1->hp <= 0)
                    {
                        venceu_fase = true; // Sinaliza que o jogador venceu a fase
                        fase = 2;           // Avança para a próxima fase
                    }
                }

                // Verifica se o projétil do chefe acertou o jogador
                // Se o jogador morreu, exibe a tela de game over e o jogo acaba
                if (verifica_acerto_do_chefe_no_jogador(chefe_1, jogador_1))
                {
                    if (jogador_1->hp <= 0)
                    {
                        destroi_jogador(jogador_1); // Destrói o jogador
                        game_over = 1;
                    }
                }
            }
        }
    }

    /*---------------------------------------------------------------------------*/
    /* LÓGICA DA FASE 02 */
    else if (fase == 2)
    {
        /* INIMIGOS*/
        atualizar_criacao_inimigo_fase2(lista_inimigos_fase2);
        inimigo *anterior = NULL;               // Inicializa o ponteiro para o inimigo anterior como NULL
        inimigo *atual = *lista_inimigos_fase2; // Ponteiro para o início da lista
        int jogador_morto = 0;                  // Flag para verificar se o jogador morreu

        // Loop principal para atualizar, mover e desenhar inimigos da fase 02
        while (atual != NULL)
        {
            inimigo *proximo = atual->proximo; // Armazena o próximo inimigo
            // Atualiza a animação e movimentação do inimigo
            atualizar_animacao_inimigo(atual, ANIMATION_DELAY_INIMIGO);
            mover_inimigo(atual, 1, NULL, X_SCREEN, Y_SCREEN_MOVIMENTO);
            desenhar_inimigo(atual);

            // Desenha os projéteis do inimigo
            for (projetil *p = atual->arma->shots; p != NULL; p = (projetil *)p->proximo)
                desenhar_projetil_inimigo_fase_2(p);

            // Verifica se o projétil do inimigo acertou o jogador
            if (verifica_acerto_no_jogador(&atual, jogador_1))
            {
                if (jogador_1->hp <= 0)
                {
                    destroi_jogador(jogador_1); // Destrói o jogador
                    game_over = 1;
                    jogador_morto = 1;
                }
            }
            if (jogador_morto)
            {
                break; // Sai do loop se o jogador morreu
            }
            // Verifica se o projétil do jogador acertou o inimigo
            if (verifica_acerto_em_inimigo(jogador_1, atual, &score))
            {
                // Remove o inimigo da lista
                if (anterior)
                {
                    anterior->proximo = proximo; // Atualiza a referência do próximo
                }
                else
                {
                    *lista_inimigos_fase2 = proximo; // Atualiza a cabeça da lista
                }
                destroi_inimigo(atual); // Destrói o inimigo
            }
            else
            {
                anterior = atual; // Atualiza o anterior se o inimigo não foi destruído
            }
            atual = proximo; // Avança para o próximo inimigo
        }

        /* LÓGICA DO CHEFE - FASE 02 */
        int animation_counter_chefe = 0;

        // Verifica se todos os inimigos foram derrotados
        // SCORE TOTAL fase 01 eh 10 * (2 * (QNTD_INIM_TIPO_0) + (QNTD_INIM_TIPO_1) + (HP_CHEFE_0))
        // SCORE TOTAL fase 02 para aparecer o chefe eh
        // SCORE TOTAL DA FASE 01 + 10 * (2 * (QNTD_INIM_TIPO_2) + (QNTD_INIM_TIPO_3))
        if (score >= (10 * (HP_INIMIGO_0 * (QNTD_INIM_TIPO_0) +  HP_INIMIGO_1 * (QNTD_INIM_TIPO_1) + (HP_CHEFE_0)) + 10 *
                            (HP_INIMIGO_2 * (QNTD_INIM_TIPO_2) +  HP_INIMIGO_3 * (QNTD_INIM_TIPO_3))))
        {
            if (chefe_2 != NULL && chefe_2->hp > 0)
            {
                atualizar_animacao_chefe(chefe_2, &chefe_2->animation_counter, ANIMATION_DELAY_CHEFE);
                mover_chefe(chefe_2, CHEFE1_STEP, 0, X_SCREEN, Y_SCREEN_MOVIMENTO);
                desenhar_chefe(chefe_2);

                // Desenha os projéteis das armas do chefe
                for (projetil *p = chefe_2->arma1->shots; p != NULL; p = (projetil *)p->proximo)
                    desenhar_projetil_chefe_1(p);

                for (projetil *p = chefe_2->arma2->shots; p != NULL; p = (projetil *)p->proximo)
                    desenhar_projetil2_chefe_1(p);

                // Verifica se o projétil do jogador acertou o chefe
                if (verifica_acerto_em_chefe(jogador_1, chefe_2, &score))
                {
                    if (chefe_2->hp <= 0)
                    {
                        venceu_fase = true;
                    }
                }

                // Verifica se o projétil do chefe acertou o jogador
                // Se o jogador morreu, exibe a tela de game over e o jogo acaba
                if (verifica_acerto_do_chefe_no_jogador(chefe_1, jogador_1))
                {
                    if (jogador_1->hp <= 0)
                    {
                        destroi_jogador(jogador_1); // Destrói o jogador
                        game_over = 1;
                    }
                }
            }
        }
    }
    /*---------------------------------------------------------------------------*/
    /* TELA DE GAME OVER */
    if (game_over)
    {
        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_textf(font, al_map_rgb(255, 255, 255), X_SCREEN / 2 - 60, Y_SCREEN / 2, 0, "GAME OVER");
        al_flip_display();
        al_rest(7.0); // Aguarda 7 segundos antes de fechar o jogo
    }

    al_flip_display();     // Atualiza a tela
    al_destroy_font(font); // Libera a memória da fonte
}

void finaliza_fase(ALLEGRO_BITMAP *background, jogador *jogador_1, inimigo *lista_inimigos_fase1,
                   inimigo *lista_inimigos_fase2, chefe *chefe_1, chefe *chefe_2, int fase)
{
    // Libera a memória do jogador
    destroi_jogador(jogador_1);

    // Libera a memória dos inimigos da fase 1
    while (lista_inimigos_fase1 != NULL)
    {
        inimigo *temp = lista_inimigos_fase1;
        lista_inimigos_fase1 = lista_inimigos_fase1->proximo;
        destroi_inimigo(temp);
    }

    // Libera a memória dos inimigos da fase 2
    while (lista_inimigos_fase2 != NULL)
    {
        inimigo *temp = lista_inimigos_fase2;
        lista_inimigos_fase2 = lista_inimigos_fase2->proximo;
        destroi_inimigo(temp);
    }

    // Libera a memória do chefe da fase 1
    if (chefe_1 != NULL)
    {
        destroi_chefe(chefe_1);
    }

    // Libera a memória do chefe da fase 2
    if (chefe_2 != NULL)
    {
        destroi_chefe(chefe_2);
    }

    // Libera a memória do background
    al_destroy_bitmap(background);
}
