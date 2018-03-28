#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=4e5+10;
const int mod=1e9+7;
int m,tot,len,ans;
int a[15];
LL n;
LL siz[N],num[N],f[15][N][2];

struct Tnode
{
	int x,y;LL v;
	Tnode(){}
	Tnode(int xx,int yy){
		x=xx;y=yy;v=siz[xx]*siz[yy];
	}
	bool operator < (const Tnode &A)const{
		return v<A.v;
	} 
};
priority_queue<Tnode>Q;

bool cmp(LL A,LL B)
{
	return A>B;
}

void dfs(int now,int dep,LL mul)
{
	if(dep==len)
		num[++tot]=mul;
	else
	{
		if(!mul)
			return;
		for(int i=now;i<10;++i)
			dfs(i,dep+1,mul*i);
	}
}

void init()
{
	scanf("%lld%d",&n,&m);LL tmp=n;
	while(tmp)
	{
		a[++len]=tmp%10;
		tmp/=10;
	}
	num[++tot]=0;
	dfs(0,0,1);
	sort(num+1,num+tot+1);
	tot=unique(num+1,num+tot+1)-num-1;
}

void dp()
{
	f[0][2][0]=1;
	for(int i=0;i<=len;++i)
		for(int j=1;j<=tot;++j)
			for(int k=0;k<=1;++k)
				if(f[i][j][k])
				{
					for(int q=i==0?0:1;q<10;++q)
					{
						int p=lower_bound(num+1,num+tot+1,num[j]*q)-num;
						f[i+1][p][(k+q)>a[i+1]]+=f[i][j][k];
					}
				}
}

void solve()
{
	for(int i=1;i<=tot;++i)
	{
		for(int j=1;j<len;++j)
			siz[i]+=f[j][i][0]+f[j][i][1];
		siz[i]+=f[len][i][0];
	}
	sort(siz+1,siz+tot+1,cmp);
	Q.push(Tnode(2,2));
	while(!Q.empty() && m)
	{
		Tnode u=Q.top();Q.pop();
		ans=(ans+u.v)%mod;
		if(!(--m))
			break;
		if(u.x!=u.y)
		{
			ans=(ans+u.v)%mod;
			if(!(--m))
				break;
			Q.push(Tnode(u.x+1,u.y));
		}
		if(u.x==2)
			Q.push(Tnode(u.x,u.y+1));
	}
	printf("%d\n",ans);
}

int main()
{
	freopen("BZOJ3131.in","r",stdin);
	freopen("BZOJ3131.out","w",stdout);
	
	init();
	dp();
	solve();
	
	return 0;
}
