#include "telaInicial.h"

/*-------------------------------------------------------------------*/
/* FUNÇÕES */

// Função de criação da tela inicial
tela_inicial_sprite *criar_tela_inicial()
{
    tela_inicial_sprite *tela_inicial = (tela_inicial_sprite *)malloc(sizeof(tela_inicial_sprite));
    if (!tela_inicial)
        return NULL;

    tela_inicial->largura = 1140;
    tela_inicial->altura = 640;
    tela_inicial->num_frames = 12;
    tela_inicial->frame_atual = 0;
    tela_inicial->sprite = al_load_bitmap(PATH_TELA_INICIAL);

    if (!tela_inicial->sprite)
    {
        free(tela_inicial);
        return NULL;
    }

    return tela_inicial;
}
// Desenhar a tela inicial
void desenhar_tela_inicial(tela_inicial_sprite *tela_inicial)
{
    if (!tela_inicial || !tela_inicial->sprite)
        return;
    
    int sprite_largura = tela_inicial->largura;
    int sprite_altura = tela_inicial->altura;

    // Calcula a posição do quadro no sprite sheet
    int frame_x = (tela_inicial->frame_atual % tela_inicial->num_frames) * sprite_largura;
    int frame_y = (tela_inicial->frame_atual / tela_inicial->num_frames) * sprite_altura;

    // Desenha a região do sprite correspondente
    al_draw_bitmap_region(tela_inicial->sprite, frame_x, frame_y, sprite_largura, sprite_altura, 0, 0, 0);
}
// Atualiza a animação da tela inicial
void atualizar_animacao_tela_inicial(tela_inicial_sprite *tela_inicial, unsigned int *animation_counter, unsigned int delay)
{
    if (!tela_inicial)
        return;

    // Atualiza contador de animação
    if (++(*animation_counter) >= delay)
    {
        tela_inicial->frame_atual = (tela_inicial->frame_atual + 1) % FRAMES_TELA_INICIAL;
        *animation_counter = 0; // Reseta o contador de animação
    }
}
