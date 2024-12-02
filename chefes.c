#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <math.h>

// Inclusões de bibliotecas locais
#include "chefes.h"

#define QUADRADO_SPRITE_SHEET 250       // Tamanho do quadro no sprite sheet
#define COLUNAS_SPRITE_SHEET_CHEFE_0 11 // Número de colunas no sprite do chefe 0
#define SPRITE_SHEET_CHEFE_0 22         // Número total de quadros no sprite
#define COLUNAS_SPRITE_SHEET_CHEFE_1 8  // Número de colunas no sprite do chefe 1
#define SPRITE_SHEET_CHEFE_1 16         // Número total de quadros no sprite
#define HP_CHEFE_0 40                   // Vida do chefe 0
#define HP_CHEFE_1 60                   // Vida do chefe 1
#define ARMA1_COOLDOWN_CHEFE 40         // Tempo de cooldown da arma do chefe (quanto maior, mais lento)
#define ARMA2_COOLDOWN_CHEFE 140        // Tempo de cooldown da segunda arma do chefe (quanto maior, mais lento)

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
    novo_chefe->tam_lateral = side;   // Insere o tamanho lateral do chefe
    novo_chefe->face = face;          // Insere a face do chefe (direção para onde ele está "olhando")
    novo_chefe->x = x;                // Posição X do centro do chefe
    novo_chefe->y = y;                // Posição Y do centro do chefe
    novo_chefe->tipo = type;          // Tipo do chefe, diferenciando-os
    novo_chefe->arma1 = criar_arma(); // Aloca e inicializa a arma do chefe
    novo_chefe->arma2 = criar_arma(); // Aloca e inicializa a arma do chefe
    novo_chefe->frame_atual = 0;      // Inicializa o frame atual do sprite
    novo_chefe->arma1->timer = 0;     // Inicializa o cooldown da primeira arma
    novo_chefe->arma2->timer = 0;     // Inicializa o cooldown da segunda arma

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
        novo_chefe->sprite_info->largura = QUADRADO_SPRITE_SHEET;           // Largura do quadro no sprite sheet
        novo_chefe->sprite_info->altura = QUADRADO_SPRITE_SHEET;            // Altura do quadro no sprite sheet
        novo_chefe->sprite_info->num_frames = COLUNAS_SPRITE_SHEET_CHEFE_0; // Número de colunas no sprite
        novo_chefe->sprite_info->num_frames_total = SPRITE_SHEET_CHEFE_0;   // Número total de quadros no sprite
        novo_chefe->hp = HP_CHEFE_0;                                        // Define a vida do chefe
        break;
    case 1: // Tipo de chefe 1
        novo_chefe->sprite_info->sprite = al_load_bitmap(PATH_CHEFE_1);
        novo_chefe->sprite_info->largura = QUADRADO_SPRITE_SHEET;           // Largura do quadro no sprite sheet
        novo_chefe->sprite_info->altura = QUADRADO_SPRITE_SHEET;            // Altura do quadro no sprite sheet
        novo_chefe->sprite_info->num_frames = COLUNAS_SPRITE_SHEET_CHEFE_1; // Número de colunas no sprite
        novo_chefe->sprite_info->num_frames_total = SPRITE_SHEET_CHEFE_1;   // Número total de quadros no sprite
        novo_chefe->hp = HP_CHEFE_1;                                        // Define a vida do chefe
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

    // Movimento do chefe baseado no tipo
    switch (elemento->tipo)
    {
    case 0: // movimento para cima e para baixo continuamente
            // Movimento oscilatório baseado no seno do tempo (frame atual)
        elemento->y = (max_y / 2) + (sin(al_get_time() * steps * 0.05) * (max_y / 4));
        // basta comentar/descomentar para obter o movimento para a esquerda tbm
        // elemento->x -= steps;
        break;
    case 1: // movimento para cima e para baixo continuamente
            // Movimento oscilatório baseado no seno do tempo (frame atual)
        elemento->y = (max_y / 2) + (sin(al_get_time() * steps * 0.05) * (max_y / 4));
        // basta comentar/descomentar para obter o movimento para a esquerda tbm
        // elemento->x -= steps;
        break;
    }

    // Alterna o disparo entre as duas armas, mas dispara uma arma apenas quando seu cooldown termina
    static int alternador = 0;

    if (alternador == 0 && elemento->arma1->timer == 0)
    {
        chefe_atira(elemento); // Dispara com arma 1
        alternador = 1;        // Alterna para a arma 2 no próximo ciclo
    }
    else if (alternador == 1 && elemento->arma2->timer == 0)
    {
        chefe_atira(elemento); // Dispara com arma 2
        alternador = 0;        // Alterna para a arma 1 no próximo ciclo
    }

    // Decrementa o timer de cooldown das armas
    if (elemento->arma1->timer > 0)
        elemento->arma1->timer--;
    if (elemento->arma2->timer > 0)
        elemento->arma2->timer--;

    // Atualiza a posição dos projéteis
    mover_projetil(&elemento->arma1->shots); // Atualiza projéteis da arma 1
    mover_projetil(&elemento->arma2->shots); // Atualiza projéteis da arma 2
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
        elemento->frame_atual = (elemento->frame_atual + 1) % elemento->sprite_info->num_frames_total;
        *animation_counter = 0; // Reseta o contador de animação
    }
}

// Função de disparo do chefe, alternando entre as duas armas assim que o cooldown de uma delas termina
void chefe_atira(chefe *element)
{
    if (!element)
        return;

    // Disparo da primeira arma
    if (!element->arma1->timer)
    {
        // Disparo da primeira arma
        disparo_arma(element->x - 80, element->y, 0, element->arma1);
        element->arma1->timer = ARMA1_COOLDOWN_CHEFE; // Define o cooldown da arma
    }

    // Disparo da segunda arma
    if (!element->arma2->timer)
    {
        // Disparo da segunda arma
        disparo_arma(element->x - 80, element->y, 0, element->arma2);
        element->arma2->timer = ARMA2_COOLDOWN_CHEFE; // Define o cooldown da arma
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
