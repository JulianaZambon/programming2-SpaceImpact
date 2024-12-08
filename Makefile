# Projeto desenvolvido por Juliana Zambon
# GRR 20224168  DINF - UFPR

# Definindo o compilador e o nome do executável
CC = gcc
EXEC = SpaceImpact

# Arquivos fontes principais
MAIN = main.c
INCLUDE = telaInicial.c jogador.c inimigos.c chefes.c joystick.c arma.c projetil.c background.c fases.c configuracoes.c narrativa.c

# Flags de compilação
CFLAGS = -lm $(shell pkg-config --cflags allegro-5 allegro_font-5 allegro_ttf-5 allegro_primitives-5 allegro_audio-5 allegro_acodec-5 allegro_image-5)

# Definindo os arquivos objeto
OBJS = telaInicial.o jogador.o inimigos.o chefes.o joystick.o arma.o projetil.o background.o fases.o configuracoes.o narrativa.o $(MAIN:.c=.o)

# Regra principal para compilar o executável
all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) -o $(EXEC) $(OBJS) $(CFLAGS) $(shell pkg-config --libs allegro-5 allegro_font-5 allegro_ttf-5 allegro_primitives-5 allegro_audio-5 allegro_acodec-5 allegro_image-5)

# Regras para compilar os arquivos objeto
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para limpar arquivos temporários
clean:
	-rm -f *~ *.o

# Regra para limpar todos os arquivos gerados, incluindo o executável
purge: clean
	-rm -f $(EXEC)
