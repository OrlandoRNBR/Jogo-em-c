#include "bibliotecas/player.h"
#include "bibliotecas/auxiliar.h"
#include "bibliotecas/maps.h"


#define largura 512
#define altura 512
//teste do tiro do personagem pegar imagem de tiro
#define VELOCIDADE_TIRO 8.0
#define VELOCIDADE_INIMIGO 2.0

/*
======================================================================================================================

       (\__/)
       (•ㅅ•) o que acha junin?
   ＿ノ ヽ ノ＼__
 /  `/ ⌒Ｙ⌒ Ｙ  ヽ
(   (三ヽ人  /    |
|  ﾉ⌒＼ ￣￣ヽ  ノ
ヽ＿＿＿＞､＿＿_／
    ｜( 王 ﾉ〈   (\__/)
    /ﾐ`ー―彡\   (•ㅅ•)bem loko


O jogo ta documentado então da uma lida rapida pelo menos no main.c ja tem a colisão dos inimigos e
um struct se for dar uma olhada ta la na biblioteca estruturas.h o inimigo não precisa ter hp ele morre com um tiro só
======================================================================================================================
*/









bool colisao_enemy(int x, int y, int array_map[32][32], int tamanho) {
    int margem_cima = 4;
    int margem_baixo = 4;
    
    int esquerda = (x + margem_cima) / 16;
    int direita  = (x + tamanho - margem_baixo - 1) / 16;
    int topo     = (y + margem_cima) / 16;
    int baixo    = (y + tamanho - margem_baixo - 1) / 16;

    if (topo < 0 || baixo >= 32 || esquerda < 0 || direita >= 32) return true;

    if (array_map[topo][esquerda] != 0) return true;
    if (array_map[topo][direita]  != 0) return true;
    if (array_map[baixo][esquerda] != 0) return true;
    if (array_map[baixo][direita]  != 0) return true;

    return false;
}

void enemy_action(player* p, enemy* i, int n, int array_map[32][32], tiro* tiro, int* pontuacao) {
    if (i[n].alive) { 

        if (tiro->ativo) { // Só checa se o tiro realmente existir na tela
            int tamanho_tiro = 8; // Conforme o +8 que você usou no seu if
            
            if (tiro->x < i[n].x + i[n].tamanho &&  // Esquerda do tiro < Direita do inimigo
                tiro->x + tamanho_tiro > i[n].x &&  // Direita do tiro > Esquerda do inimigo
                tiro->y < i[n].y + i[n].tamanho &&  // Topo do tiro < Base do inimigo
                tiro->y + tamanho_tiro > i[n].y)    // Base do tiro > Topo do inimigo
            {
                i[n].alive = false; // O inimigo morre!
                tiro->ativo = false;   // O tiro some ao impactar (para não atravessar e matar outros)
                *pontuacao += 1;
                printf("Inimigo abatido pelo tiro!\n");
            }
        }


        // Correção das condições: adicionado o ! antes de colisao_enemy
        if (p->eixox < i[n].x) {
            if (!colisao_enemy(i[n].x - VELOCIDADE_INIMIGO, i[n].y, array_map, i[n].tamanho)) {
                i[n].x -= VELOCIDADE_INIMIGO; 
            }
        } else if (p->eixox > i[n].x) {
            if (!colisao_enemy(i[n].x + VELOCIDADE_INIMIGO, i[n].y, array_map, i[n].tamanho)) {
                i[n].x += VELOCIDADE_INIMIGO;
            }
        }

        if (p->eixoy < i[n].y) {
            if (!colisao_enemy(i[n].x, i[n].y - VELOCIDADE_INIMIGO, array_map, i[n].tamanho)) {
                i[n].y -= VELOCIDADE_INIMIGO; 
            }
        } else if (p->eixoy > i[n].y) {
            if (!colisao_enemy(i[n].x, i[n].y + VELOCIDADE_INIMIGO, array_map, i[n].tamanho)) {
                i[n].y += VELOCIDADE_INIMIGO;
            }
        }

        if (abs(p->eixox - i[n].x) < 16 && abs(p->eixoy - i[n].y) < 16) {
            p->hp--;
            i[n].alive = false; 
        }
    }
}

void animacao_inimigo(player* p, enemy* i, int n) { 
    if (i[n].x != p->eixox || i[n].y != p->eixoy) {
        i[n].frame_atual = (i[n].frame_atual + 1) % 4; // Geralmente sheets têm 4 frames
    } else {
        i[n].frame_atual = 0;
    }
}

void printar_inimigo(player* p, enemy* i, int n, int array_map[32][32], ALLEGRO_BITMAP* inimigo, tiro* tiro,int* pontuacao) {
    for (int j = 0; j < n; j++) {
        if (i[j].alive) {
            if (abs(p->eixox - i[j].x) > abs(p->eixoy - i[j].y)) {
                if (i[j].x > p->eixox)      i[j].direcao_y = 1; // Esquerda
                else                        i[j].direcao_y = 3; // Direita
            } else {
                if (i[j].y < p->eixoy)      i[j].direcao_y = 0; // Baixo (Frente)
                else                        i[j].direcao_y = 2; // Cima (Costas)
            }

            animacao_inimigo(p, i, j);
            enemy_action(p, i, j, array_map, tiro, pontuacao);

            if (inimigo != NULL) {
                al_draw_bitmap_region(inimigo, 
                                      i[j].tamanho * i[j].frame_atual, 
                                      i[j].tamanho * i[j].direcao_y, 
                                      i[j].tamanho, i[j].tamanho, 
                                      i[j].x, i[j].y, 0);
            }
        }
    }
}
int main (void){
    al_init_all(); //todos os inits em uma unica função!

    player p = {256, 1, 5, 3, 32}; //declaração do player posição eixo x, posição eixo y, vidas
    tiro tiro = {0, 0, 0, 0, false};
    Chao chao = {0,0,256, 128};//informações do fundo do mapa
    int ultima_tecla_precionada = 0;
    int si = 0;
    int pontuacao = 0;
    char hp_num[10];
    char str[10];
    /*teclas nessa ordem w, d,s,a,1,2,3,0.*/
    teclas tecla = {false, false, false, false, false, false, false, false, false};
    int array_map[32][32];
    char ponto_texto[] = "pontuação: ";
    char hp_texto[]= "hp: ";
    
    bool playing = false;
    bool mudou = false;
    int x_tiro, y_tiro; 
    enemy inimigos[4] = { //inicialização de um vetor de inimigos
        {true, 470, 32, 0, 0, 32}, // alive, x, y, frame_atual, direcao_y, tamanho
        {true, 26, 26, 0, 0, 32},
        {true, 32, 470, 0, 0, 32},
        {true, 448, 448, 0, 0, 32},
    };


    Node* node = NULL; //inicialização da lista encadeada com um id numerico e o endereço do mapa.
    node = insert_node(node, 0, "maps/mapa_default.txt");
    node = insert_node(node, 1, "maps/mapa1.txt");
    node = insert_node(node, 2, "maps/mapa2.txt");
    node = insert_node(node, 3, "maps/mapa3.txt");
    node = insert_node(node, 4, "maps/mapa4.txt");
    //node = node->next; //corrige para começar no primeiro mapa.
    Node* first = node->next; 

    char url[] = "https://pokeapi.co/api/v2/pokemon/649";

    download_file(url, "data.json");
    printf("baixou o bagulho\n");
    process_json("data.json");

    ALLEGRO_SAMPLE* disparo = NULL;
    disparo = al_load_sample("disparo.ogg");
    ALLEGRO_AUDIO_STREAM *musica = al_load_audio_stream("audio/lavander.wav", 4, 2048);

    



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

    ALLEGRO_BITMAP* inimigo_sprite = al_load_bitmap("sprites/vampires.png");

    /*carregamento dos sprites do jogo*/
    int skin = 0;
    int skin_tamanho = 6;
    ALLEGRO_BITMAP** skin_set = malloc(skin_tamanho*sizeof(ALLEGRO_BITMAP*)); //skin dos personagens
    skin_set [0] = al_load_bitmap("sprites/ash.png");
    skin_set [1] = al_load_bitmap("sprites/luiza.png");
    skin_set [2] = al_load_bitmap("sprites/kayky.png");
    skin_set [3] = al_load_bitmap("sprites/david.png");
    skin_set [4] = al_load_bitmap("sprites/rayssa.png");
    skin_set [5] = al_load_bitmap("sprites/martin.png");

    ALLEGRO_BITMAP** skin_tiro = malloc(skin_tamanho*sizeof(ALLEGRO_BITMAP*));//skin das munições
    skin_tiro [0] = al_load_bitmap("sprites/bulet_ahs.png");
    skin_tiro [1] = al_load_bitmap("sprites/bulet_luiza.png");
    skin_tiro [2] = al_load_bitmap("sprites/bulet.png");
    skin_tiro [3] = al_load_bitmap("sprites/bulet_david.png");
    skin_tiro [4] = al_load_bitmap("sprites/bulet_rayssa.png");
    skin_tiro [5] = al_load_bitmap("sprites/bulet_martin.png");

    ALLEGRO_BITMAP* image = al_load_bitmap("sprites/ash.png");
    ALLEGRO_BITMAP* mapa = al_load_bitmap("sprites/chão.png");
    ALLEGRO_BITMAP* ui = al_load_bitmap("sprites/ui.png");
    
    ALLEGRO_BITMAP** parede = malloc(10*sizeof(ALLEGRO_BITMAP*)); //inicializa os sprites da parede
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
    if (musica == NULL) {
    printf("[ERRO CRÍTICO] Não foi possível carregar a música de fundo!\n");
    return -1;
    }

    al_set_audio_stream_playmode(musica, ALLEGRO_PLAYMODE_LOOP);
    al_attach_audio_stream_to_mixer(musica, al_get_default_mixer());
    al_set_audio_stream_gain(musica, 0.2
    ); // Deixa a música um pouco mais baixa


    al_register_all_event_source(queue, timer, disp);
    ALLEGRO_EVENT evento_primario; // armazena os eventos do jogo
    al_start_timer(timer); //inicia o rologio 

    while(1){
        al_wait_for_event(queue, &evento_primario); //pausa o loping até algun evento aocntecer
        al_set_audio_stream_playmode(musica, ALLEGRO_PLAYMODE_LOOP);
        al_attach_audio_stream_to_mixer(musica, al_get_default_mixer());
        
        sprintf(str, "%d", pontuacao);
        sprintf(hp_num, "%d", p.hp);

        if(skin >= skin_tamanho) skin = 0; //verificação se ele selecionou um indice do vetor que existe
        
        ALLEGRO_BITMAP* image = skin_set[skin];//seleciona a skin
        ALLEGRO_BITMAP* image_tiro = skin_tiro[skin]; //seleciona o tiro

     // verifica se p evento que acabou de acontecer foi fechar a janela
        if(evento_primario.type == ALLEGRO_EVENT_DISPLAY_CLOSE /*|| evento_primario.keyboard.keycode == ALLEGRO_KEY_ESCAPE*/) break;

        if(evento_primario.type == ALLEGRO_EVENT_KEY_DOWN){
            if(evento_primario.keyboard.keycode == ALLEGRO_KEY_P) playing = true; //inicia o jogo
            if(evento_primario.keyboard.keycode == ALLEGRO_KEY_M) playing = false; //abre o menu
        }
        if(p.hp <= 0) playing = false;

        if(!playing){//verifica se o esta no menu
           
            node = first;
            tecla.w = false; 
            tecla.d = false;
            tecla.s = false;
            tecla.a = false;
           
            p.eixox = 256;
            p.eixoy = 1;
            p.hp = 3;
            p.tamanho = 32;

            inimigos[0].x = 464;
            inimigos[0].y = 32;

            inimigos[1].x = 17;
            inimigos[1].y = 17;

            inimigos[2].x = 32;
            inimigos[2].y = 464;

            inimigos[3].x = 464;
            inimigos[3].y = 464;

            if(!inimigos[0].alive){
                inimigos[0].alive = true;
            }
            if(!inimigos[1].alive){
                inimigos[1].alive = true;
            }
            if(!inimigos[2].alive){
                inimigos[2].alive = true;
            }
            if(!inimigos[3].alive){
                inimigos[3].alive = true;
            }
            

            //verifica se você esta clicando no primeiro botão do menu
            if(evento_primario.mouse.x > 152 && evento_primario.mouse.y > 187 && evento_primario.mouse.x < 364 && evento_primario.mouse.y < 222 ){
                if(evento_primario.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
                    if(evento_primario.mouse.button == ALLEGRO_MOUSE_BUTTON_LEFT) playing = true;
            }
            //verifica se você esta clicando no segundo botão do menu
            if(evento_primario.mouse.x > 152 && evento_primario.mouse.y > 259 && evento_primario.mouse.x < 364 && evento_primario.mouse.y < 294){
                if(evento_primario.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
                    if(evento_primario.mouse.button == ALLEGRO_MOUSE_BUTTON_LEFT) skin++;

            }
            //verifica se você esta clicando no terceiro botão do menu
            if(evento_primario.mouse.x > 152 && evento_primario.mouse.y > 331 && evento_primario.mouse.x < 364 && evento_primario.mouse.y < 366){
                if(evento_primario.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
                    if(evento_primario.mouse.button == ALLEGRO_MOUSE_BUTTON_LEFT) printf("Função em desenvolvimento!\nMenu de configurações não implementado!\n");
            
            }
            //verifica se você esta clicando no quarto botão do menu
            if(evento_primario.mouse.x > 152 && evento_primario.mouse.y > 403 && evento_primario.mouse.x < 364 && evento_primario.mouse.y < 438){
                if(evento_primario.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
                    if(evento_primario.mouse.button == ALLEGRO_MOUSE_BUTTON_LEFT) break;

            }
        }
       
        if(playing){
        /*recebe as teclas usadas no jogo e declara como true ou false*/
       
        if(mudou){

                inimigos[0].x = 464;
                inimigos[0].y = 32;
                inimigos[0].alive = true;
            
          
                inimigos[1].x = 17;
                inimigos[1].y = 17;
                inimigos[1].alive = true;
      
  
                inimigos[2].x = 32;
                inimigos[2].y = 464;
                inimigos[2].alive = true;

            if(node->next != 2){
                inimigos[3].x = 264;
                inimigos[3].y = 464;
                inimigos[3].alive = true;
            }else{
                inimigos[3].x = 464;
                inimigos[3].y = 464;
                inimigos[3].alive = true;
            }
        
        }else if(!mudou){
            if(!inimigos[0].alive){
                inimigos[0].x = 464;
                inimigos[0].y = 32;
                inimigos[0].alive = true;
            }
            if(!inimigos[1].alive){
                inimigos[1].x = 17;
                inimigos[1].y = 17;
                inimigos[1].alive = true;
            }
            if(!inimigos[2].alive){
                inimigos[2].x = 32;
                inimigos[2].y = 464;
                inimigos[2].alive = true;
            }
            if(!inimigos[3].alive){
                inimigos[3].x = 464;
                inimigos[3].y = 464;
                inimigos[3].alive = true;
            }
        }

        receber_teclas(&evento_primario, &ultima_tecla_precionada, &tecla); //recebe as teclas
      
        if(evento_primario.type == ALLEGRO_EVENT_KEY_DOWN) //verifica se alguma tecla foi precionada
        if(evento_primario.keyboard.keycode == ALLEGRO_KEY_R) node = node->next; //verifica se essa tecala é R se for muda para o proximo mapa.
       

        if(evento_primario.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){ //verifica se algum botão do mause foi precionado 
            if(evento_primario.mouse.button == ALLEGRO_MOUSE_BUTTON_LEFT){// se for o botão esquerdo faz esse bloco
                x_tiro = evento_primario.mouse.x;//guarda as coordenadas do mouse
                y_tiro = evento_primario.mouse.y;

                if(!tiro.ativo){//verifica se tem tiro na tela
                    //calcula a velocidade do tiro
                    float dx = x_tiro - p.eixox;
                    float dy = y_tiro - p.eixoy;
                    float distancia = hypot(dx, dy);

                    if(distancia != 0){ //se a distancia do tiro for diferente de 0 isso acontece
                        //define a posição do tiro no player
                        tiro.x = p.eixox + 16;
                        tiro.y = p.eixoy + 16;
                        //define a velocidade do tiro
                        tiro.velx = (dx/distancia)*VELOCIDADE_TIRO;
                        tiro.vely = (dy/distancia)*VELOCIDADE_TIRO;
                        //define o tiro como ativo
                        tiro.ativo = true;
                    }
                }
            }
        }
       
        if(tiro.ativo){//se tiro estiver ativo isso acontece
            //desloca o tiro no mapa
            if(tiro.x == p.eixox + 16 && tiro.y == p.eixoy +16){
                al_play_sample(disparo, 0.2, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                
            }
            tiro.x += tiro.velx;
            tiro.y += tiro.vely;

            if(colisao_tiro(tiro.x, tiro.y, array_map)){//verifca se o tiro bateu em alguma parede
                tiro.ativo = false; //desativa o tiro
                printf("Tiro sumiu na borada da tela\n");
            }
            if(tiro.x < 0 || tiro.x > largura || tiro.y < 0 || tiro.y > altura){ //verfica se p tiro bateu na borda do mapa
                tiro.ativo = false;//desativa o tiro
                printf("Tiro sumiu na borada da tela\n");
            }
        }


        if(evento_primario.type == ALLEGRO_EVENT_TIMER && al_is_event_queue_empty(queue)) {//verifica se a fila de eventos do jogo esta vazia
    
            node = criar_mapa(array_map, parede, mapa, chao, node, &p, &mudou);//cria e printa o mapa na tela
           
            printar_tela(&tecla, &p, &si, image, array_map, tiro, image_tiro, inimigos, inimigo_sprite); //um misto de funções que fica atualizando a tela a cada tick
            printar_inimigo(&p, inimigos, 4, array_map, inimigo_sprite, &tiro, &pontuacao);
            if(playing){
            al_draw_text(font, al_map_rgb(255, 255, 255), 20, 16, 0, ponto_texto);
            al_draw_text(font, al_map_rgb(255, 255, 255), 180, 16, 0, str);

            al_draw_text(font, al_map_rgb(255, 255, 255), 220, 16, 0, hp_texto);
            al_draw_text(font, al_map_rgb(255, 255, 255), 280, 16, 0, hp_num);
            }
            al_flip_display(); //pega tudo e mostra na tela
        }
        }else{
        
            printar_menu(ui, font, image, p);//printa o menu na tela
        }
    }
    printf("fim!\nTchau Tchau\nObrigado por Jogar!\3");
    al_destroy_all(disp, timer, queue, font, image, mapa, parede, ui, skin_set, skin_tamanho, skin_tiro, musica, disparo); //roda todas as finções de liberação da memoria!
    free_list(node); //mata a lista encadeada
}
