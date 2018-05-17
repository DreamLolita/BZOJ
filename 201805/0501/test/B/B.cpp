#include<bits/stdc++.h>
#define id(x) x>14? (x-14):x
using namespace std;

typedef long long LL;
LL ans;
LL a[20];


LL read()
{
	LL ret=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c)){ret=(ret<<1ll)+(ret<<3ll)+(c^48);c=getchar();}
	return f?ret:-ret;
}

int main()
{
	freopen("B.in","r",stdin);
	freopen("B.out","w",stdout);

	for(int i=1;i<=14;++i)
		a[i]=read();
	for(int i=1;i<=14;++i)
	{
		LL t=a[i]/14,m=a[i]%14,tmp=0,tt=a[i];
//printf("%lld %lld %lld\n",a[i],t,m);
		a[i]=0;
		for(int j=1;j<=m;++j)
			a[id(i+j)]++;

		for(int j=1;j<=14;++j)
			if((a[j]+t)%2==0)
				tmp+=(LL)(a[j]+t);

		for(int j=1;j<=m;++j)
			a[id(i+j)]--;
		if(tmp>ans)
			ans=tmp;
		a[i]=tt;
	}
	printf("%I64d\n",ans);

	return 0;
}

