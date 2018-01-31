#include<bits/stdc++.h>
#define uint unsigned int
using namespace std;

const uint MAXN=2e5+10;
const uint MAX=MAXN<<6;
uint n,m,cnt;
uint root[MAXN];
uint ls[MAX],rs[MAX],tar[MAX],tr[MAX];

void updatey(uint &ky,uint l,uint r,uint L,uint R)
{
	if(!ky)
		ky=++cnt;
	if(L<=l && r<=R)
	{
		++tar[ky];
		tr[ky]+=r-l+1;
		return;
	}
	uint mid=(l+r)>>1;
	if(L<=mid)
		updatey(ls[ky],l,mid,L,R);
	if(R>mid)
		updatey(rs[ky],mid+1,r,L,R);
	tr[ky]=tr[ls[ky]]+tr[rs[ky]]+tar[ky]*(r-l+1);
}

void updatex(uint kx,uint l,uint r,uint L,uint R,uint k)
{
	updatey(root[kx],1,n,L,R);
	if(l==r)
		return;
	uint mid=(l+r)>>1;
	if(k<=mid)
		updatex(kx<<1,l,mid,L,R,k);
	else
		updatex(kx<<1|1,mid+1,r,L,R,k);
}

uint queryy(uint ky,uint l,uint r,uint L,uint R)
{
	if(!ky)
		return 0;
	if(L<=l && r<=R)
		return tr[ky];
	uint mid=(l+r)>>1,ret=0;
	if(L<=mid)
		ret+=queryy(ls[ky],l,mid,L,R);
	if(R>mid)
		ret+=queryy(rs[ky],mid+1,r,L,R);
	return ret+tar[ky]*(min(R,r)-max(L,l)+1);
}

uint queryx(uint kx,uint l,uint r,uint L,uint R,uint k)
{
	if(l==r)
		return l;
	uint mid=(l+r)>>1;
	uint sum=queryy(root[kx<<1],1,n,L,R);
	if(sum>=k)
		queryx(kx<<1,l,mid,L,R,k);
	else
		queryx(kx<<1|1,mid+1,r,L,R,k-sum);
}

int main()
{
//	freopen("BZOJ3110.in","r",stdin);
//	freopen("BZOJ3110.out","w",stdout);
	
	scanf("%d%d",&n,&m);
	++n;
	while(m--)
	{
		uint opt,l,r,k;
		scanf("%d%d%d%d",&opt,&l,&r,&k);
		if(opt&1)
		{
			k=n-k;;
			updatex(1,1,n,l,r,k);
		}
		else
			printf("%d\n",n-queryx(1,1,n,l,r,k));
	}
	
	return 0;
}
