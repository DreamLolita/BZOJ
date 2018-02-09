#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=2e5+10;
const int M=N*3;
int n,m,k,tot,T;
int h[N<<1],g[N<<1],q[N<<1],head[N<<1];
int tr[M<<1],vis[M<<1];
LL ans;

struct Tway
{
	int v,nex;
	Tway(){}
	Tway(int vv,int nexx){
		v=vv;nex=nexx;
	}
};
Tway e[M<<1];

struct Tnode
{
	int w,x,y;
	Tnode(){}
	Tnode(int ww,int xx,int yy){
		w=ww;x=xx;y=yy;
	}
};
Tnode qa[N],qb[N];

void add(int u,int v)
{
	e[++tot]=(Tway){v,head[u]};head[u]=tot;
}

bool cmp(Tnode A,Tnode B)
{
	return A.w<B.w;
}

void work(int x)
{
	int qs=0;
	for(int i=head[x];i;i=e[i].nex)
		q[++qs]=e[i].v;
	if(qs<=1)
		return;
	sort(q+1,q+qs+1);
	for(int i=1,j=1;i<=qs;++i)
	{
		while(j<qs && q[j+1]-q[i]<=k)
			++j;
		ans+=j-i;
	}
}

int lowbit(int x)
{
	return x&(-x);
}

void update(int x)
{
	x+=N;
	for(;x<M;x+=lowbit(x))
		if(vis[x]<T)
			vis[x]=T,tr[x]=1;
		else
			tr[x]++;
}

void query(int x)
{
	x=min(x+N,M-1);
	for(;x>0;x-=lowbit(x))
		if(vis[x]==T)
			ans+=tr[x];
}

void solve(int l,int r)
{
	if(l==r)
		return;
	int mid=(l+r)>>1,ca=0,cb=0;
	solve(l,mid);solve(mid+1,r);
	
	for(int i=mid,tp=N;i>=l;--i)
	{
		tp=min(tp,h[i]);
		for(int j=head[i];j;j=e[j].nex)
			qa[++ca]=(Tnode){min(tp,e[j].v),i,e[j].v};
	}
	for(int i=mid+1,tp=N;i<=r;++i)
	{
		tp=min(tp,h[i]);
		for(int j=head[i];j;j=e[j].nex)
			qb[++cb]=(Tnode){min(tp,e[j].v),i,e[j].v};
	}
	if(!ca || !cb)
		return;
	sort(qa+1,qa+ca+1,cmp);
	sort(qb+1,qb+cb+1,cmp);
	
	++T;
	for(int i=ca,j=cb;i;--i)
	{
		while(j && qa[i].w<=qb[j].w)
			update(qb[j].x+qb[j].y),--j;
		query(k+2*qa[i].w+qa[i].x-qa[i].y);
	}
	++T;
	for(int i=cb,j=ca;i;--i)
	{
		while(j	&& qb[i].w<qa[j].w)
			update(qa[j].y-qa[j].x),--j;
		query(k+2*qb[i].w-qb[i].x-qb[i].y);
	}
}

int main()
{
	freopen("BZOJ4979.in","r",stdin);
	freopen("BZOJ4979.out","w",stdout);
	
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;++i)
		scanf("%d",&h[i]);
	scanf("%d",&m);
	for(int i=1;i<=m;++i)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v);
	}
	for(int i=1;i<=n;++i)
		work(i);
	solve(1,n);
	printf("%lld\n",ans);
		
	return 0;
}
