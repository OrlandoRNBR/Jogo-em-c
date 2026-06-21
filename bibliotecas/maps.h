#ifndef MAPS_H
#define MAPS_H

#include "player.h"
#include "auxiliar.h"
#include "estructuras.h"

void printar_chao(ALLEGRO_BITMAP* mapa,Chao chao); //preenche o fundo com chão

Node* criar_mapa(int array_map[32][32],ALLEGRO_BITMAP* parede[], ALLEGRO_BITMAP* mapa, Chao chao, Node* node, player* p, bool* mudou, bool playing);//cria o mapa
//renderisa a tela do jogo
void printar_tela(teclas* tecla, player* p, int *si, ALLEGRO_BITMAP* image, int array_map[32][32], tiro tiro, ALLEGRO_BITMAP* image_tiro, enemy* inimigos, ALLEGRO_BITMAP* inimigos_sprite);

#endif