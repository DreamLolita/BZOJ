#include<bits/stdc++.h>
using namespace std;

const int INF=2e9;
const int N=205;
int n,p,ans=-INF;
int tp[2],sum[N];
int f[N][N];

struct Tque
{
	int l,r;
};
Tque a[N],q[2][N];

bool cmp1(Tque A,Tque B)
{
	return A.l<B.l;
}

bool cmp2(Tque A,Tque B)
{
	return A.r-A.l+1>B.r-B.l+1;
}

void solve(int now,int l,int r,int L,int R)
{
	int mid=(l+r)>>1,Mid=L,mx=ans;
	for(int i=min(mid-1,R);i>=L;--i)
	{
		if(q[0][i+1].r<=q[0][mid].l)
			break;
		int tmp=f[now-1][i]+q[0][i+1].r-q[0][mid].l;
		if(tmp>=mx)
			mx=tmp,Mid=i;
	}
	f[now][mid]=mx;
	if(l<mid)
		solve(now,l,mid-1,L,Mid);
	if(r>mid)
		solve(now,mid+1,r,Mid,R);
}

int main()
{
	freopen("BZOJ4426.in","r",stdin);
	freopen("BZOJ4426.out","w",stdout);
	
	scanf("%d%d",&n,&p);
	for(int i=1;i<=n;++i)
		scanf("%d%d",&a[i].l,&a[i].r);
	for(int i=1;i<=n;++i)
	{
		int flag=0;
		for(int j=1;j<=n;++j)
			if(a[i].l<=a[j].l && a[i].r>=a[j].r && (a[i].l!=a[j].l || a[i].r!=a[j].r || i<j) )
			{
				flag=1;
				break;
			}
		q[flag][++tp[flag]]=a[i];
	}
	
	sort(q[1]+1,q[1]+tp[1]+1,cmp2);
	for(int i=1;i<=tp[1];++i)
		sum[i]=sum[i-1]+q[1][i].r-q[1][i].l;
	sort(q[0]+1,q[0]+tp[0]+1,cmp1);
	for(int i=1;i<=tp[0];++i)
		f[0][i]=-INF;
	for(int i=1;i<=p;++i)
		f[i][0]=-INF;
	for(int i=1;i<=p;++i)
		solve(i,1,tp[0],0,tp[0]);
		
	for(int i=1;i<=p;++i)
		if(p-i<=tp[1] && f[i][tp[0]]>=0)
			ans=max(ans,f[i][tp[0]]+sum[p-i]);
	printf("%d\n",ans);
	return 0;
}
