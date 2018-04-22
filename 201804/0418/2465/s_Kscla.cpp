#include<iostream>
#include<string>
#include<cstring>
#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<stdio.h>
#include<algorithm>
#include<set>
#pragma GCC optimize("O3") 
using namespace std;

#define RG register

const int maxt=7;
const int maxn=12;
const int maxk=18;
const int maxs=(1<<15)+100;

set <int> f[maxt][maxn][maxn][maxn][maxn];

int Map[maxn][maxn];
int cnt[maxn][maxn];

int Val[maxs][maxk];

int id[maxk];
int Weight[maxk];
int Num[maxk];
int cur;

int h[maxk];
int t,n,m,k;

inline int Sum(int a,int b,int c,int d)
{
	--a;
	--c;
	return (cnt[b][d]-cnt[a][d]-cnt[b][c]+cnt[a][c]);
}

inline bool Judge(int u,int v)
{
	for (RG int i=1; i<=cur; ++i)
		if (Val[u][i]+Val[v][i]>Num[i]) return false;
	return true;
}

int main()
{
	freopen("2465.in","r",stdin);
	freopen("2465.out","w",stdout);
	
	scanf("%d",&t);
	while (t--)
	{
		scanf("%d%d%d",&n,&m,&k);
		int sum=0;
		for (RG int i=1; i<=n; ++i)
			for (RG int j=1; j<=m; ++j)
			{
				scanf("%d",&Map[i][j]);
				sum+=Map[i][j];
				cnt[i][j]=cnt[i-1][j]+cnt[i][j-1]-cnt[i-1][j-1]+Map[i][j];
			}
		for (RG int i=1; i<=k; ++i) scanf("%d",&h[i]),sum-=h[i];
		
		if (sum!=0)
		{
			printf("no\n");
			continue;
		}
		
		cur=0;
		sort(h+1,h+k+1);
		for (RG int i=1; i<=k; ++i)
			if (h[i-1]==h[i]) ++Num[cur];
			else Num[++cur]=1,id[cur]=i;
		
		Weight[1]=1;
		for (RG int i=2; i<=cur+1; ++i)
			Weight[i]=Weight[i-1]*(Num[i-1]+1);
		
		for (RG int i=0; i<Weight[cur+1]; ++i)
			for (RG int j=1; j<=cur; ++j)
				Val[i][j]=i%Weight[j+1]/Weight[j];
		
		set <int> :: iterator P,Q,T1,T2;
		for (RG int lx=1; lx<=n; ++lx)
			for (RG int a=1; a<=n-lx+1; ++a)
				for (RG int ly=1; ly<=m; ++ly)
					for (RG int c=1; c<=m-ly+1; ++c)
					{
						int b=a+lx-1;
						int d=c+ly-1;
						set <int> &K=f[t][a][b][c][d];
						
						for (RG int i=1; i<=cur; ++i)
							if ( Sum(a,b,c,d)==h[ id[i] ] ) K.insert(Weight[i]);
						
						for (RG int x=a; x<b; ++x)
						{
							T1=f[t][a][x][c][d].end();
							for (P=f[t][a][x][c][d].begin(); P!=T1; ++P)
							{
								T2=f[t][x+1][b][c][d].end();
								for (Q=f[t][x+1][b][c][d].begin(); Q!=T2; ++Q)
								{
									int u=(*P),v=(*Q);
									if ( !Judge(u,v) ) continue;
									K.insert(u+v);
								}
							}
						}
						
						for (RG int y=c; y<d; ++y)
						{
							T1=f[t][a][b][c][y].end();
							for (P=f[t][a][b][c][y].begin(); P!=T1; ++P)
							{
								T2=f[t][a][b][y+1][d].end();
								for (Q=f[t][a][b][y+1][d].begin(); Q!=T2; ++Q)
								{
									int u=(*P),v=(*Q);
									if ( !Judge(u,v) ) continue;
									K.insert(u+v);
								}
							}
						}
					}
		
		if (f[t][1][n][1][m].empty()) printf("no\n");
		else printf("yes\n");
	}
	
	return 0;
}

























