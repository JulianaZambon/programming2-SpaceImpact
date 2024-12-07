#include <stdlib.h>

// Inclusões de bibliotecas locais
#include "arma.h"
#include "configuracoes.h"

/*-------------------------------------------------------------------*/
/* FUNÇÕES */

// Função de criação de uma nova arma
arma *criar_arma()
{
    arma *nova_arma = (arma *)malloc(sizeof(*nova_arma)); 
    if (!nova_arma)
        return NULL;

    nova_arma->timer = ARMA_COOLDOWN; // Define o tempo de cooldown da arma
    nova_arma->shots = NULL;          // Inicializa a lista de projéteis disparados

    return nova_arma;
}
// Função de disparo de um projétil
projetil *disparo_arma(unsigned short x, unsigned short y, unsigned char trajetoria, arma *arma)
{
    projetil *novo_projetil = criar_projetil((x + 60), y, trajetoria, NULL); 
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

void destroi_arma(arma *elemento)
{
    if (!elemento)
        return;

    projetil *atual = elemento->shots;
    projetil *temp;

    // Libera todos os projéteis disparados pela arma
    while (atual != NULL)
    {
        temp = atual;
        atual = (projetil *)atual->proximo;
        destruir_projetil(temp);
    }

    free(elemento); // Libera a memória da arma
}
