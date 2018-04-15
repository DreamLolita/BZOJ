#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int INF=1e9;
const int N=1e6+10;
int T,m,cnt,a[N];

void init()
{
	a[0]=a[1]=1;
	for(int i=2;i<N;++i)
	{
		LL tmp=3ll*i*(i-1)+1;
		if(tmp>INF)
			tmp=INF+1;
		a[i]=tmp;
		if(a[i]>INF)
		{
			cnt=i;
			break;
		}
	}
}

bool check(LL k)
{
	int l=0,r=cnt;
	while(l<=r)
	{
		if(a[l]+a[r]==k)
			return true;
		else
		if(a[l]+a[r]<k)
			++l;
		else
			--r;
	}
	return false;
}

int main()
{
	freopen("I.in","r",stdin);
	freopen("I.out","w",stdout);
	
	init();
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&m);
		int pos=lower_bound(a+1,a+cnt+1,m)-a;
		if(a[pos]==m)
		{
			puts("1");
			continue;
		}
		else
		if(check(m))
		{
			puts("2");
			continue;
		}
		else
		{
			for(int i=3;;++i)
			{
				if(!((m-i)%6))
				{
					printf("%d\n",i);
					break;
				}
			}
		}
	}
	
	return 0;
}
