#include <allegro5/allegro5.h> 
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <stdbool.h>




int main (void){
    al_init(); //inicia a biblioteca do alegro
    al_init_font_addon(); //prepara a memória para receber fontes costumizadas
    al_init_ttf_addon();// permite o alegro renderizar fontes de arquivos ttf
    al_init_image_addon(); //permite a biblioteca alegro renderizar bitmaps
    al_install_keyboard(); //informa o sistema operacional que o programa vai capiturar teclas

//cria a janela do jogo no padrão largura x altura 
ALLEGRO_DISPLAY*        disp = al_create_display(1024, 512);
//cria um temporizador que controla os frames do jog1ao
ALLEGRO_TIMER*          timer = al_create_timer(1.0/30.0);
//Cria uma "fila de eventos" onde o código guarda as capturas de eventos e o ticks
ALLEGRO_EVENT_QUEUE*    queue = al_create_event_queue();
// falta dovumentar a linha abaixo 
ALLEGRO_FONT*           font = al_load_font("GODOFWAR.TTF", 30, 0);
//carrega um sprite da pasta e armazena em imagens.
ALLEGRO_BITMAP*         image = al_load_bitmap("smiley_face.png");

al_register_event_source(queue, al_get_keyboard_event_source());
al_register_event_source(queue, al_get_display_event_source(disp));
al_register_event_source(queue, al_get_timer_event_source(timer));

int x = 30;
int y = 20;
int flags = 0;

ALLEGRO_EVENT event;
al_start_timer(timer);
while(1){
    al_wait_for_event(queue, &event);

    if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) break;

    if(event.type == ALLEGRO_EVENT_KEY_DOWN){
        if(event.keyboard.keycode == ALLEGRO_KEY_D)  x += 10;
        if(event.keyboard.keycode == ALLEGRO_KEY_A)  x -= 10;

        if(event.keyboard.keycode == ALLEGRO_KEY_S)  y += 10;
        if(event.keyboard.keycode == ALLEGRO_KEY_W)  y -= 10;
    }
    if(event.type == ALLEGRO_EVENT_TIMER && al_is_event_queue_empty(queue)){
        al_clear_to_color(al_map_rgb(10, 218, 250));
        al_draw_bitmap(image, x, y, flags);
        al_flip_display();
    }
}

al_destroy_font(font);
al_destroy_display(disp);
al_destroy_timer(timer);
al_destroy_event_queue(queue);

}
