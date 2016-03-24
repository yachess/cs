#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint64_t factorial(uint64_t n){
    if (n<=1) return 1;
    return n * factorial(n-1);
}

int main(int argc, char** argv){
    int n;
    if (argc!=2){
        printf("Usage: %s n\n",argv[0]);
        return 1;
    }
    n = (int)atoi(argv[1]);
    printf("Factorial of %d: %lu\n",n ,factorial(n));
    return 0;
}
