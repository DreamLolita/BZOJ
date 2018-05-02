#include<bits/stdc++.h>
#define id(x,y) ((x-1)*n+y)
using namespace std;

const double eps=1e-9;
const int N=405;
int n,m,A,B,x,y;
int tot,head[N];
double p[N],du[N],go[N],a[N][N],b[N],ans[N];

struct Tway
{
	int v,nex;
};
Tway e[N<<1];

void add(int u,int v)
{
	e[++tot]=(Tway){v,head[u]};head[u]=tot;
	e[++tot]=(Tway){u,head[v]};head[v]=tot;
}

int cmp(double x)
{
	if(fabs(x)<=eps) 
		return 0;
	return x>0?1:-1;
}

void gauss()
{
	for(int i=1;i<=n*n;++i)
	{
		int now=i;
		for(int j=i+1;j<=n*n;++j)
			if(cmp(a[j][i]-a[now][i])>0)
				now=j;
		if(now!=i)
		{
			for(int j=1;j<=n*n;++j)
				swap(a[now][j],a[i][j]);
			swap(b[now],b[i]);
		}
		for(int j=i+1;j<=n*n;++j)
			if(cmp(a[j][i]))
			{
				double t=a[j][i]/a[i][i];
				for(int k=1;k<=n*n;++k)
					a[j][k]-=t*a[i][k];
				b[j]-=t*b[i];
			}
	}
	for(int i=n*n;i;--i)
	{
		for(int j=i+1;j<=n*n;++j)
			b[i]-=a[i][j]*ans[j];
		ans[i]=b[i]/a[i][i];
	}
}

int main()
{
	freopen("BZOJ3270.in","r",stdin);
	freopen("BZOJ3270.out","w",stdout);
	
	scanf("%d%d%d%d",&n,&m,&A,&B);
	for(int i=1;i<=m;++i)
	{
		scanf("%d%d",&x,&y);
		du[x]++;du[y]++;
		add(x,y);
	}
	for(int i=1;i<=n;++i)
	{
		scanf("%lf",&p[i]);
		go[i]=(1-p[i])/du[i];
	}
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=n;++j)
		{
			int now=id(i,j);
			a[now][now]=1;
			if(i^j)
				a[now][now]-=p[i]*p[j];
			for(int k=head[j];k;k=e[k].nex)
			{
				int v=e[k].v;
				if(v^i && v^j)
					a[now][id(i,v)]=-p[i]*go[v];
			}
			for(int k=head[i];k;k=e[k].nex)
			{
				int v=e[k].v;
				if(v^i && v^j)
					a[now][id(v,j)]=-p[j]*go[v];
			}
			for(int k=head[i];k;k=e[k].nex)
				for(int q=head[j];q;q=e[q].nex)
				{
					int v1=e[k].v,v2=e[q].v;
					if(v1^v2)
						a[now][id(v1,v2)]=-go[v1]*go[v2];
				}
		}
	}
/*	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=n;++j)
			printf("%lf ",a[i][j]);
		puts("");
	}*/
	
	b[id(A,B)]=1.0;
	gauss();
	for(int i=1;i<=n;++i)
		printf("%.6lf ",ans[id(i,i)]);
	
	return 0;
}
