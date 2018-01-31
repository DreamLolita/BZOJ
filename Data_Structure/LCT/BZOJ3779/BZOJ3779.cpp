#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int INF=1e9+7;
const int N=1e5+10;
int n,m,rt,tot,tim;
int Log[N],beg[N],en[N],dep[N];
int head[N],siz[N],fa[22][N];

struct Tway
{
	int v,nex;
};
Tway e[N<<1];

struct BIT
{
	LL sum[N];
	
	int lowbit(int x)
	{
		return x&(-x);
	}
	
	void update(int x,LL v)
	{
		for(;x<=n;x+=lowbit(x))
			sum[x]+=v;
	}
	
	LL query(int x)
	{
		LL ret=0;
		for(;x;x-=lowbit(x))
			ret+=sum[x];
		return ret;
	}
};
BIT t1,t2;

struct LCT
{
	int ch[N][2],fa[N],rev[N];
	
	bool isroot(int x)
	{
		return ch[fa[x]][0]!=x && ch[fa[x]][1]!=x;
	}
	
	void pushdown(int x)
	{
		if(rev[x])
		{
			swap(ch[x][0],ch[x][1]);
//			if(ch[x][0]);
				rev[ch[x][0]]^=1;
//			if(ch[x][1])
				rev[ch[x][1]]^=1;
			rev[x]=0;
		}
	}
	
	void update(int x)
	{
		if(!isroot(x))
			update(fa[x]);
		pushdown(x);
	}
	
	void rotate(int x)
	{
		int y=fa[x],z=fa[y],kind=(x==ch[y][1]);
		if(!isroot(y))
			ch[z][y==ch[z][1]]=x;
		fa[x]=z;fa[y]=x;
		ch[y][kind]=ch[x][kind^1];
		if(ch[x][kind^1])
			fa[ch[x][kind^1]]=y;
		ch[x][kind^1]=y;
	}
	
	void splay(int x)
	{
		update(x);
		while(!isroot(x))
		{
			int y=fa[x],z=fa[y];
			if(!isroot(y))
			{
				if((x==ch[y][0])^(y==ch[z][0]))
					rotate(x);
				else
					rotate(y);
			}
			rotate(x);
		}
	}
};
LCT tr;

/*void debug(int x)
{
	if(ch[x][0])
		debug(ch[x][0]);
	printf("%d %d\n",tr.ch[x][0],tr.fa[x]);
	if(ch[x][1])
		debug(ch[x][1]);
}*/

void sumup(int x,LL v)
{
//	printf("update:%d %I64d\n",x,v);
    t1.update(x,1ll*v*x),t2.update(x,v);
}

LL getsum(int x)
{
//	printf("%d %d %d\n",t2.query(n),t2.query(x),t1.query(x));
    return 1ll*(t2.query(n)-t2.query(x))*x+t1.query(x);
}

int findx(int x,int y)
{
    for(int i=Log[y];i>=0;i--)   
	{
//		printf("xxx:%d %d %d %d\n",x,i,Log[y],y);
		if((1<<i)<=y)  x=fa[i][x],y-=(1<<i);
		
	}
	return x;
}

void modify(int &x,LL v)
{
    if(!x)  return;
    tr.pushdown(x);
    while(tr.ch[x][0])   
		x=tr.ch[x][0],tr.pushdown(x);
    tr.splay(x);
    
    if(x==rt)   
		sumup(n,v);
    else    
	if(beg[rt]<beg[x] || beg[rt]>en[x])    
		sumup(beg[x]-1,-v),sumup(en[x],v);
    else
    {
        int y=findx(rt,dep[rt]-dep[x]-1);
//        printf("yyy:%d %d %d %d\n",y,rt,dep[rt],dep[x]);
        sumup(beg[y]-1,v);sumup(en[y],-v);sumup(n,v);
    }
}

double getans(int x)
{
//	printf("x:%d\n",x);
    if(x==rt)   
		return 1.0*getsum(n)/n;
    else    
	if(beg[rt]<beg[x] || beg[rt]>en[x])    
	{
//		printf("beg:%d end:%d\n",beg[x],en[x]);
//		printf("sum:%I64d\n",getsum(en[x])-getsum(beg[x]-1));
		return 1.0*(getsum(en[x])-getsum(beg[x]-1))/(en[x]-beg[x]+1);
	}
	else
    {
        int y=findx(rt,dep[rt]-dep[x]-1);
        return 1.0*(getsum(beg[y]-1)+getsum(n)-getsum(en[y]))/(beg[y]-1+n-en[y]);
    }
}

void access(int x)
{
    for(int y=0,t;x;)
    {
        tr.splay(x);t=tr.ch[x][1];modify(y,-1);
		tr.ch[x][1]=y;modify(t,1);
		y=x;x=tr.fa[x];
	}
}

void makeroot(int x)
{
    access(x);
	tr.splay(x);
	tr.rev[x]^=1;rt=x;
}

void add(int u,int v)
{
	++tot;
	e[tot].v=v;e[tot].nex=head[u];head[u]=tot;
}

void dfs(int u)
{
	siz[u]=1;beg[u]=++tim;
	for(int i=head[u];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(v!=fa[0][u])
		{
			fa[0][v]=u;
			dep[v]=dep[u]+1;
			dfs(v);
			siz[u]+=siz[v];
		}
	}
	en[u]=tim;
}

void init()
{
	scanf("%d%d",&n,&m);rt=1;
	for(int i=2;i<=n;++i)
		Log[i]=Log[i>>1]+1;
	for(int i=1;i<n;++i)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v);add(v,u);
	}	
	dep[1]=1;dfs(1);
	for(int j=1;(1<<j)<=n;++j)
		for(int i=1;i<=n;++i)
			fa[j][i]=fa[j-1][fa[j-1][i]];
/*	for(int j=1;(1<<j)<=n;++j)
    {
		for(int i=1;i<=n;++i)
			printf("%d ",fa[j][i]);
		printf("\n");
	}*/
	
	
	for(int i=1;i<=n;++i)
	{
		t1.update(beg[i],dep[i]),tr.fa[i]=fa[0][i];
//		printf("%d %d\n",beg[i],dep[i]);
	}
//	for(int j=1;j<=n;j++)  printf("%I64d\n",getsum(beg[j])-getsum(beg[j]-1));
}

void solve()
{
	int x;char opt[10];
	for(int i=1;i<=m;++i)
	{
		scanf("%s%d",opt,&x);
		if(opt[2]=='Q')
			printf("%0.10f\n",getans(x));
		else
		if(opt[2]=='L')
			access(x),tr.splay(x);
		else
			makeroot(x);
//		if(i==3)
//			return;
//		for(int j=1;j<=n;j++)  printf("%I64d\n",getsum(beg[j])-getsum(beg[j]-1));

	}
}

int main()
{
//	freopen("BZOJ3779.in","r",stdin);
//	freopen("BZOJ3779.out","w",stdout);
	
	init();
	solve();
	
	return 0;
}
