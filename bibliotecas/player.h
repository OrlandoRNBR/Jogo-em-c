#ifndef PLAYER_H
#define PLAYER_H


#include <stdio.h>
#include <allegro5/allegro5.h> 
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <stdbool.h>
#include "auxiliar.h"



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
    bool t1;
    bool t2;
    bool t3;
    bool t0;
}teclas;

bool colisao(int x, int y, int array_map[32][32], int tamanho);

void printar_player(ALLEGRO_BITMAP* image, teclas* tecla, player p, int si);

void receber_teclas (ALLEGRO_EVENT *evento_primario, int *ultima_tecla_precionada, teclas* tecla, int* i_mapa);

void processar_teclas (teclas *tecla, player* p, int array_map[32][32]);

void animacao_player(int * si, teclas* tecla);

void printar_tela(teclas* tecla, player* p, tela* t, int* si,ALLEGRO_BITMAP* image, int array_map[32][32]);

#endif