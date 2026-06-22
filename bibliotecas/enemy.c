#include "auxiliar.h"
#include "enemy.h"




bool colisao_enemy(int x, int y, int array_map[32][32], int tamanho) {
    int margem_cima = 4;
    int margem_baixo = 4;
    
    int esquerda = (x + margem_cima) / 16;
    int direita  = (x + tamanho - margem_baixo - 1) / 16;
    int topo     = (y + margem_cima) / 16;
    int baixo    = (y + tamanho - margem_baixo - 1) / 16;

    if (topo < 0 || baixo >= 32 || esquerda < 0 || direita >= 32) return true;

    if (array_map[topo][esquerda] != 0) return true;
    if (array_map[topo][direita]  != 0) return true;
    if (array_map[baixo][esquerda] != 0) return true;
    if (array_map[baixo][direita]  != 0) return true;

    return false;
}

void enemy_action(player* p, enemy* i, int n, int array_map[32][32], tiro* tiro, int* pontuacao, int VELOCIDADE_INIMIGO) {
    if (i[n].alive) { 

        if (tiro->ativo) { // Só checa se o tiro realmente existir na tela
            int tamanho_tiro = 8; // Conforme o +8 que você usou no seu if
            
            if (tiro->x < i[n].x + i[n].tamanho &&  // Esquerda do tiro < Direita do inimigo
                tiro->x + tamanho_tiro > i[n].x &&  // Direita do tiro > Esquerda do inimigo
                tiro->y < i[n].y + i[n].tamanho &&  // Topo do tiro < Base do inimigo
                tiro->y + tamanho_tiro > i[n].y)    // Base do tiro > Topo do inimigo
            {
                i[n].alive = false; // O inimigo morre!
                tiro->ativo = false;   // O tiro some ao impactar (para não atravessar e matar outros)
                *pontuacao += 1;
                printf("Inimigo abatido pelo tiro!\n");
            }
        }


        // Correção das condições: adicionado o ! antes de colisao_enemy
        if (p->eixox < i[n].x) {
            if (!colisao_enemy(i[n].x - VELOCIDADE_INIMIGO, i[n].y, array_map, i[n].tamanho)) {
                i[n].x -= VELOCIDADE_INIMIGO; 
            }
        } else if (p->eixox > i[n].x) {
            if (!colisao_enemy(i[n].x + VELOCIDADE_INIMIGO, i[n].y, array_map, i[n].tamanho)) {
                i[n].x += VELOCIDADE_INIMIGO;
            }
        }

        if (p->eixoy < i[n].y) {
            if (!colisao_enemy(i[n].x, i[n].y - VELOCIDADE_INIMIGO, array_map, i[n].tamanho)) {
                i[n].y -= VELOCIDADE_INIMIGO; 
            }
        } else if (p->eixoy > i[n].y) {
            if (!colisao_enemy(i[n].x, i[n].y + VELOCIDADE_INIMIGO, array_map, i[n].tamanho)) {
                i[n].y += VELOCIDADE_INIMIGO;
            }
        }

        if (abs(p->eixox - i[n].x) < 16 && abs(p->eixoy - i[n].y) < 16) {
            p->hp--;
            i[n].alive = false; 
        }
    }
}

void animacao_inimigo(player* p, enemy* i, int n) { 
    if (i[n].x != p->eixox || i[n].y != p->eixoy) {
        i[n].frame_atual = (i[n].frame_atual + 1) % 4; // Geralmente sheets têm 4 frames
    } else {
        i[n].frame_atual = 0;
    }
}

void printar_inimigo(player* p, enemy* i, int n, int array_map[32][32], ALLEGRO_BITMAP* inimigo, tiro* tiro,int* pontuacao, int vel_inimigo) {
    for (int j = 0; j < n; j++) {
        if (i[j].alive) {
            if (abs(p->eixox - i[j].x) > abs(p->eixoy - i[j].y)) {
                if (i[j].x > p->eixox)      i[j].direcao_y = 1; // Esquerda
                else                        i[j].direcao_y = 3; // Direita
            } else {
                if (i[j].y < p->eixoy)      i[j].direcao_y = 0; // Baixo (Frente)
                else                        i[j].direcao_y = 2; // Cima (Costas)
            }

            animacao_inimigo(p, i, j);
            enemy_action(p, i, j, array_map, tiro, pontuacao, vel_inimigo);

            if (inimigo != NULL) {
                al_draw_bitmap_region(inimigo, 
                                      i[j].tamanho * i[j].frame_atual, 
                                      i[j].tamanho * i[j].direcao_y, 
                                      i[j].tamanho, i[j].tamanho, 
                                      i[j].x, i[j].y, 0);
            }
        }
    }
}