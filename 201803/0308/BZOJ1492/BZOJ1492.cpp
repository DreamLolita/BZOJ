#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const double eps=1e-8;
const int N=1e5+10;
const double INF=(double)1e20;
int n;
double f[N];
vector<int>q;

struct Tpoint
{
	double a,b,x,y,k,rate;
	int id;
	
	bool operator <(const Tpoint&A)const{
		return k>A.k;
	}
};
Tpoint p[N],t[N];

double slope(int x,int y)
{
	if(!y)	return -INF;
	if(fabs(p[y].x-p[x].x)<eps)	return INF;
	return (p[y].y-p[x].y)/(p[y].x-p[x].x);
}

void solve(int l,int r)
{
	if(l==r)
	{
		f[l]=max(f[l],f[l-1]);
		p[l].y=f[l]/(p[l].a*p[l].rate+p[l].b);
		p[l].x=p[l].rate*p[l].y;
//printf("%lf %lf %lf %d\n",f[l],p[l].y,p[l].x,p[l].id);
		return;
	}
	int l1,l2,mid,j;
	mid=(l+r)>>1;j=1;
	l1=l;l2=mid+1;
	for(int i=l;i<=r;++i)
	{
		if(p[i].id<=mid)
			t[l1++]=p[i];
		else
			t[l2++]=p[i];
	}
	for(int i=l;i<=r;++i)
		p[i]=t[i];
	solve(l,mid);
	
	q.clear();
	for(int i=l;i<=mid;++i)
	{
		while(q.size()>1 && slope(q[q.size()-2],q[q.size()-1])<slope(q[q.size()-2],i)+eps)
			q.pop_back();
		q.push_back(i);
	}
	q.push_back(0);
	for(int i=mid+1;i<=r;++i)
	{
		while(j<q.size() && p[i].k<slope(q[j-1],q[j])+eps)
			++j;
		f[p[i].id]=max(f[p[i].id],p[q[j-1]].x*p[i].a+p[q[j-1]].y*p[i].b);
	}
	solve(mid+1,r);
	
	l1=l;l2=mid+1;
	for(int i=l;i<=r;++i)
	{
		if(((p[l1].x<p[l2].x || (fabs(p[l1].x-p[l2].x)<eps && p[l1].y<p[l2].y)) || l2>r) && l1<=mid)
			t[i]=p[l1++];
		else
			t[i]=p[l2++];
	}
	for(int i=l;i<=r;++i)
		p[i]=t[i];
}


int main()
{
	freopen("BZOJ1492.in","r",stdin);
	freopen("BZOJ1492.out","w",stdout);
	
	scanf("%d%lf",&n,&f[0]);
	for(int i=1;i<=n;++i)
	{
		scanf("%lf%lf%lf",&p[i].a,&p[i].b,&p[i].rate);
		p[i].k=-p[i].a/p[i].b;p[i].id=i;
	}
	sort(p+1,p+n+1);
	solve(1,n);
	printf("%0.3lf\n",f[n]);
	
	return 0;
}
