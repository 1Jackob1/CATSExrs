#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 5010
#define ROOMWALL 0

int get(int i, int *item){
    while(item[i]!=i)
        i=item[i];
    return i;
}

void add(int a, int b, int *item, int *h){
    int x=get(a,item), y=get(b,item);
    if(h[x]<h[y])
        item[x]=y;
    else
        item[y]=x;
    h[x]+=(h[x]==h[y]);
}

int CountRooms(char *m, int *n, int size, int roomclasess){
    int roomcount=0;
    int newroom=1;
    for(int i=0; i<size; i++){
        if(m[i]==' ') {
            if(newroom){
                roomcount++;
                roomclasess++;
                newroom=0;
            }

            n[i]=roomclasess;
        } else if(m[i]!='\n') {
            newroom = 1;
            n[i] = ROOMWALL;
        }
    }
    return roomcount;
}

int main()
{
    FILE *f=fopen("input.txt", "r");
    static char M1[MAXLEN], M2[MAXLEN];
    static int Line1[MAXLEN], Line2[MAXLEN];
    static int TEMP[MAXLEN], ITEM[MAXLEN], H[MAXLEN];
    static int RESETITEM[MAXLEN];
    int m, sum=0, k2=0;
    fgets(M1,MAXLEN,f);
    m=strlen(M1);
    int t=0;

    memset(H,0,m*sizeof(int));
    memset(Line1, 0, m* sizeof(int));
    memset(Line2, 0, m* sizeof(int));

    sum=CountRooms(M1, Line1,m, 0);
    t=sum;

    for (int j = 0; j < m+1; ++j) {
        RESETITEM[j] = j;
    }

    memcpy(ITEM, RESETITEM, (m+1)* sizeof(int));

    while(fgets(M2 ,MAXLEN ,f)!=NULL){

        k2=CountRooms(M2, Line2, m, t);
        sum+=k2;

        for(int i=0; i<m; i++){
            int a=Line1[i], b=Line2[i];
            if(a==0 || b==0) continue;
            if(get(a, ITEM)==get(b,ITEM)) continue;
            add(a,b,ITEM,H);
            sum--;
        }

        memset(TEMP, 0, (m+1) * sizeof(int));
        for(int i=0; i<m; i++){
            int b=get(Line2[i], ITEM);
            Line2[i]=b;
            if(b!=0)
                TEMP[b]=1;
        }

        t=1;
        for(int i=0; i<m; i++){
            if(TEMP[i]==0) continue;
            TEMP[i]=t;
            t++;
        }

        for(int i=0; i<m; i++)
            Line2[i]=TEMP[Line2[i]];

        memcpy(Line1, Line2, (m+1) * sizeof(int));
        memcpy(ITEM, RESETITEM, (m+1)* sizeof(int));

    }

    fclose(f);
    f=fopen("output.txt","w");
    fprintf(f,"%d", sum);
    fclose(f);
    return 0;
}