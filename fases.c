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
// Implementação da função que verifica se um projétil da nave do jogador acertou um inimigo, a cada acerto o jogador ganha 10 pontos
unsigned char check_kill_inimigo(jogador *killer, inimigo *victim, unsigned int *score)
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

    al_draw_textf(font, al_map_rgb(255, 255, 255), X_SCREEN - 150, 40, 0, "Score: %05d", score);

    for (projetil *p = jogador_1->arma->shots; p != NULL; p = (projetil *)p->proximo)
        desenhar_projetil_jogador(p);

    if (jogador_1->arma->timer)
        atualiza_arma(jogador_1->arma);

    atualizar_criacao_inimigo(lista_inimigos);
    inimigo *anterior = NULL;
    inimigo *atual = *lista_inimigos;

    while (atual != NULL)
    {
        inimigo *proximo = atual->proximo; // Armazena o próximo antes de possivelmente destruir o atual

        // Atualiza a animação e movimentação do inimigo
        atualizar_animacao_inimigo(atual, ANIMATION_DELAY_INIMIGO);
        mover_inimigo(atual, 1, NULL, X_SCREEN, Y_SCREEN_MOVIMENTO);
        desenhar_inimigo(atual);

        // Desenha os projéteis do inimigo
        for (projetil *p = atual->arma->shots; p != NULL; p = (projetil *)p->proximo)
            desenhar_projetil_inimigo_fase_1(p);

        // Verifica se o projétil do jogador acertou o inimigo
        if (check_kill_inimigo(jogador_1, atual, &score))
        {
            // Inimigo foi destruído
            if (anterior)
            {
                anterior->proximo = proximo; // Remove o inimigo da lista encadeada
            }
            else
            {
                *lista_inimigos = proximo; // Ajusta o início da lista se o primeiro foi destruído
            }

            destroi_inimigo(atual); // Destrói o inimigo
        }
        else
        {
            anterior = atual; // Atualiza o ponteiro anterior se o inimigo não foi destruído
        }

        atual = proximo; // Avança para o próximo inimigo
    }

    al_flip_display();

    al_destroy_font(font); // Libera a memória da fonte
}

void finaliza_fase(ALLEGRO_BITMAP *background, jogador *jogador_1, inimigo *lista_inimigos, chefe *chefe_1,
                   chefe *chefe_2, int fase)
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
