CC = gcc

CFLAGS = -Wall -Wextra -std=gnu17 -I./bibliotecas 

LDLIBS = -lallegro -lallegro_font -lallegro_ttf -lallegro_image -lallegro_primitives -lallegro_acodec -lallegro_audio -lm

SRCS = main.c bibliotecas/player.c bibliotecas/auxiliar.c bibliotecas/maps.c
OBJS = $(SRCS:.c=.o)

all: $(OBJS)
	$(CC) -o main.out $(OBJS) $(LDLIBS)

clean:
	rm -f $(OBJS) main.out
