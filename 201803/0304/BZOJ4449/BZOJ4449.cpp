#include<bits/stdc++.h>
using namespace std;

const int INF=1e9;
const int N=4e5+10;
const int M=2e7+10;
int n,m,nm,tot;
int ans[N],dis1[N],dis2[N],vis[N],head[N];
int b[M],tmp3[M],tmp4[M];
queue<int>q;
pair<int,int>nq[N];

struct Tele
{
	int l,r,t;
};
Tele a[N<<1],qs[N<<1],tmp1[N<<1],tmp2[N<<1];

struct Tway
{
	int v,nex;
};
Tway e[N<<1];

int check(int l,int r,int x)
{
	while(l<r)
	{
		int mid=(l+r)>>1;
		b[mid]>=x?r=mid:l=mid+1;
	}
	return r;
}

void spfa(int s,int l,int r,int *dis)
{
	for(int i=l;i<=r;++i)
		dis[b[i]]=INF,vis[b[i]]=0;
	vis[s]=1;dis[s]=0;
	q.push(s);
	while(!q.empty())
	{
		int u=q.front();vis[u]=0;q.pop();
		for(int i=head[u];i;i=e[i].nex)
		{
			int v=e[i].v;
			if(dis[u]+1<dis[v] && b[check(l,r,v)]==v)
			{
				dis[v]=dis[u]+1;
				if(!vis[v])
					q.push(v),vis[v]=1;
			}
		}
	}
}

void add(int u,int v)
{
	e[++tot]=(Tway){v,head[u]};head[u]=tot;
	e[++tot]=(Tway){u,head[v]};head[v]=tot;
}

int get_ans(int x,int y)
{
	int t1=min(dis1[x]+dis1[y],dis1[x]+dis2[y]+1);
	int t2=min(dis2[x]+dis2[y],dis2[x]+dis1[y]+1);
	return min(t1,t2);
}

void solve(int l,int r,int x,int y,int L,int R)
{
	if(L>R)
		return;
	int tmin=INF,pos;
	for(int i=l;i<=r;++i)
	{
		int t1=check(x,y,a[i].l),t2=check(x,y,a[i].r);
		if(t1<t2)
			swap(t1,t2);
		if(max(t1-t2+1,y-x+1-t1+t2)<tmin)
			tmin=max(t1-t2+1,y-x+1-t1+t2),pos=i;
	}
	if(a[pos].l>a[pos].r)
		swap(a[pos].l,a[pos].r);
	spfa(a[pos].l,x,y,dis1);spfa(a[pos].r,x,y,dis2);
	
	int t1=0,t2=0,t3=0,t4=0,t5=0,t6=0;
	for(int i=L;i<=R;++i)
	{
		if((qs[i].l==a[pos].l && qs[i].r==a[pos].r) || (qs[i].r==a[pos].l && qs[i].l==a[pos].r))
		{
			ans[qs[i].t]=1;
			continue;
		}
		ans[qs[i].t]=min(ans[qs[i].t],get_ans(qs[i].l,qs[i].r));
		if(qs[i].l>a[pos].l && qs[i].l<a[pos].r && qs[i].r>a[pos].l && qs[i].r<a[pos].r)
			tmp1[++t1]=qs[i];
		if((qs[i].r<a[pos].l || qs[i].r>a[pos].r) && (qs[i].l<a[pos].l || qs[i].l>a[pos].r))
			tmp2[++t2]=qs[i];
	}
	for(int i=1;i<=t1;++i)
		qs[L+i-1]=tmp1[i];
	for(int i=1;i<=t2;++i)
		qs[L+t1+i-1]=tmp2[i];
	for(int i=x;i<=y;++i)
	{
		if(b[i]>=a[pos].l && b[i]<=a[pos].r)
			tmp3[++t3]=b[i];
		if(b[i]<=a[pos].l || b[i]>=a[pos].r)
			tmp4[++t4]=b[i];
	}
	for(int i=1;i<=t3;++i)
		b[x+i-1]=tmp3[i];
	for(int i=1;i<=t4;++i)
		b[x+t3+i-1]=tmp4[i];
	for(int i=l;i<=r;++i)
	{
		if(i!=pos)
		{
			if(a[i].l>=a[pos].l && a[i].r<=a[pos].r)
				tmp1[++t5]=a[i];
			else
				tmp2[++t6]=a[i];
		}
	}
	for(int i=1;i<=t5;++i)
		a[l+i-1]=tmp1[i];
	for(int i=1;i<=t6;++i)
		a[l+t5+i-1]=tmp2[i];
	solve(l+t5,l+t5+t6-1,x+t3,x+t3+t4-1,L+t1,L+t1+t2-1);
	solve(l,l+t5-1,x,x+t3-1,L,L+t1-1);
}


int main()
{
	freopen("BZOJ4449.in","r",stdin);
	freopen("BZOJ4449.out","w",stdout);
	
	scanf("%d",&n);
	for(int i=1;i<=n-3;++i)
	{
		scanf("%d%d",&a[i].l,&a[i].r);
		add(a[i].l,a[i].r);
		if(a[i].l>a[i].r)
			swap(a[i].l,a[i].r);
	}

	scanf("%d",&m);
	for(int i=1;i<=m;++i)
	{
		scanf("%d%d",&qs[i].l,&qs[i].r);qs[i].t=i;
		nq[i].first=qs[i].l;nq[i].second=qs[i].r;
		if(nq[i].first>nq[i].second)
			swap(nq[i].first,nq[i].second);
		if(qs[i].r%n+1==qs[i].l)
			ans[i]=1;
		else
		if(qs[i].l==qs[i].r)
			ans[i]=0;
		else
			qs[++nm]=qs[i];
	};
	for(int i=1;i<=n;++i)
		add(i,i%n+1);
		
	for(int i=1;i<=m;++i)
		ans[i]=INF;
	for(int i=1;i<=n;++i)
		b[i]=i;
	solve(1,n-3,1,n,1,nm);
	
	for(int i=1;i<=m;++i)
	{
		if(ans[i]!=INF)
			printf("%d\n",ans[i]);
		else
			printf("%d\n",min(nq[i].second-nq[i].first,nq[i].first+n-nq[i].second));
	}
	
	return 0;
}
