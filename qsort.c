#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int part(int *ar, int l, int r){
    int i,j,t;
    int pv = ar[l];
    i = l;
    j = r+1;
    while(1){
        do i++; while (ar[i]<=pv && i<=r);
        do j--; while (ar[j]>pv);
        if (i>=j) break;
        t = ar[i]; ar[i]=ar[j]; ar[j]=t;
    }
    t=ar[l];ar[l]=ar[j];ar[j]=t;
    return j;
    
}

void quicksort(int* ar,int l, int r){
    int i;
    if (l>r) return;
    i = part(ar,l,r);
    quicksort(ar,l,i-1);
    quicksort(ar,i+1,r);
}

int main(int argc, char** argv){
    int i;  
    int a[100];
    
    srand(time(NULL));
    printf(" Before sort\n");
    for (i=0;i<100;i++) {
        a[i] = rand() % 100;
        printf(" %d",a[i]);
    }   
    printf("\n");

    quicksort(a,0,99);

    printf(" After sort:");
    for (i=0;i<100;i++) 
        printf(" %d", a[i]);
    return 0;
}
