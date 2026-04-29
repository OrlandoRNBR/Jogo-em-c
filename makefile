CC = gcc

CFLAGS = -Wall -Wextra -std=gnu17 -I./bibliotecas 

LDLIBS = -lallegro -lallegro_font -lallegro_ttf -lallegro_image -lallegro_primitives -lallegro_acodec -lallegro_audio

SRCS = main.c bibliotecas/player.c bibliotecas/auxiliar.c
OBJS = $(SRCS:.c=.o)

all: $(OBJS)
	$(CC) -o main.exe $(OBJS) $(LDLIBS)

clean:
	rm -f $(OBJS) main.exe
