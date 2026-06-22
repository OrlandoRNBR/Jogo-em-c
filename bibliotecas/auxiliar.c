#include "auxiliar.h"
#include "player.h"


void download_file(string url, string file_name){
     curl_global_init(CURL_GLOBAL_DEFAULT);// da o initi na api
   FILE *outfile = fopen(file_name, "wb"); // abre o arquivo
   assert(outfile != NULL); // verifica se ele foi aberto
  
   //cria a arvore de dados
    CURL *curl_handle = curl_easy_init(); 
    curl_easy_setopt(curl_handle, CURLOPT_URL, url);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, fwrite);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, outfile);


    CURLcode res = curl_easy_perform(curl_handle);
    if (res != CURLE_OK)
         fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

    curl_easy_cleanup(curl_handle);
    fclose(outfile);
    curl_global_cleanup();

}

cJSON* read_json(string file_name){
    FILE* f = fopen(file_name, "rb");//abre o arquivo
    assert(f != NULL); //verifica se ele foi aberto

    fseek(f, 0, SEEK_END); // vai até o final do arquivo
    long file_size = ftell(f); // armazena o tamaho do arquivo
    rewind(f); // volta o cursor para o começo
    char* buffer = malloc(file_size + 1); //armazena um bafer
    fread(buffer, 1, file_size, f); //coloca todo o texto do arquivo para o buffer
    fclose(f);//fecha o arquivo

    buffer[file_size] = '\0';//adiciona um \0 no final do texto importado do arquivo

    cJSON* json = cJSON_Parse(buffer);//armazena as informações do arquivo
    free(buffer); // da um free no buffer
    return json;//retorna o json
}

void process_json(string file_name){
   cJSON *json = read_json(file_name);//aramzena as informações carregadas em um
   assert(json != NULL);

   cJSON *cries = cJSON_GetObjectItem(json, "cries");
   assert(cries != NULL);

   cJSON *latest = cJSON_GetObjectItem(cries, "latest");
   assert(latest != NULL);

   const char* url_crie = latest->valuestring;
   const char* cries_filename = url_crie + strlen(CRIES_PATH);//+strlen("latest/");
   printf("arquivo de audio: %s\n", cries_filename);
   download_file(url_crie, cries_filename);
   cJSON_Delete(json);
}


Node* new_node(Node* next, int l, string endereco){ //cria um nó na lista encadeada
    Node* node = malloc(sizeof(Node));
    node->l = l;
    node->endereco  = endereco;
    node->next = next;

    return node;
}

Node* insert_node(Node* node, int l, string endereco){//cria um nó e eoncaixa ele na lista circular
   if(node == NULL){
       Node* n = new_node(NULL, l , endereco);
       n->next = n;
       return n;
   }

   return node->next = new_node(node->next, l, endereco);
}

Node* remove_node_after(Node* node){ //remove o proximo nó
   if(node == NULL)
       return NULL;

    if(node->next == NULL){
       free(node);
       return NULL;
   }
   if(node->next == node){
       free(node);
       return NULL;
   }

   Node* p = node->next;
   node->next = p->next;

   free(p);
   return node;
}

void free_list(Node* node) {//remove todos os nós
   while(node != NULL)
       node = remove_node_after(node);
}


void al_init_all(bool * audio){
    if(al_init()) printf("Allegro inicializado\n"); //inicia a biblioteca do alegro

    if(al_init_font_addon()) printf("allegro font inicializado\n"); //prepara a memória para receber fontes costumizadas

    if(al_init_ttf_addon()) printf("allegro ttf inicilisado\n");// permite o alegro renderizar fontes de arquivos ttf

    if(al_init_image_addon()) printf("allegro image inicialisado\n"); //permite a biblioteca alegro renderizar bitmaps

    al_install_keyboard(); //informa o sistema operacional que o programa vai capiturar teclas
 
    al_install_mouse(); //informa o codigo que ele precisa olhar as informações do mouse

    if (al_init_primitives_addon()) printf("allegro primitives inicialisado\n");

    // Tenta inicializar o codec de áudio padrão
if (al_init_acodec_addon()) {
    printf("Codec de audio inicializado com sucesso.\n");
}
// Tenta inicializar o instalador de áudio
    if (al_install_audio()) {
        printf("Sistema de som instalado com sucesso.\n");
    
    // SÓ RESERVA OS SAMPLES SE O SISTEMA DE SOM FOI INSTALADO!
        if (al_reserve_samples(5)) {
            printf("Canais de audio reservados com sucesso.\n");
        } else {
            printf("AVISO: Nao foi possivel reservar os canais de audio.\n");
        }
    } else {
        printf("[AVISO CRITICO]: O PC nao possui dispositivo de som ativo. O jogo rodara SEM AUDIO.\n");
        *audio = false;
    }
    fflush(stdout);
}

void al_destroy_all(ALLEGRO_DISPLAY* disp, ALLEGRO_TIMER* timer, ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_FONT* font, ALLEGRO_BITMAP* image, ALLEGRO_BITMAP* mapa, ALLEGRO_BITMAP* parede[], ALLEGRO_BITMAP* ui, ALLEGRO_BITMAP* skin[], int skin_tamanho, ALLEGRO_BITMAP* skin_tiro[],ALLEGRO_AUDIO_STREAM* musica, ALLEGRO_SAMPLE* disparo){
    al_destroy_display(disp); //destroi a janela e libera a memoria
    al_destroy_timer(timer);// destroi o relogio e libera a memoria
    al_destroy_event_queue(queue);//destroi a fila de eventos e libera da memoria
    al_destroy_font(font); //destroi as fontes e libera da memoria
    al_destroy_audio_stream(musica);
    al_destroy_sample(disparo);
    al_destroy_bitmap(image); //destroi a imagem e libera da memoria
    al_destroy_bitmap(mapa);
    al_destroy_bitmap(ui);
    for(int i = 0; i < 10; i++){ //limpa todos os indices de parede
        al_destroy_bitmap(parede[i]);
    }
    for(int i = 0; i < skin_tamanho; i++){ //limpa todos os indices de parede
        al_destroy_bitmap(skin[i]);
    }
    for(int i = 0; i < skin_tamanho; i++){ //limpa todos os indices de parede
        al_destroy_bitmap(skin_tiro[i]);
    }
    free(parede);
    free(skin);
    free(skin_tiro);
}

void al_register_all_event_source(ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_TIMER* timer, ALLEGRO_DISPLAY* disp){
//diz para o queue para prestar atenção nos imputs do teclado
    al_register_event_source(queue, al_get_keyboard_event_source());
    //diz para o queue prestar atenção na tela e verificar as informaçẽos da teça
    al_register_event_source(queue, al_get_display_event_source(disp));
    //diz para a fila prestar atenção nos ticks
    al_register_event_source(queue, al_get_timer_event_source(timer));
    
    al_register_event_source(queue, al_get_mouse_event_source());
}
