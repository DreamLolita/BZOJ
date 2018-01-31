#define FIO "BZOJ1064"
#include <bits/stdc++.h>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <cmath>
using namespace std;

const int MAXN=100005;
int n,m,Min,Max,anstmp,lmax,lmin;
int tim[MAXN];
bool bo[MAXN];
vector<int> way[MAXN],lon[MAXN];

struct Tnode
{
	int sn,ln;
};
Tnode P[MAXN];

int gcd(int x,int y)
{
	if(x%y==0)
		return y;
	return	gcd(y,x%y);
}

void dfs(int x,int ti,int las)
{
	lmax=max(lmax,ti);lmin=min(lmin,ti);
	tim[x]=ti;bo[x]=true;
	for(int i=0;i<way[x].size();++i)
	{
		int k=way[x][i];
		if(k==las)
			continue;
		if(bo[k])
		{
			int len=abs(tim[k]-(ti+lon[x][i]));
//printf("las:%d k:%d L:%d X:%d\n",las,k,len,x);
			if(len==0)
				continue;
			
			if(Max==0)
				Max=len;
			else
				Max=gcd(Max,len);
		}
		else
			dfs(k,ti+lon[x][i],x);
 }
}

int main()
{
//	freopen(FIO ".in","r",stdin);
//	freopen(FIO ".out","w",stdout);
	
	scanf("%d%d",&n,&m);
	
	for(int i=0;i<m;++i)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		way[a].push_back(b);
		way[b].push_back(a);
		lon[a].push_back(1);
		lon[b].push_back(-1);
	}
	
	memset(bo,false,sizeof(bo));
	for(int i=1;i<=n;++i)
	{
		if(!bo[i])
		{
			lmax=-MAXN;lmin=MAXN;
			memset(tim,0,sizeof(tim));
			dfs(i,0,i);
			anstmp+=lmax-lmin+1;
//printf("Anstmp:%d\n",anstmp);
		}
	}
	if(Max)
		for(Min=3;Min<Max && (Max%Min) ;++Min);
	else
		Max=anstmp,Min=3;
	if(Max<3)
		Max=Min=-1;
		
	
	printf("%d %d",Max,Min);
	
	return 0;
}
