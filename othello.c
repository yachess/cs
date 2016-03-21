#include <stdio.h>
#include <stdlib.h>

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
        do j++; while(SAMERANK(i,j) && p->bb[opp]&1L<<j);
        if (SAMERANK(i,j) && p->bb[t]&1L<<j && j-i>1){
            moves[cnt]=i;
            cnt++;
            continue;
        }
        j=i;
        do j--; while(SAMERANK(i,j) && p->bb[opp]&1L<<j);
        if (SAMERANK(i,j) && p->bb[t]&1L<<j && i-j>1){
            moves[cnt]=i;
            cnt++;
            continue; 
        }
        j=i;
        do j+=8; while(SAMEFILE(i,j) && p->bb[opp]&1L<<j);
        if (INBOUNDS(j) && p->bb[t]&1L<<j && j-i>8){
            moves[cnt]=i;
            cnt++;
            continue;
        }
        j=i;
        do j-=8; while(SAMEFILE(i,j) && p->bb[opp]&1L<<j);
        if (INBOUNDS(j) && p->bb[t]&1L<<j && i-j>8){
            moves[cnt]=i;
            cnt++;
            continue; 
        }
    }
    printf("legal move size:%d\n",cnt);
    return moves;
}

int flip (Pos p,int sq){
}

int make(Pos p,int t,int sq){
    int i;
    short* lmoves =  get_legal_moves(p,t);
    int moved = 0;

    for (i=0;i<32;i++){
        if (*(lmoves+i)==-1) break;    
        if (*(lmoves+i)==sq){
            p->bb[t] |= 1L << sq;
            print_pos(p);
            flip(p,i);
            moved = 1;
        }
    }
    free(lmoves);
    return moved;
}

int main(int argc, char** argv){
    char s[2];
    int x,y;   /* rank and file */
    int t=0;  /* turn */
    Pos p = malloc(sizeof(Position));
    short* lmoves;

    init_pos(p);

    printf("size of pos:%lu\n",sizeof(Position));

    p->bb[0] |= 1L<<27;
    p->bb[1] |= 1L<<28;
    p->bb[1] |= 1L<<35;
    p->bb[0] |= 1L<<36;
    print_pos(p);
    
    while(1){
        printf("Make move:");
        scanf("%s",s);
        if (*s=='q') break;
        x = *s-'a';
        y = '8'-*(s+1);
        printf("x=%d, y=%d\n",x,y);
        if(make(p,t,y*8+x)){
            print_pos(p);
            t^=1;
        }else
            printf("Illegal move!\n");
    }

    return 0;
}
