#include <stdio.h>

int main (void){
    char teste [16][64];

    for(int i = 0; i < 16;i++){
        for(int j = 0; j < 64; j++){
            teste [i][j] = '\0';
        }
    }
    teste [2][26] = 'u';
    printf("Matriz cheia\n");
    for (int i = 0; i < 16;i++ ){
        for(int j = 0; j < 64;j++){
            printf("%c", teste[i][j]);
        }
        printf("\n");
    }

    return 0;
}