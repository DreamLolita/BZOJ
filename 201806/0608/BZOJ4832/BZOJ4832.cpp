#include<bits/stdc++.h>
using namespace std;

const int N=52;
double f[N][N][N][N];

int read()
{
	int ret=0;char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c)){ret=ret*10+(c^48);c=getchar();}
	return ret;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("BZOJ4832.in","r",stdin);
	freopen("BZoj4832.out","w",stdout);
#endif
	for(int i=0;i<50;++i)
		for(int a=0;a<8;++a)
			for(int b=0;a+b<8;++b)
				for(int c=0;a+b+c<8;++c)
				{
					double tot=1.0/(a+b+c+1.0);
					f[i+1][a][b][c]+=(f[i][a][b][c]+1.0)*tot;
					if(a)
						f[i+1][a][b][c]+=f[i][a-1][b][c]*a*tot;
					if(b)
					{
						if(a+b+c<7)
							f[i+1][a][b][c]+=f[i][a+1][b-1][c+1]*b*tot;
						else
							f[i+1][a][b][c]+=f[i][a+1][b-1][c]*b*tot;
					}
					if(c)
					{
						if(a+b+c<7)
							f[i+1][a][b][c]+=f[i][a][b+1][c]*c*tot;
						else
							f[i+1][a][b][c]+=f[i][a][b+1][c-1]*c*tot;
					}
				}
	
	int T=read();
	while(T--)
	{
		int k=read(),a=read(),b=read(),c=read();
		printf("%.2lf\n",f[k][a][b][c]);
	}

	return 0;
}
