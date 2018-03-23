#include<bits/stdc++.h>
using namespace std;

const int N=1e5+10;
const int mod=1e9+7;
int n,m,ans;
int Log[N],fa[N][20];
bool vis[N];

int findf(int x,int t)
{
	return fa[x][t]==x?x:fa[x][t]=findf(fa[x][t],t);
}

void merge(int x,int y,int t)
{
	int fx=findf(x,t),fy=findf(y,t);
	if(fx!=fy)
	{
		fa[fx][t]=fy;
		if(!t)
			return;
		merge(x,y,t-1);merge(x+(1<<(t-1)),y+(1<<(t-1)),t-1);
	}
}

int main()
{
	freopen("BZOJ4569.in","r",stdin);
	freopen("BZOJ4569.out","w",stdout);
	
	scanf("%d%d",&n,&m);
	Log[1]=0;
	for(int i=2;i<=n;++i)
		Log[i]=Log[i>>1]+1;
	for(int j=0;j<=Log[n];++j)
		for(int i=1;i<=n;++i)
			fa[i][j]=i;
	for(int i=1;i<=m;++i)
	{
		int a,b,c,d;
		scanf("%d%d%d%d",&a,&b,&c,&d);
		int t=Log[b-a+1];
		merge(a,c,t);merge(b-(1<<t)+1,d-(1<<t)+1,t);
	}
	ans=9;vis[findf(1,0)]=true;
	for(int i=2;i<=n;++i)
	{
		int x=findf(i,0);
		if(!vis[x])
			vis[x]=true,ans=10ll*ans%mod;
	}
	printf("%d\n",ans);
	
	return 0;
}
