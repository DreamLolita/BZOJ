#include<bits/stdc++.h>
using namespace std;

const int N=5e5+5;
int n,tot;
int c[N],fa[N],ti[N],head[N];

struct Tway
{
	int v,nex;
};
Tway e[N<<1];

struct Tnode
{
	int t,b;
};
Tnode a[N];

void add(int u,int v)
{
	e[++tot]=(Tway){v,head[u]};head[u]=tot;
}

bool cmp(Tnode A,Tnode B)
{
	return max(A.b,2+A.t+B.b)<max(B.b,2+A.b+B.t);
}

void solve(int x)
{
	int cnt=0;
	for(int i=head[x];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(v==fa[x])
			continue;
		fa[v]=x;
		solve(v);
		ti[x]+=2+ti[v];
	}
	for(int i=head[x];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(v==fa[x])
			continue;
		++cnt;
		a[cnt].t=ti[v];a[cnt].b=c[v];
	}
	sort(a+1,a+cnt+1,cmp);
	
	int sum=0,mx=0;
	for(int i=1;i<=cnt;++i)
	{
		++sum;
		mx=max(mx,sum+a[i].b);
		sum+=a[i].t+1;
	}
	if(x==1)
		c[x]=max(sum+c[x],mx);
	else
		c[x]=max(c[x],mx);
}

int main()
{
	freopen("BZOJ3829.in","r",stdin);
	freopen("BZOJ3829.out","w",stdout);
	
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%d",&c[i]);
	for(int i=1;i<n;++i)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);add(y,x);
	}
	solve(1);
	printf("%d\n",c[1]);
	
	return 0;
}
