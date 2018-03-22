#include<bits/stdc++.h>
using namespace std;

const int N=2e5+10;
int n,m,q,ynum,top;
int a[N],st[N];
map<int,int>mp;
vector<int>e[N];

struct Splay
{
	int root;
	int fa[N],val[N],typ[N],dep[N];
	int ch[N][2],sg[N][2],pos[N][2];

	void pushup(int x)
	{
		int l=ch[x][0],r=ch[x][1];
		sg[x][0]=sg[l][0]^sg[r][0];
		sg[x][1]=sg[l][1]^sg[r][1];
		sg[x][typ[x]]^=val[x];
	}
	
	void rotate(int x,int &k)
	{
		int y=fa[x],z=fa[y],l,r;
		l=(ch[y][1]==x);r=l^1;
		if(y==k)
			k=x;
		else
			ch[z][ch[z][1]==y]=x;
		fa[ch[x][r]]=y;fa[y]=x;fa[x]=z;
		ch[y][l]=ch[x][r];ch[x][r]=y;
		pushup(y);pushup(x);
	}
	
	void splay(int x,int &goal)
	{
		while(x!=goal)
		{
			int y=fa[x],z=fa[y];
			if(y!=goal)
			{
				if(ch[y][0]==x^ch[z][0]==y)
					rotate(x,goal);
				else
					rotate(y,goal);
			}
			rotate(x,goal);
		}
	}
	
	int build(int l,int r,int f)
	{
		if(l>r)
			return 0;
		int mid=(l+r)>>1;
		if(st[mid]>0)
		{
			val[mid]=a[st[mid]];
			pos[st[mid]][0]=mid;
		}
		else
			pos[-st[mid]][1]=mid;
		typ[mid]=dep[abs(st[mid])];fa[mid]=f;
		ch[mid][0]=build(l,mid-1,mid);
		ch[mid][1]=build(mid+1,r,mid);
		pushup(mid);
		return mid;
	}
	
	void insert(int u,int v,int num)
	{
		splay(pos[u][0],root);
		int t=ch[root][1];
		while(ch[t][0])
			t=ch[t][0];
		int t1=++top,t2=++top;
		pos[v][0]=t1;pos[v][1]=t2;
		fa[t1]=t;fa[t2]=t1;
		ch[t][0]=t1;ch[t1][1]=t2;
		val[t1]=num;typ[t1]=typ[t2]=dep[v];
		pushup(t2);pushup(t1);
		splay(t2,root);
	}
	
	void query(int x)
	{
		splay(pos[x][0],root);
		splay(pos[x][1],ch[root][1]);
		if(sg[ch[pos[x][1]][0]][dep[x]^1])
		{
			++ynum;
			puts("MeiZ");
		}
		else
			puts("GTY");
	}
};
Splay tr;

void dfs(int x)
{
	st[++top]=x;
	for(int i=0;i<e[x].size();++i)
	{
		tr.dep[e[x][i]]=tr.dep[x]^1;
		dfs(e[x][i]);
	}
	st[++top]=-x;
}

int main()
{
	freopen("BZOJ3729.in","r",stdin);
	freopen("BZOJ3729.out","w",stdout);
	
	scanf("%d%d",&n,&m);m++;
	for(int i=1;i<=n;++i)
	{
		scanf("%d",&a[i]);a[i]%=m;
		mp[i]=i;
	}
	for(int i=1;i<n;++i)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		e[u].push_back(v);
	}
	dfs(1);
	tr.root=tr.build(1,top,0);
	scanf("%d",&q);
	while(q--)
	{
		int opt,u,v,x;
		scanf("%d",&opt);
		if(opt==1)
		{
			scanf("%d",&x);
			x^=ynum;
			tr.query(mp[x]);
		}
		else
		if(opt==2)
		{
			scanf("%d%d",&x,&v);
			x^=ynum;(v^=ynum)%=m;
			x=mp[x];tr.splay(tr.pos[x][0],tr.root);tr.val[tr.root]=v;
			tr.pushup(tr.root);
		}
		else
		{
			scanf("%d%d%d",&u,&v,&x);
			x^=ynum;u^=ynum;v^=ynum;
			u=mp[u];mp[v]=++n;
			tr.dep[n]=tr.dep[u]^1;
			tr.insert(u,n,x%m);
		}
	}
	
	return 0;
}
