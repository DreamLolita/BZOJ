#include<bits/stdc++.h>
#define id(x,y) ((x+y)%k)
using namespace std;

typedef long long LL;
const int N=55;
int n,p,k,r;

struct Tmatrix
{
	int a[N];
	
	Tmatrix init(){
		memset(a,0,sizeof(a));
	}
	
	Tmatrix operator * (const Tmatrix &now)const
	{
		Tmatrix ret;ret.init();
		for(int i=0;i<k;++i)
			for(int j=0;j<k;++j)
				ret.a[id(i,j)]=(ret.a[id(i,j)]+1ll*a[i]*now.a[j])%p;
		return ret;
	}
}ans,re;

int main()
{
	freopen("BZOJ4870.in","r",stdin);
	freopen("BZOJ4870.out","w",stdout);
	
	scanf("%d%d%d%d",&n,&p,&k,&r);
	ans.a[0]=re.a[0]=1;
	re.a[k==1?0:1]++;
	for(LL i=1ll*n*k;i;i>>=1,re=re*re)
		if(i&1)
			ans=ans*re;
	printf("%d\n",ans.a[r]);
	
	return 0;
}
