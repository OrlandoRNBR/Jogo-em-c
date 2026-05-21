CC = gcc

# COMPILAÇÃO AJUSTADA COM AS DUAS CORREÇÕES
CFLAGS = -Wall -Wextra -std=gnu11 -mcmodel=medium -I./bibliotecas -D__USE_MINGW_ANSI_STDIO=1

# Bibliotecas do Allegro
LDLIBS = -lallegro -lallegro_font -lallegro_ttf -lallegro_image -lallegro_primitives -lallegro_acodec -lallegro_audio

# Fontes e Objetos
SRCS = main.c bibliotecas/player.c bibliotecas/auxiliar.c
OBJS = $(SRCS:.c=.o)

# Alvo principal
all: main.exe

# Regra para linkar o executável final
main.exe: $(OBJS)
	$(CC) -o main.exe $(OBJS) $(LDLIBS)

# Regra genérica para compilar os arquivos .c em .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para limpar os arquivos gerados
clean:
	del /q /f main.exe bibliotecas\*.o *.o 2>nul || exit 0