#ifndef __FASES__ // Guardas de inclusão
#define __FASES__ // Guardas de inclusão

#include "inimigos.h"
#include "chefes.h"
#include "jogador.h"

typedef struct
{
    enemy enemies[NUM_INIMIGOS]; // Vetor de inimigos
    boss bosses[NUM_BOSSES];     // Vetor de chefes
} fases;

#endif
