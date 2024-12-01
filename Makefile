# Projeto "Space Impact 303" desenvolvido por Juliana Zambon
# GRR20224168

CC = gcc
EXEC = SpaceImpact
MAIN = main.c 
ALLEGRO = $(pkg-config allegro-5 allegro_main-5 allegro_font-5 allegro_image-5 allegro_primitives-5 --libs --cflags)
INCLUDE = jogador.c inimigos.c joystick.c arma.c projetil.c -lm
CFLAG = Wall
OBJS = 

all: hello

hello: $(OBJS)
	$(CC) -o $(EXEC) $(MAIN) $(INCLUDE) $(ALLEGRO)

main.o:


clean:
	-rm -f *~ *.o

purge:
	-rm -f $(OBJS) $(EXEC)