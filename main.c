#include <stdio.h>
#include <stdlib.h>
#include <termios.h> //biblioteca que permite peagar o caractere sem ter que apertar enter e sem mostrar o caractere precionado.
#include <unistd.h> //é essa biblioteca que tras a fonção de ler as teclas precionadas e define STDIN_FILENO como pradrão
#include <fcntl.h> //impede o jogo de travar caso não receba nenhum comando do teclado



void setmode (int enable){

    static struct termios oldt, newt; //struct da biblioteca termios

    if (enable){
        tcgetattr(STDIN_FILENO, &oldt); //pega a config atual do terminal e salva

        newt = oldt;//copia essas informações para 'newt' para não alterar o terminal padrão

        newt.c_lflag &= ~(ICANON | ECHO);
    /*modifica a c_lflag ICANOM desativa o modo
    canonico(não precisa preciona enter) e 
    ECHO que desativa a exibição da tecla precionada. */

        tcsetattr (STDIN_FILENO, TCSANOW, &newt); // ativa as cofigurações feitas assima.
    }else{
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt); //restalra ao normal
    }
}


int main (void){
    char mapa [16][64]; //matriz que representa o mapa do jogo
    int coordx = 32, coordy = 8; //coordenados do player definidas no meio para o inicio do jogo
    char tecla; //variavel que vai armazenar as teclas precionadas

    setmode(1); //ativa o modo especial no inicio

    while(1){// looping princiopal

        //looping que preenche o mapa de espaços
        for(int i = 0; i < 16;i++){
            for(int j = 0; j < 64; j++){
                mapa [i][j] = ' ';
            }
        }


       if(read(STDIN_FILENO, &tecla, 1)>0){ // esse bloco verifica cada tecla precionada para definir suas funções
            if(tecla == 'q') break; //finaliza o jogo
            if(tecla == 'w' && coordy > 0) coordy--; // sobe
            if(tecla == 's' && coordy < 15) coordy++;// desce
            if(tecla == 'a' && coordx > 0) coordx--; //vai para a esquerda
            if(tecla == 'd' && coordx < 63) coordx++;//vai para a direita
         }

        mapa [coordy][coordx] = 'T'; // define onde o player esta no mapa (player está representado pelo T)

        printf("\033[H"); // Comando ANSI para voltar o cursor ao topo (melhor que clear)   
        
        //esse bloco mostra o estado atual do mapa a cada frame, os printfs definem uma borda visivel em cima e em baixo
        printf("_________________________________________________________________\n");
        for (int i = 0; i < 16;i++ ){
            putchar('|'); //coloca o caractere | na borda esquerda do mapa
            for(int j = 0; j < 64;j++){
                putchar(mapa[i][j]); //imprime os caracteres do mapa
            }
            putchar('|'); //coloca o caractere | na borda direita do mapa
            putchar('\n');//pula linha
        }
        printf("_________________________________________________________________\n");

        printf("valor x = %d, y = %d | precione 'q' para sair \n", coordx, coordy); // mostra as coordenadas do player
        //e que se precionar q o jogo acaba
        
        usleep(30000); //da 30ms de pausa para não consumir 100% da cpu
    }

    setmode(0); // restaura o terminal
    return 0;
}