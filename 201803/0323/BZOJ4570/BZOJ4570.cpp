#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef long double ldb;
const int N=1e6+10;
const LL INF=1ll<<40;
int n;
ldb ans,mi,mx;

struct Tpoint 
{
	int x,y;
};
Tpoint p[N],d[N];

bool cmp(Tpoint A,Tpoint B)
{
	return A.x<B.x || (A.x==B.y && A.y>B.y);
}

ldb slope(Tpoint A,Tpoint B)
{
	return (ldb)(B.y-A.y)/(B.x-A.x);
}

ldb get_ans(Tpoint A,ldb k)
{
	return A.x+A.y-k*A.x-(1.0/k)*A.y;
}

ldb get_k(Tpoint A)
{
	return -sqrt(ldb(A.y/A.x));
}

int main()
{
	freopen("BZOJ4570.in","r",stdin);
	freopen("BZOJ4570.out","w",stdout);
	
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%d%d",&p[i].x,&p[i].y);
	sort(p+1,p+n+1,cmp);
	int top=0;
	for(int i=1;i<=n;++i)
		if(p[i].x>p[i-1].x)
		{
			while(top>1 && slope(d[top-1],d[top])<slope(d[top],p[i]))
				top--;
			d[++top]=p[i];
		}

	ans=INF;
	if(top==1)
		ans=get_ans(d[top],get_k(d[top]));
	else
	{
		mi=slope(d[1],d[2]),mx=0;
		for(int i=1;i<=top;++i)
		{
//			printf("%0.4lf %0.4lf\n",mx,mi);
			if(i^top)
				mi=slope(d[i],d[i+1]);
			else
				mi=-INF;
			ldb k=get_k(d[i]);
			if(mi<=k && mx>=k)
				ans=min(ans,get_ans(d[i],k));
			if(i>1 && d[i].y!=d[i-1].y)
				ans=min(ans,get_ans(d[i],slope(d[i-1],d[i])));
			mx=mi;
		}
	}	
	printf("%0.4lf\n",(double)ans);
	
	return 0;
}
