#include "auxiliar.h"
#include "player.h"


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

void criar_mapa(int* i_mapa,int* i_mapa_anterior, int array_map[32][32],ALLEGRO_BITMAP* parede[], ALLEGRO_BITMAP* mapa, map chao){
        if(*i_mapa_anterior != *i_mapa){
            const char* nomes[] = {
            "maps/mapa_default.txt",
            "maps/mapa1.txt",
            "maps/mapa2.txt",
            "maps/mapa3.txt"
        };
        
            FILE* mapa_default = fopen(nomes[*i_mapa], "r");
            if(mapa_default){

                for(int i = 0;i < 32;i++)
                    for(int j = 0; j < 32;j++)
                        fscanf(mapa_default, "%d", &array_map[i][j]);

                       fclose(mapa_default);
            }        
                    *i_mapa_anterior = *i_mapa;
        }  
        al_clear_to_color(al_map_rgb(90, 105, 136)); // pinta o fundo na cor do codigo RGB
        printar_chao(mapa, chao);
        for(int i = 0; i < 32;i++){
            for(int j = 0; j < 32; j++){
                int valor = array_map[i][j];
                if(valor >=1 && valor <= 9){
                    al_draw_bitmap(parede[valor], j*16, i*16, 0);
                    }
            } 
    }
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
