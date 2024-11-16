#include <stdlib.h>
#include "projetil.h"

projetil *projetil_create(unsigned short x, unsigned short y, unsigned char trajectory, projetil *next)
{ 
    if ((trajectory < 0) || (trajectory > 1))
        return NULL; // Verifica se a trajetória informada para o projétil é válida

    projetil *new_projetil = (projetil *)malloc(sizeof(projetil)); // Aloca memória na heap para uma instância de projétil
    if (!new_projetil)
        return NULL;

    new_projetil->x = x;                      // Armazena a posição X informada
    new_projetil->y = y;                      // Armazena a posição Y informada
    new_projetil->trajectory = trajectory;    // Armazena a trajetória informada
    new_projetil->next = (struct projetil *)next; // Armazena o próximo projétil informado

    return new_projetil;                      
}

void projetil_move(projetil *elements)
{ // Implementação da função "projetil_move"

    for (projetil *index = elements; index != NULL; index = (projetil *)index->next)
    { // Para cada projétil presente na lista de projéteis informada
        if (!index->trajectory)
            index->x = index->x - PROJETIL_MOVE; // Se a trajetória for para a esquerda, movimenta um passo à esquerda
        else
            index->x = index->x + PROJETIL_MOVE; // Se a trajetória for para a direita, movimenta um passo à direita
    }
}

void projetil_destroy(projetil *element)
{ 
    free(element); // Libera a memória da instância de projétil
}