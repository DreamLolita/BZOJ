#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int lim=233;
const int N=5e4+10;
const int M=2e6+10;
int n,m,q,tot;
int head[N],val[N],p[N];
LL ans[N];

int read()
{
	int ret=0,f=1;char c='.';
	while(c<'0' || c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0' && c<='9'){ret=(ret<<3)+(ret<<1)+(c-'0');c=getchar();}
	return ret*f;
}

struct Tquery
{
	int l,r,id,s;
};
Tquery qs[N];

bool cmp(Tquery A,Tquery B)
{
	if(A.s^B.s)
		return A.s<B.s;
	return A.r<B.r;
}

struct Tway
{
	int v,nex,w;
};
Tway e[N<<1];

void add(int u,int v,int w)
{
	e[++tot]=(Tway){v,head[u],w};head[u]=tot;
	e[++tot]=(Tway){u,head[v],w};head[v]=tot;
}

void dfs(int u,int fa)
{
	for(int i=head[u];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(v==fa)
			continue;
		val[v]=e[i].w^val[u];dfs(v,u);
	}
}

struct Trie
{
	int ind;
	int ch[M][20],cnt[M];

	void init()
	{
		ind=cnt[0]=0;
		ch[0][0]=ch[0][1]=0;
	}
	
	void insert(int x)
	{
		int now=0;
		for(int i=17;~i;--i)
		{
			int c=x>>i&1;
			if(!ch[now][c])
				ch[now][c]=++ind,cnt[ind]=0,ch[ind][0]=ch[ind][1]=0;
			now=ch[now][c];++cnt[now];
		}
	}
	
	void dele(int x)
	{
		int now=0;
		for(int i=17;~i;--i)
		{
			int c=x>>i&1;
			now=ch[now][c];cnt[now]--;
		}
	}
	
	LL query(int x)
	{
		LL ret=0;int now=0;
		for(int i=17;~i;--i)
		{
			int c=x>>i&1,d=p[i];
			if(d)
				now=ch[now][c^1];
			else
				ret+=cnt[ch[now][c^1]],now=ch[now][c];
			if(!now)
				return ret;	
		}	
		return ret;
	}
	
	void solve()
	{
		sort(qs+1,qs+q+1,cmp);
		int l=1,r=0;LL ret=0;
		for(int i=1;i<=q;++i)
		{
			while(r<qs[i].r) ++r,ret+=query(val[r]),insert(val[r]);
			while(l>qs[i].l) --l,ret+=query(val[l]),insert(val[l]);
			while(r>qs[i].r) dele(val[r]),ret-=query(val[r]),--r;
			while(l<qs[i].l) dele(val[l]),ret-=query(val[l]),++l;
			ans[qs[i].id]=ret;
		}
		
		for(int i=1;i<=q;++i)
			printf("%lld\n",ans[i]);
	}
}tr;

void init()
{
	for(int i=0;i<18;++i)
		p[i]=(m>>i)&1;
	memset(head,0,sizeof(head));tot=0;
	for(int i=1;i<n;++i)
	{
		int u=read(),v=read(),w=read();
		add(u,v,w);
	}
	for(int i=1;i<=q;++i)
	{
		qs[i].l=read();qs[i].r=read();
		qs[i].id=i;qs[i].s=(qs[i].l-1)/lim+1;
	}
}

int main()
{
	freopen("HDU5589.in","r",stdin);
	freopen("HDU5589.out","w",stdout);
	
	while(scanf("%d%d%d",&n,&m,&q)!=EOF)
	{
		init();dfs(1,0);
		tr.init();tr.solve();
	}
	return 0;
}
