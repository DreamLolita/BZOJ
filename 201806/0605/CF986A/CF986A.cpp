#include<bits/stdc++.h>
using namespace std;

const int INF=1e9+10;
const int N=1e5+10;
const int M=105;
int n,m,k,s,tot;
int head[N],tmp[N],d[N][M];
vector<int>mp[N];
queue<int>q;

int read()
{
	int ret=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c)){ret=ret*10+(c^48);c=getchar();}
	return f?ret:-ret;
}

void write(int x)
{
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar((x%10)^48);
}

struct Tway
{
	int v,nex;
};
Tway e[N<<1];

void add(int u,int v)
{
	e[++tot]=(Tway){v,head[u]};head[u]=tot;
	e[++tot]=(Tway){u,head[v]};head[v]=tot;
}

void bfs(int col)
{
	memset(tmp,127,sizeof(tmp));
	while(!q.empty())
		q.pop();
	for(int i=0;i<(int)mp[col].size();++i)
		q.push(mp[col][i]),tmp[mp[col][i]]=0;
	while(!q.empty())
	{
		int u=q.front();q.pop();
		for(int i=head[u];i;i=e[i].nex)
		{
			int v=e[i].v;
			if(tmp[v]<INF)
				continue;
			tmp[v]=tmp[u]+1;q.push(v);
		}
	}
	for(int i=1;i<=n;++i)
		d[i][col]=tmp[i];
}

int main()
{
	freopen("CF986A.in","r",stdin);
	freopen("CF986A.out","w",stdout);

	n=read();m=read();k=read();s=read();
	for(int i=1;i<=n;++i)
	{	
		int t=read();
		mp[t].push_back(i);
	}
	for(int i=1;i<=m;++i)
	{
		int u=read(),v=read();
		add(u,v);
	}
	memset(d,127,sizeof(d));
	for(int i=1;i<=k;++i)
		bfs(i);
	for(int i=1;i<=n;++i)
	{
		int ans=0;
		sort(d[i]+1,d[i]+k+1);
		for(int j=1;j<=s;++j)
			ans+=d[i][j];
		write(ans);putchar(' ');
	}

	return 0;
}
