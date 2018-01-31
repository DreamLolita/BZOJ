#include<bits/stdc++.h>
using namespace std;

const int MAXN=1e4+10;
int n,m,top;
int pre[MAXN],ch[MAXN][2],rt[MAXN];
int rev[MAXN],s[MAXN];

bool isroot(int x)
{
	return ch[pre[x]][0]!=x && ch[pre[x]][1]!=x;
}

void pushdown(int x)
{
	int l=ch[x][0],r=ch[x][1];
	if(rev[x])
	{
		rev[x]^=1;rev[l]^=1;rev[r]^=1;
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
//	pushup(y);
//	pushup(x);
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

int query(int x)
{
	access(x);splay(x);
	while(ch[x][0])
		x=ch[x][0];
	return x;
}

int main()
{
//	freopen("BZOJ2049.in","r",stdin);
//	freopen("BZOJ2049.out","w",stdout);
	
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i)
	{
		char opt[10];
		int x,y;
		scanf("%s%d%d",opt,&x,&y);
		
		if(opt[0]=='C')
			link(x,y);
		else
		if(opt[0]=='D')
			cut(x,y);
		else
		{
			if(query(x)==query(y))
				puts("Yes");
			else
				puts("No");
		}
	}
	
	return 0;
}
