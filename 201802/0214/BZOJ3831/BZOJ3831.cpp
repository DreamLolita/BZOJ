#include<bits/stdc++.h>
using namespace std;

const int N=1e6+10;
int n,m,k,h,t;
int a[N],q[N],f[N];

bool cmp(int x,int y)
{
	if(f[x]==f[y])
		return a[x]>a[y];
	return f[x]<f[y];
}

int main()
{
	freopen("BZOJ3831.in","r",stdin);
	freopen("BZOJ3831.out","w",stdout);
	
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%d",&a[i]);
	scanf("%d",&m);
	while(m--)
	{
		scanf("%d",&k);
		h=t=q[1]=1;
		for(int i=2;i<=n;++i)
		{
			while(h<=t && q[h]<i-k)
				++h;
			f[i]=f[q[h]]+(a[q[h]]<=a[i]);
			while(h<=t && cmp(i,q[t]))
				--t;
			q[++t]=i;
		}
		printf("%d\n",f[n]);
	}
	
	return 0;
}
