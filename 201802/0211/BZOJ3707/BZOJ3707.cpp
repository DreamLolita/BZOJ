#include<bits/stdc++.h>
using namespace std;

const int N=1e3+10;
int n,tot;
int id[N*N],a[N*N];
double ans=1e60;

struct Tpoint
{
	double x,y;
	
	bool operator <(const Tpoint &A)const{
		return x<A.x;
	}
	
	friend Tpoint operator -(const Tpoint &A, const Tpoint &B){
        return (Tpoint){A.x-B.x, A.y-B.y};
    }
};
Tpoint p[N];

struct Tline
{
	int x,y;
	double k;
	
	bool operator <(const Tline &A)const{
		return k<A.k;
	}
};
Tline l[N*N];

double cross(Tpoint A,Tpoint B)
{
	return A.x*B.y-A.y*B.x;
}

void calc(int i,int j,int k)
{
	double ret=fabs(cross(p[i]-p[k],p[j]-p[k]))/2.0;
	ans=min(ans,ret);
}

int main()
{
	freopen("BZOJ3707.in","r",stdin);
	freopen("BZOJ3707.out","w",stdout);
	
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%lf%lf",&p[i].x,&p[i].y);
	sort(p+1,p+n+1);
	for(int i=1;i<=n;++i)
		id[i]=a[i]=i;
	for(int i=1;i<n;++i)
		for(int j=i+1;j<=n;++j)
		{
			++tot;
			l[tot].x=i;l[tot].y=j;
			l[tot].k=(p[j].y-p[i].y)/(p[j].x-p[i].x);
		}
	sort(l+1,l+tot+1);
	for(int i=1;i<=tot;++i)
	{
		int t1=l[i].x,t2=l[i].y;
		if(id[t1]>id[t2])	
			swap(t1,t2);
		if(id[t1]>1)
			calc(a[id[t1]-1],t1,t2);
		if(id[t2]<n)
			calc(a[id[t2]+1],t1,t2);
		swap(id[t1],id[t2]);
		swap(a[id[t1]],a[id[t2]]);
	}
	printf("%0.2f\n",ans);
	
	return 0;	
}
