#ifndef __JOYSTICK__ // Guardas de inclusão 
#define __JOYSTICK__ // Guardas de inclusão 

typedef struct
{                        
    unsigned char right; // Botão de movimentação à direta 
    unsigned char left;  // Botão de movimentação à esquerda 
    unsigned char up;    // Botão de movimentação para cima 
    unsigned char down;  // Botão de movimentação para baixo 
} joystick;              

joystick *joystick_create();              // função de criação de um controle 
void joystick_destroy(joystick *element); // função de destruição de um controle 
void joystick_right(joystick *element);   // função de ativação/desativação do botão de movimentação à direita 
void joystick_left(joystick *element);    // função de ativação/desativação do botão de movimentação à esquerda 
void joystick_up(joystick *element);      // função de ativação/desativação do botão de movimentação para cima 
void joystick_down(joystick *element);    // função de ativação/desativação do botão de movimentação para baixo 

#endif // Guardas de inclusão 
