using System;
using System.Linq;
using System.Collections.Generic;

public struct NumFreq{
    public int num,freq;
    public NumFreq(int n,int f) {
        num = n;
        freq = f;
    }
}

class Sudoku {
    static int [,] bx_sqrs = new int[9,9]
        {{0,1,2,9,10,11,18,19,20},
        {3,4,5,12,13,14,21,22,23},
        {6,7,8,15,16,17,24,25,26},
        {27,28,29,36,37,38,45,46,47},
        {30,31,32,39,40,41,48,49,50},
        {33,34,35,42,43,44,51,52,53},
        {54,55,56,63,64,65,72,73,74},
        {57,58,59,66,67,68,75,76,77},
        {60,61,62,69,70,71,78,79,80}};
    static List<int> board = new List<int>();
    static List<int> constraints = new List<int>();
    static List<NumFreq> freq_table = new List<NumFreq>();

    static void print_list(List<int> l){
        for (int i=0;i<l.Count;i++)
            Console.Write(l[i]+",");
        Console.WriteLine("");
    }

    static void print_board(List<int> board){
        for (int i=0; i<81; i++){
            Console.Write(board[i]+" ");
            if (i%9==8)
                Console.Write("\n");
        } 
    }

    
    static IEnumerable<int> get_avail_sqrs(int num, int box){

        List<int> num_rows = new List<int>(),
                num_cols = new List<int>();

        for (int i=0;i<board.Count;i++)
            if (board[i]==num){
                num_rows.Add(i/9);
                num_cols.Add(i%9);
            }
/*
        print_list(num_rows);
        print_list(num_cols);
*/
        // Check if constraints square exists in box
        int constraints_sq = -1;
        for (int i=0;i<9;i++){
            var sq = bx_sqrs[box,i];
            if (constraints[sq] == num) {
                constraints_sq = sq;
                break;
            }
        }

        // Filter squares
        if (constraints_sq == -1) {
            for (int i=0;i<9;i++){
                var sq = bx_sqrs[box,i];
                if (board[sq] == 0 && constraints[sq] == 0 && 
                        (num_cols.IndexOf(sq%9) == -1) && 
                        (num_rows.IndexOf(sq/9) == -1))
                    yield return sq;
            }
        } else {
            if ((num_cols.IndexOf(constraints_sq%9)<0) && 
                    (num_rows.IndexOf(constraints_sq/9) == -1))
                yield return constraints_sq;
        }
    }
    
    public static void fill(int n, int box){
        if (box == 9){
            box = 0; n++;
        }
        if (n == 9) {
            print_board(board);
            return;
        }

        int num = freq_table[n].num;
        foreach (int sq in get_avail_sqrs(num, box)){
            board[sq] = num;
            fill(n, box + 1);
            board[sq] = 0;
        }
    }

    static void Main(string[] args){
        // build number frequency table
        
        if (args.Length == 0){
            Console.WriteLine("Usage: mono sudokusol.exe [puzzle]\n");
            return;
        }
        if (args[0].Length != 81){
            Console.WriteLine("Number of digits (must be 81)\n");
            return;
        }
        for (int i=0;i<args[0].Length;i++){
            int n = Int32.Parse(args[0][i]+"");
            constraints.Add(n);
            board.Add(0);
        }
        for (int i=1;i<10;i++)
            freq_table.Add(new NumFreq(i,0));       
        for (int i=0;i<constraints.Count;i++)
            if (constraints[i] !=0){
                NumFreq t = freq_table[constraints[i]-1];
                t.freq += 1;
                freq_table[constraints[i]-1] = t;
            }
        // sort frequency table

        for (int i=0;i<freq_table.Count;i++)
            for (int j=i;j<freq_table.Count;j++) {
                if (freq_table[i].freq < freq_table[j].freq){
                    NumFreq t = freq_table[i];
                    freq_table[i] = freq_table[j];
                    freq_table[j] = t;
                }
            }

//        Console.WriteLine(freq_table[4].freq);
        fill(0,0); 
    }
}
