#include <stdio.h>
#include <allegro5/allegro5.h> 
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <stdbool.h>
#include "player.h"
#include "auxiliar.h"


bool colisao(int x, int y ,int array_map[32][32], int tamanho ){
    
    int margem_cima = 8;
    int margem_baixo = 4;
    
    int esquerda = (x + margem_cima) / 16;
    int direita  = (x + tamanho - margem_baixo - 1) / 16;
    int topo     = (y + margem_cima) / 16;
    int baixo    = (y + tamanho - margem_baixo - 1) / 16;

    // verifica os 4 cantos
    if(array_map[topo][esquerda] != 0) return true;
    if(array_map[topo][direita]  != 0) return true;
    if(array_map[baixo][esquerda] != 0) return true;
    if(array_map[baixo][direita]  != 0) return true;

    return false;
}

void printar_player(ALLEGRO_BITMAP* image, teclas* tecla, player p, int si){
    int direcao_y; // linha do spritesheet

    // prioridade: define qual direção mostrar quando várias teclas estão ativas
    if(tecla->s)      direcao_y = 0; // baixo  (frente)
    else if(tecla->a) direcao_y = 1; // esquerda
    else if(tecla->w) direcao_y = 2; // cima
    else if(tecla->d) direcao_y = 3; // direita
    else              direcao_y = 0; // parado → fica de frente

    al_draw_bitmap_region(image,p.tamanho * si,p.tamanho * direcao_y, p.tamanho, p.tamanho, p.eixox, p.eixoy, 0);
}



void receber_teclas (ALLEGRO_EVENT *evento_primario, int *ultima_tecla_precionada, teclas* tecla, int * i_mapa){ //rebe as teclas do usuario e mostra se esta ou não sendo precionada
     if(evento_primario->type == ALLEGRO_EVENT_KEY_DOWN){ // se alguma tecla for precionada marca como verdadeiro
        switch(evento_primario->keyboard.keycode){
            case ALLEGRO_KEY_W: tecla->w = true; break;
            case ALLEGRO_KEY_D: tecla->d = true; break;
            case ALLEGRO_KEY_S: tecla->s = true; break;
            case ALLEGRO_KEY_A: tecla->a = true; break;
            case ALLEGRO_KEY_1: tecla->t1 = true; break;
            case ALLEGRO_KEY_2: tecla->t2 = true; break;
            case ALLEGRO_KEY_3: tecla->t3 = true; break;
            case ALLEGRO_KEY_0: tecla->t0 = true; break;
        }
        *ultima_tecla_precionada = evento_primario->keyboard.keycode; //armazena a ultima tecla precionada
      }
      if(evento_primario->type == ALLEGRO_EVENT_KEY_UP){ //se a alguma tecla for solta marca como falso
        switch(evento_primario->keyboard.keycode){ 
            case ALLEGRO_KEY_W: tecla->w = false; break;
            case ALLEGRO_KEY_D: tecla->d = false; break;
            case ALLEGRO_KEY_S: tecla->s = false; break;
            case ALLEGRO_KEY_A: tecla->a = false; break;
            case ALLEGRO_KEY_1: tecla->t1 = false; break;
            case ALLEGRO_KEY_2: tecla->t2 = false; break;
            case ALLEGRO_KEY_3: tecla->t3 = false; break;
            case ALLEGRO_KEY_0: tecla->t0 = false; break;
      }
    }

    if(tecla->t1){
            *i_mapa = 1;
        }else if(tecla->t2){
            *i_mapa = 2;
        }else if(tecla->t3){
            *i_mapa = 3;
        }else if(tecla->t0){
            *i_mapa = 0;
        }
}

    void processar_teclas(teclas *tecla, player* p, int array_map[32][32]){
    
    int novo_x = p->eixox;
    int novo_y = p->eixoy;

    if(tecla->w) novo_y -= p->speed;
    if(tecla->s) novo_y += p->speed;
    if(tecla->d) novo_x += p->speed;
    if(tecla->a) novo_x -= p->speed;

    // colisão eixo Y
    if(!colisao(p->eixox, novo_y, array_map, p->tamanho)){
        p->eixoy = novo_y;
    }

    // colisão eixo X
    if(!colisao(novo_x, p->eixoy, array_map, p->tamanho)){
        p->eixox = novo_x;
    }
}


void animacao_player(int * si, teclas* tecla){ // manipula a variavel si para navegar pelo sprite do personagem
        if(tecla->w || tecla->a || tecla->d || tecla->s){
                *si = (*si+1)%5;
            } else{
                *si = 0;
            }
}


void printar_tela(teclas* tecla, player* p, int *si, ALLEGRO_BITMAP* image, int array_map[32][32]){
    //faz toda a parte visual do jogo
     processar_teclas(tecla, p, array_map); //desloca o player na tela
     animacao_player(si, tecla); //faz animação do player
     printar_player(image, tecla, *p, *si); // printa o player
     al_flip_display(); //pega tudo e mostra na tela
}