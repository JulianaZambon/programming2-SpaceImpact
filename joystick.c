#include <stdlib.h>

// Libs locais
#include "joystick.h"

/*-----------------------------------------------------------------------------------------*/
/* FUNÇÕES */

// Cria um novo controle
joystick *criar_joystick()
{
	joystick *elemento = (joystick *)malloc(sizeof(joystick)); // Aloca memória na heap para um novo controle
	if (!elemento)
		return NULL;

	elemento->direita = 0;	// Insere o estado de desligado para o botão de movimentação à esquerda
	elemento->esquerda = 0; // Insere o estado de desligado para o botão de movimentação à direita
	elemento->cima = 0;		// Insere o estado de desligado para o botão de movimentação para cima
	elemento->baixo = 0;	// Insere o estado de desligado para o botão de movimentação para baixo
	elemento->fogo = 0;		// Insere o estado de desligado para o botão de disparo

	return elemento;		// Retorna o novo controle
}

// Libera a memória do elemento na heap
void destroi_joystick(joystick *elemento)
{
	free(elemento);
}

// Mudam o estado do botão
void joystick_esquerda(joystick *elemento)
{
	elemento->esquerda = elemento->esquerda ^ 1;
}

void joystick_direita(joystick *elemento)
{
	elemento->direita = elemento->direita ^ 1;
}

void joystick_cima(joystick *elemento)
{
	elemento->cima = elemento->cima ^ 1;
}

void joystick_baixo(joystick *elemento)
{
	elemento->baixo = elemento->baixo ^ 1;
}

void joystick_fogo(joystick *elemento)
{
	elemento->fogo = elemento->fogo ^ 1;
}
