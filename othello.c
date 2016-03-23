#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SAMERANK(a,b) (a/8 == b/8)
#define SAMEFILE(a,b) (a%8 == b%8)
#define INBOUNDS(a) (a>=0 && a<64)

typedef struct {
    unsigned long bb[2];   /* black/white bitboard */
    short *l_moves;
    int lm_size;
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
    p->l_moves = malloc(sizeof(short)*32);
    p->lm_size = -1;
}

void calc_legal_moves(Pos p,int t){
    int cnt = 0;
    int i,j;
    int opp = t^1;  
    long empt;
 
    if (p->lm_size != -1) return;

    empt = ~(p->bb[1]|p->bb[0]);

    for (i=0;i<32;i++)
        *(p->l_moves+i) = -1;
    for (i=0;i<64;i++){
        if (~empt & 1L<<i)  /* skip allocated square */
            continue;
        /* east */
        j=i;
        do j++; while((i/8==j/8) && p->bb[opp]&1L<<j);
        if ((i/8==j/8) && p->bb[t]&1L<<j && j-i>1){
            p->l_moves[cnt++]=i;
            continue;
        }
        j=i;
        do j+=9; while(INBOUNDS(j) && (i%8<j%8) && p->bb[opp]&1L<<j);
        if (INBOUNDS(j) && (i%8<j%8) && p->bb[t]&1L<<j && j-i>9){
            p->l_moves[cnt++]=i;
            continue;
        }
        j=i;
        do j+=8; while(INBOUNDS(j) && p->bb[opp]&1L<<j);
        if (INBOUNDS(j) && p->bb[t]&1L<<j && j-i>8){
            p->l_moves[cnt++]=i;
            continue;
        }
        j=i;
        do j+=7; while(INBOUNDS(j) && (i%8>j%8) && p->bb[opp]&1L<<j);
        if (INBOUNDS(j) &&(i%8>j%8) && p->bb[t]&1L<<j && j-i>7){
            p->l_moves[cnt++]=i;
            continue;
        }
        j=i;
        do j--; while((i/8==j/8) && p->bb[opp]&1L<<j);
        if ((i/8==j/8) && p->bb[t]&1L<<j && i-j>1){
            p->l_moves[cnt++]=i;
            continue; 
        }
        j=i;
        do j-=9; while(INBOUNDS(j) && (i%8>j%8) && p->bb[opp]&1L<<j);
        if (INBOUNDS(j) && (i%8>j%8) && p->bb[t]&1L<<j && i-j>9){
            p->l_moves[cnt++]=i;
            continue;
        }
        j=i;
        do j-=8; while(INBOUNDS(j) && p->bb[opp]&1L<<j);
        if (INBOUNDS(j) && p->bb[t]&1L<<j && i-j>8){
            p->l_moves[cnt++]=i;
            continue; 
        }
        j=i;
        do j-=7; while(INBOUNDS(j) && (i%8<j%8) && p->bb[opp]&1L<<j);
        if (INBOUNDS(j) && (i%8<j%8) && p->bb[t]&1L<<j && i-j>7){
            p->l_moves[cnt++]=i;
            continue;
        }
    }
    printf("legal move size:%d\n",cnt);

    p->lm_size = cnt;
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
    do j+=9; while(INBOUNDS(j) && (i%8<j%8) && p->bb[opp]&1L<<j);
    if (INBOUNDS(j) && (i%8<j%8) && p->bb[t]&1L<<j && j-i>9){
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
    do j+=7; while(INBOUNDS(j) && (i%8>j%8) && p->bb[opp]&1L<<j);
    if (INBOUNDS(j) &&(i%8>j%8) && p->bb[t]&1L<<j && j-i>7){
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
    do j-=9; while(INBOUNDS(j) &&(i%8>j%8) && p->bb[opp]&1L<<j);
    if (INBOUNDS(j) &&(i%8>j%8) && p->bb[t]&1L<<j && i-j>9){
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
    do j-=7; while(INBOUNDS(j) &&(i%8<j%8) && p->bb[opp]&1L<<j);
    if (INBOUNDS(j) &&(i%8<j%8) && p->bb[t]&1L<<j && i-j>7){
        for (k=i-7;k>j;k-=7){
            p->bb[t] |= 1L<<k;
            p->bb[opp] &= ~(1L<<k);
        }
    }
}

/*
 * returns 1 if move is successful
 *          0 if move isn't succesful
 *          -1 if there no move
 */

int make(Pos p,int t,int sq){
    int i;
    int moved = 0;
    
    calc_legal_moves(p,t);

    for (i=0;i<32;i++){
        if (*(p->l_moves+i)==-1)
            break;    
        if (*(p->l_moves+i)==sq){
            p->bb[t] |= 1L << sq;
            flip(p,sq,t);
            moved = 1;
            break;
        }
    }
    if (!moved && i==0)
        return -1;
    
    return moved;
}
int count(Pos p,int t){
    int i;
    int retval=0;
    for (i=0;i<64;i++)
        if (p->bb[t] & 1L<<i)
            retval++;  
    return retval;
}

int get_comp_move(Pos p,int t){
    return -1;
}

short get_random_move(Pos p,int t){
    int i;
    short mv=-1;
    int r;

    i=0;
    while (p->l_moves[i]!=-1 && i<32) i++;
    if (i>0){
        r = rand()%i;
        mv= p->l_moves[r];
        printf("choosing %d / %d value=%d\n",r,i,mv);
    }
    if (mv==-1)
        printf(" NO MOVE? \n");
    return mv;
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
    short sq = -1;
    short autop[] = {1,1};
    short passed = 0;
    short retval;

    srand(time(NULL));
    init_pos(p);

    printf("size of pos:%lu\n",sizeof(Position));

    p->bb[0] |= 1L<<27;
    p->bb[1] |= 1L<<28;
    p->bb[1] |= 1L<<35;
    p->bb[0] |= 1L<<36;
    print_pos(p);
    
    calc_legal_moves(p,t);
    while(1){
        if (autop[t]){
            sq = get_random_move(p,t);
           /*
            * if (sq!=-1)
                retval = make(p,t,sq);
            else
                retval = -1;
            */
            retval = make(p,t,sq);
        }else{
            if (p->lm_size == 0)
               retval = -1;
            else {
                printf("Make move:");
                scanf("%s",s);
                if (*s=='q') break;
                x = *s-'a';
                y = '8'-*(s+1);
                printf("x=%d, y=%d\n",x,y);
                sq = y*8+x;
                retval = make(p,t,sq);
            }
        }
        
        if(retval >0){
            printf("played %d\n",sq);
            print_pos(p);
            t^=1;
            passed = 0;
            /* invalidate legal moves */
            p->lm_size = -1;
            calc_legal_moves(p,t);
        }else if(retval ==0)
            printf("Illegal move!\n");
        else if (retval==-1){
            printf("No move. Passed. tried %d\n",sq);
            t^=1;
            passed++;
            p->lm_size = -1;
            if(passed >=2){
                printf("score:%d/%d\n",count(p,t),count(p,t^1));
                break;
            }
        }
    }

    return 0;
}
