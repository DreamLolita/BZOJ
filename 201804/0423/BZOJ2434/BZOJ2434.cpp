#include<bits/stdc++.h>
#define lowbit(x) (x&(-x))
using namespace std;

const int N=1e5+10;
int n,m,ind,tot,toe;
int beg[N],en[N],bit[N<<1];
int head[N],headq[N],pos[N],ans[N];
char s[N];

int read()
{
	int ret=0;char c='.';
	while(!isdigit(c)){c=getchar();}
	while(isdigit(c)){ret=(ret<<3)+(ret<<1)+(c^48);c=getchar();}
	return ret;
}

struct Tway
{
	int v,nex;
};
Tway e[N<<1],qr[N<<1];

void add(int u,int v)
{
	e[++tot]=(Tway){v,head[u]};
	head[u]=tot;
}

void ade(int u,int v)
{
	qr[++toe]=(Tway){v,headq[u]};
	headq[u]=toe;
}

void update(int x,int v)
{
	for(;x<=ind;x+=lowbit(x))
		bit[x]+=v;
}

int query(int x)
{
	int ret=0;
	for(;x;x-=lowbit(x))
		ret+=bit[x];
	return ret;
}

struct ACM
{
	int sz;
	int fa[N],fail[N],ch[N][27];
	queue<int>q;
	
	void init()
	{
		sz=1;
		for(int i=0;i<26;++i)
			ch[0][i]=1;
	}
	
	void build()
	{
		int now=1,id=0;
		for(int i=0;i<n;++i)
		{
			if(s[i]=='P')
				pos[++id]=now;
			else
			if(s[i]=='B')
				now=fa[now];
			else
			{
				if(!ch[now][s[i]-'a'])
				{
					ch[now][s[i]-'a']=++sz;
					fa[sz]=now;
				}
				now=ch[now][s[i]-'a'];
			}
		}
	}
	
	void get_fail()
	{
		fail[1]=0;q.push(1);
		while(!q.empty())
		{
			int now=q.front();q.pop();
			for(int i=0;i<26;++i)
				if(ch[now][i])
				{
					int v=ch[now][i],t=fail[now];
					while(!ch[t][i])
						t=fail[t];
					fail[v]=ch[t][i];
					q.push(v);
				}
		}
	}
	
	void solve()
	{
		int now=1,id=0;
		add(beg[1],1);
		for(int i=0;i<n;++i)
		{
			if(s[i]=='P')
			{
				++id;
				for(int j=headq[id];j;j=qr[j].nex)
				{
					int t=pos[qr[j].v];
					ans[j]=query(en[t])-query(beg[t]-1);
				}
			}
			else
			if(s[i]=='B')
				update(beg[now],-1),now=fa[now];
			else
				now=ch[now][s[i]-'a'],update(beg[now],1);
		}
	}
}ac;

void dfs(int x)
{
	beg[x]=++ind;
	for(int i=head[x];i;i=e[i].nex)
		dfs(e[i].v);
	en[x]=++ind;
}

int main()
{
	freopen("BZOJ2434.in","r",stdin);
	freopen("BZOJ2434.out","w",stdout);
	
	scanf("%s",s);n=strlen(s);
	ac.init();ac.build();ac.get_fail();
	for(int i=1;i<=ac.sz;++i)
		add(ac.fail[i],i);
	m=read();
	for(int i=1;i<=m;++i)
	{
		int x=read(),y=read();
		ade(y,x);
	}
	dfs(0);
	ac.solve();
	for(int i=1;i<=m;++i)
		printf("%d\n",ans[i]);
	
	return 0;
}
