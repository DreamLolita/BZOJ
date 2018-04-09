#include<cstdio>
#include<string>
#include<map>
#include<algorithm>
#define INF 1000000000
using namespace std;
struct dui
{
    int x,id;
}d[10000010];
string str;
char s1[55],s2[55];
map<string,int> mp;
int n,s,x,cnt,m,edgenum,Edgenum,S,T,u,p1,p2;
int vet[10000010],next[10000010],head[5000010],tick[10000010],tim[10000010],Vet[10000010],Next[10000010],Head[5000010],Tim[10000010];
int q[5000010],dis[5000010],du[5000010],Min[5000010],flag[5000010];
void add(int u,int v,int w1,int w2)
{
    edgenum++;
    vet[edgenum]=v;
    next[edgenum]=head[u];
    head[u]=edgenum;
    tick[edgenum]=w1;
    tim[edgenum]=w2;
}
void Add(int u,int v,int w)
{
    Edgenum++;
    Vet[Edgenum]=v;
    Next[Edgenum]=Head[u];
    Head[u]=Edgenum;
    Tim[Edgenum]=w;
}
void shiftdown(int i,int n)
{
    while (i*2<=n)
    {
        int t=i*2;
        if (t+1<=n&&d[t+1].x<d[t].x) t++;
        if (d[i].x>d[t].x)
        {
            q[d[i].id]=t;
            q[d[t].id]=i;
            swap(d[i],d[t]);
            i=t;
        }else break;
    }
}
void shiftup(int i)
{
    while (i>1)
    {
        int t=i/2;
        if (d[i].x<d[t].x)
        {
            q[d[i].id]=t;
            q[d[t].id]=i;
            swap(d[i],d[t]);
            i=t;
        }else break;
    }
}
int main()
{
	freopen("BZOJ4489.in","r",stdin);
	freopen("BZOJ4489.out","w",stdout);
    scanf("%d%d",&s,&n);
    for (int i=1;i<=n;i++)
    {
        scanf("%s",s1);
        str=s1;
        mp[str]=i;
    }
    cnt=n;
    for (int i=1;i<=s;i++)
    {
        scanf("%d",&x);
        for (int j=1;j<=x;j++)
        {
            scanf("%s",s1);
            str=s1;
            u=mp[str];
            add(cnt+j,u,0,0);
            add(u,cnt+j,1,0);
            add(cnt+j+x,u,0,0);
            add(u,cnt+j+x,1,0);
        }
        cnt+=2*x;
        for (int j=2;j<=x;j++) add(cnt-j-x+1,cnt-j-x+2,0,1);
        for (int j=1;j<x;j++) add(cnt-j+1,cnt-j,0,1);
    }
    scanf("%s%s",s1,s2);
    str=s1;S=mp[str];
    str=s2;T=mp[str];
    for (int i=1;i<=cnt;i++)
        Min[i]=INF;
    Min[S]=0;
    m=cnt;
    for (int i=1;i<=cnt;i++)
    {
        d[i].x=Min[i];
        d[i].id=i;
        q[i]=i;
        shiftup(i);
    }
    for (int i=1;i<=cnt;i++)
    {
        int u=d[1].id;
        flag[d[1].id]=1;
        q[d[m].id]=1;
        d[1]=d[m];
        m--;
        shiftdown(1,m);
        for (int e=head[u];e;e=next[e])
        {
            int v=vet[e];
            if (!flag[v])
            if (Min[u]+tick[e]<Min[v])
            {
                Min[v]=Min[u]+tick[e];
                d[q[v]].x=Min[v];
                shiftup(q[v]);
            }
        }
    }
    if (Min[T]>=INF) {printf("-1\n0\n");return 0;}
    printf("%d\n",Min[T]);
    
    for (int i=1;i<=cnt;i++)
    {
        for (int e=head[i];e;e=next[e])
        {
            int v=vet[e];
            if (Min[i]+tick[e]==Min[v]) {Add(i,v,tim[e]);du[v]++;}
        }
    }

    for (int i=1;i<=cnt;i++)
        dis[i]=-INF;
    for (int i=1;i<=cnt;i++)if (!du[i]) q[++p2]=i;
    while (p1<p2)
    {   
        p1++;
        u=q[p1];
        for (int e=Head[u];e;e=Next[e])
        {
            int v=Vet[e];
            du[v]--;
            if (du[v]==0) q[++p2]=v;
        }
    }
    dis[S]=0;
    for (int i=1;i<=cnt;i++)
    {
        int u=q[i];
        for (int e=Head[u];e;e=Next[e])
        {
            int v=Vet[e];
            dis[v]=max(dis[v],dis[u]+Tim[e]);
        }
    }
    printf("%d\n",dis[T]);
}
