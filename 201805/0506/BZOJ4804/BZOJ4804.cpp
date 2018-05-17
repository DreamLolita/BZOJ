#include<bits/stdc++.h>
#define mkp(x,y) make_pair(x,y)
using namespace std;

typedef long long LL;
typedef long double ldb;
typedef pair<int,int> pii;
const int N=1e7+10;
int n,prinum,pos;
int phi[N],pri[N];
LL ans,sum[N];
bool bo[N];

LL read()
{
	LL ret=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c)){ret=(ret<<1ll)+(ret<<3ll)+(c^48);c=getchar();}
	return f?ret:-ret;
}

void write(LL x)
{
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar((x%10)^48);
}

void init()
{
	sum[1]=phi[1]=1;
	for(int i=2;i<N;++i)
	{
		if(!bo[i])
			phi[i]=i-1,pri[++prinum]=i;
		for(int j=1;j<=prinum && pri[j]*i<N;++j)
		{
			bo[pri[j]*i]=1;
			if(i%pri[j])
				phi[pri[j]*i]=phi[i]*(pri[j]-1);
			else
			{
				phi[pri[j]*i]=phi[i]*pri[j];
				break;
			}
		}	
		sum[i]=sum[i-1]+phi[i];
	} 
}

void solve()
{
	int T=read();
	while(T--)
	{
		n=read();ans=0;
		for(int i=1;i<=n;i=pos+1)
		{
			pos=n/(n/i);
			ans+=(sum[pos]-sum[i-1])*sum[n/i];
		}
		ans=2ll*ans-sum[n]; 
		write(ans);puts("");
	}
}

int main()
{
	freopen("BZOJ4804.in","r",stdin);
	freopen("BZOJ4804.out","w",stdout);

	init();
	solve();

	return 0;
}

