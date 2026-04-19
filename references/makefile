CC = gcc
CFLAGS = -Wall -Wextra
LDLIBS = -lallegro -lallegro_font -lallegro_ttf -lallegro_image -lallegro_primitives -lallegro_acodec -lallegro_audio

SRCS = allegro05.c

OBJS = $(SRCS:.c=.o)

all: $(OBJS)
	$(CC) -o main.exe $(CFLAGS) $(OBJS) $(LDLIBS)
