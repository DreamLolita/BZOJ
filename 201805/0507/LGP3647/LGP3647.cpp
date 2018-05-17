#include<bits/stdc++.h>
using namespace std;

const int INF=0x3f3f3f3f;
const int N=2e5+10;
int n,ans,tot;
int head[N],f[N],mx[N],mv[N],cm[N],cv[N];

int read()
{
    int ret=0,f=1;char c=getchar();
    while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
    while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c^48);c=getchar();}
    return f?ret:-ret;
}

struct Tway
{
    int v,nex,w;
};
Tway e[N<<1];

void add(int u,int v,int w)
{
    e[++tot]=(Tway){v,head[u],w};head[u]=tot;
    e[++tot]=(Tway){u,head[v],w};head[v]=tot;
}

void update(int c,int x,int v)
{
    if(v>mx[c])
    {
        cm[c]=mx[c];cv[c]=mv[c];
        mx[c]=v;mv[c]=x;
    }
    else
    if(v>cm[c])
        cm[c]=v,cv[c]=x;
}

void dfs(int x,int fa)
{
    f[x]=0;mx[x]=cm[x]=-INF;mv[x]=cv[x]=0;
    for(int i=head[x];i;i=e[i].nex)
    {
        int v=e[i].v;
        if(v==fa)
            continue;
        dfs(v,x);
        int tmp=max(f[v],f[v]+mx[v]+e[i].w);
        f[x]+=tmp;
        update(x,v,-tmp+f[v]+e[i].w);
    }
}

void mvroot(int x,int fa)
{
    ans=max(ans,f[x]);
    for(int i=head[x];i;i=e[i].nex)
    {
        int v=e[i].v;
        if(v==fa)
            continue;
        int tmp=max(f[v],f[v]+mx[v]+e[i].w);
        int cur=max(f[x]-tmp,f[x]-tmp+(v==mv[x]?cm[x]:mx[x])+e[i].w);
        f[v]+=cur;
        update(v,x,-cur-tmp+f[x]+e[i].w);
        mvroot(v,x);
    }
}


int main()
{
    freopen("LGP3647.in","r",stdin);
    freopen("LGP3647.out","w",stdout);

    n=read();
    for(int i=1;i<n;++i)
    {
        int u=read(),v=read(),w=read();
        add(u,v,w);
    }
    dfs(1,0);
    mvroot(1,0);
    printf("%d\n",ans);

    return 0;
}
