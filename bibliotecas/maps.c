#include "player.h"
#include "maps.h"
#include "auxiliar.h"


void printar_chao(ALLEGRO_BITMAP* mapa,Chao chao){ //cada função dessa compoem um pedaço do chão do jogo
    al_draw_bitmap_region(mapa, 0, 0, chao.largura, chao.altura, chao.eixox, chao.eixoy, 0);
    al_draw_bitmap_region(mapa, 0, 0, chao.largura, chao.altura, chao.eixox+256, chao.eixoy, 0);
    al_draw_bitmap_region(mapa, 0, 0, chao.largura, chao.altura, chao.eixox+256, chao.eixoy+(1*128), 0);
    al_draw_bitmap_region(mapa, 0, 0, chao.largura, chao.altura, chao.eixox+256, chao.eixoy+(2*128), 0);
    al_draw_bitmap_region(mapa, 0, 0, chao.largura, chao.altura, chao.eixox+256, chao.eixoy+(3*128), 0);
    al_draw_bitmap_region(mapa, 0, 0, chao.largura, chao.altura, chao.eixox, chao.eixoy+(1*128), 0);
    al_draw_bitmap_region(mapa, 0, 0, chao.largura, chao.altura, chao.eixox, chao.eixoy+(2*128), 0);
    al_draw_bitmap_region(mapa, 0, 0, chao.largura, chao.altura, chao.eixox, chao.eixoy+(3*128), 0);
}


  /*cria o mapa com base em algum arquivo*/
Node* criar_mapa(int array_map[32][32],ALLEGRO_BITMAP* parede[], ALLEGRO_BITMAP* mapa, Chao chao, Node* node, player* p, bool* mudou, bool playing){

    *mudou = false;//armazena se houve mudanças no node.


    if(!playing){
                while(node->l != 0)
                    node = node->next;
                
                *mudou = true;
    }

    switch(node->l){ // verifica qual mapa esta aberto e verifica se o player esta pisando na saida dele. Coloca o player na entrada do mapa novo depos de fazer a trooca
        case 0:
            if(p->eixox > 192 && p->eixox < 320 && p->eixoy < 512 && p->eixoy > 476){
                p->eixox = 256;
                p->eixoy = 1;
                node = node->next;
                printf("Mudou para o endereço: %s\n", node->endereco);
                printf("Mudou para o mapa: %d\n", node->l);
                printf("MUDEI NO SWITCH PARA: X=%d, Y=%d\n", p->eixox, p->eixoy);
                *mudou = true;
            }
            break;
            
        case  1:
        
            if(p->eixox > 0 && p->eixox < 16 && p->eixoy < 448 && p->eixoy > 368){
                p->eixox = 480;
                p->eixoy = 448;
                node = node->next;
                printf("Mudou para o endereço: %s\n", node->endereco);
                printf("Mudou para o mapa: %d\n", node->l);
                printf("MUDEI NO SWITCH PARA: X=%d, Y=%d\n", p->eixox, p->eixoy);
                *mudou = true;
            }
            break;
        case 2:
        if(p->eixox > 192 && p->eixox < 304 && p->eixoy < 8 && p->eixoy > 0){
                p->eixox = 240;
                p->eixoy = 1;
                node = node->next;
                printf("Mudou para o endereço: %s\n", node->endereco);
                printf("Mudou para o mapa: %d\n", node->l);
                printf("MUDEI NO SWITCH PARA: X=%d, Y=%d\n", p->eixox, p->eixoy);
                *mudou = true;
            }
            break;

        case 3:
        if(p->eixox > 192 && p->eixox < 298 && p->eixoy < 512 && p->eixoy > 476){
                p->eixox = 480;
                p->eixoy = 240;
                node = node->next;
                printf("Mudou para o endereço: %s\n", node->endereco);
                printf("Mudou para o mapa: %d\n", node->l);
                printf("MUDEI NO SWITCH PARA: X=%d, Y=%d\n", p->eixox, p->eixoy);
                *mudou = true;
            }
            break;
        
        case 4:
        if(p->eixox > 0 && p->eixox < 8 && p->eixoy < 304 && p->eixoy > 192){
                p->eixox = 240;
                p->eixoy = 1;
                node = node->next;
                printf("Mudou para o endereço: %s\n", node->endereco);
                printf("Mudou para o mapa: %d\n", node->l);
                printf("MUDEI NO SWITCH PARA: X=%d, Y=%d\n", p->eixox, p->eixoy);
                *mudou = true;
            }
            break;

        default:
            break;
    }

    
            

    static bool primeiro_frame = true; //verifca se é o primeiro frame do jogo
    if(*mudou || primeiro_frame){//verifica as duas variveis para abrir o mapa.
    FILE* mapa_default = fopen(node->endereco, "r"); //abre o mapa com o endereço da lsita encadeada
        if(mapa_default){//se o mapa abriu lê e armazena no array map
            for(int i = 0;i < 32;i++){
                for(int j = 0; j < 32;j++){
                    fscanf(mapa_default, "%d", &array_map[i][j]);
                }
            }
            fclose(mapa_default);//fecha o arwuivo do mapa
            primeiro_frame = false;//não é mais o primeiro frame
        } 
    }

    //desenha o mapa carregado 
    printar_chao(mapa, chao);
        for(int i = 0; i < 32;i++){
            for(int j = 0; j < 32; j++){
                int valor = array_map[i][j];

                if(valor >=1 && valor <= 9){
                    al_draw_bitmap(parede[valor], j*16, i*16, 0);
                }
            }       
        }
        return node;
}



void printar_tela(teclas* tecla, player* p, int *si, ALLEGRO_BITMAP* image, int array_map[32][32], tiro tiro, ALLEGRO_BITMAP* image_tiro, enemy* inimigos, ALLEGRO_BITMAP* inimigos_sprite){
    //faz toda a parte visual do jogo
     processar_teclas(tecla, p, array_map); //desloca o player na tela
     animacao_player(si, tecla); //faz animação do player
     printar_player(image, tecla, *p, *si); // printa o player
     
     if(tiro.ativo){
     al_draw_bitmap(image_tiro, tiro.x, tiro.y, 0);
     }
}