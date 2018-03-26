#include<bits/stdc++.h>
using namespace std;

const int N=9;
const int M=6;
const int mod=1e9+7;
int T,n,m,c,ans,U,na,nb;
int nex[N],ta[N][M],tb[N][M];
int f[2<<N][M][M],g[2<<N][M][M];
char a[N],b[N];

int id(char x)
{
	if(x=='B')
		return 0;
	return x=='W'?1:2;
}

void up(int &x,int y)
{
	(x+=y)%=mod;
}

void clear()
{
	for(int S=0;S<U;++S)
		for(int i=0;i<c;++i)
			for(int j=0;j<c;++j)
				g[S][i][j]=0;
}

void copy()
{
	for(int S=0;S<U;++S)
		for(int i=0;i<c;++i)
			for(int j=0;j<c;++j)
				f[S][i][j]=g[S][i][j];
}

int main()
{
	freopen("BZOJ4572.in","r",stdin);
	freopen("BZOJ4572.out","w",stdout);
	
	scanf("%d%d%d%d",&n,&m,&c,&T);
	while(T--)
	{
		scanf("%s%s",a+1,b+1);
		for(int i=1;i<=c;++i)
			a[i]=id(a[i]),b[i]=id(b[i]);
		nex[1]=0;
		for(int j=0,i=2;i<=c;nex[i++]=j)
		{
			while(j && a[j+1]!=a[i])
				j=nex[j];
			if(a[j+1]==a[i])
				++j;
		}
		na=nex[c];
		for(int i=0;i<c;++i)
			for(int j=0;j<3;++j)
			{
				int k;
				for(k=i;k && a[k+1]!=j;k=nex[k]);
				if(a[k+1]==j)
					++k;
				ta[i][j]=k;
			}
		nex[1]=0;
		for(int j=0,i=2;i<=c;nex[i++]=j)
		{
			while(j && b[j+1]!=b[i])
				j=nex[j];
			if(b[j+1]==b[i])
				++j;
		}
		nb=nex[c];
		for(int i=0;i<c;++i)
			for(int j=0;j<3;++j)
			{
				int k;
				for(k=i;k && b[k+1]!=j;k=nex[k]);
				if(b[k+1]==j)
					++k;
				tb[i][j]=k;
			}
		U=1<<(m-c+1);
/*		for(int S=0;S<U;++S)
			for(int i=0;i<c;++i)
				for(int j=0;j<S;++j)
					f[S][i][j]=0;*/
		memset(f,0,sizeof(f));
		f[0][0][0]=1;
		for(int i=1;i<=n;++i)
		{
			clear();
			for(int S=0;S<U;++S)
				for(int i=0;i<c;++i)
					for(int j=0;j<c;++j)
						if(f[S][i][j])
							up(g[S][0][0],f[S][i][j]);
			copy();
			for(int x=1;x<=m;++x)
			{
				clear();
				for(int S=0;S<U;++S)
					for(int i=0;i<c;++i)
						for(int j=0;j<c;++j)
							if(f[S][i][j])
								for(int k=0;k<3;++k)
								{
									int E=S;
									if(x>=c && (S>>(x-c)&1))
										E^=1<<(x-c);
									int A=ta[i][k],B=tb[j][k];
									if(A==c)
										E|=1<<(x-c),A=na;
									if(B==c)
									{
										if(S>>(x-c)&1)
											continue;
										B=nb;
									}
									up(g[E][A][B],f[S][i][j]);
								}
				copy();
			}
		}
		ans=1;
		for(int i=n*m;i;--i)
			ans=3ll*ans%mod;
		for(int S=0;S<U;++S)
			for(int i=0;i<c;++i)
				for(int j=0;j<c;++j)
					up(ans,mod-f[S][i][j]);
		printf("%d\n",ans);
	}
	
	return 0;
}
