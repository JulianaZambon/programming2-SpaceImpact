#ifndef __JOGADOR__ // Guardas de inclusão
#define __JOGADOR__ // Guardas de inclusão

#include <allegro5/allegro.h> // Inclusão necessária para usar ALLEGRO_BITMAP

// Inclusões de bibliotecas locais
#include "joystick.h"
#include "arma.h"

/*-------------------------------------------------------------------*/
/* DEFINIÇÕES */

/* JOGADOR */
#define PATH_JOGADOR "assets/jogador/sprite_jogador.png" // Caminho para o sprite do jogador
#define NUM_FRAMES_JOGADOR 72                            // Total de quadros do sprite do jogador
#define QUADRADO_SPRITE_JOGADOR 189                      // Tamanho do quadro do sprite do jogador
#define ANIMATION_DELAY_JOGADOR 3                        // Velocidade da animação do sprite do jogador (quanto maior, mais lento)
#define JOGADOR_STEP 20                                  // Quantidade de pixels que um jogador se move por passo
#define JOGADOR_HP 5                                     // Quantidade de vida inicial do jogador

/* HP */
#define PATH_HP "assets/jogador/hp3.png" // Caminho para o sprite do coração de HP
#define SPRITE_HP 40                     // Tamanho do quadro do sprite do coração de HP
#define NUM_FRAMES_HP 10                 // Total de quadros do sprite do coração de HP
#define ANIMATION_DELAY_HP 8             // Velocidade da animação do coração de HP (quanto maior, mais lento)

/* ATAQUE ESPECIAL */
#define PATH_SIMBOLO_ATAQUE_ESPECIAL "assets/ataqueEspecial/ataque.png" // Caminho para o sprite do simbolo do ataque especial
#define ANIMATION_DELAY_SIMBOLO_ATAQUE_ESPECIAL 3                       // Velocidade da animação do símbolo do ataque especial (quanto maior, mais lento)
#define QUADRADO_SPRITE_SIMBOLO_ATAQUE_ESPECIAL 70                      // Tamanho do quadro do sprite do símbolo do ataque especial
#define COL_FRAMES_SIMBOLO_ATAQUE_ESPECIAL 6                            // Número de colunas do sprite do símbolo do ataque especial
#define NUM_FRAMES_SIMBOLO_ATAQUE_ESPECIAL 12                           // Número total de quadros do sprite do símbolo do ataque especial
#define TEMP_MAX 5000                                                   // Tempo máximo do ataque especial 5 segundos

/*-------------------------------------------------------------------*/
/* ESTRUTURAS */

/*
RESUMO DAS ESTRUTURAS
simbolo_ataque_especial: Representa o power-up no mapa.
ataque_especial: Controla o estado do ataque especial no jogador.
jogador: Contém um ponteiro para ataque_especial para gerenciar o estado do ataque.
*/

// Estrutura para o símbolo do ataque especial (apenas o "power-up")
typedef struct
{
    unsigned short x;               // Posição X do centro do símbolo
    unsigned short y;               // Posição Y do centro do símbolo
    int largura;                    // Largura do quadro do sprite
    int altura;                     // Altura do quadro do sprite
    int col_frames;                 // Número de colunas
    int num_frames;                 // Número total de quadros do sprite sheet
    unsigned short frame_atual;     // Quadro atual no sprite sheet
    unsigned int animation_counter; // Contador para gerenciar a animação
    ALLEGRO_BITMAP *sprite;         // Imagem do símbolo
} simbolo_ataque_especial;

// Estrutura para o ataque especial ativo (somente estado)
typedef struct
{
    bool ativo;                       // Indica se o ataque especial está ativo
    clock_t tempo_inicio;             // Tempo de início do efeito especial
    int duracao;                      // Duração do efeito especial (em milissegundos)
    unsigned int tempo_restante;      // Tempo restante do efeito especial (em milissegundos)
    simbolo_ataque_especial *simbolo; // Referência ao símbolo antes de ser coletado
    ALLEGRO_BITMAP *sprite;           // Sprite para representar o efeito do ataque especial
} ataque_especial;

// Estrutura para o jogador
typedef struct
{
    unsigned char tam_lateral;      // Tamanho da lateral de um jogador
    unsigned char face;             // A face principal, algo como a sua "frente"
    unsigned char hp;               // Quantidade de vida do jogador, em unidades
    unsigned short x;               // Posição X do centro do jogador
    unsigned short y;               // Posição Y do centro do jogador
    unsigned short frame_atual;     // Quadro atual (índice no sprite sheet)
    unsigned int animation_counter; // Contador de animação do sprite do jogador
    ALLEGRO_BITMAP *sprite;         // Ponteiro para o sprite do jogador
    ALLEGRO_BITMAP *hp_sprite;      // Sprite do coração para representar o HP
    joystick *controle;             // Para movimentar a nave
    arma *arma;                     // Para atirar
    ataque_especial *especial;      // Controle do estado do ataque especial
    // arma exclusiva do ataque especial
    arma *arma_especial; // Para atirar com o ataque especial
} jogador;

/*-------------------------------------------------------------------*/
/* PROTÓTIPOS DE FUNÇÕES */

// Função de criação de um jogador
jogador *criar_jogador(unsigned char side, unsigned char face, short x,
                       unsigned short y, unsigned short max_x, unsigned short max_y);

// Função de movimentação do jogador
void mover_jogador(jogador *elemento, char steps, unsigned char trajetoria,
                   unsigned short max_x, unsigned short max_y);

// Função de desenho do jogador
void desenhar_jogador(jogador *elemento);

// Função para desenhar os corações de HP na tela
void desenhar_hp(jogador *elemento, int x, int y);

// Função de atualização da animação do jogador
void atualizar_animacao_jogador(jogador *elemento, unsigned int *animation_counter,
                                unsigned int delay);

// Função de disparo do jogador
void jogador_atira(jogador *elemento);

// Função de destruição do jogador
void destroi_jogador(jogador *elemento);

/*-------------------------------------------------------------------*/
/* PROTÓTIPO DE FUNÇÕES PARA CONTROLE DO ATAQUE ESPECIAL */

// Função de criação do símbolo do ataque especial
// Cria e inicializa o símbolo que representa o ataque especial no mapa
simbolo_ataque_especial *criar_simbolo_ataque_especial(unsigned short x, unsigned short y, const char *sprite_path);

ataque_especial *criar_ataque_especial();

// Função de desenho do símbolo do ataque especial
// Renderiza o sprite do símbolo na tela
void desenhar_simbolo_ataque_especial(simbolo_ataque_especial *simbolo);

// Função de atualização da animação do símbolo do ataque especial
// Atualiza o quadro atual do sprite, respeitando o delay entre frames
void atualizar_animacao_simbolo_ataque_especial(simbolo_ataque_especial *simbolo, unsigned int delay);

// Função de destruição do símbolo do ataque especial
// Libera recursos alocados pelo símbolo
void destruir_simbolo_ataque_especial(simbolo_ataque_especial *simbolo);

// Função de verificação de colisão do jogador com o símbolo do ataque especial
// Verifica se o jogador colidiu com o símbolo do ataque especial
bool verificar_colisao_jogador_simbolo(jogador *jogador, simbolo_ataque_especial *simbolo);

// Função de ativação do ataque especial
// Ativa o ataque especial no jogador por 5 segundos ao coletar o símbolo
void ativar_ataque_especial(jogador *jogador);

// Atualizar o tempo restante do ataque especial
void atualizar_ataque_especial(jogador *jogador, simbolo_ataque_especial **simbolo_ptr);

#endif // Guardas de inclusão
