#ifndef __ARMA__ 																												//Guardas de inclusão (!)
#define __ARMA__																												//Guardas de inclusão (!)

#include "projetil.h"

#define ARMA_COOLDOWN 10																										//Tamanho, em frames, do tempo entre um tiro e outro (!)

typedef struct {																												//Definição da estrutura de uma armaa (!)
	unsigned char timer;																										//Relógio de intervalo entre tiros (!)
	projetil *shots;																												//Lista de balas ativas no campo disparadas pelas arma	 (!)
} arma;																														//Definição do nome da estrutura (!)

arma* arma_create();																										//Protótipo da função de criação de uma armaa (!)
projetil* arma_shot(unsigned short x, unsigned short y, unsigned char trajectory, arma *gun);									//Protótipo da função de disparo de uma armaa (!)
void arma_destroy(arma *element);																							//Protótipo da função de destruição de uma armaa (!)

#endif																															//Guardas de inclusão (!)