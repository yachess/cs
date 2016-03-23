#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SAMERANK(a,b) (a/8 == b/8)
#define SAMEFILE(a,b) (a%8 == b%8)
#define INBOUNDS(a) (a>=0 && a<64)

typedef struct {
    unsigned long bb[2];   /* black/white bitboard */
}*Pos,Position;

void print_pos(Pos p){
    int i;
    for (i=0;i<64;i++) {
        if (p->bb[1]&1L<<i)
            printf(".O");
        else if (p->bb[0]&1L<<i)
            printf(".X");
        else
            printf("._");
        if (i%8==7)
            printf("\n");
    }
}

void init_pos(Pos p){
    p->bb[0] = 0L; p->bb[1] = 0L;
}

short* get_legal_moves(Pos p,int t){
    short *moves;
    int cnt = 0;
    int i,j;
    int opp = t^1;  
    long empt = ~(p->bb[1]|p->bb[0]);
 
    moves = malloc(sizeof(short)*32);
    for (i=0;i<32;i++)
        *(moves+i) = -1;
    for (i=0;i<64;i++){
        if (~empt & 1L<<i)  /* skip allocated square */
            continue;
        /* east */
        j=i;
        do j++; while((i/8==j/8) && p->bb[opp]&1L<<j);
        if ((i/8==j/8) && p->bb[t]&1L<<j && j-i>1){
            moves[cnt++]=i;
            continue;
        }
        j=i;
        do j+=9; while(INBOUNDS(j) && (i%8<j%8) && p->bb[opp]&1L<<j);
        if (INBOUNDS(j) && (i%8<j%8) && p->bb[t]&1L<<j && j-i>9){
            moves[cnt++]=i;
            continue;
        }
        j=i;
        do j+=8; while(INBOUNDS(j) && p->bb[opp]&1L<<j);
        if (INBOUNDS(j) && p->bb[t]&1L<<j && j-i>8){
            moves[cnt++]=i;
            continue;
        }
        j=i;
        do j+=7; while(INBOUNDS(j) && (i%8>j%8) && p->bb[opp]&1L<<j);
        if (INBOUNDS(j) &&(i%8>j%8) && p->bb[t]&1L<<j && j-i>7){
            moves[cnt++]=i;
            continue;
        }
        j=i;
        do j--; while((i/8==j/8) && p->bb[opp]&1L<<j);
        if ((i/8==j/8) && p->bb[t]&1L<<j && i-j>1){
            moves[cnt++]=i;
            continue; 
        }
        j=i;
        do j-=9; while(INBOUNDS(j) && (i%8>j%8) && p->bb[opp]&1L<<j);
        if (INBOUNDS(j) && (i%8>j%8) && p->bb[t]&1L<<j && i-j>9){
            moves[cnt++]=i;
            continue;
        }
        j=i;
        do j-=8; while(INBOUNDS(j) && p->bb[opp]&1L<<j);
        if (INBOUNDS(j) && p->bb[t]&1L<<j && i-j>8){
            moves[cnt++]=i;
            continue; 
        }
        j=i;
        do j-=7; while(INBOUNDS(j)&&(i%8<j%8) && p->bb[opp]&1L<<j);
        if (INBOUNDS(j) && (i%8<j%8) && p->bb[t]&1L<<j && i-j>7){
            moves[cnt++]=i;
            continue;
        }
    }
    printf("legal move size:%d\n",cnt);
    return moves;
}

int flip (Pos p,int sq,int t){
    int i=sq,j,k;
    int opp=t^1;
    j=i;
    do j++; while((i/8==j/8) && p->bb[opp]&1L<<j);
    if ((i/8==j/8) && p->bb[t]&1L<<j && j-i>1){
        for (k=i+1;k<j;k++){
            p->bb[t] |= 1L<<k;
            p->bb[opp] &= ~(1L<<k);
        }
    }
    j=i;
    do j+=9; while((i%8<j%8) && p->bb[opp]&1L<<j);
    if ((i%8<j%8) && p->bb[t]&1L<<j && j-i>9){
        for (k=i+9;k<j;k+=9){
            p->bb[t] |= 1L<<k;
            p->bb[opp] &= ~(1L<<k);
        }
    }
    j=i;
    do j+=8; while(INBOUNDS(j) && p->bb[opp]&1L<<j);
    if (INBOUNDS(j) && p->bb[t]&1L<<j && j-i>8){
        for (k=i+8;k<j;k+=8){
            p->bb[t] |= 1L<<k;
            p->bb[opp] &= ~(1L<<k);
        }
    }
    j=i;
    do j+=7; while((i%8>j%8) && p->bb[opp]&1L<<j);
    if ((i%8>j%8) && p->bb[t]&1L<<j && j-i>7){
        for (k=i+7;k<j;k+=7){
            p->bb[t] |= 1L<<k;
            p->bb[opp] &= ~(1L<<k);
        }
    }
    j=i;
    do j--; while((i/8==j/8) && p->bb[opp]&1L<<j);
    if ((i/8==j/8) && p->bb[t]&1L<<j && i-j>1){
        for (k=i-1;k>j;k--){
            p->bb[t] |= 1L<<k;
            p->bb[opp] &= ~(1L<<k);
        }
    }
    j=i;
    do j-=9; while((i%8>j%8) && p->bb[opp]&1L<<j);
    if ((i%8>j%8) && p->bb[t]&1L<<j && i-j>9){
        for (k=i-9;k>j;k-=9){
            p->bb[t] |= 1L<<k;
            p->bb[opp] &= ~(1L<<k);
        }
    }
    j=i;
    do j-=8; while(INBOUNDS(j) && p->bb[opp]&1L<<j);
    if (INBOUNDS(j) && p->bb[t]&1L<<j && i-j>8){
        for (k=i-8;k>j;k-=8){
            p->bb[t] |= 1L<<k;
            p->bb[opp] &= ~(1L<<k);
        }
    }
    j=i;
    do j-=7; while((i%8<j%8) && p->bb[opp]&1L<<j);
    if ((i%8<j%8) && p->bb[t]&1L<<j && i-j>7){
        for (k=i-7;k>j;k-=7){
            p->bb[t] |= 1L<<k;
            p->bb[opp] &= ~(1L<<k);
        }
    }
}

int make(Pos p,int t,int sq){
    int i;
    short* lmoves =  get_legal_moves(p,t);
    int moved = 0;

    for (i=0;i<32;i++){
        if (*(lmoves+i)==-1)
            break;    
        if (*(lmoves+i)==sq){
            p->bb[t] |= 1L << sq;
            flip(p,sq,t);
            moved = 1;
            break;
        }
    }
    free(lmoves);
    return moved;
}

int get_comp_move(Pos p,int t){
    return -1;
}

short get_random_move(Pos p,int t){
    int i;
    short* lmoves = get_legal_moves(p,t);
    i=0;
    while (lmoves[i]!=-1 && i<32) i++;
    return lmoves[rand()%i];
    free(lmoves);
}
/*
int find_best_move(Pos p,int t,ply pl){
    int max = -10000;
    if (pl==0) 
        return eval(p)
        v = get_legal_moves(p,t)
        np = copy(p);
        for (all moves
    }
}
*/

int main(int argc, char** argv){
    char s[2];
    int x,y;    /* rank and file */
    int t=0;    /* turn (color)*/
    Pos p = malloc(sizeof(Position));
    short* lmoves;
    short sq = -1;
    short autop[] = {0,1};
    short pass_cnt = 0;

    srand(time(NULL));
    init_pos(p);

    printf("size of pos:%lu\n",sizeof(Position));

    p->bb[0] |= 1L<<27;
    p->bb[1] |= 1L<<28;
    p->bb[1] |= 1L<<35;
    p->bb[0] |= 1L<<36;
    print_pos(p);
    
    while(1){
        if (autop[t])
            sq = get_random_move(p,t);
        else{
            printf("Make move:");
            scanf("%s",s);
            if (*s=='q') break;
            x = *s-'a';
            y = '8'-*(s+1);
            printf("x=%d, y=%d\n",x,y);
            sq = y*8+x;
        }
        if(make(p,t,sq)){
            print_pos(p);
            t^=1;
            pass_cnt=0;
        }else
            printf("Illegal move!\n");
    }

    return 0;
}
