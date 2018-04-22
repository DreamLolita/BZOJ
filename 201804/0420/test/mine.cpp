#include<bits/stdc++.h>
#define key_val ch[ch[root][1]][0]
using namespace std;

const int N=1005;
const int M=N*N;
int sz,n,m;
int ch[M][2],siz[M],rev[M],fa[M],key[M];
char a[N][N],b[N];

int read()
{
	int ret=0;char c='.';
	while(c<'0' || c>'9') c=getchar();
	while(c>='0' && c<='9'){ret=(ret<<1)+(ret<<3)+(c-'0');c=getchar();}
	return ret;
}

struct Splay
{
	int root,top,ts,ls;
	int a[N];
	
	void new_node(int &x,int f,int k)
	{
		x=++sz;
		ch[x][0]=ch[x][1]=rev[x]=0;
		fa[x]=f;siz[x]=1;key[x]=k;
	}
	
	void pushup(int x)
	{
		siz[x]=siz[ch[x][0]]+siz[ch[x][1]]+1;
	}
	
	void update_rev(int x)
	{
		if(!x || x==ts)
			return;
		swap(ch[x][0],ch[x][1]);
		rev[x]^=1;
	}
	
	void pushdown(int x)
	{
		if(rev[x])
		{
			update_rev(ch[x][0]);update_rev(ch[x][1]);
			rev[x]=0;
		}
	}
	
	void build(int &x,int l,int r,int f)
	{
		if(l>r)
			return;
		int mid=(l+r)>>1;
		new_node(x,f,a[mid]);
		build(ch[x][0],l,mid-1,x);
		build(ch[x][1],mid+1,r,x);
		pushup(x);
	}
	
	void init(char *x)
	{
		ts=++sz;
		ch[sz][0]=ch[sz][1]=fa[sz]=siz[sz]=rev[sz]=key[sz]=0;
		for(int i=1;i<=n;++i)
			a[i]=x[i]-'a';
		new_node(root,sz,27);
		new_node(ch[root][1],root,27);
		build(key_val,1,n,ch[root][1]);
		pushup(ch[root][1]);pushup(root);
	}
	
	void rotate(int x,int kind)
	{
		int y=fa[x];
		pushdown(y);pushdown(x);
		ch[y][!kind]=ch[x][kind];
		fa[ch[x][kind]]=y;
		if(fa[y] && fa[y]!=ts)
			ch[fa[y]][ch[fa[y]][1]==y]=x;
		fa[x]=fa[y];ch[x][kind]=y;fa[y]=x;
		pushup(y);
	}

	void splay(int x,int goal)
	{
		while(fa[x]!=goal)
		{
			if(fa[fa[x]]==goal)
				rotate(x,ch[fa[x]][0]==x);
			else
			{
				int y=fa[x];
				int kind=ch[fa[y]][0]==y;
				
				if(ch[y][kind]==x)
				{
					rotate(x,!kind);
					rotate(x,kind);
				}
				else
				{
					rotate(y,kind);
					rotate(x,kind);
				}
			}
		}
		pushup(x);
		if(goal==ts)
			root=x;
	}
	
	int getk(int x,int k)
	{
		pushdown(x);
		int t=siz[ch[x][0]];
		if(t+1==k)
			return x;
		if(t+1<k)
			return getk(ch[x][1],k-t-1);
		return getk(ch[x][0],k);
	}
	
	void rever(int l,int r)
	{
		splay(getk(root,l),ts);splay(getk(root,r+2),root);
		update_rev(key_val);
		pushup(ch[root][1]);pushup(root);
	}
	
	void cut(int l,int r)
	{
		splay(getk(root,l),ts);splay(getk(root,r+2),root);
		top=key_val;fa[key_val]=ts;key_val=ts;
		pushup(ch[root][1]);pushup(root);
	}
	
	void link(int son,int p)
	{
		splay(getk(root,p+1),ts);splay(getk(root,p+2),root);
		fa[son]=ch[root][1];key_val=son;
		pushup(ch[root][1]);pushup(root);
	}
	
	void output(int x)
	{
		pushdown(x);
		if(ch[x][0])
			output(ch[x][0]);
		if(key[x]^27)
			putchar(key[x]+'a');//printf(" %d %d\n",x,siz[x]);
		if(ch[x][1])
			output(ch[x][1]);
	}
}t1[N],t2[N];

int main()
{
	freopen("rotate.in","r",stdin);
	freopen("rotate.out","w",stdout);
	
	n=read();m=read();
	for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
            while(!islower(a[i][j]=getchar()));
    for(int i=1;i<=n;++i)
    	t1[i].init(a[i]);
    for(int j=1;j<=n;++j)
    {
		for(int i=1;i<=n;++i)
    		b[i]=a[i][j];
		t2[j].init(b);
	}

	while(m--)
	{
		int x=read(),y=read(),l=read();
		for(int i=x;i<x+l;++i)
			t1[i].rever(y,y+l-1),t1[i].cut(y,y+l-1);
//		return 0;
		for(int i=y;i<y+l;++i)
			t2[i].cut(x,x+l-1);
/*		for(int i=y;i<y+l;++i)
			t2[i].output(t2[i].top),puts("");
		printf("\n");*/
		
		for(int i=y;i<y+l;++i)	
			t1[x+l-1-i+y].link(t2[i].top,y-1);

/*		for(int i=x;i<x+l;++i)
		{
			t1[i].output(t1[i].root);
			puts("");
		}*/
		for(int i=x;i<x+l;++i)
			t2[i-x+y].link(t1[i].top,x-1);	
	}
	for(int i=1;i<=n;++i)
		t1[i].output(t1[i].root),puts("");
	return 0;
}
