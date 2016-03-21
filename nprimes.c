/* 
 * get number of primes smaller than 1000000
 *
 * compile with -lm option to user math library
 *
 * */

#include <stdio.h>
#include <math.h>

int isprime(int n){
    int i;
    if (n<=1) return 0;
    if (n==2) return 1;
    if (n%2==0) return 0;
    for (i=sqrt(n)+1;i>1;i--){
        if (n%i==0)
            return 0;
    }
    return 1;
}

int main(int argc, char** argv){
    int mx = 10000000;     /* mx=8000 => cnt=1007 */
    int i;
    int cnt = 0;

    for (i=0;i<mx;i++){
        if (isprime(i))
            cnt++;
    }

    printf("Number of primes smaller than %d:%d",mx,cnt);
    return 0;
}
