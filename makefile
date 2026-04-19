CC = gcc
CFLAGS = -Wall -Wextra
-lallegro_ttf -lallegro_image -lallegro_primitives -lallegro_acodec -lallegro_audioLDLIBS = -lallegro -lallegro_font 

SRCS = main.c

OBJS = $(SRCS:.c=.o)

all: $(OBJS)
	$(CC) -o main.exe $(CFLAGS) $(OBJS) $(LDLIBS)
