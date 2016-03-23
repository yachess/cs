/*
 * maze drawing program
 */

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

const char *hl = "+--";
const char *h_end = "+\n";
const char *vl = "|  ";
const char *v_end = "|\n";

void walk(int x,int y)
{
}

void print_map(int w,int h,const char **horiz,const char **vert)
{
    int x,y;
    for (y=0;y<w;y++)
    {
        for (x=0;x<=h;x++)
            printf("%s",*(horiz+y*(w+1)+x));
        for (x=0;x<=h;x++)
            printf("%s",*(vert+y*(w+1)+x));
    }
    for (x=0;x<=h;x++)
        printf("%s",*(horiz+h*(w+1)+x));
}

int main(int argc, char *argv[])
{
    int w,h;
    int x,y;
    const char **horiz, **vert;

    if (argc != 3){
        printf("Usage:%s x y\n",argv[0]);
        return 1;
    }

    w = atoi(argv[1]);
    h = atoi(argv[2]);

    horiz = malloc(sizeof(char*)*(w+1)*(h+1));
    vert = malloc(sizeof(char*)*(w+1)*(h+1));

    for(y=0;y<=h;y++)
    {
        for (x=0;x<w;x++){
            *(horiz+y*(w+1)+x) = hl;
            *(vert+y*(w+1)+x) = vl;
        }
        *(horiz+y*(w+1)+w) = h_end;  
        *(vert+y*(w+1)+w) = v_end;
    }
    
    print_map(w,h,horiz,vert);
    free(horiz);
    free(vert);
}
