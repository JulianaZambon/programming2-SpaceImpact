#ifndef __CHEFES__ // Guardas de inclusão
#define __CHEFES__ // Guardas de inclusão

typedef struct
{
    float x;                // Posição X do chefe
    float y;                // Posição Y do chefe
    float speed;            // Velocidade do movimento
    int hp;                 // Pontos de vida (mais altos que os inimigos comuns)
    int damage;             // Dano causado pelo chefe
    ALLEGRO_BITMAP *sprite; // Sprite do chefe
    int phase;              // Indica a fase do chefe (ex: fase 1 ou 2)
} boss;

// Função para criar o chefe
void create_boss(boss *b, float x, float y, float speed, int hp, int damage, const char *sprite_path);
// Função para desenhar o chefe
void draw_boss(const boss *b);
// Função para mover o chefe
void move_boss(boss *b);
// Função para destruir o chefe
void destroy_boss(boss *b);

#endif // Guardas de inclusão
