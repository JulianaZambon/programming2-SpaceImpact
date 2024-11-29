#ifndef __ARMA__ // Guardas de inclusão
#define __ARMA__

// Inclusões de bibliotecas locais
#include "projetil.h"

/*-----------------------------------------------------------------------------------------*/
/* DEFINIÇÕES */

#define ARMA_COOLDOWN 10 // tempo de cooldown da arma (quanto maior, mais lento)
#define ARMA_COOLDOWN_INIMIGO 90

/*-----------------------------------------------------------------------------------------*/
/* ESTRUTURAS */

// Estrutura para a arma
typedef struct arma
{
    int timer;       // Timer de cooldown entre disparos
    projetil *shots; // Lista encadeada de projéteis disparados
} arma;

/*-----------------------------------------------------------------------------------------*/
/* PROTÓTIPOS DE FUNÇÕES */

// Função de criação de uma nova arma
arma *criar_arma();
// Função de disparo de um projétil
projetil *disparo_arma(unsigned short x, unsigned short y, unsigned char trajetoria, arma *arma);
// Função para atualizar o cooldown da arma
void atualiza_arma(arma *arma);
// Função para destruir a arma e seus projéteis
void destroi_arma(arma *arma);

#endif // __ARMA__
