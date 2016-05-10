import java.util.*;
import java.util.Random;

class qsort{
    static int part(int[] ar, int l, int r){
        int i,j,t;
        int pv = ar[l];
        i = l;
        j = r+1;
        while(true){
            do i++; while (ar[i]<=pv && i<=r);
            do j--; while (ar[j]>pv);
            if (i>=j) break;
            t = ar[i]; ar[i]=ar[j]; ar[j]=t;
        }
        t=ar[l];ar[l]=ar[j];ar[j]=t;
        return j;
        
    }

    static void quicksort(int[] ar,int l, int r){
        int i;
        if (l>r) return;
        i = part(ar,l,r);
        quicksort(ar,l,i-1);
        quicksort(ar,i+1,r);
    }

    public static void  main(String args[]){
        int[] a;
        Random rand = new Random();
        a = new int[10000];    
        for (int i=0;i<10000;i++) 
            a[i] = rand.nextInt(10000);
        System.out.println("");
        quicksort(a,0,9998);
        System.out.println(" After sort:");
        for (int i=0;i<10000;i++) 
            System.out.print(a[i]);
    }
}
