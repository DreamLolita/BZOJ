#include<bits/stdc++.h>
#define key_val ch[ch[root][1]][0]
using namespace std;

const int N=1e6+10;
const int M=N*4;
const int INF=1e8;
int n,m,ps,mx,sz;
int a[N],val[N],cnt[N],siz[N];
int f[N],p[N],key[N],fa[N];
int ch[N][2];

int read()
{
	int ret=0;char c='.';
	while(c<'0' || c>'9')c=getchar();
	while(c>='0' && c<='9'){ret=(ret<<3)+(ret<<1)+(c-'0');c=getchar();}
	return ret;
}

struct Seqment
{
	int cnt[M],num[M],pos[M];
	
	void merge(int x,int y,int a,int b,int &cs,int &ns)
	{
		if(y==b){cs=x+y;ns=y;return;}
		if(!y || !b){cs=x+a;ns=y+b;return;}
		if(x==a){cs=ns=0;return;}
		if(x>a){cs=x-a;ns=y;return;}
		cs=a-x;ns=b;
	}
	
	void build(int x,int l,int r)
	{
		if(l==r)
		{
			cnt[x]=1;num[x]=a[l];pos[l]=x;
			return;
		}
		int mid=(l+r)>>1;
		build(x<<1,l,mid);
		build(x<<1|1,mid+1,r);
		merge(cnt[x<<1],num[x<<1],cnt[x<<1|1],num[x<<1|1],cnt[x],num[x]);
	}

	void query(int x,int l,int r,int L,int R)
	{
		if(L<=l && r<=R)
		{
			merge(mx,ps,cnt[x],num[x],mx,ps);
			return;
		}
		int mid=(l+r)>>1;
		if(L<=mid)
			query(x<<1,l,mid,L,R);
		if(R>mid)
			query(x<<1|1,mid+1,r,L,R);
	}
	
	void modify(int x)
	{
		num[x=pos[x]]=ps;
		for(x>>=1;x;x>>=1)
			merge(cnt[x<<1],num[x<<1],cnt[x<<1|1],num[x<<1|1],cnt[x],num[x]);
	}
}tr;

struct Splay
{
	int root,ts;
	
	void new_node(int &x,int f,int k)
	{
		x=++sz;
		ch[x][0]=ch[x][1]=ts;
		fa[x]=f;siz[x]=1;key[x]=k;
	}
	
	void pushup(int x)
	{
		siz[x]=siz[ch[x][0]]+siz[ch[x][1]]+1;
	}
	
	void init()
	{
		ts=++sz;
		ch[sz][0]=ch[sz][1]=fa[sz]=siz[sz]=0;
		new_node(root,ts,-INF);
		new_node(ch[root][1],root,INF);
		pushup(ch[root][1]);pushup(root);
	}
	
	void rotate(int x)
	{
		int y=fa[x],z=fa[y],kind=ch[y][1]==x;
		if(y==root) root=x;
			else ch[z][ch[z][1]==y]=x;
		fa[ch[x][!kind]]=y;fa[x]=z;fa[y]=x;
		ch[y][kind]=ch[x][!kind];ch[x][!kind]=y;
		pushup(y);pushup(x);
	}
	
	void splay(int x)
	{
		while(x!=root)
		{
			int y=fa[x],z=fa[y];
			if(y!=root)
				if(ch[y][0]==x^ch[z][0]==y)
					rotate(x);
				else
					rotate(y);
			rotate(x);
		}
	}
	
	void insert(int x,int v)
	{
		int t=0;
		while(x && key[x]!=v)
			t=x,x=ch[x][key[x]<v];
		x=++sz;
		key[x]=v;fa[x]=t;
		if(t)ch[t][key[t]<v]=x,ch[t][key[t]>=v]=ts;
		printf("%d %d\n",x,t);
		splay(x);
	}
	
	int getk(int x,int v)
	{
		while(ch[x][key[x]<v] && v!=key[x])
			x=ch[x][key[x]<v];
		splay(x);
	}
	
	void dele(int x)
	{
		getk(root,x);
		if(!ch[root][0] || !ch[root][1])
			root=ch[root][0]+ch[root][1];
		else 
		{
			int tmp=root,k=ch[root][1];root=k;
			while(ch[k][0])k=ch[k][0];
			fa[ch[tmp][0]]=k;ch[k][0]=ch[tmp][0];
			splay(k);
		}
		fa[root]=0;
	}
	
	int query(int x)
	{
		getk(root,x);
		return siz[ch[x][0]]+(key[root]<=x?1:0);
	}
}sp[N];

void change(int x)
{
	sp[a[x]].dele(x);a[x]=ps;
	sp[a[x]].insert(sp[a[x]].root,x);
	tr.modify(x);
}

bool check(int l,int r,int t)
{
	if(!t) return 0;
	int w=sp[t].query(r)-sp[t].query(l-1);
	return w>=(r-l+1)/2;
}

int main()
{
	freopen("BZOJ4966.in","r",stdin);
	freopen("BZOJ4966.out","w",stdout);
	
	n=read();m=read();
	for(int i=1;i<=n;++i)
		sp[i].init();
	for(int i=1;i<=n;++i)
		printf("%d\n",sp[i].root);
	for(int i=1;i<=n;++i)
		a[i]=read(),sp[a[i]].insert(sp[a[i]].root,i);
	exit(0);
	tr.build(1,1,n);
	while(m--)
	{
		int l=read(),r=read(),s=read(),k=read();
		mx=ps=0;
		tr.query(1,1,n,l,r);
		if(!check(l,r,ps))
			ps=0;
		l=read();r=read();
		if(!ps)
			ps=l;
		for(int i=1;i<=r;++i)
			l=read(),change(l);
	}
	if(!check(1,n,f[1]))
		f[1]=-1;
	printf("%d\n",f[1]);
	
	return 0;
}
