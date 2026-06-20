#ifndef PLAYER_H
#define PLAYER_H

#include "auxiliar.h"
#include "maps.h"
#include "estructuras.h"



void printar_menu(ALLEGRO_BITMAP* ui, ALLEGRO_FONT* font, ALLEGRO_BITMAP* image, player p);

bool colisao(int x, int y, int array_map[32][32], int tamanho); //define a colisão do jogo

void printar_player(ALLEGRO_BITMAP* image, teclas* tecla, player p, int si); //mostra o player na tela

void receber_teclas (ALLEGRO_EVENT *evento_primario, int *ultima_tecla_precionada, teclas* tecla); //registra as teclas precionadasa

void processar_teclas (teclas *tecla, player* p, int array_map[32][32]); //processa o registro da função a cima

bool colisao_tiro(int x, int y ,int array_map[32][32]);

void animacao_player(int * si, teclas* tecla); //faz a navegação pelo spritesheet do player

#endif