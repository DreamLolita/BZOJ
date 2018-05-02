#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int mod=20160501;
const int inv=10080251;
const int N=1e5+10;
const int M=N<<6;
int n,q,now,cnt,tot,ind;
int head[N],siz[N],dep[N],son[N];
int top[N],beg[N],re[N],fa[19][N];
LL val[N];
LL ans;

int read()
{
	int ret=0;char c='.';
	while(c<'0' || c>'9')c=getchar();
	while(c>='0' && c<='9'){ret=(ret<<3)+(ret<<1)+(c-'0');c=getchar();}
	return ret; 
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
	siz[x]=1;dep[x]=dep[f]+1;fa[0][x]=f;son[x]=0;
	for(int i=head[x];i;i=e[i].nex)
	{
		int v=e[i].v;
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
	top[x]=tp;beg[x]=++ind;re[ind]=x;
	if(!son[x])
		return;
	dfs2(son[x],tp);
	for(int i=head[x];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(v==fa[0][x] || v==son[x])
			continue;
		dfs2(v,v);
	}
}

void init_fa()
{
	for(int i=1;i<18;++i)
		for(int j=1;j<=n;++j)
			fa[i][j]=fa[i-1][fa[i-1][j]];
}

int lca(int x,int y)
{
	if(dep[x]<dep[y])
		swap(x,y);
	int t=dep[x]-dep[y];
	for(int i=0;i<18;++i)
		if(t&(1<<i))
			x=fa[i][x];
	for(int i=17;~i;--i)
		if(fa[i][x]^fa[i][y])
			x=fa[i][x],y=fa[i][y];
	return x==y?x:fa[0][x];
}

struct Seqment
{
	int sz,ls[M],rs[M],root[N];
	LL tar[M],ad[M],ad2[M],ai[M],d[M],d2[M];
	
	void copy(int x,int y)
	{
		ls[x]=ls[y];rs[x]=rs[y];
		tar[x]=tar[y];ad[x]=ad[y];ad2[x]=ad2[y];
		ai[x]=ai[y];d[x]=d[y];d2[x]=d2[y];
	}
	
	void pushup(int x)
	{
		int l=ls[x],r=rs[x];
		ai[x]=(ai[l]+ai[r])%mod;
		ad[x]=(ad[l]+ad[r])%mod;
		ad2[x]=(ad2[l]+ad2[r])%mod;
	}
	
	void pushdown(int x,int L,int R)
	{
		if(!tar[x])
			return;
		int mid=(L+R)>>1;LL t=tar[x];
		copy(++sz,ls[x]);
		(ai[sz]+=t*(mid-L+1))%=mod;(ad[sz]+=t*d[sz])%=mod;(ad2[sz]+=t*d2[sz])%=mod;
		(tar[sz]+=t)%=mod;ls[x]=sz;
		copy(++sz,rs[x]);
		(ai[sz]+=t*(R-mid))%=mod;(ad[sz]+=t*d[sz])%=mod;(ad2[sz]+=t*d2[sz])%=mod;
		(tar[sz]+=t)%=mod;rs[x]=sz;
		tar[x]=0;
	}
	
	void build(int &x,int l,int r)
	{
		x=++sz;
		if(l==r)
		{
			int p=re[l];
			ai[x]=val[p];ad[x]=1ll*val[p]*dep[p]%mod;ad2[x]=ad[x]*dep[p]%mod;
			d[x]=dep[p];d2[x]=d[x]*dep[p]%mod;
			return;
		}
		int mid=(l+r)>>1;
		build(ls[x],l,mid);
		build(rs[x],mid+1,r);
		d[x]=d[ls[x]]+d[rs[x]];d2[x]=d2[ls[x]]+d2[rs[x]];
		pushup(x);
	}
	
	LL query(int x,int l,int r,int L,int R,LL t)
	{
//printf("%d %d %d %d %lld\n",l,r,L,R,t);
		if(L<=l && r<=R)
		{
			LL t1=ad[x]*(2ll*t+1)%mod,t2=ai[x]*t*(t+1)%mod;
//printf("getit:%lld %lld %lld %lld\n",ad2[x],t1,t2,(LL)((ad2[x]+t1+t2)%mod+mod)%mod);
			return (LL)((ad2[x]+t1+t2)%mod+mod)%mod;
		}
		pushdown(x,l,r);
		int mid=(l+r)>>1;LL ret=0;
		if(L<=mid)
			ret+=query(ls[x],l,mid,L,R,t);
		if(R>mid)
			ret+=query(rs[x],mid+1,r,L,R,t);
		return ret%mod;	
	}
	
	LL calc(int x,int y,int k)
	{
		LL ret=0;
		int LCA=lca(x,y),t,p1=dep[y]-2*dep[LCA],p2=-dep[y]-1;
		while(top[x]!=top[y])
		{
//printf("%d %d %lld\n",x,y,ret);
			if(dep[top[x]]>dep[top[y]])
			{
				t=top[x];
				(ret+=query(root[k],1,n,beg[t],beg[x],p1))%=mod;
				x=fa[0][t];
			}
			else
			{
				t=top[y];
				(ret+=query(root[k],1,n,beg[t],beg[y],p2))%=mod;
				y=fa[0][t];
			}
		}
		if(dep[x]>=dep[y])
			(ret+=query(root[k],1,n,beg[y],beg[x],p1))%=mod;
		else
			(ret+=query(root[k],1,n,beg[x],beg[y],p2))%=mod;
//printf("%d %d %lld\n",x,y,ret);
		return ret;
	}
	
	void update(int x,int &y,int l,int r,int L,int R,LL t)
	{
		pushdown(x,l,r);
		if(x==y)
			y=++sz,copy(y,x);
		if(L<=l && r<=R)
		{
			(tar[y]+=t)%=mod;(ai[y]+=t*(r-l+1))%=mod;
			(ad[y]+=t*d[y])%=mod;(ad2[y]+=t*d2[y])%=mod;
			return;
		}
		int mid=(l+r)>>1;
		if(L<=mid)
			update(ls[x],ls[y],l,mid,L,R,t);
		if(R>mid)
			update(rs[x],rs[y],mid+1,r,L,R,t);
		pushup(y);
	}
	
	void change(int x,int y,int k,LL t)
	{
		if(!root[k])
			root[k]=root[now];
		int p;
		while(top[x]!=top[y])
		{
			if(dep[top[x]]<dep[top[y]])
				swap(x,y);
			p=top[x];
			update(root[now],root[k],1,n,beg[p],beg[x],t);
			x=fa[0][p];
		}
		if(dep[x]>dep[y])
			swap(x,y);
		update(root[now],root[k],1,n,beg[x],beg[y],t);
	}
}tr;

int main()
{
	freopen("zootopia.in","r",stdin);
	freopen("zootopia.out","w",stdout);
	
	n=read();q=read();
	for(int i=1;i<n;++i)
	{
		int u=read(),v=read();
		addedge(u,v);	
	}	
	for(int i=1;i<=n;++i)
		val[i]=read();
	dfs1(1,0);dfs2(1,1);
	init_fa();tr.build(tr.root[0],1,n);
	while(q--)
	{
		int opt=read(),x=read();x^=ans;
//		printf("q:%d %d x:%d ",q,opt,x);
		if(opt==1)
		{
			int y=read(),z=read();y^=ans;
//printf("y:%d %d",y,z);
			tr.change(x,y,++cnt,z);
			now=cnt;
		}
		else
		if(opt==2)
		{
			int y=read();y^=ans;
//printf("y:%d",y);
//printf(" lasans:%d ",tr.calc(x,y,now));
			ans=tr.calc(x,y,now)*inv%mod;
			printf("%lld\n",ans);
		}
		else
			now=x;
//cerr<<q<<endl;
	}
	return 0;
}
