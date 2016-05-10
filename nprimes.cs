using System;
public class Primes {
    static bool isprime(int n){
        if (n<=1) return false;
        if (n==2) return true;
        if (n%2==0) return false;
        int rt = (int)Math.Sqrt(n)+1;
        for (int i=rt;i>1;i--)
            if (n%i==0) 
                return false;
        return true;
    }
    public static void Main(string[] args){
        int cnt = 0;
        for (int i=0;i<10000;i++)
            if (isprime(i)) cnt++;
        System.Console.WriteLine("Prime number to 10000:"+cnt);
    }
}
