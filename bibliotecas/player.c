
#include "player.h"
#include "auxiliar.h"
#include "maps.h"


void printar_menu(ALLEGRO_BITMAP* ui, ALLEGRO_FONT* font, ALLEGRO_BITMAP* image, player p){
    al_draw_bitmap(ui, 0, 0, 0); //printa o fundo do menu
    //printa os textos do menu
    al_draw_text(font, al_map_rgb(255, 255, 255), 200, 100, ALLEGRO_ALIGN_CENTRE, "Limbo Hunters");
    al_draw_text(font, al_map_rgb(138, 0, 0), 262, 188, ALLEGRO_ALIGN_CENTRE, "Play");
    al_draw_text(font, al_map_rgb(138, 0, 0), 262, 260, ALLEGRO_ALIGN_CENTRE, "characters");
    al_draw_text(font, al_map_rgb(138, 0, 0), 262, 332, ALLEGRO_ALIGN_CENTRE, "Config");
    al_draw_text(font, al_map_rgb(138, 0, 0), 262, 404, ALLEGRO_ALIGN_CENTRE, "exit");
    //printa a skin do lado do botão
    al_draw_bitmap_region(image,p.tamanho * 0,p.tamanho * 0, p.tamanho, p.tamanho, 60, 262, 0);
    al_flip_display();
}

bool colisao(int x, int y ,int array_map[32][32], int tamanho ){
    /*cria a colisão do jogo verificando todas as direções do personagem*/
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



void receber_teclas (ALLEGRO_EVENT *evento_primario, int *ultima_tecla_precionada, teclas* tecla){ //rebe as teclas do usuario e mostra se esta ou não sendo precionada
     if(evento_primario->type == ALLEGRO_EVENT_KEY_DOWN){ // se alguma tecla for precionada marca como verdadeiro
        switch(evento_primario->keyboard.keycode){
            case ALLEGRO_KEY_W: tecla->w = true; break;
            case ALLEGRO_KEY_D: tecla->d = true; break;
            case ALLEGRO_KEY_S: tecla->s = true; break;
            case ALLEGRO_KEY_A: tecla->a = true; break;

        }
        *ultima_tecla_precionada = evento_primario->keyboard.keycode; //armazena a ultima tecla precionada
      }
      if(evento_primario->type == ALLEGRO_EVENT_KEY_UP){ //se a alguma tecla for solta marca como falso
        switch(evento_primario->keyboard.keycode){ 
            case ALLEGRO_KEY_W: tecla->w = false; break;
            case ALLEGRO_KEY_D: tecla->d = false; break;
            case ALLEGRO_KEY_S: tecla->s = false; break;
            case ALLEGRO_KEY_A: tecla->a = false; break;
      }
    }

}

    void processar_teclas(teclas *tecla, player* p, int array_map[32][32]){
    /*processa as teclas e define o movimento, tambem aplica a colisão*/
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
bool colisao_tiro(int x, int y ,int array_map[32][32]){
    /*cria a colisão do jogo verificando todas as direções do personagem*/

    int tamanho = 8; 
    //a margem serve para corrigir a colisão em relação a parede
    int margem_cima = 2;
    int margem_baixo = 1;
    
    //verifica a coordenada em rela ção ao indice do array map i = x e j = y
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



void animacao_player(int * si, teclas* tecla){ // manipula a variavel si para navegar pelo sprite do personagem
        if(tecla->w || tecla->a || tecla->d || tecla->s){
                *si = (*si+1)%5;
            } else{
                *si = 0;
            }
}


