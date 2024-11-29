#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>

// Libs locais
#include "jogador.h"
#include "configuracoes.h"

/*-----------------------------------------------------------------------------------------*/
/* FUNÇÕES */

// Função de criação de um jogador
jogador *criar_jogador(unsigned char tam_lateral, unsigned char face, short x, unsigned short y, unsigned short max_x, unsigned short max_y)
{
    if ((x - tam_lateral / 2 < 0) || (x + tam_lateral / 2 > max_x) || (y - tam_lateral / 2 < 0) || (y + tam_lateral / 2 > max_y))
        return NULL; // Verifica se a posição inicial é válida

    jogador *new_jogador = (jogador *)malloc(sizeof(*new_jogador)); // Aloca memória na heap para um novo jogador
    if (!new_jogador)
        return NULL;

    new_jogador->tam_lateral = tam_lateral;   // Insere o tamanho do lado do jogador
    new_jogador->face = face;                 // Insere a indicação da face principal do jogador
    new_jogador->hp = 5;                      // Insere o total de pontos de vida de um jogador
    new_jogador->x = x;                       // Insere a posição inicial central de X
    new_jogador->y = y;                       // Insere a posição inicial central de Y
    new_jogador->controle = criar_joystick(); // Insere o elementoo de controle do jogador
    new_jogador->arma = criar_arma();         // Insere o elementoo de disparos do jogador

    // Carrega o sprite para o jogador
    new_jogador->sprite = al_load_bitmap(PATH_JOGADOR);
    if (!new_jogador->sprite)
    {
        free(new_jogador); // Libera a memória caso o carregamento do sprite falhe
        return NULL;
    }

    // Carrega o sprite para o coração de HP
    new_jogador->hp_sprite = al_load_bitmap(PATH_HP);
    if (!new_jogador->hp_sprite)
    {
        al_destroy_bitmap(new_jogador->sprite); // Libera a memória do sprite
        free(new_jogador);                      // Libera a memória do jogador
        return NULL;
    }

    return new_jogador; // Retorna o jogador criado
}

// Função para mover o jogador
void mover_jogador(jogador *elemento, char steps, unsigned char trajetoria, unsigned short max_x, unsigned short max_y)
{
    if (!trajetoria)
    {
        if ((elemento->x - steps * JOGADOR_STEP) - 90 / 2 >= 0)
            elemento->x = elemento->x - steps * JOGADOR_STEP;
    } // Verifica se a movimentação para a esquerda é desejada e possível; se sim, efetiva a mesma
    else if (trajetoria == 1)
    {
        if ((elemento->x + steps * JOGADOR_STEP) + 90 / 2 <= max_x)
            elemento->x = elemento->x + steps * JOGADOR_STEP;
    } // Verifica se a movimentação para a direita é desejada e possível; se sim, efetiva a mesma
    else if (trajetoria == 2)
    {
        if ((elemento->y - steps * JOGADOR_STEP) - 90 / 2 >= 0)
            elemento->y = elemento->y - steps * JOGADOR_STEP;
    } // Verifica se a movimentação para cima é desejada e possível; se sim, efetiva a mesma
    else if (trajetoria == 3)
    {
        if ((elemento->y + steps * JOGADOR_STEP) + 90 / 2 <= max_y)
            elemento->y = elemento->y + steps * JOGADOR_STEP;
    } // Verifica se a movimentação para baixo é desejada e possível; se sim, efetiva a mesma
}

// Função para desenhar o jogador na tela com o recorte correto do sprite
// São 3 colunas e 24 linhas no sprite sheet
void desenhar_jogador(jogador *elemento)
{
    // Definições do tamanho de cada quadro no sprite sheet
    int largura_sprite = 189; // Largura do quadro no sprite sheet
    int altura_sprite = 189;  // Altura do quadro no sprite sheet

    // Calcula a posição do quadro no sprite sheet
    int frame_x = (elemento->frame_atual % 3) * largura_sprite; // Coluna
    int frame_y = (elemento->frame_atual / 3) * altura_sprite;  // Linha

    // Desenha o quadro do sprite na tela
    al_draw_bitmap_region(elemento->sprite, frame_x, frame_y, largura_sprite, altura_sprite,
                          elemento->x - largura_sprite / 2, elemento->y - altura_sprite / 2, 0);
}

// Função para desenhar os corações de HP na tela
// São 5 colunas e 2 linhas no sprite sheet (10 frames no total)
void desenhar_hp(jogador *elemento, int x, int y)
{
    int largura_sprite = SPRITE_HP; // Largura do quadro no sprite sheet
    int altura_sprite = SPRITE_HP;  // Altura do quadro no sprite sheet

    for (int i = 0; i < elemento->hp; i++)
    {
        int frame_atual = (elemento->frame_atual + i) % NUM_FRAMES_HP;
        int frame_x = (frame_atual % 5) * largura_sprite; // Coluna no sprite sheet
        int frame_y = (frame_atual / 5) * altura_sprite;  // Linha no sprite sheet

        // Desenha o coração na posição (x + deslocamento horizontal, y)
        al_draw_bitmap_region(elemento->hp_sprite, frame_x, frame_y, largura_sprite, altura_sprite,
                              x + i * largura_sprite, y, 0);
    }
}

// Função para atualizar a animação do jogador
void atualizar_animacao_jogador(jogador *elemento, unsigned int *animation_counter, unsigned int delay)
{
    // Atualiza contador de animação
    if (++(*animation_counter) >= delay)
    {
        elemento->frame_atual = (elemento->frame_atual + 1) % NUM_FRAMES_JOGADOR;
        *animation_counter = 0; // Reseta o contador de animação
    }
}

// Função para realizar o disparo do jogador
void jogador_atira(jogador *jogador_1)
{
    if (!jogador_1->arma->timer)
    {                                                                 // Verifica se a arma do jogador não está em cooldown
        disparo_arma(jogador_1->x, jogador_1->y, 1, jogador_1->arma); // Realiza o disparo
        jogador_1->arma->timer = ARMA_COOLDOWN;                       // Inicia o cooldown da arma
    }
}

// Função para destruir o jogador
void destroi_jogador(jogador *elemento)
{
    al_destroy_bitmap(elemento->sprite);  // Libera a memória do sprite
    destroi_joystick(elemento->controle); // Libera a memória do elementoo de controle
    destroi_arma(elemento->arma);         // Libera a memória do elementoo de disparos
    free(elemento);                       // Libera a memória do jogador
}
