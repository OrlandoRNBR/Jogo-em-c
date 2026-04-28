#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h> 
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <stdbool.h>
#include "bibliotecas/player.h"

typedef struct masps{
    int eixox;
    int eixoy;
    int largura;
    int altura;
}map;

void printar_chao(ALLEGRO_BITMAP* mapa,map chao){
    al_draw_bitmap_region(mapa, 0, 0, chao.largura, chao.altura, chao.eixox, chao.eixoy, 0);
    al_draw_bitmap_region(mapa, 0, 0, chao.largura, chao.altura, chao.eixox+256, chao.eixoy, 0);
    al_draw_bitmap_region(mapa, 0, 0, chao.largura, chao.altura, chao.eixox+256, chao.eixoy+(1*128), 0);
    al_draw_bitmap_region(mapa, 0, 0, chao.largura, chao.altura, chao.eixox+256, chao.eixoy+(2*128), 0);
    al_draw_bitmap_region(mapa, 0, 0, chao.largura, chao.altura, chao.eixox+256, chao.eixoy+(3*128), 0);
    al_draw_bitmap_region(mapa, 0, 0, chao.largura, chao.altura, chao.eixox, chao.eixoy+(1*128), 0);
    al_draw_bitmap_region(mapa, 0, 0, chao.largura, chao.altura, chao.eixox, chao.eixoy+(2*128), 0);
    al_draw_bitmap_region(mapa, 0, 0, chao.largura, chao.altura, chao.eixox, chao.eixoy+(3*128), 0);
}

void receber_matriz(){

}

//al maneger, ṕossivel biblioteca de gerenciamento das funções allegro. 
void al_init_all(){
    al_init(); //inicia a biblioteca do alegro
    al_init_font_addon(); //prepara a memória para receber fontes costumizadas
    al_init_ttf_addon();// permite o alegro renderizar fontes de arquivos ttf
    al_init_image_addon(); //permite a biblioteca alegro renderizar bitmaps
    al_install_keyboard(); //informa o sistema operacional que o programa vai capiturar teclas
}

void al_destroy_all(ALLEGRO_DISPLAY* disp, ALLEGRO_TIMER* timer, ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_FONT* font, ALLEGRO_BITMAP* image){
    al_destroy_display(disp); //destroi a janela e libera a memoria
    al_destroy_timer(timer);// destroi o relogio e libera a memoria
    al_destroy_event_queue(queue);//destroi a fila de eventos e libera da memoria
    al_destroy_font(font); //destroi as fontes e libera da memoria
    al_destroy_bitmap(image); //destroi a imagem e libera da memoria
    
}

void al_register_all_event_source(ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_TIMER* timer, ALLEGRO_DISPLAY* disp){
//diz para o queue para prestar atenção nos imputs do teclado
    al_register_event_source(queue, al_get_keyboard_event_source());
    //diz para o queue prestar atenção na tela e verificar as informaçẽos da teça
    al_register_event_source(queue, al_get_display_event_source(disp));
    //diz para a fila prestar atenção nos ticks
    al_register_event_source(queue, al_get_timer_event_source(timer));
}



int main (void){
    al_init_all(); //todos os inits em uma unica função!

    player p = {30, 20, 5, 3, 32}; //declaração do player posição eixo x, posição eixo y, vidas
    map chao = {0,0,256, 128};
    int movendo = 0; //0 parado, 1 pra cima, 2 pra direita, 3 pra baixo, 4 pra esquerda 
    int ultima_tecla_precionada = 0;
    int flags = 0;//na hora de renderizar a imagem ele usa essa variavel para saber se a imagem deve ser alterada.
    tela t = {512, 512};
    int si = 0;
    teclas tecla = {false, false, false, false};
    int array_map[32][32];
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
        FILE* mapa1 = fopen("maps/mapa1.txt", "r");
        FILE* mapa2 = fopen("maps/mapa2.txt", "r");
        FILE* mapa3 = fopen("maps/mapa3.txt", "r");

     // verifica se p evento que acabou de acontecer foi fechar a janela
        if(evento_primario.type == ALLEGRO_EVENT_DISPLAY_CLOSE || evento_primario.keyboard.keycode == ALLEGRO_KEY_ESCAPE) break;

        receber_teclas(&evento_primario, &ultima_tecla_precionada, &tecla ); //verifica e earmazena se as teclas estão sendo precionadas.
        
        /*esse if verifica se houve um tick E a fila (queue event) estiver vazio esse bloco aocontece
        Isso garante que se o pc travar ou a fila estiver cheia não vai entrar um novo elemento na fila.*/
        if(evento_primario.type == ALLEGRO_EVENT_TIMER && al_is_event_queue_empty(queue)) {
            al_clear_to_color(al_map_rgb(90, 105, 136)); // pinta o fundo na cor do codigo RGB
            printar_chao(mapa, chao);
                for(int i = 0;i < 32;i++){
                    for(int j = 0; j < 32;j++){
                        fscanf(mapa2, "%d", &array_map[i][j]);
                    }
                }
        
            for(int i = 0; i < 32;i++){
                for(int j = 0; j < 32; j++){
                    int valor = array_map[i][j];
                    if(valor >=1 && valor <= 9){
                        al_draw_bitmap(parede[valor], j*16, i*16, 0);
                    }
                }
            }
            printar_tela(&tecla, &p, &t, &si, image, ultima_tecla_precionada); //um misto de funções que fica atualizando a tela a cada tick
        
        }
        fclose(mapa1);
        fclose(mapa2);
        fclose(mapa3);
    }
    al_destroy_all(disp, timer, queue, font, image); //roda todas as finções de liberação da memoria!
    
}
