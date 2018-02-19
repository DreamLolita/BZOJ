#include<bits/stdc++.h>
using namespace std;

const int INF=0x3f3f3f3f;
const int N=3005;
int T,n,m,c,h,t,ans;
int a[N],b[N],g[N],d[N];
int f[N][N];

struct Tque
{
	int x,y;
}q[N];

void init()
{
	ans=-INF;
	scanf("%d%d%d",&n,&m,&c);
	for(int i=1;i<=n;++i)
		scanf("%d",&a[i]);
	for(int i=1;i<=n;++i)
		scanf("%d",&b[i]);
	for(int i=1;i<=n;++i)
		scanf("%d",&g[i]);
	for(int i=1;i<=n;++i)
		scanf("%d",&d[i]);
	memset(f,-INF,sizeof(f));
}

void solve()
{
	for(int i=1;i<=n;++i)
	{
		for(int j=0;j<=g[i];++j)
			f[i][j]=-a[i]*j;
		for(int j=0;j<=c;++j)
			f[i][j]=max(f[i][j],f[i-1][j]);
		int k=i-m-1;
		if(k>=0)
		{
			h=t=0;
			for(int j=0;j<=c;++j)//buy
			{
				while(h<t && q[h].x<j-g[i])
					++h;
				while(h<t && q[t-1].y<=f[k][j]+a[i]*j)
					--t;
				q[t++]=(Tque){j,f[k][j]+a[i]*j};
				if(h<t)
					f[i][j]=max(f[i][j],q[h].y-a[i]*j);
			}
			h=t=0;
			for(int j=c;j>=0;--j)//sale
			{
				while(h<t && q[h].x>j+d[i])
					++h;
				while(h<t && q[t-1].y<=f[k][j]+b[i]*j)
					--t;
				q[t++]=(Tque){j,f[k][j]+b[i]*j};
				if(h<t)
					f[i][j]=max(f[i][j],q[h].y-b[i]*j);
			}
		}
		ans=max(ans,f[i][0]);
	}
	printf("%d\n",ans);	
}

int main()
{
	freopen("BZOJ2826.in","r",stdin);
	freopen("BZOJ2826.out","w",stdout);
	
	scanf("%d",&T);
	while(T--)
	{
		init();	
		solve();
	}
	
	return 0;
}
