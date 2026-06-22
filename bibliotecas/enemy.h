#ifndef ENEMY_H
#define ENEMY_H

#include "player.h"
#include "auxiliar.h"
#include "estructuras.h"

bool colisao_enemy(int x, int y, int array_map[32][32], int tamanho);

void enemy_action(player* p, enemy* i, int n, int array_map[32][32], tiro* tiro, int* pontuacao, int VELOCIDADE_INIMIGO);

void animacao_inimigo(player* p, enemy* i, int n);

void printar_inimigo(player* p, enemy* i, int n, int array_map[32][32], ALLEGRO_BITMAP* inimigo, tiro* tiro,int* pontuacao, int vel_inimigo);

#endif