#include<bits/stdc++.h>
using namespace std;

const int N=2e5+10;
const int M=4e6+10;
int n,tn,m,root,midedge,tot,TOT,mx,cnt,rt;
int head[N],HEAD[N],tail[N];
int mark[N],siz[N];

struct Tway
{
	int v,nex,w,pre;
};
Tway e[M],E[M];

struct Tpoint
{
	int u,dis;
	Tpoint(){}
	Tpoint(int uu,int ddis){
		u=uu;dis=ddis;
	}
	bool operator <(const Tpoint &A)const{
		return dis<A.dis;
	}
};

struct Tnode
{
	int rt,midlen,ans;
	int ls,rs;
	priority_queue<Tpoint>q;
};
Tnode tr[N<<1];

void init()
{
	tot=0;
	memset(head,-1,sizeof(head));
}

void INIT()
{
	TOT=0;
	memset(HEAD,-1,sizeof(HEAD));
}

void addone(int u,int v,int w)
{
	e[tot]=(Tway){v,head[u],w,0};head[u]=tot++;
}

void add(int u,int v,int w)
{
	e[tot]=(Tway){v,head[u],w,0};head[u]=tot++;
	e[tot]=(Tway){u,head[v],w,0};head[v]=tot++;
}

void ADD(int u,int v,int w)
{
	E[TOT]=(Tway){v,HEAD[u],w,0};HEAD[u]=TOT++;
	E[TOT]=(Tway){u,HEAD[v],w,0};HEAD[v]=TOT++;
}

void dele(int u,int i)
{
	if(HEAD[u]==i)	HEAD[u]=E[i].nex;
	else E[E[i].pre].nex=E[i].nex;
	if(tail[u]==i)	tail[u]=E[i].pre;
	else E[E[i].nex].pre=E[i].pre;
}

void build(int x,int f)
{
	int fa=0;
	for(int i=head[x];~i;i=e[i].nex)
	{
		int v=e[i].v,w=e[i].w;
		if(v!=f)
		{
			if(fa)
			{
				mark[++tn]=0;ADD(tn,fa,0);
				fa=tn;ADD(v,fa,w);
				build(v,x);
			}
			else
			{
				ADD(x,v,w);fa=x;
				build(v,x);
			}
		}
	}
}

void get_pre()
{
	memset(tail,-1,sizeof(tail));
	for(int i=1;i<=tn;++i)
	{
		for(int j=HEAD[i];~j;j=E[j].nex)
		{
			E[j].pre=tail[i];
			tail[i]=j;
		}
	}
}

void rebuild()
{
	INIT();
	tn=n;
	for(int i=1;i<=tn;++i)
		mark[i]=1;
	build(1,0);
	get_pre();init();
}

void dfs_size(int u,int fa,int dir)
{
	addone(u,rt,dir);
	if(mark[u])
		tr[rt].q.push(Tpoint(u,dir));
	siz[u]=1;
	for(int i=HEAD[u];~i;i=E[i].nex)
	{
		int v=E[i].v,w=E[i].w;
		if(v!=fa)
		{
			dfs_size(v,u,dir+w);
			siz[u]+=siz[v];
		}
	}
}

void dfs_edge(int u,int dir)
{
	if(max(siz[u],siz[tr[rt].rt]-siz[u])<mx)
	{
		mx=max(siz[u],siz[tr[rt].rt]-siz[u]);
		midedge=dir;
	}
	for(int i=HEAD[u];~i;i=E[i].nex)
	{
		int v=E[i].v;
		if(i!=(dir^1))
			dfs_edge(v,i);
	}
}

void pushup(int rt)
{
	tr[rt].ans=-1;
	while(!tr[rt].q.empty() && mark[tr[rt].q.top().u]==0)
		tr[rt].q.pop();
	int ls=tr[rt].ls,rs=tr[rt].rs;
	if(ls==0 && rs==0)
	{
		if(mark[tr[rt].rt])
			tr[rt].ans=0;
	}
	else
	{
		tr[rt].ans=max(tr[rt].ans,tr[ls].ans);
		tr[rt].ans=max(tr[rt].ans,tr[rs].ans);
		if(!tr[ls].q.empty() && !tr[rs].q.empty())
			tr[rt].ans=max(tr[rt].ans,tr[ls].q.top().dis+tr[rs].q.top().dis+tr[rt].midlen);
	}
}

void dfs(int u,int i)
{
	rt=i;mx=tn;midedge=-1;
	tr[i].rt=u;
	dfs_size(u,0,0);
	dfs_edge(u,-1);
	if(~midedge)
	{
		int p1=E[midedge].v,p2=E[midedge^1].v;
		tr[i].midlen=E[midedge].w;
		tr[i].ls=++cnt;tr[i].rs=++cnt;
		
		dele(p1,midedge^1);dele(p2,midedge);
		dfs(p1,tr[i].ls);dfs(p2,tr[i].rs);	
	}
	pushup(i);
}

void update(int x)
{
	mark[x]^=1;
	for(int i=head[x];~i;i=e[i].nex)
	{
		int v=e[i].v,w=e[i].w;
		if(mark[x]==1)
			tr[v].q.push(Tpoint(x,w));
		pushup(v);
	}
}

int main()
{
	freopen("SPOJ_QTREE4.in","r",stdin);
	freopen("SPOJ_QTREE4.out","w",stdout);
	
	scanf("%d",&n);
	init();
	for(int i=1;i<n;++i)
	{
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		add(u,v,w);
	}
	rebuild();
	cnt=1;dfs(1,1);
	
	scanf("%d",&m);
	while(m--)
	{
		char opt[2];int x;
		scanf("%s",opt);
		if(opt[0]=='A')
		{
			if(tr[1].ans==-1) puts("They have disappeared.");
			else printf("%d\n",tr[1].ans);
		}
		else
		{
			scanf("%d",&x);
			update(x);
		}
	}
	
	return 0;
}
