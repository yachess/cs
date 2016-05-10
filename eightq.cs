using System;
using System.Collections.Generic;

public class EightQueenPuzzle{
    static List<int> queens;
    static int num_tries=0;
    public static bool attack(int a, int b){
        if (a%8==b%8 || a/8==b/8 ||
            Math.Abs(a/8-b/8)==Math.Abs(a%8-b%8))
            return true;
        return false;
    }

    public static bool can_place(int newq, List<int> queens){
        foreach (int q in queens)
            if (attack(newq,q))
                return false;
        return true;
    }

    public static void print_queens(List<int> queens){
        for (int i=0;i<64;i++){
            if (queens.IndexOf(i)>=0)
                System.Console.Write(" Q");
            else
                System.Console.Write(" .");
            if (i%8==7)
                System.Console.WriteLine("");
        }
    }

    public static void solve(int row){
        if (row==8){
            num_tries ++;
            System.Console.WriteLine("Solution#:"+num_tries);
            print_queens(queens);
        } else {
            for (int c=0;c<8;c++){
                int newq = row*8+c;
                if (can_place(newq,queens)){
                    queens.Add(newq);
                    solve(row+1);
                    queens.RemoveAt(queens.Count-1);
                }
            }
        }
    }

    public static void Main(string[] args){
        queens = new List<int>();
        solve(0);
    }
}
