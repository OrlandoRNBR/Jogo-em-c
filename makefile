CC = gcc

CFLAGS = -Wall -Wextra -std=gnu17 -I./bibliotecas 

LDLIBS = -lallegro -lallegro_font -lallegro_ttf -lallegro_image -lallegro_primitives -lallegro_acodec -lallegro_audio -lm -lcjson -lcurl

SRCS = main.c bibliotecas/player.c bibliotecas/auxiliar.c bibliotecas/maps.c bibliotecas/enemy.c
OBJS = $(SRCS:.c=.o)

all: $(OBJS)
	$(CC) -o main.out $(OBJS) $(LDLIBS)

clean:
	rm -f $(OBJS) main.out
