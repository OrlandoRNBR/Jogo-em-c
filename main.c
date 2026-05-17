#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h> 
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <stdbool.h>
#include "bibliotecas/player.h"
#include "bibliotecas/auxiliar.h"


int main (void){
    al_init_all(); //todos os inits em uma unica função!

    player p = {16, 16, 5, 3, 32}; //declaração do player posição eixo x, posição eixo y, vidas
    map chao = {0,0,256, 128};//informações do fundo do mapa
    int ultima_tecla_precionada = 0;
    tela t = {512, 512};
    int si = 0;
    /*teclas nessa ordem w, d,s,a,1,2,3,0.*/
    teclas tecla = {false, false, false, false, false, false, false, false, false};
    int array_map[32][32];
    int i_mapa = 0;
    int i_mapa_anterior = -1;
    int skin = 0;
    bool playing = false;
    bool Play_detect = false, config_detect = false, char_detect = false, exti_detect = false;

    /*Carregamento dos ponteros allegro*/
    //cria a janela do jogo no padrão largura x altura 
    ALLEGRO_DISPLAY*        disp = al_create_display(t.largura, t.altura);
    ALLEGRO_TIMER*          timer = al_create_timer(1.0/30.0);
    ALLEGRO_EVENT_QUEUE*    queue = al_create_event_queue();
    ALLEGRO_FONT*           font = al_load_font("Fonts/GODOFWAR.TTF", 30, 0);
    if (font == NULL) {
        printf("ERRO: Nao foi possivel carregar a fonte GODOFWAR!\n");
        return -1; // Encerra o programa de forma segura
    }

    
    /*carregamento dos sprites do jogo*/
    ALLEGRO_BITMAP*         skin_set[2];
    skin_set [0]= al_load_bitmap("sprites/ash.png");
    skin_set [1]= al_load_bitmap("sprites/luiza.png");
    ALLEGRO_BITMAP*         image = al_load_bitmap("sprites/ash.png");
    ALLEGRO_BITMAP*         mapa = al_load_bitmap("sprites/chão.png");
    ALLEGRO_BITMAP*         ui = al_load_bitmap("sprites/ui.png");
    ALLEGRO_BITMAP*         parede[10]; 
    parede [0] = al_load_bitmap("sprites/void.png");
    parede [1] = al_load_bitmap("sprites/parede1.png");
    parede [2] = al_load_bitmap("sprites/parede2.png");
    parede [3] = al_load_bitmap("sprites/parede3.png");
    parede [4] = al_load_bitmap("sprites/parede4.png");
    parede [5] = al_load_bitmap("sprites/parede5.png");
    parede [6] = al_load_bitmap("sprites/parede6.png");
    parede [7] = al_load_bitmap("sprites/parede7.png");
    parede [8] = al_load_bitmap("sprites/parede8.png");
    parede [9] = al_load_bitmap("sprites/parede9.png");


    if (image == NULL) {
        printf("ERRO: Nao foi possivel carregar o sprites.png\n");
        return -1; // Encerra o programa de forma segura
    }
    if (mapa == NULL) {
        printf("ERRO: Nao foi possivel carregar o chão.png\n");
        return -1; // Encerra o programa de forma segura
    }

    al_register_all_event_source(queue, timer, disp);
    ALLEGRO_EVENT evento_primario, evento_secundario; // armazena os eventos do jogo
    al_start_timer(timer); //inicia o rologio 

    while(1){
        al_wait_for_event(queue, &evento_primario); //pausa o loping até algun evento aocntecer

     // verifica se p evento que acabou de acontecer foi fechar a janela
        if(evento_primario.type == ALLEGRO_EVENT_DISPLAY_CLOSE || evento_primario.keyboard.keycode == ALLEGRO_KEY_ESCAPE) break;

        if(evento_primario.type == ALLEGRO_EVENT_KEY_DOWN){
            if(evento_primario.keyboard.keycode == ALLEGRO_KEY_P) playing = true;
            if(evento_primario.keyboard.keycode == ALLEGRO_KEY_M) playing = false; 
        }

        if(!playing){
            if(evento_primario.type == ALLEGRO_EVENT_MOUSE_AXES || evento_primario.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){

            if(evento_primario.mouse.x > 152 && evento_primario.mouse.y > 187 && evento_primario.mouse.x < 364 && evento_primario.mouse.y < 222 ){
                if(evento_primario.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
                if(evento_primario.mouse.button == ALLEGRO_MOUSE_BUTTON_LEFT) playing = true;

                Play_detect = true;
            }else if(evento_primario.mouse.x > 152 && evento_primario.mouse.y > 224 && evento_primario.mouse.x < 364 && evento_primario.mouse.y < 259){
                if(evento_primario.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
                if(evento_primario.mouse.button == ALLEGRO_MOUSE_BUTTON_LEFT) skin++;
                if(skin > 1) skin = 0;
                char_detect = true;
            }else if(evento_primario.mouse.x > 152 && evento_primario.mouse.y > 262 && evento_primario.mouse.x < 364 && evento_primario.mouse.y < 297){
                if(evento_primario.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
                printf("Função não emplementada!\n");

                config_detect = false;
            }else if(evento_primario.mouse.x > 152 && evento_primario.mouse.y > 298 && evento_primario.mouse.x < 364 && evento_primario.mouse.y < 333){
                if(evento_primario.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) 
                if(evento_primario.mouse.button == ALLEGRO_MOUSE_BUTTON_LEFT) break;

                exti_detect = true;
            }else{ 
                Play_detect = false;
                config_detect = false;
                char_detect = false;
                exti_detect = false;
            }
            }
        }

        if(playing){
        /*recebe as teclas usadas no jogo e declara como true ou false*/
        receber_teclas(&evento_primario, &ultima_tecla_precionada, &tecla, &i_mapa ); 

                if(evento_primario.keyboard.keycode == ALLEGRO_KEY_C) skin++;
                if(skin > 1) skin = 0;
   
            ALLEGRO_BITMAP*         image = skin_set[skin];
        if(evento_primario.type == ALLEGRO_EVENT_TIMER && al_is_event_queue_empty(queue)) {
            criar_mapa(&i_mapa,&i_mapa_anterior, array_map, parede, mapa, chao);
           
            printar_tela(&tecla, &p, &si, image, array_map); //um misto de funções que fica atualizando a tela a cada tick
        }
        }else{
        
            al_draw_bitmap(ui, 0, 0, 0);
            al_draw_text(font, al_map_rgb(255, 255, 255), 100, 0, ALLEGRO_ALIGN_CENTRE, "Nome");
            al_draw_text(font, al_map_rgb(138, 0, 0), 262, 188, ALLEGRO_ALIGN_CENTRE, "Play");
            al_draw_rectangle(152, 187, 364, 222,  al_map_rgb(138, 0, 255),5);
            if(Play_detect){
                al_draw_rectangle(152, 187, 364, 222,  al_map_rgb(138, 0, 0), 5);
            }


            al_draw_text(font, al_map_rgb(138, 0, 0), 262, 260, ALLEGRO_ALIGN_CENTRE, "characters");
            al_draw_text(font, al_map_rgb(138, 0, 0), 262, 332, ALLEGRO_ALIGN_CENTRE, "Config");
            al_draw_text(font, al_map_rgb(138, 0, 0), 262, 404, ALLEGRO_ALIGN_CENTRE, "exit");
            al_draw_bitmap_region(image,p.tamanho * si,p.tamanho * 0, p.tamanho, p.tamanho, 60, 262, 0);
            al_flip_display();
        }
    }
    al_destroy_all(disp, timer, queue, font, image, mapa, parede, ui); //roda todas as finções de liberação da memoria!
    
}
