#include <stdlib.h>
#include "arma.h"
#include "configuracoes.h"

// Função de criação de uma nova arma
arma *criar_arma()
{
    arma *nova_arma = (arma *)malloc(sizeof(*nova_arma)); // Aloca memória na heap para uma nova arma
    if (!nova_arma)
        return NULL;

    nova_arma->timer = ARMA_COOLDOWN; // Define o tempo de cooldown da arma
    nova_arma->shots = NULL;          // Inicializa a lista de projéteis disparados

    return nova_arma;
}
// Função de disparo de um projétil
projetil *disparo_arma(unsigned short x, unsigned short y, unsigned char trajetoria, arma *arma)
{
    projetil *novo_projetil = criar_projetil((x + 60), y, trajetoria, NULL); // Cria um novo projétil
    if (!novo_projetil)
        return NULL;

    novo_projetil->proximo = arma->shots; // Insere o novo projétil no início da lista
    arma->shots = novo_projetil;

    return novo_projetil;
}

// Função para atualizar o cooldown da arma
void atualiza_arma(arma *arma)
{
    if (arma->timer)
        arma->timer--; // Decrementa o cooldown da arma
}
// Função para destruir a arma e seus projéteis
void destroi_arma(arma *arma)
{
    projetil *current = arma->shots;
    while (current != NULL)
    {
        projetil *next = current->proximo;
        destruir_projetil(current); // Libera a memória do projétil
        current = next;
    }
    free(arma); // Libera a memória da arma
}
