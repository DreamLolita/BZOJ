#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int MAXN=5e4+10;
int n,T;
double ans;
char opt[15];

struct Tree
{
	bool f;
	double b,k;
};
Tree tr[MAXN<<2];

double cross(double k1,double b1,double k2,double b2)
{
	return (b2-b1)/(1.0*(k1-k2));
}

void update(int rt,int l,int r,double db,double dk)
{
//printf("%d %d %d %0.3f %0.3f\n",rt,l,r,db,dk);
	if(!tr[rt].f)
	{
		tr[rt].k=dk;tr[rt].b=db;tr[rt].f=1;
		return;
	}
	int mid=(l+r)>>1;
	double f1=1.0*dk*l+db,f2=1.0*dk*r+db;
	double f3=1.0*tr[rt].k*l+tr[rt].b,f4=1.0*tr[rt].k*r+tr[rt].b;
	if(f1<=f3 && f2<=f4)
		return;
	if(f1>=f3 && f2>=f4)
		tr[rt].k=dk,tr[rt].b=db;
	else
	{
		
		double nx=cross(dk,db,tr[rt].k,tr[rt].b);
		if(f1>=f3)
		{
			if(nx<=mid)
				update(rt<<1,l,mid,db,dk);
			else
				update(rt<<1|1,mid+1,r,tr[rt].b,tr[rt].k),tr[rt].k=dk,tr[rt].b=db;
		}
		else
		{
			if(nx<=mid)
				update(rt<<1,l,mid,tr[rt].b,tr[rt].k),tr[rt].k=dk,tr[rt].b=db;
			else
				update(rt<<1|1,mid+1,r,db,dk);
		}
	}
}

void query(int rt,int l,int r,int x)
{
	if(tr[rt].f)
		ans=max(ans,1.0*tr[rt].k*x+tr[rt].b);
	if(l==r)
		return;
	int mid=(l+r)>>1;
	if(x<=mid)
		query(rt<<1,l,mid,x);
	else
		query(rt<<1|1,mid+1,r,x);
}

int main()
{
//	freopen("BZOJ1568.in","r",stdin);
//	freopen("BZOJ1568.out","w",stdout);
	
	n=MAXN-10;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%s",opt);
		if(opt[0]=='P')
		{
			double b,k;
			scanf("%lf%lf",&b,&k);
			update(1,1,n,b-k,k);
		}
		else
		{
			int x;ans=0;
			scanf("%d",&x);
			query(1,1,n,x);
			printf("%lld\n",(LL)(ans/100.0));
		}
	}
	
	return 0;
}
