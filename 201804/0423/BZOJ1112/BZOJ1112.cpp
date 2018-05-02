#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=1e5+10;
int n,m,k;
int h[N];
LL ans=(LL)1e18;

int read()
{
	int ret=0;char c='.';
	while(!isdigit(c))c=getchar();
	while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c-'0');c=getchar();}
	return ret;
}

struct Treap
{
	int sz,root;
	int siz[N],ls[N],rs[N],w[N],rnd[N];
	LL ret,sum1,sum2,mi;
	LL v[N],sum[N];
	
	void pushup(int x)
	{
		siz[x]=siz[ls[x]]+siz[rs[x]]+w[x];
		sum[x]=sum[ls[x]]+sum[rs[x]]+v[x]*w[x];
	}
	
	void rturn(int &x)
	{
		int t=ls[x];ls[x]=rs[t];rs[t]=x;
		pushup(x);pushup(t);x=t;
	}
	
	void lturn(int &x)
	{
		int t=rs[x];rs[x]=ls[t];ls[t]=x;
		pushup(x);pushup(t);x=t;
	}
	
	void insert(int &x,int val)
	{
		if(!x)
		{
			x=++sz;sum[x]=v[x]=val;
			w[x]=siz[x]=1;rnd[x]=rand();
			return;
		}
		siz[x]++;sum[x]+=val;
		if(val==v[x]) 
			w[x]++;
		else
		if(val<v[x])
		{
			insert(ls[x],val);
			if(rnd[ls[x]]<rnd[x])
				rturn(x);
		}
		else
		{
			insert(rs[x],val);
			if(rnd[rs[x]]<rnd[x])
				lturn(x);
		}
	}
	
	void dele(int &x,int val)
	{
		if(!x)
			return;
		if(val==v[x])
		{
			if(w[x]>1){--w[x];--siz[x];sum[x]-=val;return;}
			if(!ls[x] || !rs[x])
				x=ls[x]+rs[x];
			else
			if(rnd[ls[x]]<rnd[rs[x]])
				rturn(x),dele(x,val);
			else
				lturn(x),dele(x,val);
		}	
		else
		if(val<v[x])
			--siz[x],sum[x]-=val,dele(ls[x],val);
		else
			--siz[x],sum[x]-=val,dele(rs[x],val);
	}	
	
	void find(int x,int rk)
	{
		if(!x)
			return;
		if(rk>siz[ls[x]] && rk<=siz[ls[x]]+w[x])
		{
			sum1+=(sum[ls[x]]+(rk-siz[ls[x]]-1)*v[x]);
			sum2+=(sum[rs[x]]+(siz[ls[x]]+w[x]-rk)*v[x]);
			mi=v[x];
		}
		else
		if(rk<=siz[ls[x]])
		{
			sum2+=(v[x]*w[x]+sum[rs[x]]);
			find(ls[x],rk);
		}
		else
		{
			sum1+=(v[x]*w[x]+sum[ls[x]]);
			find(rs[x],rk-siz[ls[x]]-w[x]);
		}
	}
	
	void getans()
	{
		sum1=sum2=0;
		find(root,m);
		ret=(m-1)*mi-sum1+sum2-(k-m)*mi;
		ans=min(ans,ret);
	}
}tr;

int main()
{
	freopen("BZOJ1112.in","r",stdin);
	freopen("BZOJ1112.out","w",stdout);
	
	n=read();k=read();m=((k+1)>>1);
	for(int i=1;i<=n;++i)
		h[i]=read();
	for(int i=1;i<=k;++i)
		tr.insert(tr.root,h[i]);
	tr.getans();
	for(int i=k+1;i<=n;++i)
	{
		tr.dele(tr.root,h[i-k]);tr.insert(tr.root,h[i]);
		tr.getans();
	}
	printf("%lld\n",ans);
	
	return 0;
}
