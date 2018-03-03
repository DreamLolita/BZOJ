#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
double ans,a[5];
int n,num[5];
LL C[25][25];

struct Tdata
{
	double p;
	LL cnt;
	Tdata(){}
	Tdata(double pp,LL cc){
		p=pp;cnt=cc;
	}
	
	bool operator < (const Tdata &A)const{
		return p>A.p;
	}
};
priority_queue<Tdata>q;

void dfs(int x,int res)
{
	if(x==4)
	{
		num[x]=res;
		LL tmp=1ll*C[n][num[1]]*C[n-num[1]][num[2]]*C[n-num[1]-num[2]][num[3]];
		double t=1.0;
		for(int i=1;i<=4;++i)
			for(int j=1;j<=num[i];++j)
				t*=a[i];
		q.push(Tdata(t,tmp));
		return;
	}
	for(int i=0;i<=res;++i)
	{
		num[x]=i;
		dfs(x+1,res-i);
	}
}

void init()
{
	scanf("%d",&n);
	for(int i=1;i<=4;++i)
		scanf("%lf",&a[i]);
	C[0][0]=1ll;
	for(int i=1;i<=n;++i)
	{
		C[i][0]=C[i][i]=1ll;
		for(int j=1;j<i;++j)
			C[i][j]=C[i-1][j-1]+C[i-1][j];
	}
	dfs(1,n);
}

void solve()
{
	while(true)
	{
		Tdata now=q.top();q.pop();
		while(!q.empty() && q.top().p==now.p)
		{
			now.cnt+=q.top().cnt;
			q.pop();
		}
		if(now.cnt%2==0)
		{
			ans+=1.0*now.p*now.cnt;
			q.push(Tdata(now.p*2.0,now.cnt/2));
		}
		else
		if(now.cnt!=1)
		{
			ans+=1.0*now.p*(now.cnt-1ll);
			q.push(Tdata(now.p*2.0,now.cnt/2));
			q.push(Tdata(now.p,1ll));
		}
		else
		{
			if(q.empty())
				break;
			Tdata nex=q.top();q.pop();
			ans+=now.p+nex.p;
			q.push(Tdata(now.p+nex.p,1ll));
			if(nex.cnt!=1)
				q.push(Tdata(nex.p,nex.cnt-1ll));
		}
	}
	printf("%lf\n",ans);
}

int main()
{
	freopen("BZOJ4117.in","r",stdin);
	freopen("BZOJ4117.out","w",stdout);
	
	init();
	solve();
	
	return 0;
}
