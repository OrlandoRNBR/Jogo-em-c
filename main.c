#include <stdio.h>
#include <allegro5/allegro5.h> 
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <stdbool.h>

//player.h possivel biblioteca feita só com funções de controle do player
typedef struct player{//typedef para definir o player dps vai ter um de inimigos
    //posição do player
    int eixox; 
    int eixoy;
    //hp do player
    int hp;
}player;

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



int main (void){
    al_init_all(); //todos os inits em uma unica função!
    //cria a janela do jogo no padrão largura x altura 
    ALLEGRO_DISPLAY*        disp = al_create_display(1024, 512);
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
    ALLEGRO_BITMAP*         image = al_load_bitmap("sprites/smiley_face.png");
    if (image == NULL) {
        printf("ERRO: Nao foi possivel carregar o smiley_face!\n");
        return -1; // Encerra o programa de forma segura
    }


    //diz para o queue para prestar atenção nos imputs do teclado
    al_register_event_source(queue, al_get_keyboard_event_source());
    //diz para o queue prestar atenção na tela e verificar as informaçẽos da teça
    al_register_event_source(queue, al_get_display_event_source(disp));
    //diz para a fila prestar atenção nos ticks
    al_register_event_source(queue, al_get_timer_event_source(timer));

    player p = {30, 20, 3}; // declaração do player possivelmete vai ser alterado
    
    int flags = 0;//na hora de renderizar a imagem ele usa essa variavel para saber se a imagem deve ser alterada.

    ALLEGRO_EVENT event; // não sei o que faz ainda
    al_start_timer(timer); //inicia o rologio 
    while(1){ //looping principal do jogo
      al_wait_for_event(queue, &event); //pausa o loping até algun evento aocntecer

     // verifica se p evento que acabou de acontecer foi fechar a janela
      if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) break;

        //verifica se uma tecla foi pricionada
        if(event.type == ALLEGRO_EVENT_KEY_DOWN){
            //se for d soma no exio x se for a subtrai no eixo x criando a movimentação horizontal 
            if(event.keyboard.keycode == ALLEGRO_KEY_D)  p.eixox += 10;
            if(event.keyboard.keycode == ALLEGRO_KEY_A)  p.eixox -= 10;
            // se for s soma no eixo y e se for w subtrai do eixo y criando o mavimento vertical
            if(event.keyboard.keycode == ALLEGRO_KEY_S)  p.eixoy += 10;
            if(event.keyboard.keycode == ALLEGRO_KEY_W)  p.eixoy -= 10;
        /*quero mudar pois precisa ficar clicando pro buneco andar */
        }
        /*esse if verifica se houve um tick E a fila (queue event) estiver vazio esse bloco aocontece
        Isso garante que se o pc travar ou a fila estiver cheia não vai entrar um novo elemento na fila.*/ 
        if(event.type == ALLEGRO_EVENT_TIMER && al_is_event_queue_empty(queue)){
            //pinta o fundo de uma cor provavelmente vai sair
            al_clear_to_color(al_map_rgb(10, 218, 250));
            //desenha a imagem amrmazenada nessas coordenadas flags esta ai para não alterar a imagem
            al_draw_bitmap(image, p.eixox, p.eixoy, flags);
            //pega tudo dezenhado e coloca na janela/tela
            al_flip_display();
        }
    }

al_destroy_all(disp, timer, queue, font, image); //roda todas as finções de liberação da memoria!

}
