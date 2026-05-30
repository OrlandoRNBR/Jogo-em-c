#ifndef AUXILIAR_H
#define AUXILIAR_H
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h> 
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <stdbool.h>
#include <math.h>
#include "player.h"

typedef const char* string;

typedef struct masps{ //define algumas variaveis de criação de mapa
    int eixox;
    int eixoy;
    int largura;
    int altura;
}map;

void printar_chao(ALLEGRO_BITMAP* mapa,map chao); //preenche o fundo com chão

void criar_mapa(int* i_mapa,int* i_mapa_anterior, int array_map[32][32],ALLEGRO_BITMAP* parede[], ALLEGRO_BITMAP* mapa, map chao);

void al_init_all();

void al_destroy_all(ALLEGRO_DISPLAY* disp, ALLEGRO_TIMER* timer, ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_FONT* font, ALLEGRO_BITMAP* image, ALLEGRO_BITMAP* mapa, ALLEGRO_BITMAP* parede[], ALLEGRO_BITMAP* ui, ALLEGRO_BITMAP* skin[],int skin_tamanho, ALLEGRO_BITMAP* skin_tiro[]);

void al_register_all_event_source(ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_TIMER* timer, ALLEGRO_DISPLAY* disp);


#endif