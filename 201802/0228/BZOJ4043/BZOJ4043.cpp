#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int mod=1e9+9;
const int N=1e6+10;
const int K=30;
const int Z=4;

int T,n,len[Z];
char s[Z][N];
int g[K][K][K][Z][Z];  
LL f[N][Z];

void init()
{
    int lx,rx,ly,ry,lz,rz;
    for(int i=0;i<=27;++i)
        for(int j=0;j<=27;++j)
            for(int k=0;k<=27;++k)
            {
                lx=rx=i;ly=ry=j;lz=rz=k;
                if(i==27)  lx=1,rx=26; 
				if(j==27)  ly=1,ry=26; 
				if(k==27)  lz=1,rz=26; 
                for(int l1=lx;l1<=rx;++l1)
                    for(int l2=ly;l2<=ry;++l2)
                        for(int l3=lz;l3<=rz;++l3)
                            for(int t=0;t<=3;++t)
                            {
                                int tmp=t;
                                if(t==0)
                                {
                                    if(l3>l2)  tmp+=1;
                                    if(l2>l1)  tmp+=2;
                                    if(l3<l2||l2<l1)   tmp=-1;
                                }
                                if(t==1)
                                {
                                    if(l2>l1)  tmp+=2;
                                    if(l2<l1)  tmp=-1;
                                }
                                if (t==2)
                                {
                                    if(l3>l2)  tmp+=1;
                                    if(l3<l2)  tmp=-1;
                                }
                                if (tmp>=0) 
									g[i][j][k][t][tmp]++;   
                            }
            }
}

int main()
{
	freopen("BZOJ4043.in","r",stdin);
	freopen("BZOJ4043.out","w",stdout);
	
	init();
	scanf("%d",&T);
	while(T--)
	{
		n=0;f[0][0]=1;
        for(int i=0;i<3;++i)   
			scanf("%s",s[i]+1),len[i]=strlen(s[i]+1),n=max(n,len[i]);
			
        for(int i=1;i<=n;++i)  
			for(int j=0;j<4;++j)   
				f[i][j]=0;
				
        for(int i=0;i<3;++i)
            for(int j=len[i]+1;j<=n;++j)   
				s[i][j]='a'-1;
				
        for(int i=1;i<=n;++i)
        {
            int x=s[0][i]-'a'+1,y=s[1][i]-'a'+1,z=s[2][i]-'a'+1;
            if(x<0) x=27;   
			if(y<0) y=27;   
			if(z<0) z=27;
            for(int j=0;j<=3;++j)
                if(f[i-1][j])
                    for(int k=0;k<=3;++k)  
						f[i][k]=(f[i][k]+f[i-1][j]*g[x][y][z][j][k]%mod)%mod;
        }
        printf("%lld\n",f[n][3]);
	}
	
	return 0;
}
