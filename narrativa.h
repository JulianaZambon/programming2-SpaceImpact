#ifndef __NARRATIVA__ // Guardas de inclusão
#define __NARRATIVA__ // Guardas de inclusão

#include <allegro5/allegro.h>

/*-------------------------------------------------------------------*/
/* DEFINIÇÕES */

#define PATH_VELOCIDADE_LUZ "assets/extras/velocidadeLuz.png"
#define FRAMES_VELOCIDADE_LUZ 14

#define PATH_NAVE_LIGANDO "assets/extras/nave.png"
#define FRAMES_NAVE_LIGANDO 95

/*-------------------------------------------------------------------*/
/* ESTRUTURAS */
typedef struct
{
    int largura;                    // Largura do quadro do sprite (1140px)
    int altura;                     // Altura do quadro do sprite (640px)
    int num_frames;                 // Número total de colunas de quadros no sprite
    unsigned int frame_atual;       // Quadro atual (índice no sprite)
    unsigned int animation_counter; // Contador de animação
    ALLEGRO_BITMAP *sprite;         // Imagem do sprite
} tela_nave_ligando;

typedef struct
{
    int largura;                    // Largura do quadro do sprite (1140px)
    int altura;                     // Altura do quadro do sprite (640px)
    int num_frames;                 // Número total de colunas de quadros no sprite
    unsigned int frame_atual;       // Quadro atual (índice no sprite)
    unsigned int animation_counter; // Contador de animação
    ALLEGRO_BITMAP *sprite;         // Imagem do sprite
} tela_velocidade_luz;

/*-------------------------------------------------------------------*/
/* PROTÓTIPOS DE FUNÇÕES */

tela_nave_ligando *criar_tela_nave_ligando();
void desenhar_tela_nave_ligando(tela_nave_ligando *tela_nave_ligando);
void atualizar_animacao_tela_nave_ligando(tela_nave_ligando *tela_nave_ligando,
                                          unsigned int *animation_counter, unsigned int delay);

tela_velocidade_luz *criar_tela_velocidade_luz();
void desenhar_tela_velocidade_luz(tela_velocidade_luz *tela_velocidade_luz);
void atualizar_animacao_tela_velocidade_luz(tela_velocidade_luz *tela_velocidade_luz,
                                            unsigned int *animation_counter, unsigned int delay);

#endif // Guardas de inclusão