#ifndef AUXILIAR_H
#define AUXILIAR_H

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h> 
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>
#include <stdbool.h>
#include <math.h>
#include "player.h"
#include "maps.h"
#include "estructuras.h"

#define CRIES_PATH "https://raw.githubusercontent.com/PokeAPI/cries/main/cries/pokemon/latest/"

void download_file(string url, string file_name);

cJSON* read_json(const char* filename);

void process_json(const char* filename);

Node* new_node(Node* next, int l, string endereco);

Node* insert_node(Node* node, int l, string endereco);

Node* remove_node_after(Node* node);

void free_list(Node* node);

void al_init_all();

void al_destroy_all(ALLEGRO_DISPLAY* disp, ALLEGRO_TIMER* timer, ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_FONT* font, ALLEGRO_BITMAP* image, ALLEGRO_BITMAP* mapa, ALLEGRO_BITMAP* parede[], ALLEGRO_BITMAP* ui, ALLEGRO_BITMAP* skin[],int skin_tamanho, ALLEGRO_BITMAP* skin_tiro[]);

void al_register_all_event_source(ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_TIMER* timer, ALLEGRO_DISPLAY* disp);



#endif