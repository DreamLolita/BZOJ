#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=1e5+10;
const int INF=1e9;
int n,X,pos;
LL ans;
set<int>A,B,C;

struct Tpoint
{
	int x,y;
};
Tpoint a[N];

bool cmp(Tpoint q,Tpoint p)
{
	return q.x<p.x;
}

int main()
{
	freopen("BZOJ5045.in","r",stdin);
	freopen("BZOJ5045.out","w",stdout);
	
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		a[i].x=x;a[i].y=(y-x)/2;
	}
	sort(a+1,a+n+1,cmp);
	
	pos=1;X=-INF;
	while(true)
	{
		if(!A.size())
		{
			if(pos>n)
				break;
			X=a[pos].x;
		}
		C.clear();
		for(set<int>::iterator it=B.begin();it!=B.end();++it)
		{
			int x=*it;
			A.erase(x);
			if(A.find(x-1)!=A.end())
				C.insert(x-1);
		}
		B=C;
		while(pos<=n && a[pos].x==X)
		{
			int x=a[pos++].y;
			if(A.find(x)!=A.end())
				continue;
			A.insert(x);
			if(A.find(x+1)==A.end())
				B.insert(x);
			if(A.find(x-1)!=A.end())
				B.erase(x-1);
		}
		ans+=A.size();
		++X;
	}
	printf("%lld\n",ans);
	
	return 0;
}
