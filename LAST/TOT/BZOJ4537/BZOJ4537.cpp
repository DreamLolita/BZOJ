#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;

const int lim=332;
const int MAXN=1e5+10;

int n,m,qs,cnt,co;
int ans[MAXN],ida[MAXN],idb[MAXN];
int fa[MAXN],d[MAXN],va[MAXN],vb[MAXN];

struct pat
{
	int x,y,z;
	pat(){}
	pat(int _x,int _y,int _z){x=_x,y=_y;z=_z;}
};
pat opt[MAXN];

struct Tway
{
	int x,y,a,b;
};
Tway e[MAXN],q[MAXN];

inline bool cmpa(const Tway&A,const Tway&B)
{
	return A.a<B.a;
}

inline bool cmpe(int A,int B)
{
	return e[A].b<e[B].b;
}

inline bool cmpq(int A,int B)
{
	return q[A].b<q[B].b;
}

inline int findf(int x)
{
	return x==fa[x]? x : findf(fa[x]);
}

inline void merge(int x,int y,int A,int B,int typ)
{
	x=findf(x);y=findf(y);
	if(x!=y)
	{
		if(d[x]==d[y])
		{
			if(typ)
				opt[++co]=pat(1,x,d[x]);
			d[x]++;
		}
		
		if(d[x]<d[y])
			swap(x,y);
		if(typ)
			opt[++co]=pat(0,y,y);
		fa[y]=x;
		
		if(va[x]<va[y] && va[y]>A)
		{
			if(typ)
				opt[++co]=pat(2,x,va[x]);
			va[x]=va[y];
		}
		if(vb[x]<vb[y] && vb[y]>B)
		{
			if(typ)
				opt[++co]=pat(3,x,vb[x]);
			vb[x]=vb[y];
		}
	}
	if(va[x]<A)
	{
		if(typ)
			opt[++co]=pat(2,x,va[x]);
		va[x]=A;
	}
	if(vb[x]<B)
	{
		if(typ)
			opt[++co]=pat(3,x,vb[x]);
		vb[x]=B;
	}
}

inline void remark()
{
	for(int i=co;i>=1;--i)
	{
		if(!opt[i].x)
			fa[opt[i].y]=opt[i].z;
		else
		if(opt[i].x==1)
			d[opt[i].y]=opt[i].z;
		else
		if(opt[i].x==2)	
			va[opt[i].y]=opt[i].z;
		else
			vb[opt[i].y]=opt[i].z;
	}
	co=0;
}

int main()
{
//	freopen("BZOJ4537.in","r",stdin);
//	freopen("BZOJ4537.out","w",stdout);
	
	scanf("%d%d",&n,&m);
//	lim=(int)floor(sqrt(m-1));
	for(int i=1;i<=m;++i)
	{
		scanf("%d%d%d%d",&e[i].x,&e[i].y,&e[i].a,&e[i].b);
		ida[i]=i;
	}
	sort(e+1,e+m+1,cmpa);
	
	scanf("%d",&qs);
	for(int i=1;i<=qs;++i)
		scanf("%d%d%d%d",&q[i].x,&q[i].y,&q[i].a,&q[i].b);
	for(int i=0;i<=m;i+=lim)
	{
		cnt=0;
		for(int j=1;j<=qs;++j)
			if(q[j].a>=e[i].a && (i+lim>m || q[j].a<e[i+lim].a))
				idb[++cnt]=j;
		if(!cnt)
			continue;
		sort(ida+1,ida+i+1,cmpe);
		sort(idb+1,idb+cnt+1,cmpq);
		
		for(int j=1;j<=n;++j)
		{
			fa[j]=j;d[j]=0;
			va[j]=vb[j]=-1;
		}
		for(int j=1,k=1;j<=cnt;++j)
		{
			while(k<=i && e[ida[k]].b<=q[idb[j]].b)
			{
				merge(e[ida[k]].x,e[ida[k]].y,e[ida[k]].a,e[ida[k]].b,0);
				++k;
			}
			
			co=0;
			for(int t=min(i+lim-1,m);t>i;--t)
				if(e[t].a<=q[idb[j]].a && e[t].b<=q[idb[j]].b)
					merge(e[t].x,e[t].y,e[t].a,e[t].b,1);
			
			int x=findf(q[idb[j]].x),y=findf(q[idb[j]].y);
			if(x==y && va[x]==q[idb[j]].a && vb[x]==q[idb[j]].b)
				ans[idb[j]]=1;
			remark();
		}
	}
	for(int i=1;i<=qs;++i)
		(ans[i] ? puts("Yes") : puts("No"));
	return 0;
}
