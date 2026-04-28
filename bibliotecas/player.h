#ifndef PLAYER_H
#define PLAYER_H


#include <stdio.h>
#include <allegro5/allegro5.h> 
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <stdbool.h>



typedef struct tela{
    int largura; //largura da tela
    int altura; //altura da tela
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

typedef struct teclas{ //struct que armazena se as teclas estão sendo precionadas ou não
    bool w;
    bool d;
    bool s;
    bool a;
}teclas;



void printar_player(ALLEGRO_BITMAP* image, int tecla, player p, int si);

void receber_teclas (ALLEGRO_EVENT *evento_primario, int *ultima_tecla_precionada, teclas* tecla);

void processar_teclas (teclas *tecla, player* p, tela* t);

void animacao_player(int * si, teclas* tecla);

void printar_tela(teclas* tecla, player * p, tela* t, int *si, ALLEGRO_BITMAP* image,int ultima_tecla_precionada);

#endif