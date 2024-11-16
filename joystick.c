#include <stdlib.h>
#include "joystick.h"

joystick *joystick_create()
{
	joystick *element = (joystick *)malloc(sizeof(joystick)); // Aloca memória na heap para um novo controle
	if (!element)
		return NULL;
	element->right = 0; // Insere o estado de desligado para o botão de movimentação à esquerda
	element->left = 0;	// Insere o estado de desligado para o botão de movimentação à direita
	element->up = 0;	// Insere o estado de desligado para o botão de movimentação para cima
	element->down = 0;	// Insere o estado de desligado para o botão de movimentação para baixo
	element->fire = 0;
	return element; // Retorna o novo controle
}

// libera a memória do elemento na heap
void joystick_destroy(joystick *element)
{
	free(element);
}

// muda o estado do botão
void joystick_left(joystick *element)
{
	element->left = element->left ^ 1;
}
void joystick_right(joystick *element)
{
	element->right = element->right ^ 1;
}
void joystick_up(joystick *element)
{
	element->up = element->up ^ 1;
}
void joystick_down(joystick *element)
{
	element->down = element->down ^ 1;
}
void joystick_fire(joystick *element)
{
	element->fire = element->fire ^ 1;
}
