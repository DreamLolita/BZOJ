#include<bits/stdc++.h>
using namespace std;

const int N=20;
const int S=16666666;
int n,m,ans;
int a[N],b[N],c[N],id[N];
int pre[N],fac[N],f[S];

void init()
{
	scanf("%d%d",&n,&m);
	
	fac[0]=1;
	for(int i=1;i<=n;++i)
	{
		fac[i]=fac[i-1]*3;
		pre[i-1]=n;
	}
	for(int i=1;i<=m;++i)
	{
		scanf("%d",&a[i]);
		id[--a[i]]=i;
		if(i>1)
			pre[a[i]]=a[i-1];
	}
	a[m+1]=n;
}

void solve()
{
	f[0]=b[n]=1;
	for(int i=0;i<fac[n];++i)
	{
		if(!f[i])
			continue;
		int cnt=0,pos=0,k=1;c[0]=0;
		for(int j=0,t=i;j<n;++j,t/=3)
		{
			b[j]=t%3;
			if(b[j])
			{
				++cnt;
				if(id[j]>pos)
					pos=id[j];
				if(b[j]==1)
					c[++c[0]]=j;
			}
		}	
		c[c[0]+1]=n;
		if(cnt==n)
			ans+=f[i];
		for(int j=0;j<n;++j)
			if(!b[j] && b[pre[j]])
			{
				bool flag=1;
				while(j>c[k])
					++k;
				for(int l=pos+1;flag && l<=m+1 && l<=k;++l)
					if(a[l]>j)
						flag=false;
				if(flag)
					f[i+fac[j]+ (k>c[0]?0:fac[c[k]]) ]+=f[i];
			}
	}
	printf("%d\n",ans);
}

int main()
{
	freopen("sword.in","r",stdin);
	freopen("sword.out","w",stdout);
	
	init();
	solve();
	
	return 0;
}
