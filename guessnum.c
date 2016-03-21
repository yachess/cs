#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv){
    int x;
    srand (time(NULL));
    x = rand() % 100;
    
    while (1){
        int n;
        printf("Guess my number:");
        scanf("%d",&n);
        if (n>x)
            printf("too large.\n");
        else if (n<x)
            printf("too small.\n");
        else
            break;
    } 
    printf( "Correct!\n");
    return 0;
}
