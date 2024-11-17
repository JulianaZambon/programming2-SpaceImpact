#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "jogador.h"

player *player_create(unsigned char side, unsigned char face, short x, unsigned short y, unsigned short max_x, unsigned short max_y)
{
    if ((x - side / 2 < 0) || (x + side / 2 > max_x) || (y - side / 2 < 0) || (y + side / 2 > max_y))
        return NULL; // Verifica se a posição inicial é válida

    player *new_player = (player *)malloc(sizeof(*new_player)); // Aloca memória na heap para um novo jogador
    if (!new_player)
        return NULL;

    new_player->side = side;                 // Insere o tamanho do lado do jogador
    new_player->face = face;                 // Insere a indicação da face principal do jogador
    new_player->x = x;                       // Insere a posição inicial central de X
    new_player->y = y;                       // Insere a posição inicial central de Y
    new_player->control = joystick_create(); // Insere o elemento de controle na nave do jogador
    new_player->arma = arma_create();        // Insere o elemento de disparos do jogador

    // Carrega o sprite para o jogador
    new_player->sprite = al_load_bitmap("assets/jogador/sprite_jogador.png");
    if (!new_player->sprite)
    {
        free(new_player); // Libera a memória caso o carregamento do sprite falhe
        return NULL;
    }

    return new_player;
}

void player_move(player *element, unsigned char steps, unsigned char trajectory,
                 unsigned short max_x, unsigned short max_y)
{
    if (!trajectory)
    {
        if ((element->x - steps * PLAYER_STEP) - element->side / 2 >= 0)
            element->x = element->x - steps * PLAYER_STEP;
    }
    else if (trajectory == 1)
    {
        if ((element->x + steps * PLAYER_STEP) + element->side / 2 <= max_x)
            element->x = element->x + steps * PLAYER_STEP;
    }
    else if (trajectory == 2)
    {
        if ((element->y - steps * PLAYER_STEP) - element->side / 2 >= 0)
            element->y = element->y - steps * PLAYER_STEP;
    }
    else if (trajectory == 3)
    {
        if ((element->y + steps * PLAYER_STEP) + element->side / 2 <= max_y)
            element->y = element->y + steps * PLAYER_STEP;
    }
}

// Função para desenhar o jogador na tela com o recorte correto do sprite
// São 3 colunas e 24 linhas no sprite sheet
void player_draw(player *element)
{
    // Definições do tamanho de cada quadro no sprite sheet
    int sprite_width = 189;  // Largura do quadro no sprite sheet
    int sprite_height = 189; // Altura do quadro no sprite sheet

    // Calcula a posição do quadro no sprite sheet
    int frame_x = (element->current_frame % 3) * sprite_width;  // Coluna
    int frame_y = (element->current_frame / 3) * sprite_height; // Linha

    // Desenha o quadro do sprite na tela
    al_draw_bitmap_region(element->sprite, frame_x, frame_y, sprite_width, sprite_height,
                          element->x - sprite_width / 2, element->y - sprite_height / 2, 0);
}

void player_shot(player *element)
{
    projetil *shot;

    if (!element->face) // Se a face for 0, o jogador atira para a esquerda
        shot = arma_shot(element->x - element->side / 2, element->y, element->face, element->arma);
    else if (element->face == 1) // Se a face for 1, o jogador atira para a direita
        shot = arma_shot(element->x + element->side / 2, element->y, element->face, element->arma);
    if (shot) // Se o tiro foi realizado com sucesso, insere na lista de tiros
        element->arma->shots = shot;
}

void player_destroy(player *element)
{
    arma_destroy(element->arma);        // Destrói a arma do jogador
    joystick_destroy(element->control); // Destrói o controle do jogador

    if (element)
    {
        if (element->sprite)
        {
            al_destroy_bitmap(element->sprite); // Libera o sprite do jogador
        }
        free(element);
    }
}
