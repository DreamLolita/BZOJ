#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>
#define MAXINT 0x12ffffffffffffLL//max long long
#define Check   (ch>='0'&&ch<='9')
#define MAXN 10010
#define LL long long
using namespace std;
int n,top,maxnum;
LL T,M,P;
LL Tim = -1,last = 0;//last is the end time
int Head,num,HEAD;//num is the maxnum of the waiting queue

struct unit//running
{
    unit *next;
    LL l,r;
};

struct Pro
{
    LL t,m,p,l,r;
    bool operator <(const Pro& a)const
    {
        return t > a.t;
    }
}proce[MAXN],wait[MAXN];//proce have not appear   wait have not solve

void read(LL &x)
{
    char ch = getchar();x = 0;
    while (!Check)  ch = getchar();
    while (Check)   x = x * 10 + ch - '0',ch = getchar();
}

bool in()
{
    read(T);read(M);read(P);
    if  (T == 0 && M == 0 && P == 0)    return 0;
    proce[top].t = T;proce[top].m = M;proce[top++].p = P;
    return 1;
}
priority_queue<Pro> que;//when will these running task end

int main()
{
 //   freopen("BZOJ3117.in","r",stdin);
 //   freopen("BZOJ3117.out","w",stdout);
    
    scanf("%d",&n);
    while (in());
    proce[top].t = MAXINT;
    unit *head,*now,*pre,*t;
    head=new unit;head->l = -1;head->r = -2;head->next = NULL;//init list's head&tail
    head->next = new unit;head->next->l = 0;head->next->r = n - 1;head->next->next = NULL;
    head->next->next = new unit;head->next->next->l = n+1;head->next->next->r = n;head->next->next->next = NULL;
    Pro temp;temp.t = MAXINT;temp.l = temp.r = 0;
    que.push(temp);
    while   (Tim != MAXINT)
    {
        while   (Tim == que.top().t)
        {
            now = head;
            while   (now->next->r < que.top().l)
            {
                pre = now;
                now = now->next;
            }
            now->next = new unit((unit){now->next,que.top().l,que.top().r});//insert
            if  (now->r == que.top().l - 1) pre->next = now->next,now->next->l = now->l;//union
            if  (now->next->next->l == que.top().r + 1) now->next->r = now->next->next->r,now->next->next = now->next->next->next;
            que.pop();
        }

        while (Head < num)//solve watings
        {
            now = head;
            while   (now->next != NULL && now->r - now->l + 1 < wait[Head].m)   
            {
                pre = now;
                now = now->next;    
            }
            if  (now->next != NULL)
            {
                temp.t=Tim + wait[Head].p;temp.l = now->l;temp.r = now->l + wait[Head].m - 1;
                que.push(temp);
                if  (now->r - now->l + 1 == wait[Head].m)   pre->next = now->next;
                else    now->l += wait[Head].m;
            }
            else    break;//can't solve the first one so have to break
            Head++;
        }

        while   (proce[HEAD].t == Tim)//solve others
        {
            now = head;
            while   (now->next != NULL && now->r - now->l + 1 < proce[HEAD].m)  
            {
                pre = now;
                now = now->next;
            }
            if  (now->next != NULL)
            {
                temp.t=Tim + proce[HEAD].p;temp.l = now->l;temp.r = now->l + proce[HEAD].m - 1;
                que.push(temp);
                if  (now->r - now->l + 1 == proce[HEAD].m)  pre->next = now->next;
                else    now->l += proce[HEAD].m;
            }
            else//can't solve
            {
                temp.m = proce[HEAD].m;temp.p = proce[HEAD].p;
                wait[num++] = temp;
            }   
            HEAD++;
        }
        last = Tim;
        Tim = min(que.top().t,proce[HEAD].t);
    }
    cout<<last<<endl<<num;
}
