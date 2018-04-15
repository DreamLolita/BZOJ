#include<bits/stdc++.h>	
using namespace std;

const int N=1e5+10;
int n,m,mxup,mxdown,sum,tot,root,ans;
int head[N],f[N],son[N],h[N];
bool vis[N];
stack<int>mx[N],mi[N];

struct Tway
{
	int v,nex;
};
Tway e[N<<1];

void add(int u,int v)
{
	e[++tot]=(Tway){v,head[u]};head[u]=tot;
	e[++tot]=(Tway){u,head[v]};head[v]=tot;
}

void getroot(int x,int fa)
{
	son[x]=1;f[x]=0;
	for(int i=head[x];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(!vis[v] && v!=fa)
		{
			getroot(v,x);
			son[x]+=son[v];
			f[x]=max(f[x],son[v]);
		}
	}
	f[x]=max(f[x],sum-son[x]);
	if(f[x]<f[root])
		root=x;
}

int getmi(int l,int r,int x)//down
{
	int ret=l;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(h[mi[mid].top()]>x)
			ret=mid,l=mid+1;
		else
			r=mid-1;
	}
	return ret;
}

int getmx(int l,int r,int x)
{
	int ret=l;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(h[mx[mid].top()]<x)
			ret=mid,l=mid+1;
		else
			r=mid-1;
	}
	return ret;
}

void dfs(int x,int fa,int lenmi,int lenmx)
{
//printf("ways:%d %d %d %d\n",x,fa,lenmi,lenmx);
	int mipos=getmi(1,lenmi,h[x]),tmp1=mi[mipos].top();
	int mxpos=getmx(1,lenmx,h[x]),tmp2=mx[mxpos].top();
//printf("%d %d %d %d\n",mipos,mxpos,tmp1,tmp2);	
	
	if(mipos==lenmi && h[x]<h[tmp1])
		++lenmi,++mipos;
	if(h[x]<h[tmp1])
		mi[mipos].push(x);
	mxdown=max(mxdown,lenmi);
	
	if(mxpos==lenmx && h[x]>h[tmp2])
		++lenmx,++mxpos;
	if(h[x]>h[tmp2])
		mx[mxpos].push(x);
	mxup=max(mxup,lenmx);

	for(int i=head[x];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(v!=fa && !vis[v])
			dfs(v,x,lenmi,lenmx);	
	}	
	if(h[x]<h[tmp1])
		mi[mipos].pop();
	if(h[x]>h[tmp2])
		mx[mxpos].pop();
}

void calc(int x)
{
//printf("now:%d\n",x);
	mx[1].push(x);mi[1].push(x);
	int tmpup=0,tmpdown=0;
	for(int i=head[x];i;i=e[i].nex)
	{
		mxup=mxdown=1;
		int v=e[i].v;
		if(!vis[v])
			dfs(v,x,1,1);
		ans=max(ans,tmpup+mxdown-1);ans=max(ans,tmpdown+mxup-1);
		tmpup=max(tmpup,mxup);tmpdown=max(tmpdown,mxdown);
//		printf("%d %d\n",mxup,mxdown);
	}
	mi[1].pop();mx[1].pop();
}

void solve(int x)
{
	vis[x]=1;calc(x);
	for(int i=head[x];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(!vis[v])
		{
			root=0;sum=son[v];
			getroot(v,0);
			solve(root);
		}
	}
}

int main()
{
	freopen("2444.in","r",stdin);
	freopen("2444.out","w",stdout);
	
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%d",&h[i]);
	for(int i=1;i<n;++i)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v);
	}
	f[0]=sum=n;
	getroot(1,0);
	solve(root);
	printf("%d\n",ans);
	
	return 0;
}
