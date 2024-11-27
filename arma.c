#include <stdlib.h>
#include "arma.h"

// Função de criação de uma nova arma
arma *arma_create()
{
    arma *new_arma = (arma *)malloc(sizeof(arma)); // Aloca memória para uma nova arma
    if (!new_arma)
        return NULL; // Verifica se a alocação foi bem-sucedida

    new_arma->timer = 0;    // Inicializa o timer de cooldown
    new_arma->shots = NULL; // Inicializa a lista de projéteis disparados

    return new_arma;
}
// Função de disparo de um projétil
projetil *arma_shot(unsigned short x, unsigned short y, unsigned char trajectory, arma *gun)
{
    projetil *new_shot = projetil_create(x, y, trajectory, gun->shots); // Cria um novo projétil
    if (!new_shot)
        return NULL; // Verifica se a criação foi bem-sucedida

    gun->shots = new_shot; // Insere o novo projétil na lista de projéteis disparados

    return new_shot;
}
// Função para atualizar o cooldown da arma
void update_arma(arma *gun)
{
    if (gun->timer)
        gun->timer--; // Atualiza o cooldown da arma
}
// Função para destruir a arma e seus projéteis
void arma_destroy(arma *gun)
{
    if (gun)
    {
        projetil *index = gun->shots; // Variável auxiliar para percorrer a lista de projéteis
        while (index)
        {
            projetil *next = index->next; // Salva o próximo projétil
            projetil_destroy(index);      // Destrói o projétil atual
            index = next;                 // Atualiza para o próximo projétil
        }
        free(gun); // Libera a memória da arma
    }
}