#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const LL INF=(LL)1e60;
const int N=2e5+10;
int n,pos;
LL q,nps,K;
LL a[N],sum[N];

LL read()
{
	LL ret=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c^48);c=getchar();}
	return f?ret:-ret;
}

int main()
{
	freopen("C.in","r",stdin);
	freopen("C.out","w",stdout);

	n=read();q=read();
	for(int i=1;i<=n;++i)
		a[i]=read(),sum[i]=sum[i-1]+a[i];
	pos=1;sum[n+1]=INF;nps=0;
	while(q--)
	{
		K=read();
		int l=pos,r=n+1,ret=pos;
		while(l<=r)
		{
			int mid=(l+r)>>1;
			if(sum[mid]-sum[pos-1]-nps>K)
				ret=mid,r=mid-1;
			else
				l=mid+1;
		}
//		printf("ret:%d nps:%lld pos:%d\n",ret,nps,pos);
		if(ret==n+1)
		{
			pos=1;nps=0;
			printf("%d\n",n);
		}
		else
		{
			nps=sum[ret]-sum[pos-1]-nps-K;nps=a[ret]-nps;pos=ret;
			printf("%d\n",n-ret+1);
		}
	}

	return 0;
}

