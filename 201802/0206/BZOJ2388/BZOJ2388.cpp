#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=1e5+10;
const int M=450;
const int block=233;
const LL INF=(LL)(1ll<<50);

int n,m,cnt,top;
int belong[N];
int beg[M],en[M],num[M];
int sta[M],con[M][M];
LL ans,h[N],fir[M],dif[M],add[M];

double cross(int x,int y)
{
	return (double)(h[y]-h[x])/(y-x);
}

void build(int x)
{
	top=0;sta[++top]=beg[x];
	for(int i=beg[x]+1;i<=en[x];++i)
	{
		while(top>=2 && cross(sta[top-1],sta[top])<cross(sta[top-1],i))
			top--;
		sta[++top]=i;
	}
	sta[0]=0;sta[top+1]=n+1;
	num[x]=top;
	for(int i=0;i<=top+1;++i)
		con[x][i]=sta[i];
}

void init()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
	{
		int x;
		scanf("%d",&x);
		h[i]=h[i-1]+x;
	}
	h[0]=h[n+1]=-INF;
	if(n%block)
		cnt=n/block+1;
	else
		cnt=n/block;
	for(int i=1;i<=n;++i)
		belong[i]=(i-1)/block+1;
	for(int i=1;i<=cnt;++i)
	{
		beg[i]=(i-1)*block+1;
		en[i]=min(n,i*block);
	}
	for(int i=1;i<=cnt;++i)
		build(i);
}

LL calc(int x)
{
	if(x==0 || x==n+1)
		return -INF;
	int t=belong[x];
	return (LL)h[x]+fir[t]+1ll*dif[t]*(x-beg[t])+add[t];
}

void pushdown(int x)
{
	LL tmp=fir[x];
	for(int i=beg[x];i<=en[x];++i)
		h[i]+=tmp+add[x],tmp+=dif[x];
	fir[x]=dif[x]=add[x]=0;
}

LL query(int x)
{
	int l=1,r=num[x];
	LL h1,h2,h3;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		h1=calc(con[x][mid-1]);h2=calc(con[x][mid]);h3=calc(con[x][mid+1]);
		if(h1<h2 && h2<h3)
			l=mid+1;
		else
		if(h1>h2 && h2>h3)
			r=mid-1;
		else
			return h2;
	}
}

void solve()
{
	scanf("%d",&m);
	while(m--)
	{
		int f,x,y;
		scanf("%d%d%d",&f,&x,&y);
		
		if(f&1)
		{
			int l=belong[x],r=belong[y];
			ans=-INF;
			for(int i=l+1;i<r;++i)
				ans=max(ans,query(i));
			for(int i=x;i<=min(y,en[l]);++i)
				ans=max(ans,calc(i));
			if(l!=r)
			{
				for(int i=beg[r];i<=y;++i)
					ans=max(ans,calc(i));
			}
			printf("%lld\n",ans);
		}
		else
		{
			int k;scanf("%d",&k);
			int l=belong[x],r=belong[y];
			LL tmp=(LL)1ll*k*(beg[l+1]-x+1);
			for(int i=l+1;i<r;++i)
			{
				fir[i]+=tmp;dif[i]+=k;
				tmp+=1ll*block*k;
			}
			pushdown(l);
			tmp=k;
			for(int i=x;i<=min(y,en[l]);++i)
				h[i]+=tmp,tmp+=k;
			build(l);
			pushdown(r);
			if(l!=r)
			{
				tmp=1ll*k*(beg[r]-x+1);
				for(int i=beg[r];i<=y;++i)
					h[i]+=tmp,tmp+=k;
			}
			tmp=1ll*k*(y-x+1);
			for(int i=y+1;i<=en[r];++i)
				h[i]+=tmp;
			build(r);
			for(int i=r+1;i<=cnt;++i)
				add[i]+=tmp;
		}	
	}
}

int main()
{
	freopen("BZOJ2388.in","r",stdin);
	freopen("BZOJ2388.out","w",stdout);
	
	init();
	solve();
	
	return 0;	
}
