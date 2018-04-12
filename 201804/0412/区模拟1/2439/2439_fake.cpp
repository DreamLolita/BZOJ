#include<bits/stdc++.h>
using namespace std;

const int N=2e5+10;
const int M=1e6+10;
int n,m,mxx,mxy,tot;
int sx[N],sy[N],sum[M],ans[N];

struct Tdata
{
	int x,y,id,opt;
	Tdata(){}
	Tdata(int xx,int yy,int idd,int opp){x=xx;y=yy;id=idd;opt=opp;}
}a[N],q[N],nodes[M];

bool cmpid(Tdata A,Tdata B)
{
	return A.id<B.id;
}

bool cmpx(Tdata A,Tdata B)
{
	if(A.x==B.x)
		return A.opt>B.opt;
	return A.x<B.x;
}

struct Seqment
{
	int mx[M];
	
	void pushup(int rt)
	{
		mx[rt]=max(mx[rt<<1],mx[rt<<1|1]);
	}
	
	void build(int rt,int l,int r)
	{
		if(l==r)
		{
			mx[rt]=0;
			return;
		}
		int mid=(l+r)>>1;
		build(rt<<1,l,mid);
		build(rt<<1|1,mid+1,r);
		pushup(rt);
	}
	
	void update(int rt,int l,int r,int p,int del)
	{
		if(l==r)
		{
			mx[rt]=del;
			return;
		}
		int mid=(l+r)>>1;
		if(p<=mid)
			update(rt<<1,l,mid,p,del);
		else
			update(rt<<1|1,mid+1,r,p,del);
		pushup(rt);
	}
	
	int query(int rt,int l,int r,int p,int goal)
	{
		if(l==r)
			return (mx[rt]>=goal?l:1);
		int mid=(l+r)>>1;
		if(p<=r)
		{
			if(p<=mid)
				return query(rt<<1,l,mid,p,goal);
			else
				return max(query(rt<<1,l,mid,p,goal),query(rt<<1|1,mid+1,r,p,goal));
		}
		else
		{
			if(mx[rt<<1|1]>=goal)
				return query(rt<<1|1,mid+1,r,p,goal);
			else
				return query(rt<<1,l,mid,p,goal);
		}
	}
};
Seqment treex,treey;

void init()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
	{
		scanf("%d%d",&a[i].x,&a[i].y);
		sx[i]=a[i].x;sy[i]=a[i].y;
	}
	scanf("%d",&m);
	for(int i=1;i<=m;++i)
	{
		scanf("%d%d",&q[i].x,&q[i].y);q[i].id=i;
		sx[i+n]=q[i].x;sy[i+n]=q[i].y;
	}
	sx[n+m+1]=sy[n+m+1]=0;
	
	mxx=mxy=n+m+1;
	sort(sx+1,sx+mxx+1);sort(sy+1,sy+mxy+1);
	mxx=unique(sx+1,sx+mxx+1)-sx-1;mxy=unique(sy+1,sy+mxy+1)-sy-1;
	
/*	for(int i=1;i<=mxx;++i)
		printf("%d ",sx[i]);
	printf("\n");
	for(int i=1;i<=mxy;++i)
		printf("%d ",sy[i]);
	printf("\n");*/
	
	for(int i=1;i<=n;++i)
	{
		a[i].x=lower_bound(sx+1,sx+mxx+1,a[i].x)-sx;
		a[i].y=lower_bound(sy+1,sy+mxy+1,a[i].y)-sy;
	}
	for(int i=1;i<=m;++i)
	{
		q[i].x=lower_bound(sx+1,sx+mxx+1,q[i].x)-sx;
		q[i].y=lower_bound(sy+1,sy+mxy+1,q[i].y)-sy;
	}
	sort(q+1,q+m+1,cmpid);
}

int lowbit(int x)
{
	return x&(-x);
}

void change(int x,int del)
{
	for(;x<M;x+=lowbit(x))
		sum[x]+=del;
}

int qsum(int x)
{
	int ret=0;
	for(;x;x-=lowbit(x))
		ret+=sum[x];
	return ret;
}

void solve()
{
/*	for(int i=1;i<=n;++i)
		printf("%d %d\n",a[i].x,a[i].y);
	for(int i=1;i<=m;++i)
		printf("%d %d\n",q[i].x,q[i].y);*/
	for(int i=1;i<=m;++i)
	{
		int x=q[i].x,y=q[i].y;
		int tx=treex.query(1,1,mxx,q[i].x-1,q[i].y);
		int ty=treey.query(1,1,mxy,q[i].y-1,q[i].x);
		treex.update(1,1,mxx,q[i].x,q[i].y);
		treey.update(1,1,mxy,q[i].y,q[i].x);
		
		nodes[++tot]=Tdata(tx,ty,i,1);nodes[++tot]=Tdata(x,y,i,1);
		nodes[++tot]=Tdata(tx,y,i,-1);nodes[++tot]=Tdata(y,tx,i,-1);
		printf("%d %d\n",tx,ty);
	}
	for(int i=1;i<=n;++i)
		nodes[++tot]=Tdata(a[i].x,a[i].y,0,2);
	sort(nodes+1,nodes+tot+1,cmpx);
	
	puts("");
	for(int i=1;i<=tot;++i)
		printf("%d %d %d %d\n",nodes[i].x,nodes[i].y,nodes[i].id,nodes[i].opt);
	
	for(int i=1;i<=tot;++i)
	{
		int tmp;
		if(nodes[i].opt==2)
			change(nodes[i].y,1);
		else
		{
			tmp=qsum(nodes[i].y);
			printf("query:%d %d=%d\n",nodes[i].x,nodes[i].y,tmp);
			ans[nodes[i].id]+=tmp*nodes[i].opt;
		}
	}
	for(int i=1;i<=m;++i)
		printf("%d\n",ans[i]);
}

int main()
{
	freopen("2439.in","r",stdin);
	freopen("2439.out","w",stdout);
	
	init();
	solve();
	
	return 0;
}
