#include "narrativa.h"

/*-------------------------------------------------------------------*/
/* FUNÇÕES */

tela_nave_ligando *criar_tela_nave_ligando()
{
    tela_nave_ligando *nave_ligando = (tela_nave_ligando *)malloc(sizeof(tela_nave_ligando));
    if (!nave_ligando)
        return NULL;

    nave_ligando->largura = 1140;
    nave_ligando->altura = 640;
    nave_ligando->num_frames = 5;
    nave_ligando->frame_atual = 0;
    nave_ligando->animation_counter = 0;
    nave_ligando->sprite = al_load_bitmap(PATH_NAVE_LIGANDO);

    if (!nave_ligando->sprite)
    {
        free(nave_ligando);
        return NULL;
    }

    return nave_ligando;
}

void desenhar_tela_nave_ligando(tela_nave_ligando *tela_nave_ligando)
{
    if (!tela_nave_ligando || !tela_nave_ligando->sprite)
        return;

    int sprite_largura = tela_nave_ligando->largura;
    int sprite_altura = tela_nave_ligando->altura;

    // Calcula a posição do quadro no sprite sheet
    int frame_x = (tela_nave_ligando->frame_atual % tela_nave_ligando->num_frames) * sprite_largura;
    int frame_y = (tela_nave_ligando->frame_atual / tela_nave_ligando->num_frames) * sprite_altura;

    // Desenha a região do sprite correspondente
    al_draw_bitmap_region(tela_nave_ligando->sprite, frame_x, frame_y, sprite_largura, sprite_altura, 0, 0, 0);
}

void atualizar_animacao_tela_nave_ligando(tela_nave_ligando *tela_nave_ligando,
                                          unsigned int *animation_counter, unsigned int delay)
{
    if (!tela_nave_ligando)
        return;

    // Atualiza contador de animação
    if (++(*animation_counter) >= delay)
    {
        tela_nave_ligando->frame_atual = (tela_nave_ligando->frame_atual + 1) % FRAMES_NAVE_LIGANDO;
        *animation_counter = 0; // Reseta o contador de animação
    }
}

tela_velocidade_luz *criar_tela_velocidade_luz()
{
    tela_velocidade_luz *velocidade_luz = (tela_velocidade_luz *)malloc(sizeof(tela_velocidade_luz));
    if (!velocidade_luz)
        return NULL;

    velocidade_luz->largura = 1140;
    velocidade_luz->altura = 640;
    velocidade_luz->num_frames = 7;
    velocidade_luz->frame_atual = 0;
    velocidade_luz->sprite = al_load_bitmap(PATH_VELOCIDADE_LUZ);

    if (!velocidade_luz->sprite)
    {
        free(velocidade_luz);
        return NULL;
    }

    return velocidade_luz;
}

void desenhar_tela_velocidade_luz(tela_velocidade_luz *tela_velocidade_luz)
{
    if (!tela_velocidade_luz || !tela_velocidade_luz->sprite)
        return;

    int sprite_largura = tela_velocidade_luz->largura;
    int sprite_altura = tela_velocidade_luz->altura;

    // Calcula a posição do quadro no sprite sheet
    int frame_x = (tela_velocidade_luz->frame_atual % tela_velocidade_luz->num_frames) * sprite_largura;
    int frame_y = (tela_velocidade_luz->frame_atual / tela_velocidade_luz->num_frames) * sprite_altura;

    // Desenha a região do sprite correspondente
    al_draw_bitmap_region(tela_velocidade_luz->sprite, frame_x, frame_y, sprite_largura, sprite_altura, 0, 0, 0);
}

void atualizar_animacao_tela_velocidade_luz(tela_velocidade_luz *tela_velocidade_luz,
                                            unsigned int *animation_counter, unsigned int delay)
{
    if (!tela_velocidade_luz)
        return;

    // Atualiza contador de animação
    if (++(*animation_counter) >= delay)
    {
        tela_velocidade_luz->frame_atual = (tela_velocidade_luz->frame_atual + 1) % FRAMES_VELOCIDADE_LUZ;
        *animation_counter = 0; // Reseta o contador de animação
    }
}