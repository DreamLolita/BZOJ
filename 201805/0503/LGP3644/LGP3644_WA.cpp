#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=4e5+10;
const int M=N*4;
int n,K,tot;
LL ans;

int read()
{
	int ret=0;char c=getchar();
	while(!isdigit(c)){if(c=='A')return -1; if(c=='B')return -2; c=getchar();}
	while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c^48);c=getchar();}
	return ret;
}

struct Splay
{
	int sz,root,tpos,ch[M][2];
	int key[M],fa[M],siz[M];
	LL sum[M];

	void pushup(int x)
	{
		int ls=ch[x][0],rs=ch[x][1];
		sum[x]=sum[ls]+sum[rs]+key[x];
		siz[x]=siz[ls]+siz[rs]+1;
	}

	void rotate(int x,int &goal)
	{
		int y=fa[x],z=fa[y],kind=ch[y][1]==x;
		if(y==goal)
			goal=x;
		else
			ch[z][ch[z][1]==y]=x;
		fa[ch[x][!kind]]=y;fa[y]=x;fa[x]=z;
		ch[y][kind]=ch[x][!kind];ch[x][!kind]=y;
		pushup(y);pushup(x);
	}
	
	void splay(int x,int &goal)
	{
		while(x!=goal)
		{
			int y=fa[x],z=fa[y];
			if(y!=goal)
			{
				if(ch[y][1]==x^ch[z][1]==y)
					rotate(x,goal);
				else
					rotate(y,goal);
			}
			rotate(x,goal);
		}
	}
	
	void insert(int &x,int f,int val)
	{
		if(!x)
		{
			x=++sz;key[x]=sum[x]=val;fa[x]=f;siz[x]=1;
			splay(x,root);return;
		}
		if(val<key[x])
			insert(ch[x][0],x,val);
		else
			insert(ch[x][1],x,val);
	}
	
	void findk(int x,int k)
	{
		if(!x)
			return;
		if(key[x]<=k)
			tpos=x,findk(ch[x][1],k);
		else
			findk(ch[x][0],k);
	}
	
	void dele(int x)
	{
		tpos=0;findk(root,x);x=tpos;splay(x,root);
		if(!ch[x][0] || !ch[x][1])
			root=ch[x][0]+ch[x][1];
		else
		{
			int k=ch[x][1];
			while(ch[k][0])
				k=ch[k][0];
			ch[k][0]=ch[x][0];fa[ch[x][0]]=k;pushup(k);
			root=ch[x][1];pushup(root);
		}
		fa[root]=0;
	}
	
	int finds(int x,int k)
	{
		if(siz[ch[x][0]]+1==k)
			return x;
		if(siz[ch[x][0]]>=k)
			return finds(ch[x][0],k);
		return finds(ch[x][1],k-siz[ch[x][0]]-1);
	}
	
	LL query(int mid)
	{	
		splay(finds(root,mid),root);
		return (LL)(1ll*sum[ch[root][1]]-1ll*(sum[ch[root][0]]+key[root]));
	}
};
Splay tr1,tr2;

struct Tnode
{
	int S,T,md;
};
Tnode a[N];

bool cmp(Tnode A,Tnode B)
{
	return A.md<B.md;
}

void init()
{
	K=read();n=read();tot=n;
	for(int i=1,j=1;i<=n;++i,++j)
	{
		int p1,p2;
		p1=read();a[j].S=read();
		p2=read();a[j].T=read();
		a[j].md=(a[j].S+a[j].T);
		if(p1==p2)
			ans+=abs(a[j].S-a[j].T),--j,--tot;
	}
	n=tot;ans+=n;
	sort(a+1,a+n+1,cmp);
}

void solve()
{
	for(int i=1;i<=n;++i)
		tr1.insert(tr1.root,0,a[i].S),tr1.insert(tr1.root,0,a[i].T);
	LL tmpans=tr1.query(n);
	
	if(K==1)
	{
		ans+=tmpans;
		printf("%lld\n",ans);
		return;
	}
	
//printf("%d %d\n",tr1.siz[tr1.root],tr2.siz[tr2.root]);
//puts("debug:");tr1.debug(tr1.root);
	for(int i=1;i<n;++i)
	{
		tr1.dele(a[i].S);tr1.dele(a[i].T);
//puts("debug:");tr1.debug(tr1.root);
		tr2.insert(tr2.root,0,a[i].S);tr2.insert(tr2.root,0,a[i].T);
//printf("%d %d %lld %lld\n",tr1.siz[tr1.root],tr2.siz[tr2.root],tr1.query(n-i),tr2.query(i));
		tmpans=min(tmpans,(LL)tr1.query(n-i)+tr2.query(i));
	}
	ans+=tmpans;
	printf("%lld\n",ans);
}

int main()
{
	freopen("LGP3644.in","r",stdin);
	freopen("LGP3644.out","w",stdout);

	init();
	solve();

	return 0;
}

