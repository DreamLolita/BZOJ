#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=1e6+10;
const int M=1<<30;
int n,m,t1,t2,t3,ans;

int read()
{
	int ret=0,f=1;char c='.';
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c^48);c=getchar();}
	return ret*f;
}

struct Seqment
{
	int num[N<<2];
	
	void pushup(int rt)
	{
		num[rt]=(num[rt<<1]==num[rt<<1|1]?num[rt<<1]:-1);
	}
	
	void pushdown(int rt)
	{
		if(~num[rt])
			num[rt<<1]=num[rt<<1|1]=num[rt];
	}
	
	int update(int rt,int l,int r,int p,int v)
	{
//printf("%d %d %d %d %d\n",rt,l,r,p,v);
		if(l==r)
		{
			num[rt]+=v;
			if(num[rt]<0){num[rt]+=M;return -1;}
			if(num[rt]>=M){num[rt]-=M;return 1;}
			return 0;
		}
		if(num[rt]==0 && l==p && v==-1)
		{
			num[rt]=M-1;
			return -1;
		}
		if(num[rt]==M-1 && l==p && v==1)
		{
			num[rt]=0;
			return 1;
		}
		pushdown(rt);
		int mid=(l+r)>>1,ret=0;
		if(p<=mid)
		{
			ret=update(rt<<1,l,mid,p,v);
			if(ret)
				ret=update(rt<<1|1,mid+1,r,mid+1,ret);
		}
		else
			ret=update(rt<<1|1,mid+1,r,p,v);
		pushup(rt);
		return ret;
	}
	
	int query(int rt,int l,int r,int p)
	{
		if(l==r)
			return num[rt];
		pushdown(rt);
		int mid=(l+r)>>1;
		if(p<=mid)
			return query(rt<<1,l,mid,p);
		else
			return query(rt<<1|1,mid+1,r,p);
	}
}tr;

int main()
{
	freopen("LOJ2302.in","r",stdin);
	freopen("LOJ2302.out","w",stdout);
	
	m=read();t1=read();t2=read();t3=read();n=m+30;
	while(m--)
	{
		int opt,x,y;
		opt=read();
		if(opt&1)
		{
			x=read();y=read();opt=(x>=0?1:-1);x=abs(x);
			LL s1=(x<<(y%30))&(M-1),a1=y/30;
			LL s2=x>>(30-y%30),a2=a1+1;
			if(s1)
				tr.update(1,0,n,a1,s1*opt);
			if(s2)
				tr.update(1,0,n,a2,s2*opt);
//			printf("%lld %lld %lld %lld %d\n",s1,a1,s2,a2,opt);
		}
		else
		{
			x=read();
			ans=tr.query(1,0,n,x/30);
//printf("ans:%d\n",ans);
			puts(((ans>>(x%30))&1)?"1":"0");
		}
	}
	
	return 0;
}
