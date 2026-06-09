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


/*void new_mapa(int array_map[32][32], ALLEGRO_BITMAP* parede[], ALLEGRO_BITMAP* mapa, Chao chao){
    Node* node = NULL;
    node = insert_node(node, NULL, 1, "maps/mapa1.txt");
    node = insert_node(node, NULL, 2, "maps/mapa2.txt");
    node = insert_node(node, NULL, 3, "maps/mapa3.txt");
    node = insert_node(node, NULL, 4, "maps/mapa4.txt");
    node = insert_node(node, NULL, 0, "maps/mapa_default.txt");

    Node* p = node;
    do{
        if(p == NULL){
            printf("Deu ruim\n");
            return;
        }
        printf("%d\n", p->l);
        printf("%s\n", p->endereco);
        p->mapa = fopen(p->endereco, "r");
        p = p->next;
    }while(p != node);
    
     if(node->mapa){
            for(int i = 0;i < 32;i++){
                for(int j = 0; j < 32;j++){
                    fscanf(node->mapa, "%d", &array_map[i][j]);
                }
            }
        }

    printar_chao(mapa, chao);
    for(int i = 0; i < 32;i++){
        for(int j = 0; j < 32; j++){
            int valor = array_map[i][j];

            if(valor >=1 && valor <= 9){
                al_draw_bitmap(parede[valor], j*16, i*16, 0);
            }
        } 
    }
        free_list(node); //mata a lista encadeada
}*/

    /*bool troca_mapa(Node* node, player* p){
    if(node->l == 0){
        if(p->eixox > 192 || p->eixox < 320 || p->eixoy == 0 || p->eixoy == 1){
            printf("Você não pode vir por aqui");
        }else
    return false;
        if(p->eixox < 192 || p->eixox > 320 || p->eixoy < 512 || p->eixoy > 496){
            return true;
        }else
    return false;
    }
}*/

  /*cria o mapa com base em algum arquivo*/
void criar_mapa(int* i_mapa,int* i_mapa_anterior, int array_map[32][32],ALLEGRO_BITMAP* parede[], ALLEGRO_BITMAP* mapa, Chao chao, Node* node, player* p){

   
    if(node->l == 0){
        if(p->eixox < 192 && p->eixox > 320 && p->eixoy < 0 && p->eixoy > 16){
            printf("Você não pode vir por aqui");
        }
        if(p->eixox < 192 && p->eixox > 320 && p->eixoy < 512 && p->eixoy > 496){
            node = node->next;
            p->eixox = 16;
            p->eixoy = 16;
        }
    }
    /*cria um vetor de string com os endereços dos mapas*/
   /*if(*i_mapa_anterior != *i_mapa){
            string nomes[] = {
            "maps/mapa_default.txt",
            "maps/mapa1.txt",
            "maps/mapa2.txt",
            "maps/mapa3.txt",
            "maps/mapa4.txt"
    };
        
    //abre o arquivo e importa a matriz
        FILE* mapa_default = fopen(nomes[*i_mapa], "r");
        if(mapa_default){
            for(int i = 0;i < 32;i++){
                for(int j = 0; j < 32;j++){
                    fscanf(mapa_default, "%d", &array_map[i][j]);
                }
            }
            fclose(mapa_default);
        }        
    i_mapa_anterior = *i_mapa;
    }  */

    printf("%d\n", node->l);
    FILE* mapa_default = fopen(node->endereco, "r");
        if(mapa_default){
            for(int i = 0;i < 32;i++){
                for(int j = 0; j < 32;j++){
                    fscanf(mapa_default, "%d", &array_map[i][j]);
                }
            }
            fclose(mapa_default);
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
     
}

void printar_tela(teclas* tecla, player* p, int *si, ALLEGRO_BITMAP* image, int array_map[32][32], tiro tiro, ALLEGRO_BITMAP* image_tiro){
    //faz toda a parte visual do jogo
     processar_teclas(tecla, p, array_map); //desloca o player na tela
     animacao_player(si, tecla); //faz animação do player
     printar_player(image, tecla, *p, *si); // printa o player
     
     if(tiro.ativo){
     al_draw_bitmap(image_tiro, tiro.x, tiro.y, 0);
     }
     al_draw_rectangle(192, 512, 320, 496, al_map_rgb(255, 0, 0), 3);
     //(p->eixox < 192 || p->eixox > 320 || p->eixoy < 512 || p->eixoy > 496){

     al_flip_display(); //pega tudo e mostra na tela
}