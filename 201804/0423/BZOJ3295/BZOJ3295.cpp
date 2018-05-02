#include<bits/stdc++.h>
#define lowbit(x) (x&(-x))
using namespace std;

typedef long long LL;
const int K=28;
const int N=1e5+10;
const int M=N*50;
int n,m,sz,la,lb;
int A[K],B[K];
int num[N],pos[N],a1[N],a2[N];
int bit[N],root[N];
LL ans;

int read()
{
	int ret=0,f=1;char c='.';
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c^48);c=getchar();}
	return ret*f;
}

struct Seqment
{
	int ls[M],rs[M],sum[M];
	
	void update(int &x,int l,int r,int p)
	{
		if(!x)
			x=++sz;
		sum[x]++;
		if(l==r)
			return;
		int mid=(l+r)>>1;
		if(p<=mid)
			update(ls[x],l,mid,p);
		else
			update(rs[x],mid+1,r,p);
	}
	
	int querypre(int x,int y,int num)
	{
		int tmp=0;
		la=lb=0;--x;
		for(int i=x;i;i-=lowbit(i))
			A[++la]=root[i];
		for(int i=y;i;i-=lowbit(i))
			B[++lb]=root[i];
		int l=1,r=n;
		while(l<r)
		{
			int mid=(l+r)>>1;
			if(num<=mid)
			{
				for(int i=1;i<=la;++i) tmp-=sum[rs[A[i]]];
				for(int i=1;i<=lb;++i) tmp+=sum[rs[B[i]]];
				for(int i=1;i<=la;++i) A[i]=ls[A[i]];
				for(int i=1;i<=lb;++i) B[i]=ls[B[i]];
				r=mid;
			}
			else
			{
				for(int i=1;i<=la;++i) A[i]=rs[A[i]];
				for(int i=1;i<=lb;++i) B[i]=rs[B[i]];
				l=mid+1;
			}
		}
		return tmp;
	}
	
	int querysuc(int x,int y,int num)
	{
		int tmp=0;
		la=lb=0;--x;
		for(int i=x;i;i-=lowbit(i))
			A[++la]=root[i];
		for(int i=y;i;i-=lowbit(i))
			B[++lb]=root[i];
		int l=1,r=n;
		while(l<r)
		{
			int mid=(l+r)>>1;
			if(num>mid)
			{
				for(int i=1;i<=la;++i) tmp-=sum[ls[A[i]]];
				for(int i=1;i<=lb;++i) tmp+=sum[ls[B[i]]];
				for(int i=1;i<=la;++i) A[i]=rs[A[i]];
				for(int i=1;i<=lb;++i) B[i]=rs[B[i]];
				l=mid+1;
			}
			else
			{
				for(int i=1;i<=la;++i) A[i]=ls[A[i]];
				for(int i=1;i<=lb;++i) B[i]=ls[B[i]];
				r=mid;
			}
		}
		return tmp;
	}
}tr;

int getans(int x)
{
	int ret=0;
	for(int i=x;i;i-=lowbit(i))
		ret+=bit[i];
	return ret;
}

int main()
{
	freopen("BZOJ3295.in","r",stdin);
	freopen("BZOJ3295.out","w",stdout);
	
	n=read();m=read();
	for(int i=1;i<=n;++i)
	{
		num[i]=read();pos[num[i]]=i;
		a1[i]=getans(n)-getans(num[i]);
		ans+=a1[i];
		for(int j=num[i];j<=n;j+=lowbit(j))
			bit[j]++;
	}
	memset(bit,0,sizeof(bit));
	for(int i=n;i;--i)
	{
		a2[i]=getans(num[i]-1);
		for(int j=num[i];j<=n;j+=lowbit(j))
			bit[j]++;
	}
	for(int i=1;i<=m;++i)
	{
		printf("%lld\n",ans);
		int x=read();x=pos[x];
		ans-=(a1[x]+a2[x]-tr.querypre(1,x-1,num[x])-tr.querysuc(x+1,n,num[x]));
		for(int j=x;j<=n;j+=lowbit(j))
			tr.update(root[j],1,n,num[x]);
	}
	
	return 0;
}
