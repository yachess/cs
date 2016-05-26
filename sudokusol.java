import java.util.ArrayList;
import java.util.Collections;

public class sudokusol{

    public class NumFreq {
        public int num, freq;
        public NumFreq (int n, int f) {
            this.num = n;
            this.freq = f;
        }
    };

    static int[][] bx_sqrs = {{0,1,2,9,10,11,18,19,20},
         {3,4,5,12,13,14,21,22,23},
         {6,7,8,15,16,17,24,25,26},
         {27,28,29,36,37,38,45,46,47},
         {30,31,32,39,40,41,48,49,50},
         {33,34,35,42,43,44,51,52,53},
         {54,55,56,63,64,65,72,73,74},
         {57,58,59,66,67,68,75,76,77},
         {60,61,62,69,70,71,78,79,80}};

    static int[] board = new int[81],constraints = new int[81];
    static ArrayList<NumFreq> freq_table = new ArrayList<NumFreq>(); 
    static void print_board(int[] board){
        System.out.println("");
        for (int i=0;i<board.length;i++){
            System.out.print(board[i]+" ");
            if (i%9==8)
                System.out.println("");
        }
    }

    static boolean member(int e,int[] lst){
        for (int sq: lst)
            if (sq == e)
                return true;
        return false;
    }
         
    static ArrayList<Integer> get_avail_sqrs(int num, int box){
        int[] num_rows = {-1,-1,-1,-1,-1,-1,-1,-1,-1};
        int[] num_cols = {-1,-1,-1,-1,-1,-1,-1,-1,-1};
        int idx = 0;
        for (int i=0; i<board.length; i++){
            if (board[i] == num){
                num_rows[idx] = i/9;
                num_cols[idx] = i%9;
                idx++;
            }
        }

        int constraints_sq = -1;
        for (int sq: bx_sqrs[box]){
            if (constraints[sq] == num) {
                constraints_sq = sq;
                break;
            }
        }
       
        ArrayList<Integer> avail_sqrs = new ArrayList<Integer>(); 
        if (constraints_sq == -1){
            for (int sq: bx_sqrs[box])
                if (board[sq] == 0 &&  constraints[sq] == 0 &&
                    !(member(sq/9, num_rows)) && !(member(sq%9, num_cols))) {
                        avail_sqrs.add(sq);
                    }
        } else {
            if (!(member(constraints_sq/9, num_rows)) && 
                !(member(constraints_sq%9, num_cols))) {
                    avail_sqrs.add(constraints_sq);
            }
        }
        return avail_sqrs;
    }

    static void fill(int n, int box){
        if (box == 9) {
            box = 0;  n++;
        }
        if (n == 9){
            print_board(board);
            return;
        }
        int num = freq_table.get(n).num;
        for (int sq: get_avail_sqrs(num, box)) {
            //System.out.println(num+"-"+box);
            board[sq] = num;
            fill(n, box + 1);
            board[sq] = 0;
        }
    } 

    public sudokusol(){
        for (int i=1;i<10;i++){
            NumFreq nf = new NumFreq(i,0);
            freq_table.add(nf);
        }
        for (int i=0;i<constraints.length;i++)
            if (constraints[i] >0)
                freq_table.get(constraints[i]-1).freq++;
        //sort freq_table by frequency.
        for (int i=0;i<freq_table.size();i++)
            for (int j=i;j<freq_table.size();j++)
                if (freq_table.get(i).freq < freq_table.get(j).freq)
                    Collections.swap(freq_table,i,j);
    }

    public static void main(String[] args){
        if (args.length <1) {
            System.out.println("Usage:java sudokusol [puzzle].\n");
            return;
        }
        if (args[0].length() != 81) {
            System.out.println("Puzzle length must be 81");
            return;
        }

        for (int i=0; i<args[0].length();i++)
            constraints[i] = args[0].charAt(i)-48;
        sudokusol sol = new sudokusol();
        
        sol.fill(0,0);
    }
}
