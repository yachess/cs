#include <stdio.h>
#include <stdlib.h>
#include <memory.h>


typedef struct {
    int num;
    int cnt;
} number,*number_p;

const int bx_sqrs[9][9] = {
    {0,1,2,9,10,11,18,19,20},
    {3,4,5,12,13,14,21,22,23},
    {6,7,8,15,16,17,24,25,26},
    {27,28,29,36,37,38,45,46,47},
    {30,31,32,39,40,41,48,49,50}, 
    {33,34,35,42,43,44,51,52,53}, 
    {54,55,56,63,64,65,72,73,74}, 
    {57,58,59,66,67,68,75,76,77}, 
    {60,61,62,69,70,71,78,79,80}};

number_p freq_table;
/* constraints means squares that are given as problem */
int constraints[81];
int num_tries=0;

void b_sort(number_p f_table){
    int i,j;
    number tmp;
    for (i=0;i<9;i++)
    for (j=i+1;j<9;j++)
        if (f_table[i].cnt<f_table[j].cnt){
            tmp = f_table[i];
            f_table[i] = f_table[j];
            f_table[j] = tmp;
        }
}
    
void print_board(int* board){
    int i;
    printf("\n");
    for (i=0;i<81;i++){
        printf("%d ",board[i]);
        if (i%9==8)
            printf("\n");
    }
}

void print_sqrs(int* sqrs){
    int i=0;
    while (i<9 && sqrs[i]!=-1){
        printf("%d ",sqrs[i]);
        i++;
    }
    printf("\n");
}

int member(int n, int* lst){
    int i=0;
    while(lst[i]!=-1 && i<9){
        if(lst[i]==n) return 1;
        i++;
    }
    return 0;
}

void get_avail_sqrs(int* board, int num, int bx, int *avail_sqrs){
    int i, constraints_sq, idx;
    int num_rows[9] = {-1,-1,-1,-1,-1,-1,-1,-1,-1};
    int num_cols[9] = {-1,-1,-1,-1,-1,-1,-1,-1,-1};
    int sq;

    for (i=0; i<9; i++)
        avail_sqrs[i] = -1;

    
    idx = 0;
    for(i=0; i<81; i++){
        if(board[i] == num){
            num_rows[idx] = i/9;
            num_cols[idx] = i%9;
            idx++;
        }
    }

    constraints_sq = -1;
    i=0;
    while( bx_sqrs[bx][i] != -1 && i < 9 ){
        if (constraints[bx_sqrs[bx][i]] == num){
            constraints_sq = bx_sqrs[bx][i];
            break;
        }
        i++;
    }
    
    if (constraints_sq == -1){
        idx=0;
        i=0;
        while ( bx_sqrs[bx][i] !=-1 && i < 9){
            sq = bx_sqrs[bx][i];
            if (board[sq] == 0 && constraints[sq] == 0 &&\
                !(member(sq%9, num_cols)) && \
                !(member(sq/9, num_rows))){
                avail_sqrs[idx] = sq;
                idx++;
            }
            i++;
        }
    }else{
        if (!(member(constraints_sq%9, num_cols)) && \
            !(member(constraints_sq/9, num_rows))) 
                avail_sqrs[0] = constraints_sq;
    }
}

int solve(int* board, int n, int bx){
    int i,num;
    int avail_sqrs[9];
    int sq;
    if (bx==9) {
        n++;
        bx=0;
    }
    if (n==9) {
        print_board(board);
    }
    num = freq_table[n].num;
    get_avail_sqrs(board,num,bx,avail_sqrs);
    i=0;
    while(avail_sqrs[i]!=-1 && i<9){
        sq = avail_sqrs[i];
        board[sq] = num;
        if (solve(board, n, bx + 1))
            return 1;
        board[sq] = 0;
        i++;
    }
    return 0;
}


int main (int argc, char** argv){
    int i;
    int board [81]={0,};

    if (argc != 2){
        printf("Usage: %s [puzzle]\n",argv[0]);
        return 1;
    }
    if (strlen(argv[1])!=81){
        printf("string != 81\n");
        return 1;
    }

    freq_table = malloc(sizeof(number)*9);
  
    /* iterate thru 81 numbers */
    for (i=0;i<81;i++){
       constraints[i] = argv[1][i]-'0'; 
    }
    /* frequency table */
    for (i=0;i<9;i++){
        freq_table[i].num = i+1;
        freq_table[i].cnt = 0;
    }
    for (i=0;i<81;i++)
        if (constraints[i]!=0)
            freq_table[constraints[i]-1].cnt++;
    
    /* sort frequency table */
    /*b_sort(freq_table);*/
    
    solve(board,0,0);  
    return 0;        
}
