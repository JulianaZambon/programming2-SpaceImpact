#ifndef __JOYSTICK__ // Guardas de inclusão
#define __JOYSTICK__ // Guardas de inclusão

/*-------------------------------------------------------------------*/
/* ESTRUTURA */

// Estrutura para o controle do jogador
typedef struct
{
    unsigned char direita;  // Botão de movimentação à direta
    unsigned char esquerda; // Botão de movimentação à esquerda
    unsigned char cima;     // Botão de movimentação para cima
    unsigned char baixo;    // Botão de movimentação para baixo
    unsigned char fogo;     // Botão de disparo
} joystick;

/*-------------------------------------------------------------------*/
/* PROTÓTIPOS DE FUNÇÕES */

// Função de criação de um controle
joystick *criar_joystick();
// Função de destruição de um controle
void destroi_joystick(joystick *element);
// Função de ativação/desativação do botão de movimentação à direita
void joystick_direita(joystick *element);
// Função de ativação/desativação do botão de movimentação à esquerda
void joystick_esquerda(joystick *element);
// Função de ativação/desativação do botão de movimentação para cima
void joystick_cima(joystick *element);
// Função de ativação/desativação do botão de movimentação para baixo
void joystick_baixo(joystick *element);
// Função de ativação/desativação do botão de disparo
void joystick_fogo(joystick *element);

#endif // Guardas de inclusão
