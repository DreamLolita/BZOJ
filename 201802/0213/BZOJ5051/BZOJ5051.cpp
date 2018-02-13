#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=18;
const int M=2e6;
int n,m,mas,S,opt;
int p[N],cnt[N],w[M];
LL mul,f[2][M][3];
char a[N][N];

void _reset()
{
	opt^=1;
	for(int i=0;i<=mas;++i)
		for(int j=0;j<3;++j)
			f[opt][i][j]=0;
	opt^=1;
}

void dfs(int x,int y,int z)
{
	if(x==n)
	{
		w[y]=z;
		return;
	}
	for(int i=0;i<3;++i)
		dfs(x+1,y*3+i,z*2+(i?1:0));
}

int main()
{
	freopen("BZOJ5051.in","r",stdin);
	freopen("BZOJ5051.out","w",stdout);
	
	scanf("%d",&n);m=n+2;
	for(int i=0;i<m;++i)
		scanf("%s",a[i]);
	mul=p[0]=1;
	for(int i=1;i<N;++i)
		p[i]=p[i-1]*3;

	for(int i=1;i<=n;++i)
	{
		if(a[0][i]!='#' && a[m-1][i]!='#' && a[0][i]!=a[m-1][i])
			mul*=2ll;
		if(a[i][0]!='#' && a[i][m-1]!='#' && a[i][0]!=a[i][m-1])
			mul*=2ll;
		if(a[i][0]!='#')
			++cnt[i];
		if(a[i][m-1]!='#')
			++cnt[i];
		if(a[0][i]!='#')
			mas+=p[i-1];
		if(a[m-1][i]!='#')
			mas+=p[i-1];
	}
	dfs(0,0,0);
	
	f[0][mas][0]=mul;
	for(int i=1;i<=n;++i)
	{
		_reset();
		int t=cnt[i];
		for(int j=0;j<=mas;++j)
			f[opt^1][j][t]=f[opt][j][0];
		opt^=1;
		for(int j=0;j<n;++j)
			if(a[i][j+1]=='.')
			{
				_reset();
				for(int S=0;S<=mas;++S)
				{
					if(w[S]>>j&1)
						for(int k=0;k<=t;++k)
							if(f[opt][S][k])
								f[opt^1][S-p[j]][k]+=f[opt][S][k];
					for(int k=1;k<=t;++k)
						if(f[opt][S][k])
							f[opt^1][S][k-1]+=f[opt][S][k];
				}
				opt^=1;
			}
	}
	printf("%lld\n",f[opt][0][0]);
	return 0;
}
