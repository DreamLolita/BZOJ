#include<bits/stdc++.h>
#define mkp(x,y) make_pair(y,x)
using namespace std;

typedef pair<int,int> pii;
const int INF=1e8;
const int N=2e5+10;
int root,n,m,liml,limr,sum,ans;
int siz[N],mx[N],col[N];
bool vis[N];
vector<pii>e[N];

int read()
{
	int ret=0,f=1;char c='.';
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c^48);c=getchar();}
	return f?ret:-ret;
}

struct Seqment
{
	int sz,root;
	int ls[N],rs[N],s[N];
	
	void clear()
	{
		sz=root=0;s[0]=-INF;
	}
	
	void update(int &x,int l,int r,int p,int v)
	{
		if(!x)
		{
			x=++sz;s[x]=-INF;
			ls[x]=rs[x]=0;
		}
		if(l==r)
		{
			s[x]=max(s[x],v);
			return;
		}
		int mid=(l+r)>>1;
		if(p<=mid)
			update(ls[x],l,mid,p,v);
		else
			update(rs[x],mid+1,r,p,v);
		s[x]=max(s[ls[x]],s[rs[x]]);
	}
	
	int query(int x,int l,int r,int L,int R)
	{
		if(!x)
			return -INF;
		if(L<=l && r<=R)
			return s[x];
		int mid=(l+r)>>1,ret=-INF;
		if(L<=mid)
			ret=max(ret,query(ls[x],l,mid,L,R));
		if(R>mid)
			ret=max(ret,query(rs[x],mid+1,r,L,R));
		return ret;
	}
	
	int ask(int l,int r)
	{
		l=max(l,0);
		return query(root,0,n,l,r);
	}
}t1,t2;

void merge(int &x,int y)
{
	if(!y)
		return;
	if(!x)
	{
		x=++t1.sz;
		t1.s[x]=-INF;t1.ls[x]=t1.rs[x]=0;
	}
	t1.s[x]=max(t1.s[x],t2.s[y]);
	merge(t1.ls[x],t2.ls[y]);merge(t1.rs[x],t2.rs[y]);
}

void add(int u,int v,int w)
{
	e[u].push_back(mkp(v,w));
	e[v].push_back(mkp(u,w));
}

void getans(int x,int f,int len,int val,int c,int top)
{
	if(len>limr)
		return;
	ans=max(ans,max(t1.ask(liml-len,limr-len),t2.ask(liml-len,limr-len)-col[top])+val);
	for(int i=0;i<e[x].size();++i)
	{
		int v=e[x][i].second,w=e[x][i].first;
		if(vis[v] || v==f)
			continue;
		getans(v,x,len+1,val+(w==c?0:col[w]),w,top);
	}
}


void modify(int x,int f,int len,int val,int c)
{
	if(len>limr)
		return;
	t2.update(t2.root,0,n,len,val);
	for(int i=0;i<e[x].size();++i)
	{
		int v=e[x][i].second,w=e[x][i].first;
		if(vis[v] || v==f)
			continue;
		modify(v,x,len+1,val+(w==c?0:col[w]),w);
	}
}

void calc(int x)
{
	int las=0;
	t1.clear();t2.clear();
	t1.update(t1.root,0,n,0,0);
	for(int i=0;i<e[x].size();++i)
	{
		int v=e[x][i].second,w=e[x][i].first;
		if(!vis[v])
		{
			if(w!=las)
			{
				merge(t1.root,t2.root);
				t2.clear();
			}
			getans(v,x,1,col[w],w,w);modify(v,x,1,col[w],w);las=w;
		}
	}
}

void getroot(int x,int f)
{
	siz[x]=1;mx[x]=0;
	for(int i=0;i<e[x].size();++i)
	{
		int v=e[x][i].second;
		if(vis[v] || v==f)
			continue;
		getroot(v,x);
		siz[x]+=siz[v];
		if(siz[v]>mx[x])
			mx[x]=siz[v];
	}
	if(sum-siz[x]>mx[x])
		mx[x]=sum-siz[x];
	if(mx[x]<mx[root])
		root=x;
}

void solve(int x)
{
	vis[x]=1;calc(x);
	for(int i=0;i<e[x].size();++i)
	{
		int v=e[x][i].second;
		if(!vis[v])
		{
			root=0;sum=siz[v];
			getroot(v,0);
			solve(root);
		}
	}
}

int main()
{
	freopen("BZOJ4860.in","r",stdin);
	freopen("BZOJ4860.out","w",stdout);
	
	n=read();m=read();liml=read();limr=read();
	for(int i=1;i<=m;++i)
		col[i]=read();
	for(int i=1;i<n;++i)
	{
		int u=read(),v=read(),w=read();
		add(u,v,w);
	}
	for(int i=1;i<=n;++i)
		sort(e[i].begin(),e[i].end());
	
	sum=n;mx[0]=n+1;root=0;ans=-INF;
	getroot(1,0);
	solve(root);
	printf("%d\n",ans);
	
	return 0;
}

