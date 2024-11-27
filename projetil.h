#ifndef __PROJETIL__ // Guardas de inclusão
#define __PROJETIL__ // Guardas de inclusão

#include <allegro5/allegro.h> // Biblioteca base do Allegro
#include "configuracoes.h" // Biblioteca de configurações

typedef struct projetil
{
    unsigned short x;          // Local, no eixo x, onde se localiza o projetil
    unsigned short y;          // Local, no eixo y, onde se localiza o projetil
    unsigned char trajetoria;  // Trajetória da projetil
    struct projetil *proximo;  // Próxima projetil, se houver, formando uma lista encadeada
    struct projetil *especial; // Projetil especial (adquirido no mapa!)
    // ALLEGRO_BITMAP *imagem;    // Imagem do projétil (feature futura)
} projetil;

// função de criação de um projetil
projetil *criar_projetil(unsigned short x, unsigned short y, unsigned char trajectory, projetil *proximo);
// função de desenho de um projetil
void desenhar_projetil(projetil *projetil);
// função de movimentação de um projetil
void mover_projetil(projetil **elements);
// função de verificação de colisão de um projetil
int verificar_colisao_projetil(projetil *projetil, unsigned short x, unsigned short y, unsigned short side);
// função de destruição de um projetil
void destruir_projetil(projetil *element);

#endif // Guardas de inclusão
