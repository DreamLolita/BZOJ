#include<bits/stdc++.h>
#define L 16
using namespace std;

const int N=1024;
const int M=8192;
int T,n,m,k,tot,ans;
int head[M],q[M];
bool lef[M],vis[M];
char ret[L];

struct Tway
{
	int v,nex,f;
};
Tway e[M<<1];

void init()
{
	tot=ans=0;
	memset(vis,0,sizeof(vis));
	memset(head,-1,sizeof(head));
	memset(lef,0,sizeof(lef));
}

int idx(char *s)
{
	int x;
	if(sscanf(s+2,"%d",&x)==EOF)
		return -1;
	if(!strncmp(s,"AP",2))
		return x;
	if(!strncmp(s,"AS",2))
		return x+n;
	if(!strncmp(s,"BP",2))
		return x+n+k;
	if(!strncmp(s,"BS",2))
		return x+n+k+m;
	return -1;
}

void idx_ans(int x)
{
//	if(x<= 0)
//		sprintf(out,"error! index < 0!");
//	else 
	if(x<=n)
		sprintf(ret,"AP%d",x);
	else 
	if(x<=n+k)
		sprintf(ret,"AS%d",x-n);
	else 
	if(x<=n+k+m)
		sprintf(ret,"BP%d",x-n-k);
	else 
	if(x<=n+k+m+k)
		sprintf(ret,"BS%d",x-n-k-m);
//	else
//		sprintf(out, "error! index > n + k + m + k");
}

void add(int u,int v)
{
//	printf("u:%d v:%d %d\n",u,v,tot);
	e[tot]=(Tway){v,head[u],0};
	head[u]=tot++;
	e[tot]=(Tway){u,head[v],0};
	head[v]=tot++;
}

bool dfs(int u,int p)
{
//	printf("%d %d\n",u,p);
	int cnt=0;
	for(int i=head[u];~i;i=e[i].nex)
	{
//		printf("%d %d i:%d %d %d\n",u,p,i,e[i].nex,e[i].f);
		if(i==(p^1))
			continue;
		int v=e[i].v;
		if(!dfs(v,i))
			return 0;
		cnt+=(!e[i].f);
	}
	if(cnt==2 && p!=-1)
		e[p].f=e[p^1].f=1;
//	printf("%d!!! %d\n",cnt,lef[u]);
	return lef[u] || cnt==1 || cnt==2;
}

bool pfs(int u)
{
	vis[u]=1;q[ans++]=u;
	int cnt=0;
	for(int i=head[u];~i;i=e[i].nex)
	{
		int v=e[i].v;
		if(e[i].f)
			continue;
		++cnt;
		if(!vis[v] && !pfs(v))
			return 0;
	}
	return cnt==2;
}

void solve()
{
	bool flag=1;            
	char u[L],v[L];
	scanf("%d%d%d",&k,&n,&m);
	for(int i=1;i<=k;++i)
		lef[n+i]=lef[n+k+m+i]=1;
	for(int i=1;i<n+k;++i)
	{
		scanf("%s%s",u,v);
		add(idx(u),idx(v));
	}
	flag&=dfs(1,-1);


	for(int i=1;i<m+k;++i)
	{
		scanf("%s%s",u,v);
		add(idx(u),idx(v));
	}
	if(flag)
		flag&=dfs(n+k+1,-1);
	
	for(int i=0;i<k;++i)
	{
		scanf("%s%s",u,v);
		add(idx(u),idx(v));
	}
	if(flag)
		flag&=pfs(1);
	
	if(flag && ans==n+k+m+k)
	{
		printf("YES");
		for(int i=0;i<ans;++i)
		{
			idx_ans(q[i]);
			printf(" %s",ret);
		}
		printf("\n");
	}
	else
		puts("NO");
}

int main()
{
//	freopen("BZOJ4065.in","r",stdin);
//	freopen("BZOJ4065.out","w",stdout);
	
	scanf("%d",&T);
	while(T--)
	{
		init();
		solve();
	}
	
	return 0;
}
