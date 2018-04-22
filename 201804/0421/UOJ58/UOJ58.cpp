#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=1e5+10;
const int lim=332;
int n,m,q,ind,tot,c1,c2,LCA,cnt;
int val[N],w[N],col[N],tim[N],pre[N],bl[N];
int head[N],vis[N],dep[N],dfn[N],fa[19][N];
LL totans[N],ans;
stack<int>stk;

inline int read()
{
	int ret=0;char c='.';
	while(c<'0' || c>'9') c=getchar();
	while(c>='0' && c<='9'){ret=(ret<<1)+(ret<<3)+(c-'0');c=getchar();}
	return ret;
}

struct Tway
{
	int v,nex;
};
Tway e[N<<1];

struct Tquery
{
	int l,r,id,ls,rs,t;
};
Tquery q1[N],q2[N];

inline void add(int u,int v)
{
	e[++tot]=(Tway){v,head[u]};head[u]=tot;
	e[++tot]=(Tway){u,head[v]};head[v]=tot;
}

inline bool cmp(Tquery A,Tquery B)
{
	if(A.ls^B.ls) return A.ls<B.ls;
	if(A.rs^B.rs) return A.rs<B.rs;
	return A.t<B.t;
}

inline void getfa()
{
	for(int j=1;j<18;++j)
		for(int i=1;i<=n;++i)
			fa[j][i]=fa[j-1][fa[j-1][i]];
}

inline int dfs(int x,int f)
{
	int ret=0;
	dep[x]=dep[f]+1;dfn[x]=++ind;fa[0][x]=f;
	for(int i=head[x];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(v==f)
			continue;
		ret+=dfs(v,x);
		if(ret>=lim)
		{
			cnt++;
			while(ret>0)
				bl[stk.top()]=cnt,stk.pop(),--ret;
		}
	}
	stk.push(x);
	return ret+1;
}

inline void init()
{
	n=read();m=read();q=read();
	for(int i=1;i<=m;++i)
		val[i]=read();
	for(int i=1;i<=n;++i)
		w[i]=read();
	for(int i=1;i<n;++i)
	{
		int u=read(),v=read();
		add(u,v);
	}
	for(int i=1;i<=n;++i)
		pre[i]=col[i]=read();
	dfs(1,0);getfa();
}

inline int lca(int x,int y)
{
	if(dep[x]<dep[y])
		swap(x,y);
	int t=dep[x]-dep[y];
	for(int i=0;i<18;++i)
		if(t&(1<<i))
			x=fa[i][x];
	if(x==y)
		return x;
	for(int i=17;~i;--i)
		if(fa[i][x]^fa[i][y])
			x=fa[i][x],y=fa[i][y];
	return fa[0][x];
}

inline void calc(int x)
{
	if(vis[x])
	{
		vis[x]=0;ans-=1ll*w[tim[col[x]]]*val[col[x]];
		--tim[col[x]];
	}
	else
	{
		vis[x]=1;++tim[col[x]];
		ans+=1ll*w[tim[col[x]]]*val[col[x]];
	}
}

inline void change(int x,int y)
{
	while(x^y)
	{
		if(dep[x]<dep[y])
			swap(x,y);
		calc(x),x=fa[0][x];
	}
}

inline void update(int x,int co)
{
	if(!vis[x])
		col[x]=co;
	else
		calc(x),col[x]=co,calc(x);
}

inline void solve()
{
	for(int i=1;i<=q;++i)
	{
		int opt=read(),x=read(),y=read();
		if(opt)
		{
			if(dfn[x]>dfn[y])
				swap(x,y);
			q1[++c1].l=x;q1[c1].r=y;
			q1[c1].ls=bl[x];q1[c1].rs=bl[y];
			q1[c1].t=c2;q1[c1].id=c1;
		}
		else
		{
			q2[++c2].t=pre[x];pre[x]=y;
			q2[c2].l=x;q2[c2].r=y;
		}
	}
	sort(q1+1,q1+c1+1,cmp);c2=q1[1].t;
	for(int i=1;i<=q1[1].t;++i)
		update(q2[i].l,q2[i].r);
	change(q1[1].l,q1[1].r);
	LCA=lca(q1[1].l,q1[1].r);calc(LCA);
	totans[q1[1].id]=ans;calc(LCA);
	for(int i=2;i<=c1;++i)
	{
		while(c2<q1[i].t)
			++c2,update(q2[c2].l,q2[c2].r);
		while(c2>q1[i].t)
			update(q2[c2].l,q2[c2].t),--c2;
		change(q1[i-1].l,q1[i].l);change(q1[i-1].r,q1[i].r);
		LCA=lca(q1[i].l,q1[i].r);calc(LCA);
		totans[q1[i].id]=ans;calc(LCA);
	}
	
	for(int i=1;i<=c1;++i)
		printf("%lld\n",totans[i]);
}

int main()
{
	freopen("UOJ58.in","r",stdin);
	freopen("UOJ58.out","w",stdout);
	
	init();
	solve();
	
	return 0;
}
