#ifndef __ARMA__ // Guardas de inclusão
#define __ARMA__ 

#include "projetil.h"

typedef struct arma {
    int timer;        // Timer de cooldown entre disparos
    projetil *shots;  // Lista encadeada de projéteis disparados
} arma;

// Função de criação de uma nova arma
arma *arma_create();
// Função de disparo de um projétil
projetil *arma_shot(unsigned short x, unsigned short y, unsigned char trajectory, arma *gun);
// Função para atualizar o cooldown da arma
void update_arma(arma *gun);
// Função para destruir a arma e seus projéteis
void arma_destroy(arma *gun);

#endif // __ARMA__
