#include<bits/stdc++.h>
using namespace std;

const int N=205;
const int M=1005;
const int C=5e5+5;
int n,m,q;
int val[N][N][M],num[N][N][M],A[C],B[N][N],s[C];

int read()
{
	int ret=0;char c='.';
	while(c<'0' || c>'9')
		c=getchar();
	while(c>='0' && c<='9')
	{
		ret=(ret<<3)+(ret<<1)+(c-'0');
		c=getchar();
	}
	return ret;
}

struct Seqment_Tree
{
	int tot;
	int ls[C*20],rs[C*20],sum[C*20],v[C*20],root[C];
	
	void update(int &rt,int l,int r,int las,int p)
	{
		rt=++tot;
		ls[rt]=ls[las];rs[rt]=rs[las];
		sum[rt]=sum[las]+1;v[rt]=v[las]+p;
		if(l==r)
			return;
		int mid=(l+r)>>1;
		if(p<=mid)
			update(ls[rt],l,mid,ls[las],p);
		else
			update(rs[rt],mid+1,r,rs[las],p);
	}
	
	int query(int rt,int las,int l,int r,int p)
	{
		if(l==r)
			return (p-1)/l+1;
		int ts=sum[rs[rt]]-sum[rs[las]],tv=v[rs[rt]]-v[rs[las]],ret=0;
		int mid=(l+r)>>1;
		if(p>tv)
			ret+=ts+query(ls[rt],ls[las],l,mid,p-tv);
		else
			ret+=query(rs[rt],rs[las],mid+1,r,p);
		return ret;
	}
}tr;

int get_sum(int a[N][N][M],int ux,int uy,int lx,int ly,int st)
{
	return a[lx][ly][st]-a[ux-1][ly][st]-a[lx][uy-1][st]+a[ux-1][uy-1][st];
}

void solve1()
{
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
		{
			B[i][j]=read();
			val[i][j][B[i][j]]+=B[i][j];
			num[i][j][B[i][j]]++;
			for(int k=1;k<=1000;++k)
			{
				val[i][j][k]+=val[i-1][j][k]+val[i][j-1][k]-val[i-1][j-1][k];
				num[i][j][k]+=num[i-1][j][k]+num[i][j-1][k]-num[i-1][j-1][k];
			}
		}
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			for(int k=1000;k;--k)
			{
				val[i][j][k]+=val[i][j][k+1];
				num[i][j][k]+=num[i][j][k+1];
			}
	while(q--)
	{
		int ux,uy,lx,ly,h;
		ux=read();uy=read();lx=read();ly=read();h=read();
//		scanf("%d%d%d%d%d",&ux,&uy,&lx,&ly,&h);
		
		int l=1,r=1000,ret=-1;
		while(l<=r)
		{
			int mid=(l+r)>>1;
			if(get_sum(val,ux,uy,lx,ly,mid)>=h)
				ret=mid,l=mid+1;
			else
				r=mid-1;
		}
		if(ret==-1)
			puts("Poor QLW");
		else
		{
			int mi=get_sum(val,ux,uy,lx,ly,ret+1),ans=get_sum(num,ux,uy,lx,ly,ret+1);
			ans+=(h-mi-1)/ret+1;
			printf("%d\n",ans);
		}
	}
}

void solve2()
{
	for(int i=1;i<=m;++i)
	{
//		scanf("%d",&A[i]);
		A[i]=read();
		s[i]=s[i-1]+A[i];
		tr.update(tr.root[i],1,C,tr.root[i-1],A[i]);
	}
	while(q--)
	{
		int l,r,h;
		l=read();l=read();r=read();r=read();h=read();
//		scanf("%d%d%d%d%d",&ll,&l,&rr,&r,&h);
		if(s[r]-s[l-1]<h)
			puts("Poor QLW");
		else
			printf("%d\n",tr.query(tr.root[r],tr.root[l-1],1,C,h));
	}
}


int main()
{
	freopen("BZOJ1926.in","r",stdin);
	freopen("BZOJ1926.out","w",stdout);
	
//	scanf("%d%d%d",&n,&m,&q);
	n=read();m=read();q=read();
	if(n==1)
		solve2();
	else
		solve1();
	
	return 0;
}
