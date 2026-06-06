#ifndef PLAYER_H
#define PLAYER_H

#include "auxiliar.h"
#include "maps.h"
#include "estructuras.h"



void printar_menu(ALLEGRO_BITMAP* ui, ALLEGRO_FONT* font, ALLEGRO_BITMAP* image, player p);

bool colisao(int x, int y, int array_map[32][32], int tamanho); //define a colisão do jogo

void printar_player(ALLEGRO_BITMAP* image, teclas* tecla, player p, int si); //mostra o player na tela

void receber_teclas (ALLEGRO_EVENT *evento_primario, int *ultima_tecla_precionada, teclas* tecla, int* i_mapa); //registra as teclas precionadasa

void processar_teclas (teclas *tecla, player* p, int array_map[32][32]); //processa o registro da função a cima

void animacao_player(int * si, teclas* tecla); //faz a navegação pelo spritesheet do player

void printar_tela(teclas* tecla, player* p, int* si,ALLEGRO_BITMAP* image, int array_map[32][32], tiro tiro, ALLEGRO_BITMAP* image_tiro); //usa as fubções a cima para compor a tela do jogo

#endif