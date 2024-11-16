#include <stdlib.h>
#include "arma.h"

arma *arma_create()
{ 
    arma *new_arma = (arma *)malloc(sizeof(arma)); // Aloca a memória na heap para uma instância de armaa 
    if (!new_arma)
        return NULL;

    new_arma->timer = 0;    // Inicializa o relógio de disparos em zero (pronto para atirar) 
    new_arma->shots = NULL; // Inicializa a lista de disparos com NULL; ou seja, sem disparos 

    return new_arma;        
}

projetil *arma_shot(unsigned short x, unsigned short y, unsigned char trajectory, arma *gun)
{ 

    projetil *new_projetil = projetil_create(x, y, trajectory, gun->shots); // Cria uma nova instância de projétil a ser disparado 
    if (!new_projetil)
        return NULL;     // Verifica o sucesso da alocação de memória; retorna NULL em caso de falha 
    return new_projetil; // Retorna uma nova instância de projétil 
}

void arma_destroy(arma *element)
{ 
    projetil *sentinel; // Sentinela para a remoção de projéteis ativos 
    for (projetil *index = element->shots; index != NULL; index = sentinel)
    {                                       // Para cada projétil na lista de disparos 
        sentinel = (projetil *)index->next; // Armazena o próximo projétil 
        projetil_destroy(index);            // Chama o destrutor do projétil atual 
    }
    free(element); // Libera a memória da instância de arma
}