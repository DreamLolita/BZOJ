#include<bits/stdc++.h>
#define ls (x<<1)
#define rs (x<<1|1)
#define mkp(x,y) make_pair(x,y)
using namespace std;

const int N=1e5+10;
const int M=N*8;
typedef long long LL;
typedef long double ldb;
typedef pair<int,int> pii;
int n,Q,tot,ind;
int head[N],dep[N],siz[N],son[N];
int fa[N],top[N],nu[N],pos[N];
int val[N],price[N];

LL read()
{
	LL ret=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c)){ret=(ret<<1ll)+(ret<<3ll)+(c^48);c=getchar();}
	return f?ret:-ret;
}

struct Tway
{
    int v,nex;
};
Tway e[N<<1];

void addedge(int u,int v)
{
    e[++tot]=(Tway){v,head[u]};head[u]=tot;
    e[++tot]=(Tway){u,head[v]};head[v]=tot;
}

void dfs1(int x,int f)
{
    fa[x]=f;dep[x]=dep[f]+1;siz[x]=1;
    for(int i=head[x];i;i=e[i].nex)
    {
        int v=e[i].nex;
        if(v==f)
            continue;
       dfs1(v,x);
       siz[x]+=siz[v];
       if(siz[v]>siz[son[x]])
           son[x]=v;
    }
}

void dfs2(int x,int tp)
{
    top[x]=tp;pos[x]=++ind;nu[ind]=x;
    if(!son[x])
        return;
    dfs2(son[x],tp);
    for(int i=head[x];i;i=e[i].nex)
    {
        int v=e[i].v;
        if(v==son[x] || v==fa[v])
            continue;
        dfs2(v,v);
    }

}

struct Segment
{
    int mx[M],mi[M],add[M],mxl[M],mxr[M];   
    
    void pushup(int x)
    {
        mxl[x]=max(mx[rs]-mi[ls],max(mxl[ls],mxl[rs]));
        mxr[x]=max(mx[ls]-mi[ls],max(mxr[ls],mxr[rs]));
        mx[x]=max(mx[ls],mx[rs]);mi[x]=min(mi[ls],mi[rs]);
    }

    void pushdown(int x)
    {
        if(!add[x])
            return;
        int t=add[x];
        mx[ls]+=t;mxl[ls]+=t;mxr[ls]+=t;
        mx[rs]+=t;mxl[rs]+=t;mxr[rs]+=t;
        add[x]=0;
    }

    void build(int x,int l,int r)
    {
        if(l==r)
        {
            add[x]=mxl[x]=mxr[x]=0;
            mx[x]=mi[x]=val[l];
            return;
        }
        int mid=(l+r)>>1;
        build(ls,l,mid);build(rs,mid+1,r);
        pushup(x);
    }

    void update(int x,int l,int r,int L,int R,int c)
    {
        if(L<=l && r<=R)
        {
            mx[x]+=c;mi[x]+=c;add[x]+=c;
            return;
        }
        pushdown(x);
        int mid=(l+r)>>1;
        if(L<=mid)
            update(ls,l,mid,L,R,c);
        if(R>mid)
            update(rs,mid+1,r,L,R,c);
        pushup(x);
    }

    LL query(int x,int l,int r,int L,int R,int op,LL &mxp,LL &mip)
    {
        if(L<=l && r<=R)
        {
            mxp=mx[x];mip=mi[x];
            if(op==0)
                return mxl[x];
            return mxr[x];
        }
        pushdown(x);
        int mid=(l+r)>>1;
        if(R<=mid)
            return query(ls,l,mid,L,R,op,mxp,mip);
        if(L>mid)
            return query(rs,mid+1,r,L,R,op,mxp,mip);
        LL lmx,lmi,rmx,rmi,ret=0;
        ret=max(ret,query(ls,l,mid,L,R,op,lmx,lmi));
        ret=max(ret,query(rs,mid+1,r,L,R,op,rmx,rmi));
        if(op==0)
            ret=max(ret,rmx-rmi);
        else
            ret=max(ret,rmx-lmi);
        mxp=max(lmx,rmx);mip=min(lmi,rmi);
        return ret;
    }
}tr;

LL solve(int u,int v,int c)
{
    LL ret=0,tmx,tmi;
    LL mxu=0,mxv=0,miv=tr.mx[1],miu=tr.mx[1];
    int fu=top[u],fv=top[v];
    while(fu!=fv)
	{
        if(dep[fu]>=dep[fv])
		{
            ret=max(ret,tr.query(1,1,ind,pos[fu],pos[u],1,tmx,tmi) );
            ret=max(ret,tmx-miu);
            ret=max(ret,mxv-tmi);
            mxu=max(mxu,tmx); 
            miu=min(miu,tmi);  
            tr.update(1,1,ind,pos[fu],pos[u],(LL)c);
            u=fa[fu];fu=top[u];
        }
        else
		{
            ret=max(ret,tr.query(1,1,ind,pos[fv],pos[v],0,tmx,tmi) );
            ret=max(ret,mxv-tmi);
            ret=max(ret,tmx-miu);
            mxv=max(mxv,tmx);
            miv=min(miv,tmi);
            tr.update(1,1,ind,pos[fv],pos[v],(LL)c);
            v=fa[fv]; fv=top[v];
        }
    }
    if(dep[u]>=dep[v])
	{
        ret=max(ret,tr.query(1,ind,1,pos[v],pos[u],1,tmx,tmi) );
        ret=max(ret,mxv-tmi);
        ret=max(ret,tmx-miu);
        tr.update(1,1,ind,pos[v],pos[u],(LL)c);
    }
    else
	{
        ret=max(ret,tr.query(1,1,ind,pos[u],pos[v],0,tmx,tmi) );
        ret=max(ret,mxv-tmi);
        ret=max(ret,tmx-miu);
        tr.update(1,1,ind,pos[u],pos[v],(LL)c);
    }
    return ret;
}

int main()
{
	freopen("HDU5052.in","r",stdin);
	freopen("HDU5052.out","w",stdout);

	int cas=read();
	
	while(cas--)
	{
		memset(head,0,sizeof(head));tot=ind=0;
		n=read();
		for(int i=1;i<=n;++i)
			price[i]=read();
		for(int i=1;i<n;++i)
		{
			int u=read(),v=read();
	        addedge(u,v);			
		}
	    dfs1(1,0);dfs2(1,1);
	    ind=n;
	    for(int i=1;i<=n;++i)
	    	val[pos[i]]=price[i];
	    tr.build(1,1,ind);
	    Q=read();
	    while(Q--)
	    {
	    	int a=read(),b=read(),c=read();
	    	printf("%lld\n",solve(a,b,c));
		}
	}

	return 0;
}

