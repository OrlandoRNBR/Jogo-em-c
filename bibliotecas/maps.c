#include "player.h"
#include "maps.h"
#include "auxiliar.h"


void printar_chao(ALLEGRO_BITMAP* mapa,map chao){ //cada função dessa compoem um pedaço do chão do jogo
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
void criar_mapa(int* i_mapa,int* i_mapa_anterior, int array_map[32][32],ALLEGRO_BITMAP* parede[], ALLEGRO_BITMAP* mapa, map chao){
    /*cria um vetor de string com os endereços dos mapas*/
    if(*i_mapa_anterior != *i_mapa){
            string nomes[] = {
            "maps/mapa_default.txt",
            "maps/mapa1.txt",
            "maps/mapa2.txt",
            "maps/mapa3.txt",
            "maps/mapa4.txt"
    };
        
    /*abre o arquivo e importa a matriz*/
        FILE* mapa_default = fopen(nomes[*i_mapa], "r");
        if(mapa_default){
            for(int i = 0;i < 32;i++){
                for(int j = 0; j < 32;j++){
                    fscanf(mapa_default, "%d", &array_map[i][j]);
                }
            }
            fclose(mapa_default);
        }        
    *i_mapa_anterior = *i_mapa;
    }  


    /*desenha o mapa carregado */
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