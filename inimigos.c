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
    novo_inimigo->proximo = NULL;      // Inicializa o próximo inimigo como NULL

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
        novo_inimigo->sprite_info->largura = QUADRADO_SPRITE_INIMIGO_0;
        novo_inimigo->sprite_info->altura = QUADRADO_SPRITE_INIMIGO_0;
        novo_inimigo->sprite_info->num_frames = COLUNAS_SPRITE_INIMIGO_0;
        novo_inimigo->hp = HP_INIMIGO_0;
        novo_inimigo->pode_atirar = NAO_ATIRA;
        novo_inimigo->contador_animacao = CONTADOR_ZERADO;
        break;
    case 1:
        novo_inimigo->sprite_info->sprite = al_load_bitmap(PATH_INIMIGO_1);
        novo_inimigo->sprite_info->largura = QUADRADO_SPRITE_INIMIGO_1;
        novo_inimigo->sprite_info->altura = QUADRADO_SPRITE_INIMIGO_1;
        novo_inimigo->sprite_info->num_frames = COLUNAS_SPRITE_INIMIGO_1;
        novo_inimigo->hp = HP_INIMIGO_1;
        novo_inimigo->pode_atirar = ATIRA;
        novo_inimigo->contador_animacao = CONTADOR_ZERADO;
        break;
    case 2:
        novo_inimigo->sprite_info->sprite = al_load_bitmap(PATH_INIMIGO_2);
        novo_inimigo->sprite_info->largura = QUADRADO_SPRITE_INIMIGO_2;
        novo_inimigo->sprite_info->altura = QUADRADO_SPRITE_INIMIGO_2;
        novo_inimigo->sprite_info->num_frames = COLUNAS_SPRITE_INIMIGO_2;
        novo_inimigo->hp = HP_INIMIGO_2;
        novo_inimigo->pode_atirar = NAO_ATIRA;
        novo_inimigo->contador_animacao = CONTADOR_ZERADO;
        break;
    case 3:
        novo_inimigo->sprite_info->sprite = al_load_bitmap(PATH_INIMIGO_3);
        novo_inimigo->sprite_info->largura = QUADRADO_SPRITE_INIMIGO_3;
        novo_inimigo->sprite_info->altura = QUADRADO_SPRITE_INIMIGO_3;
        novo_inimigo->sprite_info->num_frames = COLUNAS_SPRITE_INIMIGO_3;
        novo_inimigo->hp = HP_INIMIGO_3;
        novo_inimigo->pode_atirar = ATIRA;
        novo_inimigo->contador_animacao = CONTADOR_ZERADO;
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
    case 1: // Movimento simples para a esquerda (somente no eixo X)
        elemento->x -= INIMIGO_STEP * steps;
        break;
    case 2: // Movimento em círculo
        // Movimento contínuo no eixo X
        elemento->x -= INIMIGO2_STEP * steps; // Movimento para a esquerda
        // Se o inimigo sair da tela pela esquerda, ele reaparece no lado direito
        if (elemento->x + elemento->tam_lateral / 2 < 0)
        {
            elemento->x = max_x; // Reposiciona no lado direito da tela
        }
        // Movimento circular no eixo Y com função seno
        // Para dar um efeito de círculo, usamos um valor de X para calcular Y de forma contínua
        elemento->y = max_y / 2 + 100 * sin(elemento->x / 50.0); // Ajustar o 50.0 para controlar a frequência da oscilação no Y
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
void atualizar_animacao_inimigo(inimigo *elemento, unsigned int delay)
{
    if (!elemento || !elemento->sprite_info)
        return;

    // Atualiza o contador de animação específico de cada inimigo
    if (++(elemento->contador_animacao) >= delay)
    {
        elemento->frame_atual = (elemento->frame_atual + 1) % elemento->sprite_info->num_frames;
        elemento->contador_animacao = 0; // Reseta o contador de animação do inimigo
    }
}

// Função para adicionar um inimigo à lista
// Função para adicionar inimigos na lista
// Função para adicionar inimigos na lista
void adicionar_inimigo_lista(inimigo **lista, unsigned char sprite, unsigned short tipo)
{
    inimigo **atual = lista;

    // Percorre a lista até encontrar o final
    while (*atual != NULL)
    {
        atual = &(*atual)->proximo;
    }

    // Determina a altura do sprite com base no tipo do inimigo
    int altura_sprite;
    switch (tipo)
    {
    case 0:
        altura_sprite = QUADRADO_SPRITE_INIMIGO_0;
        break;
    case 1:
        altura_sprite = QUADRADO_SPRITE_INIMIGO_1;
        break;
    case 2:
        altura_sprite = QUADRADO_SPRITE_INIMIGO_2;
        break;
    case 3:
        altura_sprite = QUADRADO_SPRITE_INIMIGO_3;
        break;
    default:
        altura_sprite = 0; // Fallback
        break;
    }

    // Gera uma posição Y válida para o inimigo, garantindo que ele não sobreponha os corações
    int pos_y = rand() % (Y_SCREEN - ESPACO_INTERFACE - altura_sprite);
    
    if (pos_y < altura_sprite) // Ajusta para que o inimigo não fique acima da tela visível
    {
        pos_y = altura_sprite;
    }

    // Cria um novo inimigo com a posição ajustada
    inimigo *novo_inimigo = criar_inimigo(sprite, 1, X_SCREEN - 50, pos_y, tipo, X_SCREEN, Y_SCREEN);

    if (novo_inimigo)
    {
        *atual = novo_inimigo;
    }
}

/*
Na fase 1, devem ser criados todos os inimigos do tipo 0, para então serem criados todos os inimigos do tipo 1
Na fase 2, devem ser criados todos os inimigos do tipo 2, para então serem criados todos os inimigos do tipo 3
*/

// Função de atualização da criação de inimigos
// Função de atualização da criação de inimigos na fase 1
void atualizar_criacao_inimigo_fase1(inimigo **lista)
{
    static unsigned int intervalo_criacao = 0;                                       // Intervalo entre a criação de inimigos
    static unsigned int max_inimigos_tipo[2] = {QNTD_INIM_TIPO_0, QNTD_INIM_TIPO_1}; // Limite de inimigos por tipo
    static unsigned short tipo_atual = 0;                                            // Tipo atual de inimigo a ser criado

    // Atualiza o intervalo de criação de inimigos
    if (intervalo_criacao > 0)
    {
        intervalo_criacao--;
        return; // Aguarda o intervalo para criar o próximo inimigo
    }

    if (tipo_atual == 0 || tipo_atual == 1)
    {
        adicionar_inimigo_lista(lista, tipo_atual, tipo_atual);

        if (--max_inimigos_tipo[tipo_atual] == 0)
        {
            tipo_atual++; // Passa para o próximo tipo de inimigo
        }
    }

    // Verifica se todos os tipos foram criados
    if (tipo_atual > 1) // Quando todos os inimigos dos tipos 0 e 1 foram criados
    {
        return; // Todos os inimigos foram criados
    }

    // Define o próximo intervalo de criação
    intervalo_criacao = rand() % MIN_INTERVALO_FASE01 + MAX_INTERVALO_FASE01; // Intervalo aleatorio entre 150 e 300
}

// Função de atualização da criação de inimigos na fase 2
void atualizar_criacao_inimigo_fase2(inimigo **lista)
{
    static unsigned int intervalo_criacao = 0;                                       // Intervalo entre a criação de inimigos
    static unsigned int max_inimigos_tipo[2] = {QNTD_INIM_TIPO_2, QNTD_INIM_TIPO_3}; // Limite de inimigos por tipo
    static unsigned short tipo_atual = 2;                                            // Tipo atual de inimigo a ser criado

    // Atualiza o intervalo de criação de inimigos
    if (intervalo_criacao > 0)
    {
        intervalo_criacao--;
        return; // Aguarda o intervalo para criar o próximo inimigo
    }

    if (tipo_atual == 2 || tipo_atual == 3)
    {
        adicionar_inimigo_lista(lista, tipo_atual, tipo_atual);

        if (--max_inimigos_tipo[tipo_atual - 2] == 0) // Decrementa a quantidade de inimigos para o tipo atual
        {
            tipo_atual++; // Passa para o próximo tipo de inimigo
        }
    }

    // Verifica se todos os tipos foram criados
    if (tipo_atual > 3) // Quando todos os inimigos dos tipos 2 e 3 foram criados
    {
        return; // Todos os inimigos foram criados
    }

    // Define o próximo intervalo de criação
    intervalo_criacao = rand() % MIN_INTERVALO_FASE02 + MAX_INTERVALO_FASE02;
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
    if (!elemento)
        return;

    // Destroi o sprite associado ao inimigo, se existir
    if (elemento->sprite_info)
    {
        if (elemento->sprite_info->sprite)
        {
            al_destroy_bitmap(elemento->sprite_info->sprite); // Destroi o sprite
            elemento->sprite_info->sprite = NULL;             // Anula o ponteiro
        }
        free(elemento->sprite_info); // Libera a estrutura sprite_info
        elemento->sprite_info = NULL;
    }

    // Destroi a arma associada ao inimigo, se existir
    if (elemento->arma)
    {
        destroi_arma(elemento->arma);
        elemento->arma = NULL; // Anula o ponteiro da arma
    }

    free(elemento);  // Libera a memória do inimigo
    elemento = NULL; // Anula o ponteiro para evitar acessos futuros
}
