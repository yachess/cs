#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <memory.h>

#define INBOUNDS(a) (a>=0 && a<64)
#define SQ_VALUE_FACTOR 1
#define MOBILITY_FACTOR 3
#define MOBILITY_FACTOR2 6
#define COUNT_FACTOR 5
#define CENTER_FACTOR 5

typedef struct {
    unsigned long bb[2];   /* black/white bitboard */
/*    short *l_moves; */
    short l_moves[32];
    int lm_size;
    int ply;
    int pass_cnt;  /* set if previous turn is passed */
    int t;
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
    p->pass_cnt = 0;
    p->t=0;
}

void calc_legal_moves(Pos p){
    int cnt = 0;
    int i,j;
    int t= p->t;
    int opp = p->t^1;  
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
        if (INBOUNDS(j) && (i/8==j/8) && p->bb[t]&1L<<j && j-i>1){
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
        if (INBOUNDS(j) && (i/8==j/8) && p->bb[t]&1L<<j && i-j>1){
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

int flip (Pos p,int sq){
    int i=sq,j,k;
    int t = p->t;
    int opp=t^1;
    j=i;
    do j++; while(INBOUNDS(j) && (i/8==j/8) && p->bb[opp]&1L<<j);
    if (INBOUNDS(j) && (i/8==j/8) && p->bb[t]&1L<<j && j-i>1){
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
    do j--; while(INBOUNDS(j) && (i/8==j/8) && p->bb[opp]&1L<<j);
    if (INBOUNDS(j) && (i/8==j/8) && p->bb[t]&1L<<j && i-j>1){
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

int make(Pos p,int sq){
    int i;
    int moved = 0;
    int t=p->t;

    calc_legal_moves(p);

    for (i=0;i<p->lm_size;i++){
        if (*(p->l_moves+i)==sq){
            p->bb[t] |= 1L << sq;
            flip(p,sq);
            moved = 1;
            p->ply++;
            p->pass_cnt = 0;
            p->t^=1;
            p->lm_size=-1;
            break;
        }
    }
    if (!moved && p->lm_size==0){
        p->pass_cnt++;
        p->t^=1;
        return -1;
    }
     
    return moved;
}

inline int count(Pos p,int t){
    unsigned long i = p->bb[t];
    i = i - ((i >> 1) & 0x5555555555555555UL);
    i = (i & 0x3333333333333333UL) + ((i >> 2) & 0x3333333333333333UL);
    return (int)((((i + (i >> 4)) & 0xF0F0F0F0F0F0F0FUL) * 0x101010101010101UL) >> 56);
}
inline int bitcount(unsigned long i){
    i = i - ((i >> 1) & 0x5555555555555555UL);
    i = (i & 0x3333333333333333UL) + ((i >> 2) & 0x3333333333333333UL);
    return (int)((((i + (i >> 4)) & 0xF0F0F0F0F0F0F0FUL) * 0x101010101010101UL) >> 56);
}

short get_random_move(Pos p){
    calc_legal_moves(p);
    if (p->lm_size<=0) return -1;
    randomize_moves(p); 
    return p->l_moves[0];
}
int eval(Pos p){
    int i;
    int retval=0;

    long empt = ~(p->bb[0]|p->bb[1]);

    if (p->ply>51)
        return count(p,0)-count(p,1);

    for (i=0;i<8;i++)
        if (p->bb[0] & 1L<<i) 
            retval += 10;
        else if(p->bb[1] & 1L<<i)
            retval -= 10;
    for (i=0;i<64;i+=8)
        if (p->bb[0] & 1L<<i) 
            retval += 10;
        else if(p->bb[1] & 1L<<i)
            retval -= 10;
    for (i=7;i>=0;i--)
        if (p->bb[0] & 1L<<i) 
            retval += 10;
        else if(p->bb[1] & 1L<<i)
            retval -= 10;
    for (i=7;i<64;i+=8)
        if (p->bb[0] & 1L<<i) 
            retval += 10;
        else if(p->bb[1] & 1L<<i)
            retval -= 10;
    for (i=56;i>=0;i-=8)
        if (p->bb[0] & 1L<<i) 
            retval += 10;
        else if(p->bb[1] & 1L<<i)
            retval -= 10;
    for (i=56;i<64;i++)
        if (p->bb[0] & 1L<<i) 
            retval += 10;
        else if(p->bb[1] & 1L<<i)
            retval -= 10;
    for (i=63;i>=0;i-=8)
        if (p->bb[0] & 1L<<i) 
            retval += 10;
        else if(p->bb[1] & 1L<<i)
            retval -= 10;
    for (i=63;i>=56;i--)
        if (p->bb[0] & 1L<<i) 
            retval += 10;
        else if(p->bb[1] & 1L<<i)
            retval -= 10;

    if (empt & 1L<<0){
        if (p->bb[0] & 1L<<9)
            retval -= 20;
        else if (p->bb[1] & 1L<<9)
            retval += 20;
        if (p->bb[0] & 1L<<1)
            retval -=20;
        else if (p->bb[1] & 1L<<1)
            retval += 20;
        if (p->bb[0] & 1L<<8)
            retval -=20;
        else if (p->bb[1] & 1L<<8)
            retval += 20;
    } 
    if (empt & 1L<<7){
        if (p->bb[0] & 1L<<14)
            retval -=20;
        else if (p->bb[1] & 1L<<14)
            retval += 20;
        if (p->bb[0] & 1L<<6)
            retval -=20;
        else if (p->bb[1] & 1L<<6)
            retval += 20;
        if (p->bb[0] & 1L<<15)
            retval -=20;
        else if (p->bb[1] & 1L<<15)
            retval += 20;
    }
    if (empt & 1L<<56){
        if (p->bb[0] & 1L<<49)
            retval -=20;
        else if (p->bb[1] & 1L<<49)
            retval += 20;
        if (p->bb[0] & 1L<<57)
            retval -=20;
        else if (p->bb[1] & 1L<<57)
            retval += 20;
        if (p->bb[0] & 1L<<48)
            retval -=20;
        else if (p->bb[1] & 1L<<48)
            retval += 20;
    }    
    if (empt & 1L<<63){
        if (p->bb[0] & 1L<<54)
            retval -=20;
        else if (p->bb[1] & 1L<<54)
            retval += 20;
        if (p->bb[0] & 1L<<62)
            retval -=20;
        else if (p->bb[1] & 1L<<62)
            retval += 20;
        if (p->bb[0] & 1L<<55)
            retval -=20;
        else if (p->bb[1] & 1L<<55)
            retval += 20;
    }    
        
    retval=retval*2;

    /*
    if (p->ply<20)
        for (i=0;i<64;i++)
           if (p->bb[0] & 1L << i)
               retval += SQ_VALUES[i] * SQ_VALUE_FACTOR;
           if (p->bb[1] & 1L << i)
               retval -= SQ_VALUES[i] * SQ_VALUE_FACTOR;
    */
/*
    if (p->ply>=50) 
        retval+=(count(p,0)-count(p,1)) * COUNT_FACTOR;
*/



    if (p->t==0)
        retval += p->lm_size*MOBILITY_FACTOR;
    else
        retval -= p->lm_size*MOBILITY_FACTOR;

    return retval;
}

int eval2(Pos p){
    int i;
    int retval=0;

    long empt = ~(p->bb[0]|p->bb[1]);

    /* bonus corner */
    if (p->bb[0] & 1L<<0)
        retval +=20;
    if (p->bb[0] & 1L<<7)
        retval +=20;
    if (p->bb[0] & 1L<<54)
        retval += 20;
    if (p->bb[0] & 1L <<63)
        retval += 20;
    if (p->bb[1] & 1L<<0)
        retval -=20;
    if (p->bb[1] & 1L<<7)
        retval -=20;
    if (p->bb[1] & 1L<<54)
        retval -= 20;
    if (p->bb[1] & 1L <<63)
        retval -= 20;

    /* bonus connected edge */
    for (i=0;p->bb[0] & 1L<<i && (i<8);i++)
        retval += 10;
    for (i=7;p->bb[0] & 1L<<i && (i>=0);i--)
        retval += 10;
    for (i=0;p->bb[0] & 1L<<i && (i<64);i+=8)
        retval += 10;
    for (i=56;p->bb[0] & 1L<<i && (i>=0);i-=8)
        retval += 10;
    for (i=7;p->bb[0] & 1L<<i && (i<64);i+=8)
        retval += 10;
    for (i=63;p->bb[0] & 1L<<i && (i>=0);i-=9)
        retval += 10;
    for (i=56;p->bb[0] & 1L<<i && (i<64);i++)
        retval += 10;
    for(i=63;p->bb[0] & 1L<<i && (i>=56);i--)
        retval += 10;

    for (i=0;p->bb[1] & 1L<<i && (i<8);i++)
        retval -= 10;
    for (i=7;p->bb[1] & 1L<<i && (i>=0);i--)
        retval -= 10;
    for (i=0;p->bb[1] & 1L<<i && (i<64);i+=8)
        retval -= 10;
    for (i=56;p->bb[1] & 1L<<i && (i>=0);i-=8)
        retval -= 10;
    for (i=7;p->bb[1] & 1L<<i && (i<64);i+=8)
        retval -= 10;
    for (i=63;p->bb[1] & 1L<<i && (i>=0);i-=9)
        retval -= 10;
    for (i=56;p->bb[1] & 1L<<i && (i<64);i++)
        retval -= 10;
    for(i=63;p->bb[1] & 1L<<i && (i>=56);i--)
        retval -= 10;
   

    if (p->ply>49)
        return retval+count(p,0)-count(p,1);

    if (p->lm_size==0){
        if (p->t==0)
            return INT_MIN;
        return INT_MAX;
    }

    /*  bonus edge */
    retval += bitcount(p->bb[0]&0xFF818181818181FF)*10;
    retval -= bitcount(p->bb[1]&0xFF818181818181FF)*10;
    
    /* penalty for early adjacent corner square 
    */
    if (empt & 1L<<0){
        retval -= bitcount(p->bb[0] & 0x40c0000000000000)*20;
        retval += bitcount(p->bb[1] & 0x40c0000000000000)*20;
    } 
    if (empt & 1L<<7){
        retval -= bitcount(p->bb[0] & 0x0203000000000000)*20;
        retval += bitcount(p->bb[1] & 0x0203000000000000)*20;
    }
    if (empt & 1L<<56){
        retval -= bitcount(p->bb[0] & 0x000000000000c040)*20;
        retval += bitcount(p->bb[1] & 0x000000000000c040)*20;
    }    
    if (empt & 1L<<63){
        retval -= bitcount(p->bb[0] & 0x0000000000000302)*20;
        retval += bitcount(p->bb[1] & 0x0000000000000302)*20;
    }    
        
    retval=retval*2;

    /*
    if (p->ply<20)
        for (i=0;i<64;i++)
           if (p->bb[0] & 1L << i)
               retval += SQ_VALUES[i] * SQ_VALUE_FACTOR;
           if (p->bb[1] & 1L << i)
               retval -= SQ_VALUES[i] * SQ_VALUE_FACTOR;
    */
/*
    if (p->ply>=50) 
        retval+=(count(p,0)-count(p,1)) * COUNT_FACTOR;
*/



    if (p->t==0)
        retval += p->lm_size*MOBILITY_FACTOR2;
    else
        retval -= p->lm_size*MOBILITY_FACTOR2;
    

    return retval;
}

int minmax_search(Pos p,int color, int depth){
    int i,pts,max_pts = INT_MIN,min_pts= INT_MAX;
    Pos np;
    short retval = -1;
    if (depth ==0){ 
        if (color==0) return eval(p);
            else return -eval(p);
    }
    calc_legal_moves(p); 
    if (p->lm_size ==0){
        if(p->pass_cnt)
            return eval(p);
        
        p->t^=1;
        pts = minmax_search(p,color,depth-1);
        if (depth%2==(color^1)){
            if (pts>max_pts){
                max_pts = pts;
                retval = max_pts;
            }
        }
        else{
            if (pts<min_pts){
                min_pts = pts;
                retval = min_pts;
            }
        }
    }

    for (i=0;i<p->lm_size;i++){
        np = (Pos)malloc(sizeof(Position));
        memcpy(np,p,sizeof(Position));
        np->lm_size = -1;
        make(np,p->l_moves[i]);
        pts = minmax_search(np,color,depth-1);
        if (depth%2==0){    /* even depth number is maximizing player */
            if (pts>max_pts){
                max_pts = pts;
                retval = max_pts;
            }
        }
        else{
            if (pts<min_pts){
                min_pts = pts;
                retval = min_pts;
            }
        }
        free(np);
    }

    return retval;
}

int minmax_search2(Pos p,int color, int depth, int alpha, int beta){
    int i,pts,max_pts = INT_MIN,min_pts= INT_MAX;
    Pos np;
    short retval = -1;
    if (depth == 0) {
        if (color==0) return eval2(p);
        else return -eval2(p);
    }   
    calc_legal_moves(p); 
    if (p->lm_size ==0){
        if(p->pass_cnt)
            return eval2(p);
        
        p->t^=1;
        pts = minmax_search2(p,color,depth-1,alpha,beta);
        if (depth%2==(color^1)){
            if (pts>max_pts){
                max_pts = pts;
                retval = max_pts;
            }
            if (pts>alpha)
                alpha = pts;
            if (beta<=alpha)
                return retval;
        }
        else{
            if (pts<min_pts){
                min_pts = pts;
                retval = min_pts;
            }
            if (pts<beta)
                beta = pts;
            if (alpha>=beta)
                return retval;
        }
    }

    for (i=0;i<p->lm_size;i++){
        np = (Pos)malloc(sizeof(Position));
        memcpy(np,p,sizeof(Position));
        np->lm_size = -1;
        make(np,p->l_moves[i]);
        pts = minmax_search2(np,color,depth-1,alpha,beta);
        if (depth%2==0){    /* even depth number is maximizing player */
            if (pts>max_pts){
                max_pts = pts;
                retval = max_pts;
            }
            if (pts>alpha)
                alpha = pts;
            if (beta<=alpha)
                break;
        }
        else{
            if (pts<min_pts){
                min_pts = pts;
                retval = min_pts;
            }
            if (pts<beta)
                beta = pts;
            if (alpha>=beta)
                break;
        }
        free(np);
    }

    return retval;
}

short get_comp_move(Pos p){
    int i,pts,max_pts = INT_MIN;
    Pos np;
    short retval = -1;
    
    calc_legal_moves(p);
    if(p->lm_size==0) return -1;

    randomize_moves(p); 
    for (i=0;i<p->lm_size;i++){
        np = (Pos)malloc(sizeof(Position));
        memcpy(np,p,sizeof(Position));
        np->lm_size = -1;  /* init legal moves */

        make(np,p->l_moves[i]);
        
        if (np->ply<51)
            pts = minmax_search(np,p->t,3);
        else
            pts = minmax_search(np,p->t,9);
        if (pts>max_pts){
            max_pts = pts;
            retval = p->l_moves[i];
        }
        free(np);
    }
    
    return retval;
}

short get_comp_move2(Pos p){
    int i,pts,max_pts = INT_MIN;
    Pos np;
    short retval = -1;
    int depth = (p->ply<51)?5:9; 
    calc_legal_moves(p);
    if(p->lm_size==0) return -1;

    randomize_moves(p); 
    for (i=0;i<p->lm_size;i++){
        np = (Pos)malloc(sizeof(Position));
        memcpy(np,p,sizeof(Position));
        np->lm_size = -1;  /* init legal moves */

        make(np,p->l_moves[i]);
        
        pts = minmax_search2(np,p->t,depth,INT_MIN,INT_MAX);
        if (pts>max_pts){
            max_pts = pts;
            retval = p->l_moves[i];
        }
        free(np);
    }
    
    return retval;
}

int read_user_move(Pos p){
    char s[2];
    int x,y;
    short sq = -1;
    int i;

    calc_legal_moves(p);
    if (p->lm_size==0) 
        return -1;
    while(1){    
        printf("Make move:");
        scanf("%s",s);
        if (*s=='q') exit(0);
        x = *s-'a';
        y = '8'-*(s+1);
        printf("x=%d, y=%d\n",x,y);
        sq = y*8+x;
        for (i =0;i<p->lm_size;i++)
            if (p->l_moves[i]==sq)
                return sq;
    }
}

int main(int argc, char** argv){
    Pos p = malloc(sizeof(Position));
    short autop[] = {1,1};
    short retval;
    short sq;

    srand(time(NULL));
    init_pos(p);

    printf("size of pos:%lu\n",sizeof(Position));

    p->bb[1] |= 1L<<28;
    p->bb[0] |= 1L<<27;
    p->bb[0] |= 1L<<36;
    p->bb[1] |= 1L<<35;
    print_pos(p);
    
    while(1){
        calc_legal_moves(p);
        if (autop[p->t]){
            if (p->t==0)
                sq = get_comp_move2(p);
            else
                sq = get_comp_move(p);
            retval = make(p,sq);
        }else{
            sq = read_user_move(p);
            if (sq!=-1)
                make(p,sq);
            else
                p->pass_cnt++;
        }
        if (sq==-1)
            retval = -1;

        if(retval >0){
            printf("ply:%d,%d played %d\n",p->ply,p->t,sq);
            print_pos(p);
            /* invalidate legal moves */
            p->lm_size = -1;
        }else if(retval ==0)
            printf("Illegal move! sq=%d\n",sq);
        else if (retval==-1){
            printf("No move. Passed.\n");
            p->lm_size = -1;
            if(p->pass_cnt>1){
                if (count(p,0)>count(p,1))
                    printf("First player won!\n");
                else if(count(p,0)==count(p,1))
                    printf("Draw.\n");
                else
                    printf("Second player won!\n");
                printf("score:%d/%d\n",count(p,0),count(p,1));
                break;
            }
        }
    }
    return 0;
}
