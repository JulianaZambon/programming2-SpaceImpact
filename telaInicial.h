#ifndef __TELAINICIAL__ // Guardas de inclusão
#define __TELAINICIAL__ // Guardas de inclusão

#include <allegro5/allegro.h> // Inclusão necessária para usar ALLEGRO_BITMAP

/*-----------------------------------------------------------------------------------------*/
/* DEFINIÇÕES */

#define PATH_TELA_INICIAL "assets/abertura/abertura.png"
#define FRAMES 48

/*-----------------------------------------------------------------------------------------*/
/* ESTRUTURAS */

typedef struct
{
    int largura;              // Largura do quadro do sprite (1140px)
    int altura;               // Altura do quadro do sprite (640px)
    int num_frames;           // Número total de colunas de quadros no sprite (12 colunas, 48 frames)
    unsigned int frame_atual; // Quadro atual (índice no sprite)
    ALLEGRO_BITMAP *sprite;   // Imagem do sprite
} tela_inicial_sprite;



/*-----------------------------------------------------------------------------------------*/
/* PROTÓTIPO DE FUNÇÕES */

// Função de criação da tela inicial
tela_inicial_sprite *criar_tela_inicial();
// Desenhar a tela inicial
void desenhar_tela_inicial(tela_inicial_sprite *tela_inicial);
// Atualiza a animação da tela inicial
void atualizar_animacao_tela_inicial(tela_inicial_sprite *tela_inicial, unsigned int *animation_counter, unsigned int delay);

#endif // Guardas de inclusão