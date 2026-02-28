#include <stdio.h>
#include <stdlib.h>


int main (void){
    char teste [16][64], tirox = 0, tiroy = 8;

    for(int i = 0; i < 16;i++){
        for(int j = 0; j < 64; j++){
            teste [i][j] = ' ';
        }
    }
    printf("Matriz cheia\n");

    while(tirox != 64){
        system("clear");
        teste [tiroy][tirox] = 'o';

        if(tirox > 0){
            teste [tiroy][tirox-1]= ' ';
        }
    
        for (int i = 0; i < 16;i++ ){
            for(int j = 0; j < 64;j++){
                printf("%c", teste[i][j]);
            }
            printf("\n");
        }
        printf("valor x = %d\n", tirox);
        tirox++;
    
    }
    return 0;
}