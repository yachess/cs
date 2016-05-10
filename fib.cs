using System;
public class fibonacci {
    static int fib(int n){
        if (n==0) 
            return 0;
        if (n==1)
            return 1;
        return fib(n-1)+fib(n-2);
    }
    public static void Main(string[] args){
        System.Console.WriteLine(fib(30));
    }
}
