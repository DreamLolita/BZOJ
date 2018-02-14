#include<bits/stdc++.h>
using namespace std;

const int N=1e6+10;
int n,l1,l2,num,cnt,tmp;
int a[N],b[N],c[N],pa[N],pb[N];
int p[N],lp[N],rp[N],ls[N],rs[N];
int ans[N];

void ERASE(int x)
{
	if(ls[x]>=rs[x])
		--num;
	rs[x]--;
}

void ADD(int x)
{
	if(ls[x]<rs[x])
		++num;
	ls[x]++;
}

int main()
{
	freopen("BZOJ3828.in","r",stdin);
	freopen("BZOJ3828.out","w",stdout);

	scanf("%d%d",&n,&tmp);
	for(int i=1;i<=n;++i)
		scanf("%d",&c[i]);
	scanf("%d%d",&l1,&l2);
	for(int i=1;i<=l1;++i)
		scanf("%d",&a[i]),pa[a[i]]=i;
	for(int i=1;i<=l2;++i)
		scanf("%d",&b[i]),pb[b[i]]=i;
		
	for(int i=1;i<=n;++i)
	{
		if(pa[c[i]])
		{
			int x=pa[c[i]];
			if(x==1)
				p[1]=i;
			else
			if(p[x-1])
				p[x]=p[x-1];
		}
		lp[i]=p[l1];
	}
	memset(p,0,sizeof(p));
	for(int i=n;i;--i)
	{
		if(pb[c[i]])
		{
			int x=pb[c[i]];
			if(x==1)
				p[1]=i;
			else
			if(p[x-1])
				p[x]=p[x-1];
		}
		rp[i]=p[l2];
	}
	
	for(int i=rp[1]+1;i<=n;++i)
		rs[c[i]]++;
	for(int i=2;i<=n && rp[i];++i)
	{
		for(int j=rp[i-1]+1;j<=rp[i];++j)
			ERASE(c[j]);
		for(int j=lp[i-1];j<lp[i];++j)
			ADD(c[j]);
		if(num && a[l1]==c[i])
			ans[++cnt]=i;
	}
	printf("%d\n",cnt);
	for(int i=1;i<=cnt;++i)
		printf("%d ",ans[i]);
	
	return 0;
}
