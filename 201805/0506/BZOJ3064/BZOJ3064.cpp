#include<bits/stdc++.h>
#define mkp(x,y) make_pair(x,y)
#define ls (x<<1)
#define rs (x<<1|1)
using namespace std;

typedef long long LL;
typedef long double ldb;
typedef pair<int,int> pii;
const LL INF=(LL)1e18;
const int N=1e5+10;
const int M=8e5+10;
int n,m,a[N]; 

LL read()
{
	LL ret=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c)){ret=(ret<<1ll)+(ret<<3ll)+(c^48);c=getchar();}
	return f?ret:-ret;
}

void write(LL x)
{
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar((x%10)^48);
}

struct Segment
{
	LL mx[M],add[M],cov[M];
	LL hmx[M],hadd[M],hcov[M];
	
	void pushup(int x)
	{
		mx[x]=max(mx[ls],mx[rs]);
		hmx[x]=max(hmx[ls],hmx[rs]);
	}
	
	void pushdown(int x)
	{
		hmx[ls]=max(hmx[ls],max(hcov[x],mx[ls]+hadd[x]));
		hmx[rs]=max(hmx[rs],max(hcov[x],mx[rs]+hadd[x]));
		if(cov[ls]==-INF) hadd[ls]=max(hadd[ls],add[ls]+hadd[x]);
			else hcov[ls]=max(hcov[ls],cov[ls]+hadd[x]);
		if(cov[rs]==-INF) hadd[rs]=max(hadd[rs],add[rs]+hadd[x]);
			else hcov[rs]=max(hcov[rs],cov[rs]+hadd[x]);	
			
		if(add[x])
		{
			if(cov[ls]!=-INF) cov[ls]+=add[x];
				else add[ls]+=add[x];
			if(cov[rs]!=-INF) cov[rs]+=add[x];
				else add[rs]+=add[x];
			mx[ls]+=add[x];mx[rs]+=add[x];
		}
		if(cov[x]!=-INF)
		{
			mx[ls]=cov[ls]=cov[x];mx[rs]=cov[rs]=cov[x];
			add[ls]=add[rs]=0;
		}
	
		hcov[ls]=max(hcov[ls],max(cov[ls],hcov[x]));hadd[ls]=max(hadd[ls],add[ls]);
		hcov[rs]=max(hcov[rs],max(cov[rs],hcov[x]));hadd[rs]=max(hadd[rs],add[rs]);
		add[x]=hadd[x]=0;cov[x]=hcov[x]=-INF;
	}
	
	void build(int x,int l,int r)
	{
		add[x]=hadd[x]=0;cov[x]=hcov[x]=-INF;
		if(l==r)
		{
			mx[x]=hmx[x]=a[l];
			return;
		}
		int mid=(l+r)>>1;
		build(ls,l,mid);build(rs,mid+1,r);
		pushup(x);
	}
	
	void update(int x,int l,int r,int L,int R,LL val,int op)
	{
		pushdown(x);
		if(L<=l && r<=R)
		{
			if(!op)
				mx[x]+=val,add[x]+=val,hadd[x]+=val;
			else
				cov[x]=hcov[x]=mx[x]=val;
			hmx[x]=max(hmx[x],mx[x]);
			return;
		}
		int mid=(l+r)>>1;
		if(L<=mid)
			update(ls,l,mid,L,R,val,op);
		if(R>mid)
			update(rs,mid+1,r,L,R,val,op);
		pushup(x);
	}
	
	LL query(int x,int l,int r,int L,int R,int op)
	{
		pushdown(x);
		if(L<=l && r<=R)
			return (op?hmx[x]:mx[x]);
		int mid=(l+r)>>1;LL ret=-INF;
		if(L<=mid)
			ret=max(ret,query(ls,l,mid,L,R,op));
		if(R>mid)
			ret=max(ret,query(rs,mid+1,r,L,R,op));
		return ret;
	}
}tr;

int main()
{
	freopen("BZOJ3064.in","r",stdin);
	freopen("BZOJ3064.out","w",stdout);

	n=read();
	for(int i=1;i<=n;++i)
		a[i]=read();
	tr.build(1,1,n);
	
	m=read();
	while(m--)
	{
		char s[3];int l,r,x;
		scanf("%s",s);l=read();r=read();
		if(s[0]=='Q')
			write(tr.query(1,1,n,l,r,0)),puts("");
		else
		if(s[0]=='A')
			write(tr.query(1,1,n,l,r,1)),puts("");
		else
		if(s[0]=='P')
			x=read(),tr.update(1,1,n,l,r,x,0);
		else
			x=read(),tr.update(1,1,n,l,r,x,1);
	}

	return 0;
}

