#include<bits/stdc++.h>
using namespace std;

const int N=1e6+10;
int m,ans;

int read()
{
	int ret=0,f=1;char c='.';
	while(c<'0' || c>'9')
	{
		if(c=='-') f=-1;
		if(c=='?') return 0;
		if(c=='I') return 2;
        if(c=='O') return 1;
		c=getchar();
	}
	while(c>='0' && c<='9')
	{
		ret=(ret<<1)+(ret<<3)+(c-'0');
		c=getchar();
	}
	return ret*f;
}

struct Splay
{
	int root,sz;
	int key[N],fa[N],las[N],ch[N][2];
	bool vis[N];
	
	void rotate(int x)
	{
		int y=fa[x],z=fa[y],kind=ch[y][1]==x;
		if(y==root) root=x;
			else ch[z][ch[z][1]==y]=x;
		fa[ch[x][!kind]]=y;fa[x]=z;fa[y]=x;
		ch[y][kind]=ch[x][!kind];ch[x][!kind]=y;
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
/*		if(!x)
		{
			x=++sz;key[x]=v;fa[x]=f;splay(x);
			return;
		}
		if(v<key[x])
			insert(ch[x][0],x,v);
		else
			insert(ch[x][1],x,v);*/
		int f=0;
		while(x && key[x]!=v)
			f=x,x=ch[x][key[x]<v];
		x=++sz;
		key[x]=v;fa[x]=f;
		if(f)ch[f][key[f]<v]=x;
		splay(x);
	}
	
	int getk(int x,int v)
	{
		while(ch[x][key[x]<v] && v!=key[x])
			x=ch[x][key[x]<v];
		splay(x);
//		printf("x:%d\n",x);
	}
	
	void del(int x)
	{
		getk(root,x);
		if(!ch[root][0] || !ch[root][1])
			root=ch[root][0]+ch[root][1];
		else 
		{
/*			int k=ch[x][1];
			while(ch[k][0])
				k=ch[k][0];
			ch[k][0]=ch[x][0];fa[ch[x][0]]=k;
			root=ch[x][1];*/
			int tmp=root,k=ch[root][1];
			root=k;
			while(ch[k][0])k=ch[k][0];
			fa[ch[tmp][0]]=k;ch[k][0]=ch[tmp][0];
			splay(k);
		}
		fa[root]=0;
	}
	
	int findsuc(int x)
	{
		getk(root,x);
		if(key[root]>x)
			return root;
		int t=ch[root][1];
		while(ch[t][0])
			t=ch[t][0];
		return t;
	}
	
	void solve(int opt,int i)
	{
		int x=read();
		if(vis[x]^(opt&1))
		{
//			printf("i:%d\n",i);
//			printf("%d %d %d %d\n",i,root,key[root],las[x]);
			int tmp=key[findsuc(las[x])];
			
//			printf("%d %d %d\n",las[x],findsuc(las[x]),key[root]);
			if(!tmp)
			{
				printf("%d\n",i);
				exit(0);
			}
			else
				del(tmp);
		}
		vis[x]=(opt&1)^1;
		las[x]=i;	
	}
}tr;

int main()
{
	freopen("LOJ6085.in","r",stdin);
	freopen("LOJ6085.out","w",stdout);
	
	m=read();ans=-1;
	for(int i=1;i<=m;++i)
	{
		int opt=read();
		if(opt)
			tr.solve(opt,i);
		else
			tr.insert(tr.root,i);
//		cerr<<i<<endl;
	}
	printf("%d\n",ans);
	
	return 0;
}
