#include <stdlib.h>
#include "projetil.h"
#include "configuracoes.h"

// função de criação de um projetil
projetil *projetil_create(unsigned short x, unsigned short y, unsigned char trajectory, projetil *next)
{
    projetil *new_proj = (projetil *)malloc(sizeof(projetil)); // Aloca memória para um novo projétil
    if (!new_proj)
        return NULL; // Verifica se a alocação foi bem-sucedida

    new_proj->x = x;             // Insere a posição inicial de X
    new_proj->y = y;             // Insere a posição inicial de Y
    new_proj->trajectory = trajectory; // Insere a trajetória do projétil
    new_proj->next = next;       // Insere o próximo projétil

    return new_proj;
}
// função de movimentação de um projetil
void projetil_move(projetil *elements)
{
    if (!elements->trajectory)
    {
        if (elements->x - PROJETIL_MOVE >= 0)
            elements->x -= PROJETIL_MOVE;
    } // Verifica se a movimentação para a esquerda é desejada e possível; se sim, efetiva a mesma
    else if (elements->trajectory == 1)
    {
        if (elements->x + PROJETIL_MOVE <= X_SCREEN)
            elements->x += PROJETIL_MOVE;
    } // Verifica se a movimentação para a direita é desejada e possível; se sim, efetiva a mesma
}
// função de destruição de um projetil
void projetil_destroy(projetil *element)
{
    if (element)
    {
        free(element); // Libera a memória do projétil
    }
}