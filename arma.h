#ifndef __ARMA__ // Guardas de inclusão
#define __ARMA__ // Guardas de inclusão

#include "projetil.h"

#define ARMA_COOLDOWN 10  //Tamanho, em frames, do tempo entre um tiro e outro

typedef struct
{
	unsigned char timer; // Relógio de intervalo entre tiros
	projetil *shots;	 // Lista de balas ativas no campo disparadas pelas arma
} arma;

// função de criação de uma arma
arma *arma_create();
// função de disparo de uma arma
projetil *arma_shot(unsigned short x, unsigned short y, unsigned char trajectory, arma *gun);
// função de destruição de uma arma
void arma_destroy(arma *element);

#endif // Guardas de inclusão
