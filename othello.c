#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define INBOUNDS(a) (a>=0 && a<64)

/* If this squares are  empty it is considered opening phase */

const int SQ_VALUES[64]={
    20,-10,10,0,0,10,-10,20,
   -10,-15,0,0,0,0,-15,-10,
    10,0,5,0,0,5,0,10,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    10,0,5,0,0,5,0,10,
   -10,-15,0,0,0,0,-15,-10,
    20,-10,10,0,0,10,-10,20,
};

typedef struct {
    unsigned long bb[2];   /* black/white bitboard */
/*    short *l_moves; */
    short l_moves[32];
    int lm_size;
    int ply;
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
    /*p->l_moves = malloc(sizeof(short)*32);*/
    p->lm_size = -1;
    p->ply = 0;
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
        do j++; while(INBOUNDS(j) && (i/8==j/8) && p->bb[opp]&1L<<j);
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
        do j--; while(INBOUNDS(j) && (i/8==j/8) && p->bb[opp]&1L<<j);
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
    p->lm_size = cnt;
}

void randomize_moves(Pos p){
    int r1,r2,t,i;
    if (p->lm_size <0) return;
    for (i=0;i<p->lm_size/2;i++){
        r1 = rand() % p->lm_size;
        r2 = rand() % p->lm_size;
        if (r1==r2) continue;
        t=p->l_moves[r1]; p->l_moves[r1]=p->l_moves[r2]; p->l_moves[r2]=t;
    }

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
            p->ply++;
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


/*
short get_comp_move(Pos p,int t){
    int i;
    short mv=-1;
    int r;

    i=0;
    while (p->l_moves[i]!=-1 && i<32) i++;
    if (i>0){
        r = rand() % i;
        mv= p->l_moves[r];
        printf("choosing %d / %d value=%d\n",r,i,mv);
    }
    if (mv==-1)
        printf(" NO MOVE? \n");
    return mv;
}
*/

int eval(Pos p,int t){
    int i;
    int op_mobility;
    int retval=0;

    if (p->ply > 50)
        return count(p,t);
    for (i=0;i<64;i++)
       if (p->bb[t] & 1L << i)
           retval += SQ_VALUES[i];
    
    p->lm_size=-1;
    calc_legal_moves(p,t^1);
    op_mobility = p->lm_size;
    p->lm_size=-1;
    
    retval -=op_mobility*2;
    
    return retval;
}
int eval2(Pos p,int t){
    int i;
    int op_mobility;
    int retval=0;
    for (i=0;i<64;i++)
       if (p->bb[t] & 1L << i)
           retval += SQ_VALUES[i]*2;
        else if (p->bb[t^1] & 1L << i)
            retval -= SQ_VALUES[i]*2;
    p->lm_size=-1;
    calc_legal_moves(p,t^1);
    op_mobility = p->lm_size;
    p->lm_size=-1;
    retval += (50-op_mobility)  +count(p,t)*2-count(p,t^1)*2;
    return retval;
}
int eval3(Pos p,int t){
    int i;
    int op_mobility;
    int retval=0;
    for (i=0;i<64;i++)
       if (p->bb[t] & 1L << i)
           retval += SQ_VALUES[i];
       if (p->bb[t^1] & 1L << i)
           retval -= SQ_VALUES[i];
    
    retval += count(p,t);
    
    return retval;
}
/*
 * returns computer move
 * find lowest mobility for opponent player
 */

short get_comp_move(Pos p, int t){
    int i,pts,max_pts = INT_MIN;
    Pos np;
    short retval = -1;

    calc_legal_moves(p,t);
    randomize_moves(p); 
    for (i=0;i<p->lm_size;i++){
        np = (Pos)malloc(sizeof(Position));
        memcpy(np,p,sizeof(Position));
        np->lm_size = -1;  /* init legal moves */

        make(np,t,p->l_moves[i]);
        /* pts = eval(np); */
        pts = eval(np,t);
        if (pts>max_pts){
            max_pts = pts;
            retval = p->l_moves[i];
        }
        free(np);
    }
    return retval;
}

int evaluate(Pos p,int t,int depth){
    int i,pts,max_pts = INT_MIN,min_pts= INT_MAX;
    Pos np;
    short retval = -1;
    if (depth==0 || p->lm_size==0)
        return eval(p,t);
/*    calc_legal_moves(p,t); */
    if (depth%2==0){
        for (i=0;i<p->lm_size;i++){
            np = (Pos)malloc(sizeof(Position));
            memcpy(np,p,sizeof(Position));
            np->lm_size = -1;

            make(np,t,p->l_moves[i]);
            pts = evaluate(np,t,depth-1);
            if (pts>max_pts){
                max_pts = pts;
                retval = max_pts;
            }
            free(np);
        }
    } else {
        for (i=0;i<p->lm_size;i++){
            np = (Pos)malloc(sizeof(Position));
            memcpy(np,p,sizeof(Position));
            np->lm_size = -1;

            make(np,t,p->l_moves[i]);
            pts = evaluate(np,t,depth-1);
            if (pts<min_pts){
                min_pts = pts;
                retval = min_pts;
            }
            free(np);
        }
    }
    return retval;
}

short get_comp2_move(Pos p, int t){
    int i,pts,max_pts = -9999;
    Pos np;
    short retval = -1;

    calc_legal_moves(p,t);
    randomize_moves(p);
    for (i=0;i<p->lm_size;i++){
        np = (Pos)malloc(sizeof(Position));
        memcpy(np,p,sizeof(Position));
        np->lm_size = -1;  /* init legal moves */

        make(np,t,p->l_moves[i]);
        /* pts = eval(np); */
        calc_legal_moves(np,t^1);
        pts = evaluate(np,t,5);
        if (pts>max_pts){
            max_pts = pts;
            retval = p->l_moves[i];
        }
        free(np);

    }
    printf("Eval:%d\n",max_pts);
    return retval;
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

    p->bb[0] |= 1L<<28;
    p->bb[1] |= 1L<<27;
    p->bb[1] |= 1L<<36;
    p->bb[0] |= 1L<<35;
    print_pos(p);
    
    calc_legal_moves(p,t);
    while(1){
        if (autop[t]){
            if (t==0)
                sq = get_comp2_move(p,t);
            else
                sq = get_comp_move(p,t);
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
            printf("ply:%d,%d played %d\n",p->ply,t,sq);
            print_pos(p);
            t^=1;
            passed = 0;
            /* invalidate legal moves */
            p->lm_size = -1;
            calc_legal_moves(p,t);
        }else if(retval ==0)
            printf("Illegal move! sq=%d\n",sq);
        else if (retval==-1){
            printf("No move. Passed. tried %d\n",sq);
            t^=1;
            passed++;
            p->lm_size = -1;
            if(passed >=2){
                printf("score:%d/%d\n",count(p,0),count(p,1));
                break;
            }
        }
    }

    return 0;
}
