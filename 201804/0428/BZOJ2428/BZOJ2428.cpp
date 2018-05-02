#include<bits/stdc++.h>
using namespace std;

const double bas=0.93;
const double eps=1e-4;
const int N=50;
int n,m,a[N],sum[N],bl[N];
double aver,ans=1e30;

double sqr(double x)
{
	return x*x;
}

double rnd1()
{
	return rand()%456+321;
}

double rnd2()
{
	return rand()%1000/1000.0;
 } 

void solve(double temp)
{
	memset(sum,0,sizeof(sum));
	for(int i=1;i<=n;++i)
	{
		bl[i]=rand()%m+1;
		sum[bl[i]]+=a[i];
	}
	double now=0;
	for(int i=1;i<=m;++i)
		now+=sqr(sum[i]-aver);
	while(temp>eps)
	{
		temp*=bas;
		int t=rand()%n+1,x=bl[t],y;
		if(temp>rnd1())
			y=min_element(sum+1,sum+m+1)-sum;
		else
			y=rand()%m+1;
		if(x==y)
			continue;
		double tmp=now;
		tmp-=sqr(sum[x]-aver);tmp-=sqr(sum[y]-aver);
		sum[x]-=a[t];sum[y]+=a[t];
		tmp+=sqr(sum[x]-aver);tmp+=sqr(sum[y]-aver);
		if(tmp<=now || exp((now-tmp)/temp)>rnd2())
			bl[t]=y,now=tmp;
		else
			sum[x]+=a[t],sum[y]-=a[t];
	}
	if(now<ans)
		ans=now;
}

int main()
{
	freopen("BZOJ2428.in","r",stdin);
	freopen("BZOJ2428.out","w",stdout);
	
	srand(19260817);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
		scanf("%d",&a[i]),aver+=a[i];
	aver/=(double)m;
	for(int i=1;i<=1000;++i)
		solve(1e5);
	printf("%.2lf\n",sqrt(ans/m));
	
	return 0;
}
