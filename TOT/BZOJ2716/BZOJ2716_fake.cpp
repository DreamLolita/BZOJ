#include<bits/stdc++.h>
using namespace std;

const int N=1e6+5;
const int lim=N-4;;
const int INF=1e9+7;

int n,m,now;
int tr[N],ans[N],tim[N];

struct Tnode
{
	int k,x,y,t,p;
	
	friend bool operator<(const Tnode &A,const Tnode &B)
	{
		if(A.x==B.x)
			return A.k<B.k;
		return A.x<B.x;
	}
};
Tnode p[N],q[N],s[N];

int lowbit(int x)
{
	return x&(-x);
}

void add(int x,int v)
{
	for(;x<N;x+=lowbit(x))
		if(tr[x]<v || tim[x]!=now)
			tr[x]=v,tim[x]=now;
}

int query(int x)
{
	int ret=-INF;
	for(;x;x-=lowbit(x))
		if(ret<tr[x] && tim[x]==now)
			ret=tr[x];
	return ret;
}

void solve(int l,int r)
{
	if(l>=r)
		return;
	int mid=(l+r)>>1;
	solve(l,mid);solve(mid+1,r);
	
	int t1=l,t2=mid+1,tot=l;
	while(t1<=mid && t2<=r)
		if(s[t1]<s[t2])
			q[tot++]=s[t1++];
		else
			q[tot++]=s[t2++];
	while(t1<=mid)
		q[tot++]=s[t1++];
	while(t2<=r)
		q[tot++]=s[t2++];
	for(int i=l;i<=r;++i)
		s[i]=q[i];
	
	++now;
	for(int i=l;i<=r;++i)
	{
		if(s[i].k && s[i].t>mid)
		{
			int tmp=s[i].x+s[i].y-query(s[i].y);
			ans[s[i].p]=min(ans[s[i].p],tmp);
		}	
		else
		if(!s[i].k && s[i].t<=mid)
			add(s[i].y,s[i].x+s[i].y);
	}
}

void CDQ1()
{
	memcpy(s,p,sizeof(s));
	solve(1,n+m);
}

void CDQ2()
{
	memcpy(s,p,sizeof(s));
	for(int i=1;i<=n+m;++i)
		s[i].x=lim-s[i].x;
	solve(1,n+m);
}

void CDQ3()
{
	memcpy(s,p,sizeof(s));
	for(int i=1;i<=n+m;++i)
		s[i].y=lim-s[i].y;
	solve(1,n+m);
}

void CDQ4()
{
	memcpy(s,p,sizeof(s));
	for(int i=1;i<=n+m;++i)
		s[i].x=lim-s[i].x,s[i].y=lim-s[i].y;
	solve(1,n+m);
}

int main()
{
	freopen("BZOJ2716.in","r",stdin);
	freopen("BZOJ2716.out","w",stdout);
	
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
	{
		scanf("%d%d",&p[i].x,&p[i].y);
		p[i].k=0;p[i].t=i;
	}
	for(int i=1;i<=m;++i)
	{
		scanf("%d%d%d",&p[i+n].k,&p[i+n].x,&p[i+n].y);
		--p[i+n].k;p[i+n].t=i+n;p[i+n].p=i;
		ans[i]=INF;
	}
	
	CDQ1();CDQ2();
	CDQ3();CDQ4();
	
	for(int i=1;i<=m;++i)
		if(p[i+n].k)
			printf("%d\n",ans[i]);
	
	return 0;
}
