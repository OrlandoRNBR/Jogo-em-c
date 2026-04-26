#include <stdio.h>
#include <allegro5/allegro5.h> 
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <stdbool.h>
#include "player.h"

player p = {30, 20, 1, 3, 32}; //declaração do player posição eixo x, posição eixo y, vidas
int movendo = 0; //0 parado, 1 pra cima, 2 pra direita, 3 pra baixo, 4 pra esquerda 
int ultima_tecla_precionada = 0;
extern tela t = {1024, 512};

void printar_player(ALLEGRO_BITMAP* image, int teclas){
    
    switch (teclas){
    case ALLEGRO_KEY_D:
        al_draw_bitmap_region(image, p.tamanho*si, p.tamanho*3, p.tamanho, p.tamanho, p.eixox, p.eixoy, 0);
        break;
    case ALLEGRO_KEY_A:
        al_draw_bitmap_region(image, p.tamanho*si, p.tamanho, p.tamanho, p.tamanho, p.eixox, p.eixoy, 0);
        break;
    case ALLEGRO_KEY_S:
        al_draw_bitmap_region(image, p.tamanho*si, p.tamanho*0, p.tamanho, p.tamanho, p.eixox, p.eixoy, 0);
        break;
    case ALLEGRO_KEY_W:
        al_draw_bitmap_region(image, p.tamanho*si, p.tamanho*2, p.tamanho, p.tamanho, p.eixox, p.eixoy, 0);
        break;
    default:
    al_draw_bitmap_region(image, p.tamanho, p.tamanho*0, p.tamanho, p.tamanho, p.eixox, p.eixoy, 0);
        break;
    }

}


void receber_teclas (int teclas){
    switch (teclas)
    {
    case ALLEGRO_KEY_D:
        ultima_tecla_precionada = ALLEGRO_KEY_D;
        if(p.eixox <= t.largura - p.tamanho){
            p.eixox += p.speed;
            movendo = 2;
        }
        break;
    case ALLEGRO_KEY_A:
        ultima_tecla_precionada = ALLEGRO_KEY_A;
        if(p.eixox >= 0){
            p.eixox -= p.speed;
            movendo = 4;
        }
        break;
    case ALLEGRO_KEY_S:
        ultima_tecla_precionada = ALLEGRO_KEY_S;
        if(p.eixoy <= t.altura - p.tamanho){
            p.eixoy += p.speed;
            movendo = 3;
        }
        break;
    case ALLEGRO_KEY_W:
        ultima_tecla_precionada = ALLEGRO_KEY_W;
        if(p.eixoy >= 0){
            p.eixoy -= p.speed;
            movendo = 1;
        }
        break;
    default:
        break;
    }
}