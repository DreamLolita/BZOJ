#include<bits/stdc++.h>
using namespace std;

const int INF=1e9;
const int N=3005;
int n,m,sum;
int a[N],f[N][N];

int sqr(int x)
{
	return x*x;
}

void solve(int l,int r,int L,int R,int p)
{
	if(l>r || L>R)
		return;
	int mid=(l+r)>>1,v=INF,pos;
	for(int i=L;i<mid && i<=R;++i)
	{
		if(sqr(a[mid]-a[i])+f[i][p-1]<v)
		{
			v=sqr(a[mid]-a[i])+f[i][p-1];
			pos=i;
		}
	}
	f[mid][p]=v;
	solve(l,mid-1,L,pos,p);
	solve(mid+1,r,pos,R,p);
}

int main()
{
	freopen("BZOJ4518.in","r",stdin);
	freopen("BZOJ4518.out","w",stdout);
	
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
	{
		scanf("%d",&a[i]);
		sum+=a[i];a[i]+=a[i-1];
	}
	for(int i=1;i<=n;++i)
		f[i][0]=INF;
	for(int j=1;j<=m;++j)
		solve(1,n,0,n,j);
	printf("%lld\n",1ll*m*f[n][m]-1ll*sum*sum);
	
	return 0;
}
