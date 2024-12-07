#include <allegro5/allegro.h>

#include "configuracoes.h"
#include "jogador.h"

// Atualiza a posição e ações do jogador e projéteis disparados
void atualiza_posicao(jogador *jogador_1)
{
    // Movimentação do jogador
    if (jogador_1->controle->esquerda)
        mover_jogador(jogador_1, 1, 0, X_SCREEN, Y_SCREEN);
    if (jogador_1->controle->direita)
        mover_jogador(jogador_1, 1, 1, X_SCREEN, Y_SCREEN);
    if (jogador_1->controle->cima)
        mover_jogador(jogador_1, 1, 2, X_SCREEN, Y_SCREEN);
    if (jogador_1->controle->baixo)
        mover_jogador(jogador_1, 1, 3, X_SCREEN, Y_SCREEN);

    // Disparo de projétil
    if (jogador_1->controle->fogo && !jogador_1->arma->timer)
    {
        jogador_atira(jogador_1);               // Realiza o disparo
        jogador_1->arma->timer = ARMA_COOLDOWN; // Define o tempo de cooldown da arma
    }

    // Atualiza a posição/movimentação dos projéteis
    mover_projetil(&jogador_1->arma->shots);
}

void processa_evento_teclado(ALLEGRO_EVENT event, jogador *jogador_1)
{
    switch (event.keyboard.keycode)
    {
    case ALLEGRO_KEY_LEFT:
        joystick_esquerda(jogador_1->controle);
        break;
    case ALLEGRO_KEY_RIGHT:
        joystick_direita(jogador_1->controle);
        break;
    case ALLEGRO_KEY_UP:
        joystick_cima(jogador_1->controle);
        break;
    case ALLEGRO_KEY_DOWN:
        joystick_baixo(jogador_1->controle);
        break;
    case ALLEGRO_KEY_SPACE:
        joystick_fogo(jogador_1->controle);
        break;
    }
}