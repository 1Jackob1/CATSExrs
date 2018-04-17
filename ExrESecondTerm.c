/*ExrE Top Places
 * solve with binary tree
 * using ShiftUp and ShiftDown
 https://imcs.dvfu.ru/cats/static/problem_text-cpid-1289414.html?sid=HvLYzyeKYgb2eE3GHwHDmh6At9XfQV
 */
#include <stdio.h>
#include <mem.h>

#define MAXARRSIZE 100000

typedef struct Member{
    int pos;//position of member
    int score;// scores of member
    int queue;// order of up/down scoring
}Member;

void swap(Member *a, Member *b, Member **Fadress, Member **Sadress){
    Member tmp=*a;
    *a=*b;
    *b=tmp;
    Member *_tmp=*Fadress;
    *Fadress=*Sadress;
    *Sadress=_tmp;
}

void ShiftUp(Member* M, int ElNum, Member** Adress){
    int p;
    if(ElNum%2==0)
        p=((ElNum-2) / 2);
    else
        p=((ElNum-1) / 2);
    if(p>-1 && M[ElNum].score>=M[p].score){
        swap(&M[ElNum], &M[p], &Adress[ElNum], &Adress[p]);
        ShiftUp(M, p, Adress);
    }
}

void ShiftDown(Member* M, int ElNum, int size, int shift, Member** Adress){
    int Lch=ElNum*2+1 - shift;
    int Rch=ElNum*2+2 - shift;
    int _ElNum= ElNum;
    if(Lch<size && ((M[Lch].score>M[ElNum].score) || (M[Lch].score==M[ElNum].score && M[Lch].queue>M[ElNum].queue)))
        ElNum=Lch;
    if(Lch<size && ((M[Rch].score>M[ElNum].score) || (M[Rch].score==M[ElNum].score && M[Rch].queue>M[ElNum].queue)))
        ElNum=Rch;
    if(ElNum!=_ElNum){
        swap(&M[ElNum], &M[_ElNum], &Adress[ElNum], &Adress[_ElNum]);
        ShiftDown(M, ElNum, size, shift, Adress);
    }
}

void PrintResults(Member* M, int size, FILE *f, Member** Adress){
    int k=0, Winners[3];
    memset(Winners, -1, 3* sizeof(int));
    for (int i = 0; i < 3 ; ++i) {
        if(M[i].score==0) break;
        Winners[k]=M[i].pos;
        ShiftDown(M, i+1, size, i+1, Adress);
        k++;
    }
    if(k==0){
        fprintf(f,"%d", k);
    } else{
        fprintf(f,"%d ",k);
        for (int i = 0; i < k; ++i) {
            fprintf(f,"%d ",M[i].pos);
        }

    }
    fprintf(f,"\n");
}


Member MemberList[10];
Member *MemberListAdresses[10];

int main(){
    int n, m, a, b;//n-count of members, m - count of requests, a-member that receive scores, b - requests

    FILE *in=fopen("input.txt","r");
    FILE *out=fopen("output.txt", "w");
    fscanf(in,"%d%d",&n, &m);

    for (int i = 0; i < n; ++i) {
        MemberList[i].score= 0;
        MemberList[i].queue= 0;
        MemberList[i].pos= i;
        MemberListAdresses[i]= &MemberList[i];
    }

    for (int i = 0; i < m; ++i) {
        fscanf(in, "%d%d", &a, &b);
        int j=0;
//        while(MemberList[j].pos!=a)
//            j++;
//        MemberList[j].score+=b;
//        if(b>0)
//            MemberList[j].queue=i;
//        (b>=0) ? ShiftUp(MemberList, j) : ShiftDown(MemberList, j, n, 0);

        MemberListAdresses[a]->score+=b;
        if(b>0)
            MemberListAdresses[a]->queue=i;
        (b>=0) ? ShiftUp(MemberList, a, MemberListAdresses):ShiftDown(MemberList, a, n, 0, MemberListAdresses);

//        fprintf(out,"%d\n",i);
//
//        for(int j=0; j<n; ++j)
//            fprintf(out," %d, %d, %d\n", MemberList[j].pos, MemberList[j].score, MemberList[j].queue);
        PrintResults(MemberList, n, out, MemberListAdresses);
    }
}
