#include <stdio.h>


int factorial(int n){
    if (n==0) return 1;
    return n * factorial(n-1);
}

int main(int argc, char** argv){
    int n = 5;
    printf("Factorial of %d: %d",n ,factorial(n));
    return 0;
}
