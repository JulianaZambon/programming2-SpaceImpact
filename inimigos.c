#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Inclusão de bibliotecas locais
#include "inimigos.h"
#include "configuracoes.h"
/*-----------------------------------------------------------------------------------------*/
/* FUNÇÕES INIMIGO */

// Função de criação de um inimigo
inimigo *criar_inimigo(unsigned char side, unsigned char face, short x, unsigned short y, unsigned short type, unsigned short max_x, unsigned short max_y)
{
    if ((x - side / 2 < 0) || (x + side / 2 > max_x) || (y - side / 2 < 0) || (y + side / 2 > max_y))
        return NULL; // Verifica se a posição inicial é válida

    inimigo *novo_inimigo = (inimigo *)malloc(sizeof(*novo_inimigo));
    if (!novo_inimigo)
        return NULL;

    novo_inimigo->tam_lateral = side;  // Insere o tamanho do lado do inimigo
    novo_inimigo->face = face;         // Insere a indicação da face principal do inimigo
    novo_inimigo->x = x;               // Insere a posição inicial central de X
    novo_inimigo->y = y;               // Insere a posição inicial central de Y
    novo_inimigo->tipo = type;         // Insere o tipo de inimigo
    novo_inimigo->arma = criar_arma(); // Insere o elemento de disparos do inimigo

    // Inicializa as informações do sprite do inimigo
    novo_inimigo->sprite_info = (inimigo_sprite *)malloc(sizeof(inimigo_sprite));
    if (!novo_inimigo->sprite_info)
    {
        free(novo_inimigo);
        return NULL;
    }

    switch (novo_inimigo->tipo)
    {
    case 0:
        novo_inimigo->sprite_info->sprite = al_load_bitmap(PATH_INIMIGO_0);
        novo_inimigo->sprite_info->largura = 100;
        novo_inimigo->sprite_info->altura = 100;
        novo_inimigo->sprite_info->num_frames = 5;
        novo_inimigo->pode_atirar = 0; // Define que o inimigo não pode atirar
        break;
    case 1:
        novo_inimigo->sprite_info->sprite = al_load_bitmap(PATH_INIMIGO_1);
        novo_inimigo->sprite_info->largura = 110;
        novo_inimigo->sprite_info->altura = 110;
        novo_inimigo->sprite_info->num_frames = 4;
        novo_inimigo->pode_atirar = 1; // Define que o inimigo pode atirar
        break;
    case 2:
        novo_inimigo->sprite_info->sprite = al_load_bitmap(PATH_INIMIGO_2);
        novo_inimigo->sprite_info->largura = 118;
        novo_inimigo->sprite_info->altura = 118;
        novo_inimigo->sprite_info->num_frames = 6;
        novo_inimigo->pode_atirar = 0; // Define que o inimigo não pode atirar
        break;
    case 3:
        novo_inimigo->sprite_info->sprite = al_load_bitmap(PATH_INIMIGO_3);
        novo_inimigo->sprite_info->largura = 110;
        novo_inimigo->sprite_info->altura = 110;
        novo_inimigo->sprite_info->num_frames = 4;
        novo_inimigo->pode_atirar = 1; // Define que o inimigo pode atirar
        break;
    default:
        free(novo_inimigo->sprite_info);
        free(novo_inimigo);
        return NULL;
    }

    if (!novo_inimigo->sprite_info->sprite)
    {
        free(novo_inimigo->sprite_info);
        free(novo_inimigo);
        return NULL;
    }

    return novo_inimigo;
}
// Função de movimentação de um inimigo
void mover_inimigo(inimigo *elemento, unsigned char steps, unsigned char *trajetoria, unsigned short max_x, unsigned short max_y)
{
    if (!elemento)
        return;

    switch (elemento->tipo)
    {
    case 0: // Movimento simples para a esquerda (somente no eixo X)
        elemento->x -= INIMIGO_STEP * steps;
        break;
    case 1: // Movimento em zigue-zague
        if (*trajetoria == 0)
        {
            elemento->x -= INIMIGO1_STEP * steps;
            elemento->y += INIMIGO1_STEP * steps;
            if (elemento->y >= max_y - elemento->tam_lateral / 2)
                *trajetoria = 1;
        }
        else
        {
            elemento->x -= INIMIGO1_STEP * steps;
            elemento->y -= INIMIGO1_STEP * steps;
            if (elemento->y <= elemento->tam_lateral / 2)
                *trajetoria = 0;
        }
        break;
    case 2: // Movimento em círculo
        // Movimento contínuo no eixo X
        elemento->x -= INIMIGO2_STEP * steps; // Movimento para a esquerda (pode ajustar a velocidade conforme necessário)
        // Se o inimigo sair da tela pela esquerda, ele reaparece no lado direito
        if (elemento->x + elemento->tam_lateral / 2 < 0)
        {
            elemento->x = max_x; // Reposiciona no lado direito da tela
        }
        // Movimento circular no eixo Y com função seno
        // Para dar um efeito de círculo, usamos um valor de X para calcular Y de forma contínua
        elemento->y = max_y / 2 + 100 * sin(elemento->x / 50.0); // Ajuste o 50.0 para controlar a frequência da oscilação no Y
        break;
    case 3:                                   // Movimento em onda
        elemento->x -= INIMIGO3_STEP * steps; // Movimento contínuo para a esquerda
        // Garante que o inimigo não saia da tela pela esquerda
        if (elemento->x + elemento->tam_lateral / 2 < 0)
        {
            elemento->x = max_x; // Reposiciona no lado direito da tela
        }
        // Movimento em onda (efeito suave no eixo Y)
        elemento->y = max_y / 2 + 100 * sin(elemento->x / 100.0); // Função seno para onda suave
        break;
    default:
        return;
    }

    // Disparo automático com cooldown
    if (elemento->arma->timer == 0)
    {
        inimigo_atira(elemento);                       // Inimigo realiza o disparo
        elemento->arma->timer = ARMA_COOLDOWN_INIMIGO; // Define um cooldown para o próximo disparo
    }
    else
    {
        elemento->arma->timer--; // Decrementa o cooldown a cada frame
    }

    mover_projetil(&elemento->arma->shots); // Atualiza a posição dos projéteis do inimigo
}
// Função de desenho de um inimigo
void desenhar_inimigo(inimigo *elemento)
{
    if (!elemento || !elemento->sprite_info)
        return;

    int sprite_largura = elemento->sprite_info->largura;
    int sprite_altura = elemento->sprite_info->altura;

    // Calcula a posição do quadro no sprite sheet
    int frame_x = (elemento->frame_atual % elemento->sprite_info->num_frames) * sprite_largura;
    int frame_y = (elemento->frame_atual / elemento->sprite_info->num_frames) * sprite_altura;

    // Desenha a região do sprite correspondente
    al_draw_bitmap_region(elemento->sprite_info->sprite, frame_x, frame_y, sprite_largura, sprite_altura,
                          elemento->x - sprite_largura / 2, elemento->y - sprite_altura / 2, 0);
}
// Função de atualização da animação do inimigo
void atualizar_animacao_inimigo(inimigo *elemento, unsigned int *animation_counter, unsigned int delay)
{
    if (!elemento || !elemento->sprite_info)
        return;

    // Atualiza contador de animação
    if (++(*animation_counter) >= delay)
    {
        elemento->frame_atual = (elemento->frame_atual + 1) % elemento->sprite_info->num_frames;
        *animation_counter = 0; // Reseta o contador de animação
    }
}
// Gera uma posicão Y aleatória, com um X fixo, e um tempo entre a criação do mesmo tipo de inimigos
// Assim, criando uma espécie de "onda" de inimigos
void atualizar_criacao_inimigo(inimigo **lista)
{
}

// Função de disparo do inimigo (se o inimigo puder atirar)
void inimigo_atira(inimigo *elemento)
{
    if (!elemento->arma->timer && elemento->pode_atirar)
    {                                                                   // Verifica se a arma do jogador não está em cooldown
        disparo_arma(elemento->x - 80, elemento->y, 0, elemento->arma); // Realiza o disparo
        elemento->arma->timer = ARMA_COOLDOWN_INIMIGO;                  // Inicia o cooldown da arma
    }
}
// Função de destruição do inimigo
void destroi_inimigo(inimigo *elemento)
{
    if (elemento)
    {
        al_destroy_bitmap(elemento->sprite_info->sprite); // Libera a imagem do sprite
        free(elemento->sprite_info);                      // Libera a memória da struct do sprite
        destroi_arma(elemento->arma);                     // Libera a arma do inimigo
        free(elemento);                                   // Libera a memória alocada para o inimigo
    }
}
