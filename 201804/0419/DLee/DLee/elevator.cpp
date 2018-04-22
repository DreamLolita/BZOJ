#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const LL INF=(LL)1e18;
const LL inf=1e9;
const LL N=55555;
LL n,cnt,tot;
LL maxl[N],cp[N];
LL f[N];

LL read()
{
	LL ret=0,f=1;char ch='.';
	while(ch<'0' || ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0' && ch<='9'){ret=(ret<<3ll)+(ret<<1ll)+(ch-'0');ch=getchar();}
	return ret*f;
}

struct Tele
{
	LL a,b;
	Tele(){}
	Tele(LL aa,LL bb){a=aa;b=bb;}
};
Tele peo[N];

inline bool cmp(Tele A,Tele B)
{
	if(A.a^B.a)
		return A.a<B.a;
	return A.b<B.b;
}

struct Tnode
{
	LL x,y;
	LL pos,flag;
	Tnode(){}
	Tnode(LL xx,LL yy,LL ff){x=xx;y=yy;pos=0;flag=ff;}
};
Tnode now[N];

inline bool cmp1(Tnode A,Tnode B)
{
	if(A.x^B.x)
		return A.x<B.x;
	return A.flag<B.flag;
}

inline bool cmp2(Tnode A,Tnode B)
{
	if(A.x^B.x)
		return A.x>B.x;
	return A.flag<B.flag;
}

struct Seqment
{
	Tele sum[N<<2];
	
	inline Tele comp(Tele A,Tele B,LL flag)
	{
		bool ret=0;
		if(flag==1 && A.b<B.b)
			ret=1;
		else
		if(flag==2 && A.a<B.a)
			ret=1;
		else
		if(A.a+2*A.b<B.a+2*B.b)
			ret=1;
		if(ret)
			return A;
		else
			return B;
	}
	
	inline void build(LL rt,LL l,LL r)
	{
		sum[rt]=Tele(INF,inf);
		if(l==r)
			return;
		LL mid=(l+r)>>1;
		build(rt<<1,l,mid);
		build(rt<<1|1,mid+1,r);
	}
	
	inline void update(LL rt,LL l,LL r,LL L,LL R,LL nx,LL ny,LL flag)
	{
		if(L<=l && r<=R)
		{
			sum[rt]=Tele(nx,ny);
			return;
		}
		LL mid=(l+r)>>1;
		if(L<=mid)
			update(rt<<1,l,mid,L,R,nx,ny,flag);
		if(R>mid)
			update(rt<<1|1,mid+1,r,L,R,nx,ny,flag);
		sum[rt]=comp(sum[rt<<1],sum[rt<<1|1],flag);
	}
	
	inline Tele query(LL rt,LL l,LL r,LL L,LL R,LL flag)
	{
		if(L<=l && r<=R)
			return sum[rt];
		LL mid=(l+r)>>1;
		Tele ret=Tele(INF,inf);
		if(L<=mid)
			ret=comp(ret,query(rt<<1,l,mid,L,R,flag),flag);
		if(R>mid)
			ret=comp(ret,query(rt<<1|1,mid+1,r,L,R,flag),flag);
		return ret;
	}
}tr;

inline void reinit(LL l,LL r)
{
	LL mid=(l+r)>>1;
	tot=1;cp[0]=0;
	for(LL i=l-1;i<=r;++i)
		cp[tot++]=peo[i].b;
	sort(cp,cp+tot);
	tot=unique(cp,cp+tot)-cp;
	
	maxl[mid]=peo[mid].b;
	for(LL i=mid-1;i>=l;--i)
		maxl[i]=max((LL)peo[i].b,maxl[i+1]);
	maxl[mid+1]=peo[mid+1].b;
	for(LL i=mid+2;i<=r;++i)
		maxl[i]=max((LL)peo[i].b,maxl[i-1]);
		
	cnt=0;
	for(LL i=l-1;i<mid;++i)	
		now[++cnt]=Tnode(f[i],maxl[i+1],0);
	now[++cnt]=Tnode(f[mid],0,0);
	for(LL i=mid+1;i<=r;++i)
		now[++cnt]=Tnode(peo[i].a,maxl[i],i);
	for(LL i=1;i<=cnt;++i)
		now[i].pos=lower_bound(cp,cp+tot,now[i].y)-cp+1;
}

inline void solve(LL l,LL r)
{
	LL mid=(l+r)>>1;
	if(l==r)
	{
		LL tmp=max(peo[mid].a,f[mid-1])+2ll*peo[mid].b;
		f[mid]=min(f[mid],tmp);
		return;
	}
	solve(l,mid);

	reinit(l,r);
//	printf("l:%d r:%d\n",l,r);
//	for(LL i=1;i<=cnt;++i)
//		printf("%lld %lld %d %d\n",now[i].x,now[i].y,now[i].pos,now[i].flag);
	
	Tele tmp;
	
	sort(now+1,now+cnt+1,cmp1);
	tr.build(1,1,tot);
	for(LL i=1;i<=cnt;++i)
	{
		if(now[i].flag==0)
			tr.update(1,1,tot,now[i].pos,now[i].pos,now[i].x,now[i].y,1);
		else
		{
			tmp=tr.query(1,1,tot,1,now[i].pos,1);//own
			if(tmp.b<inf)
				f[now[i].flag]=min(f[now[i].flag],now[i].x+2ll*now[i].y);	
//			printf("query:%lld %lld\n",tmp.a,tmp.b);
			tmp=tr.query(1,1,tot,now[i].pos,tot,1);//with back go up&down
			if(tmp.b<inf)
				f[now[i].flag]=min(f[now[i].flag],now[i].x+2ll*tmp.b);
//			printf("query:%lld %lld\n",tmp.a,tmp.b);
		}
	}
//	printf("ffffffffff:\n");
//	for(LL i=1;i<=n;++i)
//		printf("%d ",f[i]);
//	printf("\n");
	
	sort(now+1,now+cnt+1,cmp2);
	tr.build(1,1,tot);
	for(LL i=1;i<=cnt;++i)
	{
		if(now[i].flag==0)
			tr.update(1,1,tot,now[i].pos,now[i].pos,now[i].x,now[i].y,2);
		else
		{
			tmp=tr.query(1,1,tot,1,now[i].pos,2);
			if(tmp.b<inf)
				f[now[i].flag]=min(f[now[i].flag],tmp.a+2ll*now[i].y);
		}
	}
//	printf("ffffffffff:\n");
//	for(LL i=1;i<=n;++i)
//		printf("%d ",f[i]);
//	printf("\n");
	
	tr.build(1,1,tot);
	for(LL i=1;i<=cnt;++i)
	{
		if(now[i].flag==0)
			tr.update(1,1,tot,now[i].pos,now[i].pos,now[i].x,now[i].y,3);
		else
		{
			tmp=tr.query(1,1,tot,now[i].pos,tot,3);
			if(tmp.b<inf)
				f[now[i].flag]=min(f[now[i].flag],tmp.a+2ll*tmp.b);
		}
	}
//	printf("ffffffffff:\n");
//	for(LL i=1;i<=n;++i)
//		printf("%lld ",f[i]);
//	printf("\n");
	
	solve(mid+1,r);
}


int main()
{
	freopen("elevator.in","r",stdin);
	freopen("elevator.out","w",stdout);
	
	n=read();
	for(LL i=1;i<=n;++i)
		peo[i].a=read(),peo[i].b=read(),f[i]=INF;
	sort(peo+1,peo+n+1,cmp);
	solve(1,n);
	printf("%lld\n",f[n]);
	
	return 0;
}
