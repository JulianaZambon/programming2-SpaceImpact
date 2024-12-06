#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>

// Inclusão de bibliotecas locais
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
    new_jogador->hp = JOGADOR_HP;             // Insere a quantidade de vida inicial do jogador
    new_jogador->x = x;                       // Insere a posição inicial central de X
    new_jogador->y = y;                       // Insere a posição inicial central de Y
    new_jogador->controle = criar_joystick(); // Insere o elementoo de controle do jogador
    new_jogador->arma = criar_arma();         // Insere o elementoo de disparos do jogador
    new_jogador->frame_atual = 0;             // Inicializa o quadro atual do sprite
    new_jogador->animation_counter = 0;       // Inicializa o contador de animação

    // Carrega o sprite para o jogador
    new_jogador->sprite = al_load_bitmap(PATH_JOGADOR);
    if (!new_jogador->sprite)
    {
        free(new_jogador);
        return NULL;
    }

    // Carrega o sprite para o coração de HP
    new_jogador->hp_sprite = al_load_bitmap(PATH_HP);
    if (!new_jogador->hp_sprite)
    {
        al_destroy_bitmap(new_jogador->sprite);
        free(new_jogador);
        return NULL;
    }

    return new_jogador;
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
        if ((elemento->y - steps * JOGADOR_STEP) - 240 / 2 >= 0)
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
    int largura_sprite = QUADRADO_SPRITE_JOGADOR;
    int altura_sprite = QUADRADO_SPRITE_JOGADOR;

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
    {                                                                         // Verifica se a arma do jogador não está em cooldown
        disparo_arma(jogador_1->x + 5, jogador_1->y - 5, 1, jogador_1->arma); // Realiza o disparo
        jogador_1->arma->timer = ARMA_COOLDOWN;                               // Inicia o cooldown da arma
    }
}

// Função para destruir o jogador
void destroi_jogador(jogador *elemento)
{
    if (elemento == NULL)
    {
        return; // Retorna se o ponteiro for inválido
    }

    al_destroy_bitmap(elemento->sprite);  // Libera a memória do sprite
    destroi_joystick(elemento->controle); // Libera a memória do controle
    destroi_arma(elemento->arma);         // Libera a memória da arma
    free(elemento);                       // Libera a memória do jogador
}

/*---------------------------------------------------------------------------*/
/* FUNÇÕES PARA CONTROLE DO ATAQUE ESPECIAL */

// Função de criação do símbolo do ataque especial
// Cria e inicializa o símbolo que representa o ataque especial no mapa
simbolo_ataque_especial *criar_simbolo_ataque_especial(unsigned short x, unsigned short y, const char *sprite_path)
{
    simbolo_ataque_especial *novo_simbolo = (simbolo_ataque_especial *)malloc(sizeof(simbolo_ataque_especial));
    if (!novo_simbolo)
        return NULL;

    novo_simbolo->altura = QUADRADO_SPRITE_SIMBOLO_ATAQUE_ESPECIAL;
    novo_simbolo->largura = QUADRADO_SPRITE_SIMBOLO_ATAQUE_ESPECIAL;
    novo_simbolo->animation_counter = 0;
    novo_simbolo->frame_atual = 0;
    novo_simbolo->num_frames = NUM_FRAMES_SIMBOLO_ATAQUE_ESPECIAL;
    novo_simbolo->col_frames = COL_FRAMES_SIMBOLO_ATAQUE_ESPECIAL;
    novo_simbolo->x = x;
    novo_simbolo->y = y;
    novo_simbolo->sprite = al_load_bitmap(PATH_SIMBOLO_ATAQUE_ESPECIAL);

    return novo_simbolo;
}

// Função de movimentação do símbolo do ataque especial
// Movimento simples (para a esquerda)
void mover_simbolo_ataque_especial(simbolo_ataque_especial *simbolo, int dx, int dy, unsigned short max_x, unsigned short max_y)
{
}

// Função de desenho do símbolo do ataque especial
// Renderiza o sprite do símbolo na tela
void desenhar_simbolo_ataque_especial(simbolo_ataque_especial *simbolo)
{
    if (!simbolo || !simbolo->sprite)
        return;

    int sprite_x = (simbolo->frame_atual % simbolo->col_frames) * simbolo->largura;
    int sprite_y = (simbolo->frame_atual / simbolo->col_frames) * simbolo->altura;

    al_draw_bitmap_region(simbolo->sprite, sprite_x, sprite_y, simbolo->largura, simbolo->altura, simbolo->x, simbolo->y, 0);
}

// Função de atualização da animação do símbolo do ataque especial
// Atualiza o quadro atual do sprite, respeitando o delay entre frames
void atualizar_animacao_simbolo_ataque_especial(simbolo_ataque_especial *simbolo, unsigned int delay)
{
    if (!simbolo)
        return;

    simbolo->animation_counter++;
    if (simbolo->animation_counter >= delay)
    {
        simbolo->animation_counter = 0;
        simbolo->frame_atual = (simbolo->frame_atual + 1) % simbolo->num_frames;
    }
}

// Função de destruição do símbolo do ataque especial
// Libera recursos alocados pelo símbolo
void destruir_simbolo_ataque_especial(simbolo_ataque_especial *simbolo)
{
    if (!simbolo)
        return;

    if (simbolo->sprite)
        al_destroy_bitmap(simbolo->sprite);

    free(simbolo);
}

// Função de verificação de colisão do jogador com o símbolo do ataque especial
// Verifica se o jogador colidiu com o símbolo do ataque especial
bool verificar_colisao_jogador_simbolo(jogador *jogador, simbolo_ataque_especial *simbolo)
{
    if (!jogador || !simbolo) return false;

    return !(jogador->x + jogador->tam_lateral / 2 < simbolo->x - simbolo->largura / 2 ||
             jogador->x - jogador->tam_lateral / 2 > simbolo->x + simbolo->largura / 2 ||
             jogador->y + jogador->tam_lateral / 2 < simbolo->y - simbolo->altura / 2 ||
             jogador->y - jogador->tam_lateral / 2 > simbolo->y + simbolo->altura / 2);
}

// Função de ativação do ataque especial
// Ativa o ataque especial no jogador por 5 segundos ao coletar o símbolo
void ativar_ataque_especial(jogador *jogador)
{
    if (!jogador) return;

    jogador->ataque_especial = true;
    jogador->ataque_especial->tempo_restante = TEMP_MAX;
}

// Atualizar o tempo restante do ataque especial
void atualizar_tempo_ataque_especial(jogador *jogador)
{
    if (!jogador || !jogador->ataque_especial) return;

    if (jogador->ataque_especial && jogador->ataque_especial->tempo_restante > 0)
    {
        jogador->ataque_especial->tempo_restante--;
    }

    if (jogador->ataque_especial->tempo_restante <= 0)
    {
        jogador->ataque_especial = false;  // Desativa o ataque especial
    }
}
