//divide the way,into two ways
#include<bits/stdc++.h>
using namespace std;

const int INF=0x3f3f3f3f;
const int MAXN=2e5+10;
int n,m;
int pre[MAXN],ed[MAXN],s[MAXN];
int sum[MAXN],v[MAXN],mx[MAXN],mn[MAXN];
int ch[MAXN][2];
bool rev[MAXN],opp[MAXN];

bool isroot(int x)
{
	return ch[pre[x]][0]!=x && ch[pre[x]][1]!=x;
}

void rever(int x)
{
	sum[x]=-sum[x];v[x]=-v[x];
	swap(mn[x],mx[x]);
	mn[x]=-mn[x];mx[x]=-mx[x];
	opp[x]^=1;
}

void pushup(int x)
{
	int l=ch[x][0],r=ch[x][1];
	mx[x]=max(mx[l],mx[r]);
	mn[x]=min(mn[l],mn[r]);
	if(x>n) 
		mx[x]=max(mx[x],v[x]),mn[x]=min(mn[x],v[x]);
	sum[x]=sum[l]+sum[r]+v[x];
}

void pushdown(int x)
{
	int l=ch[x][0],r=ch[x][1];
	if(opp[x])
	{
		opp[x]=0;
		if(l) rever(l);
		if(r) rever(r);
	}
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
				rotate(x);
			else
				rotate(y);
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
		pushup(x);
		t=x;x=pre[x];
//		printf("x:%d\n",x);
	}
}

void makeroot(int x)
{
	access(x);
	splay(x);
	rev[x]^=1;
}

void cut(int x,int y)
{
	makeroot(x);
	access(y);
	splay(y);
}

void link(int x,int y)
{
//	printf("%d %d\n",x,y);
	makeroot(x);
	pre[x]=y;
//	splay(x);
}

void CHANGE(int x,int y)
{
	splay(ed[x]);
	v[ed[x]]=y;
	pushup(ed[x]);
}

void OPPO(int x,int y)
{
	cut(x+1,y+1);
	rever(y+1);
}

void SUM(int x,int y)
{
	cut(x+1,y+1);
	printf("%d\n",sum[y+1]);
}

void MAX(int x,int y)
{
	cut(x+1,y+1);
	printf("%d\n",mx[y+1]);
}

void MIN(int x,int y)
{
	cut(x+1,y+1);
	printf("%d\n",mn[y+1]);
}

int main()
{
//	freopen("BZOJ2157.in","r",stdin);
//	freopen("BZOJ2157.out","w",stdout);
	
	scanf("%d",&n);
	for(int i=0;i<=n;++i)
		mn[i]=INF,mx[i]=-INF;
	
	int id=n;
	for(int i=1;i<n;++i)
	{
		int us,vs,w;
		scanf("%d%d%d",&us,&vs,&w);++us;++vs;
		ed[i]=++id;
		link(us,id);link(vs,id);
		v[id]=sum[id]=mx[id]=mn[id]=w;
	}

	scanf("%d",&m);
	while(m--)
	{
		int us,vs;
		char opt[5];
		scanf("%s%d%d",opt,&us,&vs);
		
		if(opt[0]=='C')
			CHANGE(us,vs);
		else
		if(opt[0]=='N')
			OPPO(us,vs);
		else
		if(opt[0]=='S')
			SUM(us,vs);
		else
		if(opt[1]=='A')
			MAX(us,vs);
		else
			MIN(us,vs);	
	}
		
	return 0;
}
