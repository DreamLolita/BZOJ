#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define MAXN 1000100
#define lowbit(x) (x&(-x))
#define MAXINT 0x7fffffff
using namespace std;
int n,m,size;
int c[MAXN],ans[MAXN];
void in(int &x)
{
    char ch=getchar();x=0;int flag=1;
    while (!(ch>='0'&&ch<='9')) flag=ch=='-'?-1:flag,ch=getchar();
    while (ch>='0'&&ch<='9')    x=x*10+ch-'0',ch=getchar();
}
void add(int x,int delta)
{
    for (int i=x;i<=size;i+=lowbit(i))  c[i]=max(c[i],delta);
}
int query(int x)
{
    int ret=0;
    for (int i=x;i;i-=lowbit(i))    ret=max(ret,c[i]);
    return ret;
}
void init(int x)
{
    for (int i=x;i<=size;i+=lowbit(i))  c[i]=0;
}
struct Query
{
    int opt,x,y,id;
    bool operator <(const Query& a)const
    {
        return x==a.x?id<a.id:x<a.x;
    }
}q[MAXN],newq[MAXN];
void solve(int l,int r)
{
    int mid=(l+r)>>1,tp1=l,tp2=mid+1;
    if (l==r)   return;
    for (int i=l;i<=r;i++)
        if (q[i].id<=mid)   newq[tp1++]=q[i];
        else    newq[tp2++]=q[i];
    memcpy(q+l,newq+l,sizeof(Query)*(r-l+1));
    solve(l,mid);
    int i=mid+1,j=l;
    for (i=mid+1;i<=r;i++)
        if (q[i].opt==2)
        {
            for (;j<=mid&&q[j].x<=q[i].x;j++)
                if (q[j].opt==1)    add(q[j].y,q[j].x+q[j].y);
            int temp=query(q[i].y);
            if (temp)   ans[q[i].id]=min(ans[q[i].id],q[i].x+q[i].y-temp);
        }
    for (i=l;i<j;i++)
        if (q[i].opt==1)    init(q[i].y);
    solve(mid+1,r);
    tp1=l,tp2=mid+1;
    for (i=l;i<=r;i++)
        if ((q[tp1]<q[tp2]||tp2>r)&&tp1<=mid)   newq[i]=q[tp1++];
        else    newq[i]=q[tp2++];
    memcpy(q+l,newq+l,sizeof(Query)*(r-l+1));   
}
int main()
{
    in(n);in(m);
    for (int i=1;i<=n;i++)  scanf("%d%d",&q[i].x,&q[i].y),q[i].id=i,q[i].opt=1,q[i].x++,q[i].y++,size=max(size,max(q[i].x,q[i].y));
    for (int i=n+1;i<=n+m;i++)  scanf("%d%d%d",&q[i].opt,&q[i].x,&q[i].y),q[i].id=i,q[i].x++,q[i].y++,size=max(size,max(q[i].x,q[i].y));
    size++;
    for (int i=1;i<=n+m;i++)    ans[i]=MAXINT;
    sort(q+1,q+n+m+1);solve(1,n+m);
    for (int i=1;i<=n+m;i++)    q[i].x=size-q[i].x;
    sort(q+1,q+n+m+1);solve(1,n+m);
    for (int i=1;i<=n+m;i++)    q[i].y=size-q[i].y;
    sort(q+1,q+n+m+1);solve(1,n+m);
    for (int i=1;i<=n+m;i++)    q[i].x=size-q[i].x;
    sort(q+1,q+n+m+1);solve(1,n+m);
    for (int i=1;i<=n+m;i++)
        if (ans[i]!=MAXINT) printf("%d\n",ans[i]);
}
