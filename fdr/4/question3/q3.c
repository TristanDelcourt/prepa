#include <stdio.h>

int main(void){
    int t[8] = {1, 2, 4, 8, 12, 56, -3, 19};

    for(int i = 0; i<8; i++){
        printf("%d ", t[i]);
    }
    printf("\n");
    
    return 0;
}