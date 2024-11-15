#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "jogador.h"

player *player_create(unsigned char side, unsigned short x, unsigned short y, unsigned short max_x, unsigned short max_y)
{
    if ((x - side / 2 < 0) || (x + side / 2 > max_x) || (y - side / 2 < 0) || (y + side / 2 > max_y))
        return NULL; // Verifica se a posição inicial é válida; caso não seja, retorna NULL

    player *new_player = (player *)malloc(sizeof(player)); // Aloca memória na heap para um novo quadrado
    if (!new_player)
        return NULL; // Verifica se a alocação de memória foi bem-sucedida

    new_player->side = side; // Insere o tamanho do lado de um quadrado
    new_player->x = x;       // Insere a posição inicial central de X
    new_player->y = y;       // Insere a posição inicial central de Y

    // Carrega o sprite para o jogador
    new_player->sprite = al_load_bitmap("assets/jogador/sprite_jogador.png");
    if (!new_player->sprite)
    {
        free(new_player); // Libera a memória caso o carregamento do sprite falhe
        return NULL;
    }

    return new_player; // Retorna o novo jogador
}

void player_move(player *element, unsigned char steps, unsigned char trajectory, unsigned short max_x, unsigned short max_y)
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
    int frame_x = (element->current_frame % 3) * sprite_width; // Coluna
    int frame_y = (element->current_frame / 3) * sprite_height; // Linha

    // Desenha o quadro do sprite na tela
    al_draw_bitmap_region(element->sprite, frame_x, frame_y, sprite_width, sprite_height,
                          element->x - sprite_width / 2, element->y - sprite_height / 2, 0);
}

// Função para atualizar o quadro
void player_update(player *element)
{
    // Atualiza o quadro do jogador
    element->current_frame = (element->current_frame + 1) % 69; // Cicla entre 0 e 68
}

void player_destroy(player *element)
{
    if (element)
    {
        if (element->sprite)
        {
            al_destroy_bitmap(element->sprite); // Libera o sprite do jogador
        }
        free(element); // Libera a memória do jogador na heap
    }
}
