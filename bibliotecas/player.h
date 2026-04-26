#include <stdio.h>
#include <allegro5/allegro5.h> 
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <stdbool.h>



typedef struct tela{
    int largura;
    int altura;
}tela;


//player.h possivel biblioteca feita só com funções de controle do player
typedef struct player{//typedef para definir o player dps vai ter um de inimigos
    //posição e deslocamento do player
    int eixox; 
    int eixoy;
    int speed;
    //hp do player
    int hp;
    //tamanho
    int tamanho;
}player;

void printar_player(ALLEGRO_BITMAP* image, int teclas);

void receber_teclas (int teclas);