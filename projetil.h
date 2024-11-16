#ifndef __PROJETIL__ // Guardas de inclusão (!)
#define __PROJETIL__ // Guardas de inclusão (!)

#define PROJETIL_MOVE 5

typedef struct
{                             // estrutura de um pŕojétil
    unsigned short x;         // Local, no eixo x, onde se localiza o projetil
    unsigned short y;         // Local, no eixo y, onde se localiza o projetil
    unsigned char trajectory; // Trajetória da projetil
    struct projetil *next;    // Próxima projetil, se houver, formando uma lista encadeada
} projetil;                   // Definição do nome da estrutura

// função de criação de um projetil
projetil *projetil_create(unsigned short x, unsigned short y, unsigned char trajectory, projetil *next);
// função de movimentação de um projetil
void projetil_move(projetil *elements);
// função de destruição de um projetil                                                                  
void projetil_destroy(projetil *element);                                                                

#endif // Guardas de inclusão