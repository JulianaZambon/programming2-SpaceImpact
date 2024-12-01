#ifndef __PROJETIL__ // Guardas de inclusão
#define __PROJETIL__ // Guardas de inclusão

#include <allegro5/allegro.h>

/*-----------------------------------------------------------------------------------------*/
/* DEFINIÇÕES */
#define PROJETIL_MOVE 5 // Velocidade do projetil (quanto maior, mais rápido)

/*-----------------------------------------------------------------------------------------*/
/* ESTRUTURAS */

// Estrutura para o ataque especial
typedef struct ataque_especial
{
    int tempo; // Tempo em que o ataque especial dura (max de 5s)
} ataque_especial;

// Estrutura para o projetil
typedef struct projetil
{
    unsigned short x;          // Local, no eixo x, onde se localiza o projetil
    unsigned short y;          // Local, no eixo y, onde se localiza o projetil
    unsigned char trajetoria;  // Trajetória da projetil
    struct projetil *proximo;  // Próxima projetil, se houver, formando uma lista encadeada
    ataque_especial *especial; // Projetil especial (adquirido no mapa!)
} projetil;

/*-----------------------------------------------------------------------------------------*/
/* PROTÓTIPOS DE FUNÇÕES */

// Função de criação de um projetil
projetil *criar_projetil(unsigned short x, unsigned short y, unsigned char trajectory, projetil *proximo);
// Função de movimentação de um projetil
void mover_projetil(projetil **elements);
// Função de destruição de um projetil
void destruir_projetil(projetil *element);

/*-----------------------------------------------------------------------------------------*/
/* DESENHO DE PROJETEIS */
/*-----------------------------------------------------------------------------------------*/
/* JOGADOR */
// Função de desenho de projetil para o jogador
void desenhar_projetil_jogador(projetil *projetil);
void desenhar_projetil_especial_jogador_1(projetil *projetil);
void desenhar_projetil_especial_jogador_2(projetil *projetil);
/*-----------------------------------------------------------------------------------------*/
/* INIMIGOS */
// Função de desenho de projetil para os inimigos
void desenhar_projetil_inimigo_fase_1(projetil *projetil);
void desenhar_projetil_inimigo_fase_2(projetil *projetil);
/*-----------------------------------------------------------------------------------------*/
// Função de desenho de projetil para os chefes
/* CHEFE FASE 01 */
void desenhar_projetil_chefe_0(projetil *projetil);
void desenhar_projetil2_chefe_0(projetil *projetil);
/*-----------------------------------------------------------------------------------------*/
/* CHEFE FASE 02 */
void desenhar_projetil_chefe_1(projetil *projetil);
void desenhar_projetil2_chefe_1(projetil *projetil);

/*-----------------------------------------------------------------------------------------*/
/* ATAQUE ESPECIAL */

#endif // Guardas de inclusão
