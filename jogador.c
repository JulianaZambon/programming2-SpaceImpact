#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "jogador.h"

#define Y_SCREEN 640

player *player_create(unsigned char side, unsigned short x, unsigned short y, unsigned short max_x, unsigned short max_y) {
    if ((x - side / 2 < 0) || (x + side / 2 > max_x) || (y - side / 2 < 0) || (y + side / 2 > max_y))
        return NULL; // Verifica se a posição inicial é válida; caso não seja, retorna NULL 

    player *new_player = (player *)malloc(sizeof(player)); // Aloca memória na heap para um novo quadrado 
    if (!new_player) return NULL; // Verifica se a alocação de memória foi bem-sucedida

    new_player->side = side; // Insere o tamanho do lado de um quadrado 
    new_player->x = x; // Insere a posição inicial central de X 
    new_player->y = y; // Insere a posição inicial central de Y 

    // Carrega o sprite para o jogador
    new_player->sprite = al_load_bitmap("assets/jogador/sprite-player2.png");
    if (!new_player->sprite) {
        free(new_player); // Libera a memória caso o carregamento do sprite falhe
        return NULL;
    }

    return new_player; // Retorna o novo jogador
}

void player_move(player *element, unsigned char steps, unsigned char trajectory, unsigned short max_x, unsigned short max_y) {
    if (!trajectory) {
        if ((element->x - steps * PLAYER_STEP) - element->side / 2 >= 0)
            element->x = element->x - steps * PLAYER_STEP;
    } else if (trajectory == 1) {
        if ((element->x + steps * PLAYER_STEP) + element->side / 2 <= max_x)
            element->x = element->x + steps * PLAYER_STEP;
    } else if (trajectory == 2) {
        if ((element->y - steps * PLAYER_STEP) - element->side / 2 >= 0)
            element->y = element->y - steps * PLAYER_STEP;
    } else if (trajectory == 3) {
        if ((element->y + steps * PLAYER_STEP) + element->side / 2 <= max_y)
            element->y = element->y + steps * PLAYER_STEP;
    }
}

// Função para desenhar o jogador na tela com o recorte correto do sprite
// São 72 quadros num sprite sheet de 7680x2560px
// Função para desenhar o jogador na tela com o recorte correto do sprite
// São 15 colunas e 5 linhas no sprite sheet de 7680x2560px
void player_draw(player *element) {
    // Definições do tamanho de cada quadro no sprite sheet
    int sprite_width = 512;  // Largura do quadro no sprite sheet
    int sprite_height = 512; // Altura do quadro no sprite sheet

    // Ajustar o tamanho do quadro para excluir as bordas
    int border_size = 180; // Tamanho da borda a ser excluída

    // Número de quadros por linha nas primeiras 2 linhas e últimas 3 linhas
    int num_columns_first_rows = 15;  // Para as duas primeiras linhas
    int num_columns_last_rows = 14;   // Para as últimas três linhas

    // Garantir que o número total de quadros não ultrapasse o limite
    int total_frames = 69 ;  // Total de quadros no sprite sheet

    // Calcular a posição do quadro no sprite sheet
    int frame_x = element->current_frame % num_columns_first_rows;  // Coluna do quadro
    int frame_y = element->current_frame / num_columns_first_rows; // Linha do quadro

    // Verifica se está nas 3 últimas linhas (com 14 quadros)
    if (frame_y >= 2) {
        // Ajusta para não tentar acessar a 15ª coluna, pois as últimas linhas têm apenas 14 quadros
        if (frame_x >= num_columns_last_rows) {
            frame_x = num_columns_last_rows - 1;  // Impede que acesse a coluna 15
        }
        frame_y -= 2;  // Ajusta a linha para as últimas 3 linhas
    }

    // Calcular as coordenadas do recorte para desenhar o quadro, aplicando a borda
    int sprite_x = sprite_width * frame_x + border_size; // Coluna no sprite, com a borda cortada
    int sprite_y = sprite_height * frame_y + border_size; // Linha no sprite, com a borda cortada

    // Ajusta o tamanho do quadro ao remover as bordas
    int frame_width = sprite_width - 2 * border_size;  // Largura do quadro sem borda
    int frame_height = sprite_height - 2 * border_size; // Altura do quadro sem borda

    // Desenhar o jogador na tela com o recorte ajustado
    al_draw_bitmap_region(element->sprite, sprite_x, sprite_y, frame_width, frame_height,
                          element->x, element->y, 0); // Posição do jogador na tela
}

// Função para atualizar o quadro
void player_update(player *element) {
    // Atualiza o quadro do jogador
    element->current_frame = (element->current_frame + 1) % 69;  // Cicla entre 0 e 68
}

void player_destroy(player *element) {
    if (element) {
        if (element->sprite) {
            al_destroy_bitmap(element->sprite); // Libera o sprite do jogador
        }
        free(element); // Libera a memória do jogador na heap
    }
}
