#include<bits/stdc++.h>
using namespace std;

const int N=1e5+10;
const int M=N*4;
int n,m;
double a[N];

int read()
{
	int ret=0,f=1;char c='.';
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c^48);c=getchar();}
	return ret*f;
}

struct Seqment
{
	double s[M],sd[M],tar[M];
	
	void pushdown(int rt,int l,int r)
	{
		if(tar[rt]==0)
			return;
		int mid=(l+r)>>1,ls=rt<<1,rs=ls|1;
		double t=tar[rt];	
		sd[ls]+=2*t*s[ls]+(mid-l+1)*t*t;sd[rs]+=2*t*s[rs]+(r-mid)*t*t;
		s[ls]+=t*(mid-l+1);s[rs]+=t*(r-mid);
		tar[ls]+=t;tar[rs]+=t;
		tar[rt]=0;
	}	
	
	void pushup(int rt)
	{
		s[rt]=s[rt<<1]+s[rt<<1|1];
		sd[rt]=sd[rt<<1]+sd[rt<<1|1];
	}
	
	void build(int rt,int l,int r)
	{
		if(l==r)
		{
			s[rt]=a[l];sd[rt]=a[l]*a[l];
			return;
		}
		int mid=(l+r)>>1;
		build(rt<<1,l,mid);
		build(rt<<1|1,mid+1,r);
		pushup(rt);
	}
	
	void update(int rt,int l,int r,int L,int R,double v)
	{
		if(L<=l && r<=R)
		{
			tar[rt]+=v;
			sd[rt]+=2*v*s[rt]+v*v*(r-l+1);s[rt]+=(r-l+1)*v;
			return;
		}
		pushdown(rt,l,r);
		int mid=(l+r)>>1;
		if(L<=mid)
			update(rt<<1,l,mid,L,R,v);
		if(R>mid)
			update(rt<<1|1,mid+1,r,L,R,v);
		pushup(rt);
	}
	
	double query(int rt,int l,int r,int L,int R)
	{
		if(L<=l && r<=R)
			return s[rt];
		pushdown(rt,l,r);
		int mid=(l+r)>>1;double ret=0;
		if(L<=mid)
			ret+=query(rt<<1,l,mid,L,R);
		if(R>mid)
			ret+=query(rt<<1|1,mid+1,r,L,R);
		return ret;
	}
	
	double queryd(int rt,int l,int r,int L,int R)
	{
		if(L<=l && r<=R)
			return sd[rt];
		pushdown(rt,l,r);
		int mid=(l+r)>>1;double ret=0;
		if(L<=mid)
			ret+=queryd(rt<<1,l,mid,L,R);
		if(R>mid)
			ret+=queryd(rt<<1|1,mid+1,r,L,R);
		return ret;
	}
}tr;


int main()
{
	freopen("LGP1471.in","r",stdin);
	freopen("LGP1471.out","w",stdout);
	
	n=read();m=read();
	for(int i=1;i<=n;++i)
		scanf("%lf",&a[i]);
	tr.build(1,1,n);
	for(int i=1;i<=m;++i)
	{
		int opt,x,y;double w;
		opt=read();x=read();y=read();
		if(opt==1)
			scanf("%lf",&w),tr.update(1,1,n,x,y,w);
		else
		if(opt==2)
		{
			double s1=tr.query(1,1,n,x,y)/(y-x+1);
			printf("%0.4lf\n",s1);
		}
		else
		{
			double s1=tr.queryd(1,1,n,x,y)/(y-x+1),s2=tr.query(1,1,n,x,y)/(y-x+1);
			printf("%0.4lf\n",s1-s2*s2);
		}
	}
	
	return 0;
}
