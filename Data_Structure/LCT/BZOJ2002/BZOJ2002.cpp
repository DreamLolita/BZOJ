#include<bits/stdc++.h>
using namespace std;

const int MAXN=2e5+10;
int n,m;
int nex[MAXN],siz[MAXN],pre[MAXN],rev[MAXN],s[MAXN];
int ch[MAXN][2];

bool isroot(int x)
{
	return ch[pre[x]][0]!=x && ch[pre[x]][1]!=x;
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
	int y=pre[x],z=pre[y];
	int l=ch[y][1]==x,r=l^1;
	if(!isroot(y))
		ch[z][ch[z][1]==y]=x;
	pre[x]=z;pre[y]=x;pre[ch[x][r]]=y;
	ch[y][l]=ch[x][r];
	ch[x][r]=y;
	pushup(y);
	pushup(x);
}

void splay(int x)
{
	int top=0;s[++top]=x;
	for(int i=x;!isroot(i);i=pre[i])
		s[++top]=pre[i];
	for(int i=top;i;i--)
		pushdown(s[i]);
	while(!isroot(x))
	{
		int y=pre[x],z=pre[y];
		if(!isroot(y))
			if(ch[y][0]==x^ch[z][0]==y)//same son
				rotate(y);
			else
				rotate(x);
		rotate(x);
	}
}

void access(int x)
{
	int t=0;
	while(x)
	{
		splay(x);
		ch[x][1]=t;
		t=x;x=pre[x];
	}
}

void rever(int x)
{
	access(x);
	splay(x);
	rev[x]^=1;
}

void link(int x,int y)
{
	rever(x);
	pre[x]=y;
	splay(x);
}

void cut(int x,int y)
{
	rever(x);
	access(y);
	splay(y);
	ch[y][0]=pre[x]=0;
}

int main()
{
//	freopen("BZOJ2002.in","r",stdin);
//	freopen("BZOJ2002.out","w",stdout);
	
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
	{
		int x;
		scanf("%d",&x);
		pre[i]=x+i;siz[i]=1;
		if(pre[i]>n+1)
			pre[i]=n+1;
		nex[i]=pre[i];
	}
	
	siz[n+1]=1;
	scanf("%d",&m);
	for(int i=1;i<=m;++i)
	{
		int opt,x,y;
		scanf("%d",&opt);
		if(opt&1)
		{
			rever(n+1);
			scanf("%d",&x);++x;
			access(x);splay(x);
			printf("%d\n",siz[ch[x][0]]);
		}
		else
		{
			scanf("%d%d",&x,&y);++x;
			int t=min(n+1,x+y);
			cut(x,nex[x]);link(x,t);nex[x]=t;
		}
	}
	
	return 0;
}
