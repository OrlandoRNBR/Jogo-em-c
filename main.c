#include "bibliotecas/player.h"
#include "bibliotecas/auxiliar.h"
#include "bibliotecas/maps.h"


#define largura 512
#define altura 512
//teste do tiro do personagem pegar imagem de tiro
#define VELOCIDADE_TIRO 8.0


bool colisao_tiro(int x, int y ,int array_map[32][32]){
    /*cria a colisão do jogo verificando todas as direções do personagem*/
    int tamanho = 0; 
    int margem_cima = 2;
    int margem_baixo = 1;
    
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



int main (void){
    al_init_all(); //todos os inits em uma unica função!

    player p = {16, 16, 5, 3, 32}; //declaração do player posição eixo x, posição eixo y, vidas
    tiro tiro = {0, 0, 0, 0, false};
    Chao chao = {0,0,256, 128};//informações do fundo do mapa
    int ultima_tecla_precionada = 0;
    int si = 0;
    /*teclas nessa ordem w, d,s,a,1,2,3,0.*/
    teclas tecla = {false, false, false, false, false, false, false, false, false};
    int array_map[32][32];
    int i_mapa = 0;
    int i_mapa_anterior = -1;
    int skin = 0;
    bool playing = false;
    int x_mouse, y_mouse, x_tiro, y_tiro;

    Node* head = NULL;
    head = new_node(&p, NULL, head, 1);
    insert_node(head, &p, NULL, 5);
    insert_node(head, &p, NULL, 4);
    insert_node(head, &p, NULL, 3);
    insert_node(head, &p, NULL, 2);


    /*Carregamento dos ponteros allegro*/
    //cria a janela do jogo no padrão largura x altura 
    ALLEGRO_DISPLAY*        disp = al_create_display(largura, altura);
    ALLEGRO_TIMER*          timer = al_create_timer(1.0/30.0);
    ALLEGRO_EVENT_QUEUE*    queue = al_create_event_queue();
    ALLEGRO_FONT*           font = al_load_font("Fonts/GODOFWAR.TTF", 30, 0);
    if (font == NULL) {
        printf("ERRO: Nao foi possivel carregar a fonte GODOFWAR!\n");
        return -1; // Encerra o programa de forma segura
    }   

    /*carregamento dos sprites do jogo*/
    int skin_tamanho = 5;
    ALLEGRO_BITMAP* skin_set[5];
    skin_set [0] = al_load_bitmap("sprites/ash.png");
    skin_set [1] = al_load_bitmap("sprites/luiza.png");
    skin_set [2] = al_load_bitmap("sprites/kayky.png");
    skin_set [3] = al_load_bitmap("sprites/david.png");
    skin_set [4] = al_load_bitmap("sprites/rayssa.png");

    ALLEGRO_BITMAP* skin_tiro[5];
    skin_tiro [0] = al_load_bitmap("sprites/bulet_ahs.png");
    skin_tiro [1] = al_load_bitmap("sprites/bulet_luiza.png");
    skin_tiro [2] = al_load_bitmap("sprites/bulet.png");
    skin_tiro [3] = al_load_bitmap("sprites/bulet_david.png");
    skin_tiro [4] = al_load_bitmap("sprites/bulet.png");

    ALLEGRO_BITMAP* image = al_load_bitmap("sprites/ash.png");
    ALLEGRO_BITMAP* mapa = al_load_bitmap("sprites/chão.png");
    ALLEGRO_BITMAP* ui = al_load_bitmap("sprites/ui.png");
    ALLEGRO_BITMAP* parede[10]; 
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
    ALLEGRO_EVENT evento_primario; // armazena os eventos do jogo
    al_start_timer(timer); //inicia o rologio 

    printf("%d", head->l);
    printf("%d", head->next->l);
    printf("%d", head->next->next->l);
    printf("%d", head->next->next->next->l);
    printf("%d", head->next->next->next->next->l);
    printf("============\n");
    //new_mapa(head, array_map, parede, mapa, chao);
    printf("A");

    while(1){
        al_wait_for_event(queue, &evento_primario); //pausa o loping até algun evento aocntecer

        if(skin >= skin_tamanho) skin = 0;
        
        ALLEGRO_BITMAP* image = skin_set[skin];
        ALLEGRO_BITMAP* image_tiro = skin_tiro[skin];

     // verifica se p evento que acabou de acontecer foi fechar a janela
        if(evento_primario.type == ALLEGRO_EVENT_DISPLAY_CLOSE || evento_primario.keyboard.keycode == ALLEGRO_KEY_ESCAPE) break;

        if(evento_primario.type == ALLEGRO_EVENT_KEY_DOWN){
            if(evento_primario.keyboard.keycode == ALLEGRO_KEY_P) playing = true;
            if(evento_primario.keyboard.keycode == ALLEGRO_KEY_M) playing = false; 
        }


        if(!playing){
           
            if(evento_primario.mouse.x > 152 && evento_primario.mouse.y > 187 && evento_primario.mouse.x < 364 && evento_primario.mouse.y < 222 ){
                if(evento_primario.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
                    if(evento_primario.mouse.button == ALLEGRO_MOUSE_BUTTON_LEFT) playing = true;
            }
            if(evento_primario.mouse.x > 152 && evento_primario.mouse.y > 259 && evento_primario.mouse.x < 364 && evento_primario.mouse.y < 294){
                if(evento_primario.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
                    if(evento_primario.mouse.button == ALLEGRO_MOUSE_BUTTON_LEFT) skin++;

            }
            if(evento_primario.mouse.x > 152 && evento_primario.mouse.y > 331 && evento_primario.mouse.x < 364 && evento_primario.mouse.y < 366){
                if(evento_primario.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
                    if(evento_primario.mouse.button == ALLEGRO_MOUSE_BUTTON_LEFT) printf("Função em desenvolvimento!\nMenu de configurações não implementado!\n");
            
            }
            if(evento_primario.mouse.x > 152 && evento_primario.mouse.y > 403 && evento_primario.mouse.x < 364 && evento_primario.mouse.y < 438){
                if(evento_primario.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
                    if(evento_primario.mouse.button == ALLEGRO_MOUSE_BUTTON_LEFT) break;

            }
            
        }

        if(playing){
        /*recebe as teclas usadas no jogo e declara como true ou false*/
        receber_teclas(&evento_primario, &ultima_tecla_precionada, &tecla, &i_mapa ); 

        if(evento_primario.type == ALLEGRO_EVENT_MOUSE_AXES){
            x_mouse = evento_primario.mouse.x;
            y_mouse = evento_primario.mouse.y;
        }
       
        if(evento_primario.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
            if(evento_primario.mouse.button == ALLEGRO_MOUSE_BUTTON_LEFT){
                x_tiro = evento_primario.mouse.x;
                y_tiro = evento_primario.mouse.y;

                if(!tiro.ativo){
                    float dx = x_tiro - p.eixox;
                    float dy = y_tiro - p.eixoy;
                    float distancia = hypot(dx, dy);
                    if(distancia != 0){
                        tiro.x = p.eixox + 8;
                        tiro.y = p.eixoy + 8;
                        tiro.velx = (dx/distancia)*VELOCIDADE_TIRO;
                        tiro.vely = (dy/distancia)*VELOCIDADE_TIRO;
                        tiro.ativo = true;
                    }
                }
            }
        }

        if(tiro.ativo){
            tiro.x += tiro.velx;
            tiro.y += tiro.vely;

            if(colisao_tiro(tiro.x, tiro.y, array_map)){
                tiro.ativo = false;
                printf("Tiro sumiu na borada da tela\n");
            }
            if(tiro.x < 0 || tiro.x > largura || tiro.y < 0 || tiro.y > altura){
                tiro.ativo = false;
                printf("Tiro sumiu na borada da tela\n");
            }
        }

        if(evento_primario.type == ALLEGRO_EVENT_TIMER && al_is_event_queue_empty(queue)) {
            criar_mapa(&i_mapa,&i_mapa_anterior, array_map, parede, mapa, chao);
           
            printar_tela(&tecla, &p, &si, image, array_map, tiro, image_tiro); //um misto de funções que fica atualizando a tela a cada tick
        }
        }else{
        
            printar_menu(ui, font, image, p);
        }
    }
    printf("aaa\n");
    free_list(head);
    printf("aaa\n");
    al_destroy_all(disp, timer, queue, font, image, mapa, parede, ui, skin_set, skin_tamanho, skin_tiro); //roda todas as finções de liberação da memoria!
    
}
