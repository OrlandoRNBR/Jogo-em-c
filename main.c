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

    player p = {30, 20, 5, 3, 32}; //declaração do player posição eixo x, posição eixo y, vidas
    map chao = {0,0,256, 128};
    int ultima_tecla_precionada = 0;
    int flags = 0;//na hora de renderizar a imagem ele usa essa variavel para saber se a imagem deve ser alterada.
    tela t = {512, 512};
    int si = 0;
    teclas tecla = {false, false, false, false};
    int array_map[32][32];
    int i_mapa = 0;
    //cria a janela do jogo no padrão largura x altura 
    ALLEGRO_DISPLAY*        disp = al_create_display(t.largura, t.altura);
    //cria um temporizador que controla os frames do jogo atraves de ticks que apitão até 30 vezes por segundo
    ALLEGRO_TIMER*          timer = al_create_timer(1.0/30.0);
    //Cria uma "fila de eventos" onde o código guarda as capturas de eventos e o ticks
    ALLEGRO_EVENT_QUEUE*    queue = al_create_event_queue();
    // carrega a fonte selecionada o primeiro numero (30) é o tamanho e o segunndo (0) alterações que a fonte pode recerber mas não precisa de nenhum
    ALLEGRO_FONT*           font = al_load_font("Fonts/GODOFWAR.TTF", 30, 0);
    if (font == NULL) {
        printf("ERRO: Nao foi possivel carregar a fonte GODOFWAR!\n");
        return -1; // Encerra o programa de forma segura
    }
    //carrega um sprite da pasta e armazena em imagens.
    ALLEGRO_BITMAP*         image = al_load_bitmap("sprites/sprites.png");
    ALLEGRO_BITMAP*         mapa = al_load_bitmap("sprites/chão.png");
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
        printf("ERRO: Nao foi possivel carregar o smiley_face!\n");
        return -1; // Encerra o programa de forma segura
    }

    al_register_all_event_source(queue, timer, disp);


    ALLEGRO_EVENT evento_primario; // armazena os eventos do jogo
    al_start_timer(timer); //inicia o rologio 
    while(1){ //looping principal do jogo
        al_wait_for_event(queue, &evento_primario); //pausa o loping até algun evento aocntecer
        
     // verifica se p evento que acabou de acontecer foi fechar a janela
        if(evento_primario.type == ALLEGRO_EVENT_DISPLAY_CLOSE || evento_primario.keyboard.keycode == ALLEGRO_KEY_ESCAPE) break;

        receber_teclas(&evento_primario, &ultima_tecla_precionada, &tecla, &i_mapa ); //verifica e earmazena se as teclas estão sendo precionadas.
        /*esse if verifica se houve um tick E a fila (queue event) estiver vazio esse bloco aocontece
        Isso garante que se o pc travar ou a fila estiver cheia não vai entrar um novo elemento na fila.*/
        
        if(evento_primario.type == ALLEGRO_EVENT_TIMER && al_is_event_queue_empty(queue)) {
            criar_mapa(&i_mapa, array_map, parede, mapa, chao);
           
            printar_tela(&tecla, &p, &t, &si, image, ultima_tecla_precionada, array_map); //um misto de funções que fica atualizando a tela a cada tick
        
        }
       
    }
    al_destroy_all(disp, timer, queue, font, image); //roda todas as finções de liberação da memoria!
    
}
