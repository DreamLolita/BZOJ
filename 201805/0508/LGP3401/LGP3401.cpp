#include<bits/stdc++.h>
#define ls (x<<1)
#define rs (x<<1|1)
#define mkp(x,y) make_pair(x,y)
using namespace std;

typedef long long LL;
typedef pair<int,int> pii;
const int N=3e4+10;
const int M=N*4;
int n,m,cnt,tot;
int siz[N],dep[N],son[N],fa[N],top[N],id[N];
int b[N],ed[N],num[N],head[N];

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

pii merge(pii A,pii B)
{
    return mkp(A.first+B.first,A.second+B.second);
}

struct Segment
{
    int n0[M],n1[M],rev[M];

    void pushup(int x)
    {
        n0[x]=n0[ls]+n0[rs];n1[x]=n1[ls]+n1[rs];
        rev[x]=0;
    }

    void pushdown(int x)
    {
        if(!rev[x])
            return;
        swap(n0[ls],n1[ls]);swap(n0[rs],n1[rs]);
        rev[ls]^=1;rev[rs]^=1;rev[x]=0;
    }

    void build(int k,int x,int l,int r)
    {
        if(l==r)
        {
            if((num[l]>>k)&1) n1[x]=1;
                else n0[x]=1;
            return;
        }
        int mid=(l+r)>>1;
        build(k,ls,l,mid);build(k,rs,mid+1,r);
        pushup(x);
    } 

    void rever(int x,int l,int r,int L,int R)
    {
        if(L<=l && r<=R)
        {
            swap(n0[x],n1[x]);rev[x]^=1;
            return;
        }
        pushdown(x);
        int mid=(l+r)>>1;
        if(L<=mid)
            rever(ls,l,mid,L,R);
        if(R>mid)
            rever(rs,mid+1,r,L,R);
        pushup(x);
    }

    pii query(int x,int l,int r,int L,int R)
    {
        if(L<=l && r<=R)
            return mkp(n0[x],n1[x]);
        pushdown(x);
        int mid=(l+r)>>1;
        pii ret;ret.first=ret.second=0;
        if(L<=mid)
            ret=merge(ret,query(ls,l,mid,L,R));
        if(R>mid)
            ret=merge(ret,query(rs,mid+1,r,L,R));
        return ret;
    }

};
Segment tr[12];

void Change(int u,int w)
{
    for(int i=0;i<10;++i)
        if(((w^ed[u])>>i)&1)
            tr[i].rever(1,1,n,id[u],id[u]+siz[u]-1);
    ed[u]=w;
}

LL Query(int u,int v)
{
    LL ret=0;int x=u,y=v;
    for(int i=0;i<10;++i)
    {
        u=x;v=y;
        pii res;res.first=res.second=0;
        while(top[u]^top[v])
        {
            if(dep[top[u]]<dep[top[v]])
                swap(u,v);
            res=merge(res,tr[i].query(1,1,n,id[top[u]],id[u]));
            u=fa[top[u]];
        }
        if(dep[u]>dep[v])
            swap(u,v);
        res=merge(res,tr[i].query(1,1,n,id[u],id[v]));
        ret+=(1ll<<i)*(LL)res.first*(LL)res.second;
    }
    return ret;
}

void dfs1(int x,int f)
{
    siz[x]=1;dep[x]=dep[f]+1;fa[x]=f;
    for(int i=head[x];i;i=e[i].nex)
    {
        int v=e[i].v;
        if(v==f)
            continue;
        b[v]=b[x]^e[i].w;ed[v]=e[i].w;
        dfs1(v,x);siz[x]+=siz[v];
        if(siz[v]>siz[son[x]])
            son[x]=v;
    }
}

void dfs2(int x,int tp)
{
    id[x]=++cnt;num[cnt]=b[x];top[x]=tp;
    if(!son[x])
        return;
    dfs2(son[x],tp);
    for(int i=head[x];i;i=e[i].nex)
    {
        int v=e[i].v;
        if(v==fa[x] || v==son[x])
            continue;
        dfs2(v,v);
    }
}

int main()
{
    freopen("LGP3401.in","r",stdin);
    freopen("LGP3401.out","w",stdout);

    n=read();m=read();
    for(int i=1;i<n;++i)
    {
        int u=read(),v=read(),w=read();
        add(u,v,w);
    }
    dfs1(1,1);
    dfs2(1,1);
    for(int i=0;i<10;++i)
        tr[i].build(i,1,1,n);
    for(int i=1;i<=m;++i)
    {
        int opt=read(),u=read(),v=read();
        if(opt&1)
            printf("%lld\n",Query(u,v));
        else
        {
            int w=read();
            if(u!=fa[v])
                swap(u,v);
            Change(v,w);
        }
    }

    return 0;
}

