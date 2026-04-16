#include <allegro5/allegro5.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <stdbool.h>

int main(){
    al_init();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();
    al_install_keyboard();

    ALLEGRO_DISPLAY*      disp = al_create_display(600, 400);
    ALLEGRO_TIMER*       timer = al_create_timer(1.0/100.0);
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    ALLEGRO_FONT*         font = al_load_font("GROBOLD.ttf", 30, 0);
    ALLEGRO_BITMAP*      image = al_load_bitmap("smiley_face.png");

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

        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            break;

        if(event.type == ALLEGRO_EVENT_KEY_DOWN){
            if(event.keyboard.keycode == ALLEGRO_KEY_RIGHT)
                x += 10;
            if(event.keyboard.keycode == ALLEGRO_KEY_LEFT)
                x -= 10;

            if(event.keyboard.keycode == ALLEGRO_KEY_DOWN)
                y += 10;
            if(event.keyboard.keycode == ALLEGRO_KEY_UP)
                y -= 10;
        }

        if(event.type == ALLEGRO_EVENT_TIMER && al_is_event_queue_empty(queue)){
            al_clear_to_color(al_map_rgb(150, 150, 200));
            al_draw_bitmap(image, x, y, flags);
            al_flip_display();
        }
    }

    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
}
