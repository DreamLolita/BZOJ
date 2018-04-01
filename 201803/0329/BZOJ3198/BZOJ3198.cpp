#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=1e5+10;
const int P1=1000007;
const int P2=19260817;
const int B1=233;
const int B2=1007;
int n,k,tot,cnt,sum;
int las[P1],nex[N],t[N];
int hs[N][3],a[N][6],b[6];
LL ret,ans[7],C[10][10];

int query(int x)
{
	int t1=0,t2=0;
	for(int i=0;i<6;++i)
		if(b[i]==1)
			t1=(1ll*t1*B1+a[x][i])%P1,t2=(1ll*t2*B2+a[x][i])%P2;
	for(int i=las[t1];i;i=nex[i])
		if(hs[i][1]==t2)
		{
			hs[i][2]++;
			return i;
		}
	if(las[t1]==0)
		t[++tot]=t1;
	nex[++cnt]=las[t1];las[t1]=cnt;
	hs[cnt][0]=t1;hs[cnt][1]=t2;hs[cnt][2]=1;
	return cnt;
}

void init()
{
	C[0][0]=C[1][1]=C[1][0]=1;
	for(int i=2;i<=6;++i)
	{
		C[i][0]=1;
		for(int j=1;j<=i;++j)
			C[i][j]=C[i-1][j]+C[i-1][j-1];
	}
}

int main()
{
	freopen("BZOJ3198.in","r",stdin);
	freopen("BZOJ3198.out","w",stdout);
	
	init();
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;++i)
		for(int j=0;j<6;++j)
			scanf("%d",&a[i][j]);
			
	for(int sta=0;sta<(1<<6);++sta)
	{
		sum=0;
		for(int i=0;i<6;++i)
			b[i]=((sta>>i)&1),sum+=b[i];
		if(sum<k)
			continue;
		for(int i=1;i<=n;++i)
		{
			int p=query(i),q=hs[p][2];
			ans[sum]+=q-1;
		}
		for(int i=1;i<=tot;++i)
			las[t[i]]=0;
		tot=cnt=0;
	}
	for(int i=k;i<=6;++i)
		if((i-k)%2==0)
			ret+=ans[i]*C[i][k];
		else
			ret-=ans[i]*C[i][k];
	printf("%lld\n",ret);
	
	return 0;
}
