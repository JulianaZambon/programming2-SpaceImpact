#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <stdlib.h>

// Libs locais
#include "projetil.h"
#include "configuracoes.h"

/*-----------------------------------------------------------------------------------------*/
/* FUNÇÕES */

// Função de criação de um projetil
projetil *criar_projetil(unsigned short x, unsigned short y, unsigned char trajetoria, projetil *proximo)
{
    projetil *novo_projetil = (projetil *)malloc(sizeof(*novo_projetil)); // Aloca memória na heap para um novo projetil
    if (!novo_projetil)
        return NULL;

    novo_projetil->x = x;                   // Insere a posição inicial de X
    novo_projetil->y = y;                   // Insere a posição inicial de Y
    novo_projetil->trajetoria = trajetoria; // Insere a trajetória do projetil
    novo_projetil->proximo = proximo;       // Insere o próximo projetil na lista

    return novo_projetil;
}

// Função de desenho de um projetil
void desenhar_projetil(projetil *projetil)
{
    // futuramente usar uma imagem
    // ALLEGRO_BITMAP *imagem = projetil->imagem;
    // al_draw_bitmap(imagem, projetil->x, projetil->y, 0);

    // Desenha um círculo vermelho representando o projétil
    al_draw_filled_circle(projetil->x, projetil->y, 7, al_map_rgb(255, 0, 0));
}

// Função de movimentação de um projetil
void mover_projetil(projetil **elements)
{
    projetil *anterior = NULL;
    projetil *atual = *elements; // Começa a partir do primeiro projetil na lista

    while (atual != NULL)
    {
        // Movimenta o projetil baseado na sua trajetória
        if (atual->trajetoria == 0) // Esquerda
        {
            atual->x -= PROJETIL_MOVE; // Move o projetil para a esquerda
        }
        else if (atual->trajetoria == 1) // Direita
        {
            atual->x += PROJETIL_MOVE; // Move o projetil para a direita
        }

        // Verifica se o projetil saiu da tela (no eixo X)
        if (atual->x < 0 || atual->x > X_SCREEN)
        {
            projetil *proximo = atual->proximo;

            if (anterior)
                anterior->proximo = proximo; // Remove o projetil da lista
            else
                *elements = proximo; // Atualiza o início da lista

            destruir_projetil(atual); // Libera memória do projetil fora da tela
            atual = proximo;          // Atualiza para o próximo projetil
        }
        else
        {
            // Avança para o próximo projetil
            anterior = atual;
            atual = atual->proximo;
        }
    }
}

// Função de verificação de colisão de um projetil
int verificar_colisao_projetil(projetil *projetil, unsigned short x, unsigned short y, unsigned short side)
{
    // Verifique se o projétil está dentro dos limites da área (centro em x, y, com lado 'side')
    if ((projetil->x >= x - side / 2) && (projetil->x <= x + side / 2) && // Verificação no eixo X
        (projetil->y >= y - side / 2) && (projetil->y <= y + side / 2))     // Verificação no eixo Y
    {
        return 1; // Se a colisão for detectada, retorne 1 (verdadeiro)
    }
    return 0; // Se não houve colisão, retorne 0 (falso)
}

// Função de destruição de um projetil
void destruir_projetil(projetil *element)
{
    free(element); // Libera a memória alocada para o projetil
}
