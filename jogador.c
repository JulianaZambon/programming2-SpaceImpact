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

    jogador *new_jogador = (jogador *)malloc(sizeof(*new_jogador));
    if (!new_jogador)
        return NULL;

    new_jogador->tam_lateral = tam_lateral;   // Insere o tamanho do lado do jogador
    new_jogador->face = face;                 // Insere a indicação da face principal do jogador
    new_jogador->hp = JOGADOR_HP;             // Insere a quantidade de vida inicial do jogador
    new_jogador->x = x;                       // Insere a posição inicial central de X
    new_jogador->y = y;                       // Insere a posição inicial central de Y
    new_jogador->frame_atual = 0;             // Inicializa o quadro atual do sprite
    new_jogador->animation_counter = 0;       // Inicializa o contador de animação
    new_jogador->controle = criar_joystick(); // Insere o elementoo de controle do jogador
    new_jogador->arma = criar_arma();         // Insere o elementoo de disparos do jogador

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

/*-------------------------------------------------------------------*/
/* FUNÇÕES PARA CONTROLE DO ATAQUE ESPECIAL */

// Função de criação do símbolo do ataque especial
simbolo_ataque_especial *criar_simbolo_ataque_especial(unsigned short x, unsigned short y, const char *sprite_path)
{
    simbolo_ataque_especial *novo_simbolo = (simbolo_ataque_especial *)malloc(sizeof(simbolo_ataque_especial));
    if (!novo_simbolo)
        return NULL;

    novo_simbolo->x = x;
    novo_simbolo->y = y;
    novo_simbolo->largura = QUADRADO_SPRITE_SIMBOLO_ATAQUE_ESPECIAL;
    novo_simbolo->altura = QUADRADO_SPRITE_SIMBOLO_ATAQUE_ESPECIAL;
    novo_simbolo->col_frames = COL_FRAMES_SIMBOLO_ATAQUE_ESPECIAL;
    novo_simbolo->num_frames = NUM_FRAMES_SIMBOLO_ATAQUE_ESPECIAL;
    novo_simbolo->frame_atual = 0;
    novo_simbolo->animation_counter = 0;
    novo_simbolo->sprite = al_load_bitmap(sprite_path);

    if (!novo_simbolo->sprite)
    {
        free(novo_simbolo);
        return NULL; // Verifica se o sprite foi carregado corretamente
    }

    return novo_simbolo;
}

// Função para criar um ataque especial
ataque_especial *criar_ataque_especial()
{
    ataque_especial *novo_ataque = malloc(sizeof(ataque_especial));
    if (novo_ataque)
    {
        novo_ataque->ativo = false;
        novo_ataque->tempo_restante = TEMP_MAX;
        novo_ataque->simbolo = NULL; // Inicializa o símbolo como NULL
        novo_ataque->sprite = NULL;  // Inicializa o sprite como NULL
    }
    return novo_ataque;
}

// Função de desenho do símbolo do ataque especial
void desenhar_simbolo_ataque_especial(simbolo_ataque_especial *simbolo)
{
    if (!simbolo || !simbolo->sprite)
        return;

    int largura_sprite = simbolo->largura;
    int altura_sprite = simbolo->altura;

    int frame_x = (simbolo->frame_atual % simbolo->col_frames) * largura_sprite;
    int frame_y = (simbolo->frame_atual / simbolo->col_frames) * altura_sprite;

    al_draw_bitmap_region(simbolo->sprite, frame_x, frame_y, largura_sprite, altura_sprite,
                          simbolo->x - largura_sprite / 2, simbolo->y - altura_sprite / 2, 0);
}

// Função de atualização da animação do símbolo do ataque especial
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
void destruir_simbolo_ataque_especial(simbolo_ataque_especial *simbolo)
{
    if (!simbolo)
        return;

    al_destroy_bitmap(simbolo->sprite); // Libera a memória do sprite
    free(simbolo);                      // Libera a memória do símbolo
}

// Função de verificação de colisão do jogador com o símbolo do ataque especial
bool verificar_colisao_jogador_simbolo(jogador *jogador, simbolo_ataque_especial *simbolo)
{
    if (jogador->x + jogador->face / 2 > simbolo->x &&
        jogador->x - jogador->face / 2 < simbolo->x + simbolo->largura &&
        jogador->y + QUADRADO_SPRITE_JOGADOR / 2 > simbolo->y &&
        jogador->y - QUADRADO_SPRITE_JOGADOR / 2 < simbolo->y + simbolo->altura)
    {
        return true; // Colisão detectada
    }
    return false; // Nenhuma colisão
}

// Função de ativação do ataque especial
void ativar_ataque_especial(jogador *jogador)
{
    jogador->especial->ativo = true;
    jogador->especial->tempo_inicio = clock();
    jogador->especial->duracao = 5000;

    // Configura os projéteis existentes para serem especiais
    for (projetil *p = jogador->arma->shots; p != NULL; p = (projetil *)p->proximo)
    {
        p->especial = true;
    }
}

// Função para atualizar o estado do ataque especial
void atualizar_ataque_especial(jogador *jogador, simbolo_ataque_especial **simbolo_ptr)
{
    if (jogador->especial->ativo)
    {
        // Calcula o tempo decorrido desde a ativação
        clock_t agora = clock();
        int tempo_decorrido = (int)((double)(agora - jogador->especial->tempo_inicio) * 10000.0 / CLOCKS_PER_SEC);

        // Verifica se o tempo decorrido excedeu a duração do ataque especial
        if (tempo_decorrido >= jogador->especial->duracao)
        {
            jogador->especial->ativo = false;

            // Restaura os projéteis para o estado normal
            for (projetil *p = jogador->arma->shots; p != NULL; p = (projetil *)p->proximo)
            {
                p->especial = false; // Remove a marcação de especial
            }

            // Após o término, destrua o símbolo do ataque especial se ainda existir
            if (*simbolo_ptr)
            {
                destruir_simbolo_ataque_especial(*simbolo_ptr);
                *simbolo_ptr = NULL;
            }
        }
    }
}
