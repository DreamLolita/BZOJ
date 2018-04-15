#include<bits/stdc++.h>
using namespace std;

const int N=2e5+10;
int n,m;
int nex[N],siz[N],fa[N],rev[N],s[N];
int ch[N][2];
stack<int>q;

bool isroot(int x)
{
	return ch[fa[x]][0]!=x && ch[fa[x]][1]!=x;
}

void pushup(int x)
{
	siz[x]=siz[ch[x][0]]+siz[ch[x][1]]+1;
}

void pushdown(int x)
{
	if(rev[x])
	{
		rev[x]^=1;rev[ch[x][0]]^=1;rev[ch[x][1]]^=1;
		swap(ch[x][0],ch[x][1]);
	}
}

void rotate(int x)
{
	int y=fa[x],z=fa[y];
	int kind=ch[y][1]==x;
	if(!isroot(y))
		ch[z][ch[z][1]==y]=x;
	fa[x]=z;fa[y]=x;fa[ch[x][!kind]]=y;
	ch[y][kind]=ch[x][!kind];
	ch[x][!kind]=y;
	pushup(y);pushup(x);
}

void splay(int x)
{
	q.push(x);
	for(int i=x;!isroot(i);i=fa[i])
		q.push(fa[i]);
	while(!q.empty())
		pushdown(q.top()),q.pop();
	while(!isroot(x))
	{
		int y=fa[x],z=fa[y];
		if(!isroot(y))
			if(ch[y][0]==x^ch[z][0]==y)
				rotate(x);
			else
				rotate(y);
		rotate(x);
	}
}

void access(int x)
{
	for(int t=0;x;t=x,x=fa[x])
		splay(x),ch[x][1]=t;
}

void rever(int x)
{
	access(x);splay(x);
	rev[x]^=1;
}

void link(int x,int y)
{
	rever(x);fa[x]=y;
	splay(x);
}

void cut(int x,int y)
{
	rever(x);access(y);splay(y);
	ch[y][0]=fa[x]=0;
}

int main()
{
	freopen("B.in","r",stdin);
	freopen("B.out","w",stdout);
	
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
	{
		int x;
		scanf("%d",&x);
		fa[i]=x+i;siz[i]=1;
		if(fa[i]>n+1)
			fa[i]=n+1;
		nex[i]=fa[i];
	}
	
	siz[n+1]=1;
	scanf("%d",&m);
	for(int i=1;i<=m;++i)
	{
		int opt,x,y;
		scanf("%d%d",&opt,&x);++x;
		if(opt&1)
		{
			rever(n+1);
			access(x);splay(x);
			printf("%d\n",siz[ch[x][0]]);
		}
		else
		{
			scanf("%d",&y);
			int t=min(n+1,x+y);
			cut(x,nex[x]);link(x,t);nex[x]=t;
		}
	}
	
	return 0;
}
