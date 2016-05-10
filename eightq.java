
import java.util.*;

public class eightq{
    static int tries=0;
    static ArrayList<Integer> queens = new ArrayList<Integer>();

    static boolean attack(int a, int b){
        if ((a%8==b%8) || (a/8==b/8) ||
            Math.abs(a/8-b/8)==Math.abs(a%8-b%8)) return true;
        return false;
    }

    static boolean can_place(int newq,ArrayList<Integer> queens){
        for (int i=0;i<queens.size();i++){
            if (attack(newq,queens.get(i)))
                return false;
        }
        return true;
    }
    static void print_queens(ArrayList<Integer> queens){
        for (int i=0;i<64;i++){
            if (queens.indexOf(i)>=0)
                System.out.print(" Q");
            else
                System.out.print(" .");
            if (i%8==7)
                System.out.println("");
        }
    }

    static void solve(int row){
        if (row == 8) {
            tries++;
            System.out.println("Solution#:"+tries);
            print_queens(queens);
        }else{

            for (int c=0;c<8;c++){
                int newq = row*8+c;
                if(can_place(newq,queens)){
                    queens.add(newq);
                    solve(row+1);
                    queens.remove(queens.size()-1);
                }
            }
        }
    }

    public static void main(String args[]){
        solve(0);
    }
}
