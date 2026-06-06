#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H



typedef const char* string;

typedef struct player{//typedef para definir o player dps vai ter um de inimigos
    //posição e deslocamento do player
    int eixox; 
    int eixoy;
    int speed;
    //hp do player
    int hp;
    //tamanho
    int tamanho;
}player;


typedef struct maps{ //define algumas variaveis de criação de mapa
    int eixox;
    int eixoy;
    int largura;
    int altura;
}Chao;

typedef struct node{
    player* player;
    FILE* mapa;
    char l;
    struct node* next; 
}Node;


typedef struct teclas{ //struct que armazena se as teclas estão sendo precionadas ou não
    bool w;
    bool d;
    bool s;
    bool a;
    bool t1;
    bool t2;
    bool t3;
    bool t4;
    bool t0;
    bool r;
}teclas;


typedef struct{
    float x, y;
    float velx, vely;
    bool ativo;
} tiro;



#endif