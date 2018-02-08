#include<bits/stdc++.h>
using namespace std;

const int INF=105;
const int M=20001;
const int N=30;
int W,P,K,cnt;
int v[N],q[N<<1];
int C[N][N],f[N][M],g[N][M];

void init()
{
	C[0][0]=1;
	for(int i=1;i<=20;++i)
	{
		C[i][0]=1;
		for(int j=1;j<=i;++j)
			v[j]=C[i][j]=C[i-1][j-1]+C[i-1][j];
		for(int j=1;j<M;++j)
			f[i][j]=INF;
		for(int j=0;j<M-1;++j)
			if(f[i][j]<INF)
				for(int k=1;k<=i;++k)
					if(j+v[k]<M && f[i][j]+1<f[i][j+v[k]])
					{
						f[i][j+v[k]]=f[i][j]+1;
						g[i][j+v[k]]=k;
					}			
	}
}

void get_ans()
{
	if(!K)
	{
		printf("1\n%d\n",W-1);
		return;
	}

	for(int i=1;i<=20;++i)
	{	
		if(f[i][K]+i<=40)
		{
			for(int j=1;j<=i;++j)
				q[j]=1;
			
			cnt=i;
			while(K)
			{
				
				int tmp=g[i][K];
				q[++cnt]=W-tmp;
				K-=C[i][tmp];
			}
			printf("%d\n",cnt);
			for(int j=1;j<=cnt;++j)
				printf("%d%c",q[j],j==cnt?'\n':' ');
			return;
		}
	}
}

void solve()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
//		printf("%d\n",T);
		scanf("%d%d%d",&W,&P,&K);
		get_ans();
	}
}

int main()
{
//	freopen("BZOJ4971.in","r",stdin);
//	freopen("BZOJ4971.out","w",stdout);
	
	init();
	solve();
	
	return 0;
}
