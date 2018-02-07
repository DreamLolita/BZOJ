#include<bits/stdc++.h>
using namespace std;

const int N=1005;
int n;
int a[N][N],b[N][N],c[N][N];
int rnd[N],ans1[N],ans2[N]; 

void mul(int a[N],int b[N][N],int s[N])
{
	int tmp[N];
	for(int j=1;j<=n;j++)
    {
    	tmp[j]=0;
    	for(int k=1;k<=n;k++)
    	   tmp[j]+=a[k]*b[k][j];
    }
    for(int i=1;i<=n;i++)
		s[i]=tmp[i];
}

bool check()
{
	for(int i=1;i<=n;i++)
	    if(ans1[i]!=ans2[i])
			return 0;
	return 1;
}

int main()
{
	freopen("BZOJ2396.in","r",stdin);
	freopen("BZOJ2396.out","w",stdout);
	
	for(int i=1;i<N;i++)
		rnd[i]=rand();
	while(scanf("%d",&n)!=EOF)
	{
		for(int i=1;i<=n;i++)
		    for(int j=1;j<=n;j++)
		        scanf("%d",&a[i][j]);
		for(int i=1;i<=n;i++)
		    for(int j=1;j<=n;j++)
		        scanf("%d",&b[i][j]);
		for(int i=1;i<=n;i++)
		    for(int j=1;j<=n;j++)
		        scanf("%d",&c[i][j]);
		mul(rnd,a,ans1);
		mul(ans1,b,ans1);
		mul(rnd,c,ans2);
		if(check())
			puts("Yes");
		else 
			puts("No");
	}
	return 0;
}
