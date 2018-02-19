#include<bits/stdc++.h>
using namespace std;

const int N=5e5+5;
int n,m,cnt,ind;
int bin[20],t[N],l[N],r[N],val[N];
int head[N],deep[N],fa[N][20];

struct Tway
{
	int v,nex;
}e[N<<1];

void add(int u,int v)
{
	e[++cnt].v=v;e[cnt].nex=head[u];head[u]=cnt;
	e[++cnt].v=u;e[cnt].nex=head[v];head[v]=cnt;
}

void update(int x,int val)
{
	for(int i=x;i<=n;i+=i&-i)
		t[i]^=val;
}

int query(int x)
{
	int tmp=0;
	for(int i=x;i;i-=i&-i)
		tmp^=t[i];
	return tmp;
}

void dfs(int x)
{
	for(int i=1;i<=18;i++)
		if(deep[x]>=bin[i])
			fa[x][i]=fa[fa[x][i-1]][i-1];
		else break;
	l[x]=++ind;
	for(int i=head[x];i;i=e[i].nex)
		if(e[i].v!=fa[x][0])
		{
			deep[e[i].v]=deep[x]+1;
			fa[e[i].v][0]=x;
			dfs(e[i].v);
		}
	r[x]=ind;
}

int lca(int x,int y)
{
	if(deep[x]<deep[y])swap(x,y);
	int t=deep[x]-deep[y];
	for(int i=0;i<=18;i++)
		if(bin[i]&t)x=fa[x][i];
	for(int i=18;i>=0;i--)
		if(fa[x][i]!=fa[y][i])
			x=fa[x][i],y=fa[y][i];
	if(x==y)return x;
	return fa[x][0];
}

int main()
{
	freopen("BZOJ2819.in","r",stdin);
	freopen("BZOJ2819.out","w",stdout);
	
	bin[0]=1;for(int i=1;i<20;i++)
		bin[i]=bin[i-1]<<1;
		
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&val[i]);
	for(int i=1;i<n;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v);
	}
	
	dfs(1);
	for(int i=1;i<=n;i++)
		update(l[i],val[i]),update(r[i]+1,val[i]);
		
	scanf("%d",&m);
	while(m--)
	{
		int x,y;
		char ch[2];
		scanf("%s%d%d",ch,&x,&y);
	
		if(ch[0]=='Q')
		{
			int t=lca(x,y);
			int res=query(l[x])^query(l[y])^val[t];
			if(res)puts("Yes");
			else puts("No");
		}
		else 
		{
			update(l[x],val[x]);update(r[x]+1,val[x]);
			val[x]=y;
			update(l[x],y);update(r[x]+1,y);
		}
	}
	return 0;
}
