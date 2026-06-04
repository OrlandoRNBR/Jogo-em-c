#include "auxiliar.h"
#include "player.h"





void al_init_all(){
    al_init(); //inicia a biblioteca do alegro
    al_init_font_addon(); //prepara a memória para receber fontes costumizadas
    al_init_ttf_addon();// permite o alegro renderizar fontes de arquivos ttf
    al_init_image_addon(); //permite a biblioteca alegro renderizar bitmaps
    al_install_keyboard(); //informa o sistema operacional que o programa vai capiturar teclas
    al_install_mouse(); //informa o codigo que ele precisa olhar as informações do mouse
    al_init_primitives_addon();
}

void al_destroy_all(ALLEGRO_DISPLAY* disp, ALLEGRO_TIMER* timer, ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_FONT* font, ALLEGRO_BITMAP* image, ALLEGRO_BITMAP* mapa, ALLEGRO_BITMAP* parede[], ALLEGRO_BITMAP* ui, ALLEGRO_BITMAP* skin[], int skin_tamanho, ALLEGRO_BITMAP* skin_tiro[]){
    al_destroy_display(disp); //destroi a janela e libera a memoria
    al_destroy_timer(timer);// destroi o relogio e libera a memoria
    al_destroy_event_queue(queue);//destroi a fila de eventos e libera da memoria
    al_destroy_font(font); //destroi as fontes e libera da memoria
    al_destroy_bitmap(image); //destroi a imagem e libera da memoria
    al_destroy_bitmap(mapa);
    al_destroy_bitmap(ui);
    for(int i = 0; i < 10; i++){ //limpa todos os indices de parede
        al_destroy_bitmap(parede[i]);
    }
    for(int i = 0; i < skin_tamanho; i++){ //limpa todos os indices de parede
        al_destroy_bitmap(skin[i]);
    }
    for(int i = 0; i < skin_tamanho; i++){ //limpa todos os indices de parede
        al_destroy_bitmap(skin_tiro[i]);
    }
    
}

void al_register_all_event_source(ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_TIMER* timer, ALLEGRO_DISPLAY* disp){
//diz para o queue para prestar atenção nos imputs do teclado
    al_register_event_source(queue, al_get_keyboard_event_source());
    //diz para o queue prestar atenção na tela e verificar as informaçẽos da teça
    al_register_event_source(queue, al_get_display_event_source(disp));
    //diz para a fila prestar atenção nos ticks
    al_register_event_source(queue, al_get_timer_event_source(timer));
    
    al_register_event_source(queue, al_get_mouse_event_source());
}
