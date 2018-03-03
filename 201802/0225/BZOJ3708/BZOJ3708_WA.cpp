#include<bits/stdc++.h>
using namespace std;

const int M=12005;
int n,m,cnt,tot,totalm,top;
int head[M],sta[M];
int cir[M],nex[M],v[M],path[M];
bool vis[M],cirvis[M],insta[M];

void add(int us,int vs)
{
	++tot;
	v[tot]=vs;cir[tot]=0;
	nex[tot]=head[us];head[us]=tot;
}

void init()
{
	scanf("%d",&n);tot=m=0;
	for(int i=1;i<=n;++i)
	{
		int x,y;
		scanf("%d",&x);
		m+=x;
		for(int j=1;j<=x;++j)
		{
			scanf("%d",&y);
			add(i,y);
		}
	}
}

int dfs(int x)
{
	path[++cnt]=x;
	for(int i=head[x];i;i=nex[i])
		if(!vis[i])
		{
			vis[i]=1;
			totalm++;
			return dfs(v[i]);
		}
	return x;
}

void dfs_no_cir(int x)
{
	path[++cnt]=x;
	for(int i=head[x];i;i=nex[i])
		if(!vis[i] && !cir[i])
		{
			vis[i]=1;
			dfs_no_cir(v[i]);
			return;
		}
}

void out_put()
{
	for(int i=2;i<=cnt;++i)
		printf("%d ",path[i]);
	printf("0\n");
}

bool solve_cir(int x,int ecnt)
{
	cirvis[x]=1;
	++top;insta[x]=top;sta[top]=ecnt;
	for(int i=head[x];i;i=nex[i])
	{
		if(v[i]==n)
			continue;
		if(!vis[i])
		{
			vis[i]=1;
			if(insta[v[i]])
			{
				cir[i]=1;
				while(top>insta[v[i]])
				{
					cir[sta[top]]=1;
					--top;
				}
				return true;
			}
			else
			{
				bool flag=solve_cir(v[i],i);
				if(flag)
					return flag;
			}
		}
	}
	insta[x]=0;sta[top]=0;--top;
	return false;
}

void _reset()
{
	top=0;
	memset(vis,0,sizeof(vis));
	memset(sta,0,sizeof(sta));
	memset(insta,0,sizeof(insta));
}

void solve()
{
	int endv=dfs(1);
	if(endv!=n || totalm<m)
		out_put();
	else
	{
		bool flag=false;
		for(int i=1;i<n;++i)
		{
			if(cirvis[i])
				continue;
			_reset();
			if(solve_cir(i,0))
			{
				flag=true;
				break;
			}
		}
		if(!flag)
			puts("NIE");
		else
		{
			cnt=0;
			memset(vis,0,sizeof(vis));
			dfs_no_cir(1);
			out_put();
		}
	}
}

int main()
{
//	freopen("BZOJ3708.in","r",stdin);
//	freopen("BZOJ3708.out","w",stdout);
	
	init();
	solve();
	
	return 0;
}
