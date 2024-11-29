#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>

// Libs locais
#include "chefes.h"

/*-----------------------------------------------------------------------------------------*/
/* FUNÇÕES */

// Função de criação de um chefe
chefe *criar_chefe(unsigned char side, unsigned char face, short x, unsigned short y, unsigned short type, unsigned short max_x, unsigned short max_y)
{
    // Verifica se a posição inicial do chefe é válida
    if ((x - side / 2 < 0) || (x + side / 2 > max_x) || (y - side / 2 < 0) || (y + side / 2 > max_y))
        return NULL; // Se a posição não for válida, retorna NULL

    // Aloca memória para o novo chefe
    chefe *novo_chefe = (chefe *)malloc(sizeof(*novo_chefe));
    if (!novo_chefe)
        return NULL;

    // Inicializa os atributos básicos do chefe
    novo_chefe->tam_lateral = side;  // Insere o tamanho lateral do chefe
    novo_chefe->face = face;         // Insere a face do chefe (direção para onde ele está "olhando")
    novo_chefe->x = x;               // Posição X do centro do chefe
    novo_chefe->y = y;               // Posição Y do centro do chefe
    novo_chefe->tipo = type;         // Tipo do chefe, diferenciando-os
    novo_chefe->arma = criar_arma(); // Aloca e inicializa a arma do chefe (caso tenha)

    // Aloca a estrutura para o sprite do chefe
    novo_chefe->sprite_info = (chefe_sprite *)malloc(sizeof(chefe_sprite));
    if (!novo_chefe->sprite_info)
    {
        free(novo_chefe);
        return NULL;
    }

    // Configuração dos sprites com base no tipo do chefe
    switch (novo_chefe->tipo)
    {
    case 0: // Tipo de chefe 0
        novo_chefe->sprite_info->sprite = al_load_bitmap(PATH_CHEFE_0);
        novo_chefe->sprite_info->largura = 270;   // Largura do quadro no sprite sheet
        novo_chefe->sprite_info->altura = 270;    // Altura do quadro no sprite sheet
        novo_chefe->sprite_info->num_frames = 17; // Número de quadros no sprite
        break;
    case 1: // Tipo de chefe 1
        novo_chefe->sprite_info->sprite = al_load_bitmap(PATH_CHEFE_1);
        novo_chefe->sprite_info->largura = 250;  // Largura do quadro no sprite sheet
        novo_chefe->sprite_info->altura = 250;   // Altura do quadro no sprite sheet
        novo_chefe->sprite_info->num_frames = 8; // Número de quadros no sprite
        break;
    default:
        free(novo_chefe->sprite_info);
        free(novo_chefe);
        return NULL;
    }
    // Verifica se o sprite foi carregado corretamente
    if (!novo_chefe->sprite_info->sprite)
    {
        free(novo_chefe->sprite_info);
        free(novo_chefe);
        return NULL;
    }
    return novo_chefe;
}

// Função de movimentação do chefe
void mover_chefe(chefe *elemento, unsigned char steps, unsigned char trajetoria, unsigned short max_x, unsigned short max_y)
{
    if (!elemento)
        return;

    switch (elemento->tipo)
    {
    case 0: // Movimento para a esquerda
        elemento->x -= CHEFE0_STEP * steps;
        break;
    case 1: // Movimento em círculo
        // Movimento contínuo no eixo X
        elemento->x -= CHEFE1_STEP * steps; // Movimento para a esquerda (pode ajustar a velocidade conforme necessário)

        // Se o inimigo sair da tela pela esquerda, ele reaparece no lado direito
        if (elemento->x + elemento->tam_lateral / 2 < 0)
        {
            elemento->x = max_x; // Reposiciona no lado direito da tela
        }
        // Movimento circular no eixo Y com função seno
        // Para dar um efeito de círculo, usamos um valor de X para calcular Y de forma contínua
        elemento->y = max_y / 2 + 100 * sin(elemento->x / 50.0); // Ajuste o 50.0 para controlar a frequência da oscilação no Y
        break;
    default:
        break;
    }
}

// Função de desenho do chefe
void desenhar_chefe(chefe *element)
{
    if (!element || !element->sprite_info)
        return;

    int sprite_largura = element->sprite_info->largura;
    int sprite_altura = element->sprite_info->altura;

    // Calcula a posição do quadro no sprite sheet
    int frame_x = (element->frame_atual % element->sprite_info->num_frames) * sprite_largura;
    int frame_y = (element->frame_atual / element->sprite_info->num_frames) * sprite_altura;

    // Desenha a região do sprite correspondente
    al_draw_bitmap_region(element->sprite_info->sprite, frame_x, frame_y, sprite_largura, sprite_altura,
                          element->x - sprite_largura / 2, element->y - sprite_altura / 2, 0);
}

// Função de atualização da animação do chefe
void atualizar_animacao_chefe(chefe *elemento, unsigned int *animation_counter, unsigned int delay)
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

// Função de disparo do chefe
void chefe_atira(chefe *element)
{
    if (!element->arma->timer)
    {                                                           // Verifica se a arma do jogador não está em cooldown
        disparo_arma(element->x, element->y, 1, element->arma); // Realiza o disparo
        element->arma->timer = ARMA_COOLDOWN;                   // Inicia o cooldown da arma
    }
}

// Função de destruição do chefe
void destroi_chefe(chefe *element)
{
    if (element)
    {
        al_destroy_bitmap(element->sprite_info->sprite); // Libera a imagem do sprite
        free(element->sprite_info);                      // Libera a memória da struct do sprite
        free(element);                                   // Libera a memória do chefe
    }
}
