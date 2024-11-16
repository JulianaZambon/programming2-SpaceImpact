#ifndef __INIMIGOS__ // Guardas de inclusão
#define __INIMIGOS__ // Guardas de inclusão

#include <allegro5/allegro.h> // Inclusão necessária para usar ALLEGRO_BITMAP

typedef struct
{
    float x;                // Posição X do inimigo
    float y;                // Posição Y do inimigo
    float speed;            // Velocidade do movimento
    int hp;                 // Pontos de vida
    int type;               // Tipo de inimigo (diferencia os 4 inimigos)
    ALLEGRO_BITMAP *sprite; // Sprite do inimigo
} enemy;

// Função para criar o inimigo
enemy *create_enemy(float x, float y, float speed, int health, int type, const char *sprite_path);
// Função para desenhar o inimigo
void draw_enemy(const enemy *enemies);
// Função para mover o inimigo
void move_enemy(enemy *enemies, unsigned char steps, unsigned char trajectory, unsigned short max_x, unsigned short max_y);
// Função para destruir o inimigo
void destroy_enemy(enemy *enemies);

#endif // Guardas de inclusão
