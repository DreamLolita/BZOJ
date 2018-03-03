#include<bits/stdc++.h>
using namespace std;

const int N=1e5+10;
int T,n,k,ans;
int l[N],r[N],tr[N];
int vec[N],pre[N],w[N];

struct Tpoint
{
	int x,y,col,id;
	Tpoint(){}
	Tpoint(int xx,int yy,int cc,int dd){
		x=xx;y=yy;col=cc;id=dd;
	}
};
Tpoint a[N];

bool cmpx(Tpoint A,Tpoint B){
	return A.x<B.x;
}

bool cmpy(Tpoint A,Tpoint B){
	return A.y<B.y;
}

int lowbit(int x){
	return x&(-x);
}

void add(int x,int v)
{
	for(;x<=n+1;x+=lowbit(x))
		tr[x]+=v;
}

int query(int x)
{
	int ret=0;
	for(;x;x-=lowbit(x))
		ret+=tr[x];
	return ret;
}

void pushup(int l,int r)
{
	if(l>r)
		return;
	int tmp=query(r)-query(l-1);
	ans=max(ans,tmp);
}

void _reset()
{
	memset(tr,0,sizeof(tr));
	memset(pre,0,sizeof(pre));
	w[0]=0;w[n+1]=n+1;
}

void solve()
{
	_reset();
	sort(a+1,a+n+1,cmpx);
	for(int i=1;i<=n;++i)
		add(a[i].x,1);
	for(int i=1;i<=n;++i)
	{
		int x=a[i].id,y=pre[a[i].col];
		l[x]=y;r[x]=n+1;
		if(y)
			r[y]=x;
		pushup(w[y]+1,w[x]-1);
		pre[a[i].col]=x;
	}
	for(int i=1;i<=k;++i)
		pushup(w[pre[i]]+1,n+1);
	sort(a+1,a+n+1,cmpy);
	for(int i=1,j=1;i<=n;++i)
	{
		int x=a[i].id;
		while(j<=n && a[j].y==a[i].y)
			add(a[j].x,-1),++j;
		l[r[x]]=l[x];r[l[x]]=r[x];
		pushup(w[l[x]]+1,w[r[x]]-1);
	}
}

int main()
{
	freopen("BZOJ4548.in","r",stdin);
	freopen("BZOJ4548.out","w",stdout);
	
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&k);ans=0;
		for(int i=1;i<=n;++i)
		{
			scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].col);
			a[i].id=i;
		}
		for(int i=1;i<=n;++i)
			vec[i]=a[i].x;
		sort(vec+1,vec+n+1);
		for(int i=1;i<=n;++i)
			w[i]=a[i].x=lower_bound(vec+1,vec+n+1,a[i].x)-vec;
		solve();
		for(int i=1;i<=n;++i)
			a[i].y=-a[i].y;
		solve();
		printf("%d\n",ans);
	}
	
	return 0;
}
