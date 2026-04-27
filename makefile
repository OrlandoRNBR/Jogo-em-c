CC = gcc

# O -I./bibliotecas diz ao GCC onde procurar pelos seus arquivos .h
CFLAGS = -Wall -Wextra -I./bibliotecas

LDLIBS = -lallegro -lallegro_font -lallegro_ttf -lallegro_image -lallegro_primitives -lallegro_acodec -lallegro_audio

# Aqui ficam TODOS os seus arquivos .c
SRCS = main.c bibliotecas/player.c

OBJS = $(SRCS:.c=.o)

all: $(OBJS)
	$(CC) -o main.exe $(CFLAGS) $(OBJS) $(LDLIBS)

# Regra bônus para limpar o projeto antes de zipar para o professor!
clean:
	rm -f $(OBJS) main.exe