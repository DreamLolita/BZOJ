#include<bits/stdc++.h>
using namespace std;

const int INF=1e9;
const int N=5e5+10;
const int M=2e6+10;
int n,m,h,t,mn,ans;
int du[M],qs[M],w[M];
priority_queue<int>p,q; 

struct Tst
{
	int u[M],v[M],nex[M],head[N],dis[N],du[N],tot;
	
	inline void add(int x,int y)
	{
		++tot;
		u[tot]=x;v[tot]=y;
		nex[tot]=head[x];head[x]=tot;
	}
	
	inline void solve(int S)
	{
		memset(dis,0,sizeof(dis));
		h=t=1;qs[1]=S;
		while(h<=t)
		{
			int x=qs[h++];
			for(int i=head[x];i;i=nex[i])
			{
				int y=v[i];
				dis[y]=max(dis[y],dis[x]+1);
				du[y]--;
				if(!du[y])
					qs[++t]=y;
			}
		}
	}
};
Tst A,B;

inline void dele(int x)
{
	q.push(x);
	while(!p.empty() && !q.empty() && q.top()==p.top())
	{
		q.pop();
		p.pop();
	}
}

int read()
{
	int x=0;char c='.';
	while(c<'0' || c>'9')
		c=getchar();
	while(c>='0' && c<='9')
	{
		x=x*10+(c-'0');
		c=getchar();
	}
	return x;
}

int main()
{
//	freopen("BZOJ3832.in","r",stdin);
//	freopen("BZOJ3832.out","w",stdout);
	
	n=read();m=read();
	for(int i=1;i<=m;++i)
	{
		int u,v;
		u=read();v=read();
		du[v]++;A.du[v]++;B.du[u]++;
		A.add(u,v);B.add(v,u);
	}
	for(int i=1;i<=n;++i)
	{
		du[i]++;du[n+1]++;
		A.du[i]++;A.du[n+1]++;
		B.du[i]++;B.du[0]++;
		A.add(0,i);A.add(i,n+1);
		B.add(i,0);B.add(n+1,i);
	}
	A.solve(0);B.solve(n+1);
	
	for(int i=1;i<=m+2*n;++i)
		w[i]=A.dis[A.u[i]]+B.dis[A.v[i]]-1;
	
	h=t=1;qs[1]=0;
	mn=INF;
	while(h<=t)
	{
		int x=qs[h++];
		for(int i=B.head[x];i;i=B.nex[i])
		dele(w[i]);
		if(x!=0 && x!=n+1)
		{
			int y=p.top();
			if(y<mn)
				mn=y,ans=x;
		}
		for(int i=A.head[x];i;i=A.nex[i])
		{
			int y=A.v[i];
			p.push(w[i]);
			du[y]--;
			if(!du[y])
				qs[++t]=y;
		}
	}
	printf("%d %d\n",ans,mn);
	
	return 0;
}
