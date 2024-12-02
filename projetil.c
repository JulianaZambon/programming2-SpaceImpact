#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <stdlib.h>
#include <math.h>

// Inclusão de bibliotecas locais
#include "configuracoes.h"
#include "projetil.h"

/*-----------------------------------------------------------------------------------------*/
/* FUNÇÕES */

// Função de criação de um projetil
projetil *criar_projetil(unsigned short x, unsigned short y, unsigned char trajetoria, projetil *proximo)
{
    projetil *novo_projetil = (projetil *)malloc(sizeof(*novo_projetil)); // Aloca memória na heap para um novo projetil
    if (!novo_projetil)
        return NULL;

    novo_projetil->x = x;                   // Insere a posição inicial de X
    novo_projetil->y = y;                   // Insere a posição inicial de Y
    novo_projetil->trajetoria = trajetoria; // Insere a trajetória do projetil
    novo_projetil->proximo = proximo;       // Insere o próximo projetil na lista

    return novo_projetil;
}
// Função que atualiza o posicionamento de projéteis conforme o movimento dos mesmos
void mover_projetil(projetil **elements)
{
    projetil *anterior = NULL;
    projetil *atual = *elements; // Começa a partir do primeiro projetil na lista

    while (atual != NULL)
    {
        // Movimenta o projetil baseado na sua trajetória
        if (atual->trajetoria == 0) // Esquerda
        {
            atual->x -= PROJETIL_MOVE; // Move o projetil para a esquerda
        }
        else if (atual->trajetoria == 1) // Direita
        {
            atual->x += PROJETIL_MOVE; // Move o projetil para a direita
        }

        // Verifica se o projetil saiu da tela (no eixo X)
        if (atual->x < 0 || atual->x > X_SCREEN)
        {
            projetil *proximo = atual->proximo;

            if (anterior)
                anterior->proximo = proximo; // Remove o projetil da lista
            else
                *elements = proximo; // Atualiza o início da lista

            destruir_projetil(atual); // Libera memória do projetil fora da tela
            atual = proximo;          // Atualiza para o próximo projetil
        }
        else
        {
            // Avança para o próximo projetil
            anterior = atual;
            atual = atual->proximo;
        }
    }
}

// Função de destruição de um projetil
void destruir_projetil(projetil *element)
{
    if (element)
    {
        free(element); // Libera a memória do projetil
    }
}

/*-----------------------------------------------------------------------------------------*/
/* DESENHO DE PROJETEIS*/

/* JOGADOR*/

/* FUNÇÕES AUXILIARES PARA DESENHO DE PROJETIL */

ALLEGRO_COLOR cor(int r, int g, int b)
{
    return al_map_rgb(r, g, b);
}

void desenhar_retorno_pulsante(float variacao, float x, float y, ALLEGRO_COLOR cor_interna, ALLEGRO_COLOR cor_1, ALLEGRO_COLOR cor_2)
{
    // Função para desenhar círculos com efeito de pulsação
    al_draw_filled_circle(x, y, 10 + variacao, cor_2);
    al_draw_filled_circle(x, y, 8 + variacao / 2, cor_1);
    al_draw_filled_circle(x, y, 5, cor_interna);
}

/* PROJETIL JOGADOR */

void desenhar_projetil_jogador(projetil *projetil)
{
    ALLEGRO_COLOR cor_vermelho_escuro = cor(139, 0, 0);
    ALLEGRO_COLOR cor_vermelho_claro = cor(255, 0, 0);

    al_draw_filled_rectangle(projetil->x - 10, projetil->y - 3, projetil->x + 10, projetil->y + 3, cor_vermelho_escuro);
    al_draw_rectangle(projetil->x - 10, projetil->y - 3, projetil->x + 10, projetil->y + 3, cor_vermelho_claro, 1);
}

void desenhar_projetil_especial_jogador_1(projetil *projetil)
{
    ALLEGRO_COLOR cor_azul = cor(0, 0, 255);
    ALLEGRO_COLOR cor_branco = cor(255, 255, 255);
    ALLEGRO_COLOR cor_azul_claro = cor(173, 216, 230);

    al_draw_filled_rectangle(projetil->x - 15, projetil->y - 4, projetil->x + 15, projetil->y + 4, cor_azul);
    al_draw_filled_rectangle(projetil->x - 12, projetil->y - 3, projetil->x + 12, projetil->y + 3, cor_azul_claro);
    al_draw_filled_rectangle(projetil->x - 9, projetil->y - 2, projetil->x + 9, projetil->y + 2, cor_branco);
}

void desenhar_projetil_especial_jogador_2(projetil *projetil)
{
    ALLEGRO_COLOR cor_amarela = cor(255, 255, 0);
    ALLEGRO_COLOR cor_laranja = cor(255, 140, 0);
    ALLEGRO_COLOR cor_branco = cor(255, 255, 255);
    ALLEGRO_COLOR cor_vermelho_escuro = cor(139, 0, 0);

    al_draw_filled_rectangle(projetil->x - 15, projetil->y - 4, projetil->x + 15, projetil->y + 4, cor_vermelho_escuro);
    al_draw_filled_rectangle(projetil->x - 12, projetil->y - 3, projetil->x + 12, projetil->y + 3, cor_laranja);
    al_draw_filled_rectangle(projetil->x - 10, projetil->y - 2, projetil->x + 10, projetil->y + 2, cor_amarela);
    al_draw_filled_rectangle(projetil->x - 7, projetil->y - 1, projetil->x + 7, projetil->y + 1, cor_branco);
}

/* PROJETIL INIMIGOS */

void desenhar_projetil_inimigo_fase_1(projetil *projetil)
{
    ALLEGRO_COLOR cor_verde_escuro = cor(0, 100, 0);
    ALLEGRO_COLOR cor_verde_claro = cor(0, 255, 0);

    al_draw_filled_rectangle(projetil->x - 10, projetil->y - 3, projetil->x + 10, projetil->y + 3, cor_verde_escuro);
    al_draw_rectangle(projetil->x - 10, projetil->y - 3, projetil->x + 10, projetil->y + 3, cor_verde_claro, 1);
}

void desenhar_projetil_inimigo_fase_2(projetil *projetil)
{
    ALLEGRO_COLOR cor_rosa_escuro = cor(255, 20, 147);
    ALLEGRO_COLOR cor_rosa_claro = cor(255, 105, 180);

    al_draw_filled_rectangle(projetil->x - 10, projetil->y - 3, projetil->x + 10, projetil->y + 3, cor_rosa_escuro);
    al_draw_rectangle(projetil->x - 10, projetil->y - 3, projetil->x + 10, projetil->y + 3, cor_rosa_claro, 1);
}

/* CHEFE FASE 01 */

void desenhar_projetil_chefe_0(projetil *projetil)
{
    float variacao = sin(al_get_time() * 10) * 2;

    ALLEGRO_COLOR cor_amarela = cor(255, 255, 0);
    ALLEGRO_COLOR cor_laranja = cor(255, 140, 0);
    ALLEGRO_COLOR cor_vermelha = cor(255, 69, 0);

    desenhar_retorno_pulsante(variacao, projetil->x, projetil->y, cor_amarela, cor_laranja, cor_vermelha);
}

void desenhar_projetil2_chefe_0(projetil *projetil)
{
    float variacao = sin(al_get_time() * 10) * 3;

    ALLEGRO_COLOR cor_rosa_escuro = cor(255, 20, 147);
    ALLEGRO_COLOR cor_vermelha = cor(255, 69, 0);
    ALLEGRO_COLOR cor_laranja = cor(255, 140, 0);
    ALLEGRO_COLOR cor_amarela = cor(255, 255, 0);

    al_draw_filled_circle(projetil->x, projetil->y, 15 + variacao, cor_rosa_escuro);
    al_draw_filled_circle(projetil->x, projetil->y, 12 + variacao, cor_vermelha);
    al_draw_filled_circle(projetil->x, projetil->y, 9 + variacao / 1.5, cor_laranja);
    al_draw_filled_circle(projetil->x, projetil->y, 6, cor_amarela);
}

/* CHEFE FASE 02 */

void desenhar_projetil_chefe_1(projetil *projetil)
{
    float variacao = sin(al_get_time() * 10) * 2;

    ALLEGRO_COLOR cor_azul_claro = cor(173, 216, 230);
    ALLEGRO_COLOR cor_azul = cor(135, 206, 235);
    ALLEGRO_COLOR cor_roxo = cor(128, 0, 128);

    desenhar_retorno_pulsante(variacao, projetil->x, projetil->y, cor_azul_claro, cor_azul, cor_roxo);
}

void desenhar_projetil2_chefe_1(projetil *projetil)
{
    float variacao = sin(al_get_time() * 10) * 3;

    ALLEGRO_COLOR cor_azul = cor(0, 0, 255);
    ALLEGRO_COLOR cor_azul_claro = cor(173, 216, 230);
    ALLEGRO_COLOR cor_branco = cor(255, 255, 255);

    al_draw_filled_circle(projetil->x, projetil->y, 15 + variacao, cor_azul);
    al_draw_filled_circle(projetil->x, projetil->y, 12 + variacao, cor_azul_claro);
    al_draw_filled_circle(projetil->x, projetil->y, 9 + variacao / 1.5, cor_branco);
    al_draw_filled_circle(projetil->x, projetil->y, 6, cor_azul_claro);
}
