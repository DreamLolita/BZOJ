#include<bits/stdc++.h>
using namespace std;

const int N=1e4+10;
const int M=5e4+10;
const int K=32;

int n,m,ans,cnt;
int num[N][K],f[N][K];
int h[N],nex[N];

int read()
{
	int ret=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c^48);c=getchar();}
	return f?ret:-ret;
}

struct Tnode
{
	int nex,n1,n2;
	int L[6],R[6];
};
Tnode q[M];

void init(int x)
{
	x+=4;if(x>n)x-=n;
	++cnt;q[cnt].nex=h[x];h[x]=cnt;
	q[cnt].n2=read();q[cnt].n1=read();
	for(int i=1;i<=q[cnt].n2;++i)
		q[cnt].L[i]=read();
	for(int i=1;i<=q[cnt].n1;++i)
		q[cnt].R[i]=read();
}


int main()
{
	freopen("LGP3622.in","r",stdin);
	freopen("LGP3622.out","w",stdout);

	n=read();m=read();
	for(int i=1;i<=m;++i)
	{
		int x=read();
		init(x);
	}
	
	for(int x=1;x<=n;++x)
	{
		for(int sta=0;sta<(1<<5);++sta)
		{
			for(int i=h[x];i;i=q[i].nex)
			{
				int k=0;
				for(int j=1;j<=q[i].n1;++j)
				{
					int y=x-q[i].R[j];y=(y+n)%n;
					if(sta&(1<<y))
						k=1;
				}
				for(int j=1;j<=q[i].n2;++j)
				{
					int y=x-q[i].L[j];y=(y+n)%n;
					if(!(sta&(1<<y)))
						k=1;
				}
				num[x][sta]+=k;
			}	
			
		}
	}
	
	for(int sta=0;sta<(1<<5);++sta)
	{
		for(int j=0;j<(1<<5);++j)
			if(j^sta)
				f[1][j]=-2*n;
			else
				f[1][j]=num[1][j];
		for(int i=2;i<=n;++i)
			for(int j=0;j<(1<<5);++j)
				f[i][j]=max(f[i-1][(j>>1)&31],f[i-1][(j>>1)+16])+num[i][j];
		ans=max(ans,f[n][(sta>>1)&31]);ans=max(ans,f[n][(sta>>1)+16]);
	}
	printf("%d\n",ans);
	
	return 0;
}

