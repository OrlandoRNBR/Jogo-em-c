#include <stdio.h>
#include <allegro5/allegro5.h> 
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <stdbool.h>
#include "player.h"


void printar_player(ALLEGRO_BITMAP* image, int tecla, player p, int si){
    switch (tecla){ //seleciona as teclas pecionadas
    case ALLEGRO_KEY_D: //preinta o player com animação indo para a direita
        al_draw_bitmap_region(image, p.tamanho*si, p.tamanho*3, p.tamanho, p.tamanho, p.eixox, p.eixoy, 0);
        break;
    case ALLEGRO_KEY_A: // printa o player com animação indo para a esquerda
        al_draw_bitmap_region(image, p.tamanho*si, p.tamanho, p.tamanho, p.tamanho, p.eixox, p.eixoy, 0);
        break;
    case ALLEGRO_KEY_S: //printa o player com animação indo para baixo
        al_draw_bitmap_region(image, p.tamanho*si, p.tamanho*0, p.tamanho, p.tamanho, p.eixox, p.eixoy, 0);
        break;
    case ALLEGRO_KEY_W: //printa o player com animação de ir para cima
        al_draw_bitmap_region(image, p.tamanho*si, p.tamanho*2, p.tamanho, p.tamanho, p.eixox, p.eixoy, 0);
        break;
    default: //printa o player para baixo/de frente
        al_draw_bitmap_region(image, p.tamanho*si, p.tamanho*0, p.tamanho, p.tamanho, p.eixox, p.eixoy, 0);
        break;
    }
}



void receber_teclas (ALLEGRO_EVENT *evento_primario, int *ultima_tecla_precionada, teclas* tecla){ //rebe as teclas do usuario e mostra se esta ou não sendo precionada
     if(evento_primario->type == ALLEGRO_EVENT_KEY_DOWN){ // se alguma tecla for precionada marca como verdadeiro
        switch(evento_primario->keyboard.keycode){
            case ALLEGRO_KEY_W: tecla->w = true; break;
            case ALLEGRO_KEY_D: tecla->d = true; break;
            case ALLEGRO_KEY_S: tecla->s = true; break;
            case ALLEGRO_KEY_A: tecla->a = true; break;
        }
        *ultima_tecla_precionada = evento_primario->keyboard.keycode; //armazena a ultima tecla precionada
      }
      if(evento_primario->type == ALLEGRO_EVENT_KEY_UP){ //se a alguma tecla for solta marca como falso
        switch(evento_primario->keyboard.keycode){ 
            case ALLEGRO_KEY_W: tecla->w = false; break;
            case ALLEGRO_KEY_D: tecla->d = false; break;
            case ALLEGRO_KEY_S: tecla->s = false; break;
            case ALLEGRO_KEY_A: tecla->a = false; break;
      }
    }
}

void processar_teclas (teclas *tecla, player* p, tela* t){ //enquanto as teclas são verdadeiras ele soma o speed do personagem
    if(tecla->w && p->eixoy >= 0) p->eixoy -= p->speed;
    if(tecla->s && p->eixoy <= t->altura - p->tamanho) p->eixoy += p->speed;
    if(tecla->d && p->eixox <= t->largura - p->tamanho) p->eixox += p->speed;
    if(tecla->a && p->eixox >= 0) p->eixox -= p->speed;
}

void animacao_player(int * si, teclas* tecla){ // manipula a variavel si para navegar pelo sprite do personagem
        if(tecla->w || tecla->a || tecla->d || tecla->s){
                *si = (*si+1)%5;
            } else{
                *si = 0;
            }
}


void printar_tela(teclas* tecla, player * p, tela* t, int *si, ALLEGRO_BITMAP* image,int ultima_tecla_precionada){
    //faz toda a parte visual do jogo
     processar_teclas(&*tecla, &*p, &*t); //desloca o player na tela
     animacao_player(&*si, &*tecla); //faz animação do player
     //al_clear_to_color(al_map_rgb(10, 218, 250)); // pinta o fundo na cor do codigo RGB
     printar_player(image, ultima_tecla_precionada, *p, *si); // printa o player
     al_flip_display(); //pega tudo e mostra na tela
}