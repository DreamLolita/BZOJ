#include<bits/stdc++.h>
#define mkp(x,y) make_pair(x,y)
using namespace std;

typedef long long LL;
typedef pair<LL,int> pii;
const int N=2e5+10;
int n,m,tot;
int head[N],vis[N];
LL dis[N];
priority_queue<pii>q;

struct Tway
{
	int v,nex;
	LL w;
	Tway(){}
	Tway(int vv,int nexx,LL ww){
		v=vv;nex=nexx;w=ww;
	}
};
Tway e[N<<1];

void add(int u,int v,LL w)
{
	e[++tot]=Tway(v,head[u],w);head[u]=tot;
	e[++tot]=Tway(u,head[v],w);head[v]=tot;
}

LL read()
{
	LL ret=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c)){ret=(ret<<1ll)+(ret<<3ll)+(c^48);c=getchar();}
	return f?ret:-ret;
}

void write(LL x)
{
	if(x<0)putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar((x%10)^48);
}

int main()
{
	freopen("CF938D.in","r",stdin);
	freopen("CF938D.out","w",stdout);
	
	n=read();m=read();
	for(int i=1;i<=m;++i)
	{
		int u=read(),v=read();LL w=read();
		add(u,v,w);
	}
	for(int i=1;i<=n;++i)
	{
		dis[i]=read();
		q.push(mkp(-dis[i],i));
	}
	while(!q.empty())
	{
		int u=q.top().second;LL ds=-q.top().first;q.pop();
		if(vis[u])
			continue;
		vis[u]=1;
		for(int i=head[u];i;i=e[i].nex)
		{
			int v=e[i].v;
			if(dis[v]>dis[u]+e[i].w*2)
			{
				dis[v]=dis[u]+e[i].w*2;
				q.push(mkp(-dis[v],v));
			}
		}
	}
	for(int i=1;i<=n;++i)
		write(dis[i]),putchar(' ');	

	return 0;
}
