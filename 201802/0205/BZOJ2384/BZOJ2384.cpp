#include<bits/stdc++.h>
using namespace std;

const int N=1e6+10;
int n,m,tot;
int a[N],s[N],v[N],b[N],c[N];
int tr[N],nex[N],ans[N];

int lowbit(int x)
{
	return x&(-x);
}

void update(int x,int d)
{
	for(;x<=m;x+=lowbit(x))
		tr[x]+=d;
}

int query(int x)
{
	int ret=0;
	for(;x;x-=lowbit(x))
		ret+=tr[x];
	return ret;
}

int main()
{
//	freopen("BZOJ2384.in","r",stdin);
//	freopen("BZOJ2384.out","w",stdout);
	
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
		scanf("%d",&a[i]),s[a[i]]=i;
	for(int i=1;i<=n;++i)
		v[i]=query(s[i]),update(s[i],1);
	for(int i=1;i<=m;++i)
		scanf("%d",&b[i]),c[i]=b[i];
	memset(tr,0,sizeof(tr));
	
	for(int i=2,j=0;i<=n;++i)
	{
		while(query(s[i])!=v[j+1])
		{
			for(int k=i-j;k<i-nex[j];++k)
				update(s[k],-1);
			j=nex[j];
		}
		if(query(s[i])==v[j+1])
		{
			update(s[i],1);
			++j;
		}
		nex[i]=j;
	}
	sort(c+1,c+m+1);
	memset(tr,0,sizeof(tr));
	
	for(int i=1,j=0;i<=m;++i)
	{
		b[i]=lower_bound(c+1,c+m+1,b[i])-c;
		while(j==n || query(b[i])!=v[j+1])
		{
			for(int k=i-j;k<i-nex[j];++k)
				update(b[k],-1);
			j=nex[j];
		}
		if(query(b[i])==v[j+1])
		{
			++j;
			update(b[i],1);
		}
		if(j==n)
			ans[++tot]=i-j+1;
	}
	printf("%d\n",tot);
	for(int i=1;i<=tot;++i)
		printf("%d%c",ans[i],i==tot?'\n':' ');
	
	return 0;
}
