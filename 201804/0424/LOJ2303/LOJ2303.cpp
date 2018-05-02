#include<bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
const int mod=998244353;
const int N=10233333;
const int M=2e7+10;
const int K=2e6+10;
const int bas=233;
int n,m,a[K],las[K],nex[K];
ull vx,vy,ans,base[55];
char s[M];

int read()
{
	int ret=0;char c='.';
	while(!isdigit(c)){c=getchar();}
	while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c^48);c=getchar();}
	return ret;
}

void write(ull x)
{
     if(x>9) write(x/10);
     putchar(x%10+'0');
}

struct hashmap
{
	int tot,head[N],len[M],cnt[M],nx[M];
	ull val[M];
	
	void insert(int l,ull vs)
	{
		register int x=vs%N,ls=0,i;
		for(i=head[x];i;ls=i,i=nx[i])
			if(len[i]==l && val[i]==vs)
				break;
		if(i)
			cnt[i]++;
		else
		{
			if(!ls) head[x]=++tot;
				else nx[ls]=++tot;
			len[tot]=l;val[tot]=vs;cnt[tot]++;
		}
	}

	void dele(int l,ull vs)
	{
		register int x=vs%N,i;
		for(i=head[x];i;i=nx[i])
			if(len[i]==l && val[i]==vs)
				--cnt[i];
	}
	
	int query(int l,ull vs)
	{
		register int x=vs%N,i;
		for(i=head[x];i;i=nx[i])
			if(len[i]==l && val[i]==vs)
				return cnt[i];
		return 0;
	}
}mp;

void init()
{
	register int i;
	base[0]=1;
	for(i=1;i<50;++i)
		base[i]=base[i-1]*bas;
		
	n=read();m=read();
	for(i=1;i<=n;++i)
		a[i]=read(),mp.insert(1,a[i]^48);
}

void solve()
{
	while(m--)
	{
		register int opt,x,y,i,p,j,q;
		opt=read();
		if(opt==1)
		{
			x=read();y=read();nex[x]=y;las[y]=x;vx=0;
			for(i=1,p=x;i<50 && p;++i,p=las[p])
			{
				vx+=(a[p]^48)*base[i-1];vy=0;
				for(j=1,q=y;i+j<=50 && q;++j,q=nex[q])
					vy=vy*bas+(a[q]^48),mp.insert(i+j,vx*base[j]+vy);
			}
		}
		else
		if(opt==2)
		{
			x=read();y=nex[x];nex[x]=las[y]=0;vx=0;
			for(i=1,p=x;i<50 && p;++i,p=las[p])
			{
				vx+=(a[p]^48)*base[i-1];vy=0;
				for(j=1,q=y;i+j<=50 && q;++j,q=nex[q])
					vy=vy*bas+(a[q]^48),mp.dele(i+j,vx*base[j]+vy);
			}
		}
		else
		{
			scanf("%s",s+1);x=read();vx=0;ans=1;
			for(i=1;i<x;++i)
				vx=vx*bas+s[i];
			for(i=x;s[i];++i)
				vx=vx*bas+s[i],ans=ans*mp.query(x,vx)%mod,vx-=s[i-x+1]*base[x-1];
			write(ans);puts("");
		}
	}
}

int main()
{
	freopen("LOJ2303.in","r",stdin);
	freopen("LOJ2303.out","w",stdout);
	
	init();
	solve();
	
	return 0;
}

