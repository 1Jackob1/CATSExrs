/*ExrE Top Places
 * solve with binary tree
 * using ShiftUp and ShiftDown procedures
 * and additional arrays to change member for O(log(n))
 * so all exr will work for O(m*log(n))
 */
#include <stdio.h>
#include <mem.h>
#define MAXARRSIZE 100000

typedef struct Member{
    int pos;//position of member
    int score;// scores of member
    int queue;// order of up/down scoring
    struct Member* adress;// adresses of each member
}Member;

Member MemberList[MAXARRSIZE];
Member *MemberListAdresses[MAXARRSIZE];
int Member_in_Arr[MAXARRSIZE];
Member *ZeroEl=&MemberList[0];


void swap(int a, int b){
    Member tmp=MemberList[a];
    MemberList[a]=MemberList[b];
    MemberList[b]=tmp;

    unsigned int _a=MemberList[a].adress - ZeroEl, _b=MemberList[b].adress - ZeroEl;
    Member *tmp_ptr= MemberListAdresses[_a];
    MemberListAdresses[_a]=MemberListAdresses[_b];
    MemberListAdresses[_b]=tmp_ptr;

    int tmp_i= Member_in_Arr[_a];
    Member_in_Arr[_a]= Member_in_Arr[_b];
    Member_in_Arr[_b]=tmp_i;
}

Member max(Member* a, Member* b){
    if((a->score > b->score) || (a->score == b->score && a->queue > b->queue))
        return *a;
    return *b;
}

Member min(Member *a, Member *b){
    if((a->score < b->score) || (a->score == b->score && a->queue < b->queue))
        return *a;
    return *b;
}

void ShiftUp(int ElNum){
    int p;
    if(ElNum%2==0)
        p=((ElNum-2) / 2);
    else
        p=((ElNum-1) / 2);
    if(p>-1 && MemberList[ElNum].score>=MemberList[p].score){
        swap(ElNum, p);
        ShiftUp(p);
    }
}

void ShiftDown(int ElNum, int size, int shift){
    int Lch=ElNum*2+1 - shift;
    int Rch=ElNum*2+2 - shift;
    int _ElNum= ElNum;
    if(Lch<size && ((MemberList[Lch].score>MemberList[ElNum].score) ||
                    (MemberList[Lch].score==MemberList[ElNum].score && MemberList[Lch].queue>MemberList[ElNum].queue)))
        ElNum=Lch;
    if(Rch<size && ((MemberList[Rch].score>MemberList[ElNum].score) ||
                    (MemberList[Rch].score==MemberList[ElNum].score && MemberList[Rch].queue>MemberList[ElNum].queue)))
        ElNum=Rch;
    if(ElNum!=_ElNum){
        swap(ElNum, _ElNum);
        ShiftDown(ElNum, size, shift);
    }
}

void PrintResults(FILE *f){
    int Winners[3];
    if(MemberList[0].score!=0){
        Winners[0]=MemberList[0].pos;
        Member tmp=max(&MemberList[1], &MemberList[2]);
        if(tmp.score!=0){
            Winners[1]=tmp.pos;
            Member tmp1=max(&MemberList[3], &MemberList[4]);
            Member tmp3=max(&MemberList[5], &MemberList[6]);
            Member tmp2=min(&MemberList[1], &MemberList[2]);
            tmp=max(&tmp1, &tmp3);
            tmp=max(&tmp, &tmp2);
            if(tmp.score!=0){
                Winners[2]=tmp.pos;
                fprintf(f,"3 ");
                for (int i = 0; i < 3; ++i) {
                    fprintf(f,"%d ", Winners[i]);
                }
            } else
                fprintf(f,"2 %d %d", Winners[0], Winners[1]);
        }
        else
            fprintf(f,"1 %d",Winners[0]);
    } else
        fprintf(f,"0");
}

int main(){
    int n, m, a, b;//n-count of members, m - count of requests, a-member that receive scores, b - score

    FILE *in=fopen("input.txt","r");
    FILE *out=fopen("output.txt", "w");
    fscanf(in,"%d%d",&n, &m);

    for (int i = 0; i < n; ++i) {
        MemberList[i].score= 0;
        MemberList[i].queue= 0;
        MemberList[i].pos= i;
        MemberList[i].adress= &MemberList[i];
        MemberListAdresses[i]= MemberList[i].adress;
        Member_in_Arr[i]=i;
    }

    for (int i = 0; i < m; ++i) {
        fscanf(in, "%d%d", &a, &b);

        (MemberListAdresses[a])->score+=b;
        if(b>0)
            (MemberListAdresses[a])->queue=i;
        (b>=0) ? ShiftUp(Member_in_Arr[(MemberListAdresses[a])->adress - ZeroEl]) :
                 ShiftDown(Member_in_Arr[(MemberListAdresses[a])->adress - ZeroEl], n, 0);

        PrintResults(out);
        fprintf(out,"\n");
    }
}