#define FIO "BZOJ2743"
#include <bits/stdc++.h>
#include <algorithm>
#include <cstdio>
using namespace std;

const int MAXN=1000005;
int n,c,m;
int num[MAXN],ans[MAXN],C[4*MAXN];

struct Tflow
{
	int l,r,id;
};
Tflow d[MAXN];

struct Trem
{
	int fir,sed;
};
Trem p[MAXN];

int cmp(Tflow a,Tflow b)
{
	if(a.l==b.l)
		return	a.r>b.r;
	return a.l>b.l;
}

int sum(int x)
{
	int ret=0;
	while(x>0)
	{
		ret+=C[x];
		x-=(x&-x);
	}
	return ret;
}

void add(int x,int y)
{
	while(x<=n)
	{
		C[x]+=y;
		x+=(x&-x);
	}
}

int main()
{
//	freopen(FIO ".in","r",stdin);
//	freopen(FIO ".out","w",stdout);
	
	scanf("%d%d%d",&n,&c,&m);
	for(int i=1;i<=n;++i)
	{
		scanf("%d",&num[i]);
		p[i].fir=p[i].sed=-1;
	}
	for(int i=1;i<=m;++i)
	{
		scanf("%d%d",&d[i].l,&d[i].r);
		d[i].id=i;
	}
	
	sort(d+1,d+m+1,cmp);
	
	int t=1;
	for(int i=n;i>=1;--i)
	{
		if(p[num[i]].fir!=-1)
		{
			if(p[num[i]].sed!=-1)
				add(p[num[i]].sed,-1);
				
			p[num[i]].sed=p[num[i]].fir;	
			add(p[num[i]].sed,1);
		}
		p[num[i]].fir=i;
		
		while(d[t].l==i &&t<=m)
		{
			ans[d[t].id]=sum(d[t].r);
			++t;
		}
	}
	for(int i=1;i<=m;++i)
		printf("%d\n",ans[i]);
	
	return 0;
}
