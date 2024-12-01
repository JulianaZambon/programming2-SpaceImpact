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

void desenhar_projetil_jogador(projetil *projetil)
{
    ALLEGRO_COLOR cor_vermelho_escuro = al_map_rgb(139, 0, 0); // Cor interna do projetil
    ALLEGRO_COLOR cor_vermelho_claro = al_map_rgb(255, 0, 0);  // Cor da borda do projetil

    // Sensação de laser:
    al_draw_filled_rectangle(projetil->x - 10, projetil->y - 3, projetil->x + 10, projetil->y + 3, cor_vermelho_escuro);
    al_draw_rectangle(projetil->x - 10, projetil->y - 3, projetil->x + 10, projetil->y + 3, cor_vermelho_claro, 1);
}
void desenhar_projetil_especial_jogador_1(projetil *projetil)
{
    // Cores para o projétil especial
    ALLEGRO_COLOR cor_azul = al_map_rgb(0, 0, 255);           // Azul intenso
    ALLEGRO_COLOR cor_branco = al_map_rgb(255, 255, 255);     // Branco brilhante
    ALLEGRO_COLOR cor_azul_claro = al_map_rgb(173, 216, 230); // Azul claro para brilho

    // Desenha retângulos concêntricos com efeito de camadas
    al_draw_filled_rectangle(projetil->x - 15, projetil->y - 4, projetil->x + 15, projetil->y + 4, cor_azul);       // Camada central azul
    al_draw_filled_rectangle(projetil->x - 12, projetil->y - 3, projetil->x + 12, projetil->y + 3, cor_azul_claro); // Camada de azul claro
    al_draw_filled_rectangle(projetil->x - 9, projetil->y - 2, projetil->x + 9, projetil->y + 2, cor_branco);       // Camada brilhante no centro
}
void desenhar_projetil_especial_jogador_2(projetil *projetil)
{
    // Cores para o projétil especial de "raio"
    ALLEGRO_COLOR cor_amarela = al_map_rgb(255, 255, 0);       // Amarelo intenso
    ALLEGRO_COLOR cor_laranja = al_map_rgb(255, 140, 0);       // Laranja vibrante
    ALLEGRO_COLOR cor_branco = al_map_rgb(255, 255, 255);      // Branco para um brilho forte
    ALLEGRO_COLOR cor_vermelho_escuro = al_map_rgb(139, 0, 0); // Vermelho escuro para as bordas

    // Desenha um efeito de raio com múltiplas camadas
    al_draw_filled_rectangle(projetil->x - 15, projetil->y - 4, projetil->x + 15, projetil->y + 4, cor_vermelho_escuro); // Camada externa escura
    al_draw_filled_rectangle(projetil->x - 12, projetil->y - 3, projetil->x + 12, projetil->y + 3, cor_laranja);         // Camada intermediária laranja
    al_draw_filled_rectangle(projetil->x - 10, projetil->y - 2, projetil->x + 10, projetil->y + 2, cor_amarela);         // Camada central amarela
    al_draw_filled_rectangle(projetil->x - 7, projetil->y - 1, projetil->x + 7, projetil->y + 1, cor_branco);            // Camada de brilho branco
}

/* INIMIGOS */
// Função de desenho de projetil para inimigos
void desenhar_projetil_inimigo_fase_1(projetil *projetil)
{
    ALLEGRO_COLOR cor_verde_escuro = al_map_rgb(0, 100, 0); // Cor interna do projetil
    ALLEGRO_COLOR cor_verde_claro = al_map_rgb(0, 255, 0);  // Cor da borda do projetil

    // Sensação de laser:
    al_draw_filled_rectangle(projetil->x - 10, projetil->y - 3, projetil->x + 10, projetil->y + 3, cor_verde_escuro);
    al_draw_rectangle(projetil->x - 10, projetil->y - 3, projetil->x + 10, projetil->y + 3, cor_verde_claro, 1);
}
void desenhar_projetil_inimigo_fase_2(projetil *projetil)
{
    ALLEGRO_COLOR cor_rosa_escuro = al_map_rgb(255, 20, 147); // Cor interna do projetil
    ALLEGRO_COLOR cor_rosa_claro = al_map_rgb(255, 105, 180); // Cor da borda do projetil

    // Sensação de laser:
    al_draw_filled_rectangle(projetil->x - 10, projetil->y - 3, projetil->x + 10, projetil->y + 3, cor_rosa_escuro);
    al_draw_rectangle(projetil->x - 10, projetil->y - 3, projetil->x + 10, projetil->y + 3, cor_rosa_claro, 1);
}

/* CHEFE FASE 01 */
// Chefe com chamas, portanto dar uma sensação de bolas de fogo aos projeteis
// Primeiro ataque unico do chefe 0
void desenhar_projetil_chefe_0(projetil *projetil)
{
    // Variação de tamanho para pulsação da chama
    float variacao = sin(al_get_time() * 10) * 2;

    ALLEGRO_COLOR cor_amarela = al_map_rgb(255, 255, 0); // Amarelo interno
    ALLEGRO_COLOR cor_laranja = al_map_rgb(255, 140, 0); // Laranja intermediário
    ALLEGRO_COLOR cor_vermelha = al_map_rgb(255, 69, 0); // Vermelho externo

    // Desenha círculos concêntricos (com mesmo centro) com variação no tamanho
    al_draw_filled_circle(projetil->x, projetil->y, 10 + variacao, cor_vermelha);   // Vermelho externo
    al_draw_filled_circle(projetil->x, projetil->y, 8 + variacao / 2, cor_laranja); // Laranja intermediário
    al_draw_filled_circle(projetil->x, projetil->y, 5, cor_amarela);                // Amarelo interno
}
// Segundo ataque único do chefe 0
void desenhar_projetil2_chefe_0(projetil *projetil)
{
    // Variação de tamanho para dar a sensação de pulsação ou aumento de energia
    float variacao = sin(al_get_time() * 10) * 3;

    // Cores com base em chamas, usando vermelho, laranja, amarelo e uma cor de brilho
    ALLEGRO_COLOR cor_rosa_escuro = al_map_rgb(255, 20, 147); // Rosa escuro (brilho intenso)
    ALLEGRO_COLOR cor_vermelha = al_map_rgb(255, 69, 0);      // Vermelho (externo)
    ALLEGRO_COLOR cor_laranja = al_map_rgb(255, 140, 0);      // Laranja (intermediário)
    ALLEGRO_COLOR cor_amarela = al_map_rgb(255, 255, 0);      // Amarelo (interno)

    // Desenha uma aura de brilho (rosa) para o efeito do projétil
    al_draw_filled_circle(projetil->x, projetil->y, 15 + variacao, cor_rosa_escuro); // Brilho rosa escuro ao redor

    // Desenha as camadas de cores das chamas com variação de tamanho
    al_draw_filled_circle(projetil->x, projetil->y, 12 + variacao, cor_vermelha);     // Vermelho externo
    al_draw_filled_circle(projetil->x, projetil->y, 9 + variacao / 1.5, cor_laranja); // Laranja intermediário
    al_draw_filled_circle(projetil->x, projetil->y, 6, cor_amarela);                  // Amarelo interno
}

/* CHEFE FASE 02 */
// Primeiro ataque unico do chefe 1
void desenhar_projetil_chefe_1(projetil *projetil)
{
    // Variação de tamanho para pulsação da chama
    float variacao = sin(al_get_time() * 10) * 2;

    ALLEGRO_COLOR cor_azul_claro = al_map_rgb(173, 216, 230); // Azul claro
    ALLEGRO_COLOR cor_azul = al_map_rgb(135, 206, 235);       // Azul céu
    ALLEGRO_COLOR cor_roxo = al_map_rgb(128, 0, 128);         // Roxo

    // Desenha círculos concêntricos (com mesmo centro) com variação no tamanho
    al_draw_filled_circle(projetil->x, projetil->y, 10 + variacao, cor_roxo);
    al_draw_filled_circle(projetil->x, projetil->y, 8 + variacao / 2, cor_azul);
    al_draw_filled_circle(projetil->x, projetil->y, 5, cor_azul_claro);
}
// Segundo ataque unico do chefe 1
void desenhar_projetil2_chefe_1(projetil *projetil)
{
    // Variação de tamanho para dar uma sensação de pulsação ou aumento de energia
    float variacao = sin(al_get_time() * 10) * 2;

    // Cores com base em azul e roxo, com efeitos de brilho e energia
    ALLEGRO_COLOR cor_roxo_escuro = al_map_rgb(75, 0, 130);   // Roxo escuro (energético)
    ALLEGRO_COLOR cor_roxo = al_map_rgb(128, 0, 128);         // Roxo (intermediário)
    ALLEGRO_COLOR cor_azul = al_map_rgb(100, 149, 237);       // Azul (centrado)
    ALLEGRO_COLOR cor_azul_claro = al_map_rgb(173, 216, 230); // Azul claro (brilho externo)

    // Desenha a aura externa do projétil, com cor roxa mais escura
    al_draw_filled_circle(projetil->x, projetil->y, 15 + variacao, cor_roxo_escuro); // Roxo escuro externo
    // Desenha a camada intermediária do projétil, com cor roxa
    al_draw_filled_circle(projetil->x, projetil->y, 12 + variacao / 1.5, cor_roxo); // Roxo intermediário
    // Desenha a camada de azul, representando o núcleo do projétil
    al_draw_filled_circle(projetil->x, projetil->y, 9, cor_azul); // Azul central
    // Camada final de azul claro, criando um brilho suave ao redor
    al_draw_filled_circle(projetil->x, projetil->y, 7, cor_azul_claro); // Azul claro externo
}
