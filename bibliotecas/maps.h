#ifndef MAPS_H
#define MAPS_H

#include "player.h"
#include "auxiliar.h"

typedef struct maps{ //define algumas variaveis de criação de mapa
    int eixox;
    int eixoy;
    int largura;
    int altura;
}map;

typedef struct Treenode{
    map m;
}Treenode;


void printar_chao(ALLEGRO_BITMAP* mapa,map chao); //preenche o fundo com chão

void criar_mapa(int* i_mapa,int* i_mapa_anterior, int array_map[32][32],ALLEGRO_BITMAP* parede[], ALLEGRO_BITMAP* mapa, map chao);



#endif