#include<bits/stdc++.h>
#define lowbit(x) (x&(-x))
using namespace std;

const int N=1e5+10;
int T,n,m;
int a[N],vis[N];
int tr[N][15];

struct Tquery
{
	int opt,l,r;
	int d,p,x,y,ans;
};
Tquery q[N];

void update(int x,int num,int v)
{
	for(;x<=n;x+=lowbit(x))
		tr[x][num]+=v;
}

int query(int x,int num)
{
	int ret=0;
	for(;x;x-=lowbit(x))
		ret+=tr[x][num];
	return ret;
}

int main()
{
	freopen("C.in","r",stdin);
	freopen("C.out","w",stdout);
	
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;++i)
			scanf("%d",&a[i]);
		for(int i=1;i<=m;++i)
		{
			char op[3];
			scanf("%s",op);
			if(op[0]=='S')
			{
				q[i].opt=0;
				scanf("%d%d",&q[i].x,&q[i].y);
			}
			else
			{
				q[i].opt=1;
				scanf("%d%d%d%d",&q[i].l,&q[i].r,&q[i].d,&q[i].p);
			}
		}
		int tmp=1;
		for(int i=1;i<=10;++i)
		{
			memset(tr,0,sizeof(tr));
			for(int j=1;j<=n;++j)
			{
				int t=a[j]/tmp%10;
				update(j,t,1);
				vis[j]=t;
			}
			for(int j=1;j<=m;++j)
			{
				if(q[j].opt && q[j].d==i)
					q[j].ans=query(q[j].r,q[j].p)-query(q[j].l-1,q[j].p);
				else
				if(!q[j].opt)
				{
					int t=q[j].y/tmp%10;
					update(q[j].x,vis[q[j].x],-1);	
					update(q[j].x,t,1);
					vis[q[j].x]=t;
				}
			}
			tmp*=10;
		}
		for(int i=1;i<=m;++i)
			if(q[i].opt)
				printf("%d\n",q[i].ans);
	}
}
