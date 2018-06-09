#include<bits/stdc++.h>
#define id(x,y) (x-1)*n+y
using namespace std;

const int N=25;
const int M=405;
int n,m,A,B,cnt,tot;
double a[M][M],p[N],d[N];
vector<int>e[N];

void build(int x,int y)
{
    a[id(x,y)][id(x,y)]--;
    for(int i=0;i<(int)e[x].size();++i)
        for(int j=0;j<(int)e[y].size();++j)
        {
            int tx=e[x][i],ty=e[y][j];
            int t1=id(x,y),t2=id(tx,ty);
            if(tx^ty)
            {
                if(tx==x && ty==y)
                    a[t1][t2]+=p[tx]*p[ty];
                else
                if(tx==x)
                    a[t1][t2]+=p[tx]*(1-p[ty])/d[ty];
                else
                if(ty==y)
                    a[t1][t2]+=p[ty]*(1-p[tx])/d[tx];
                else
                    a[t1][t2]+=(1-p[tx])*(1-p[ty])/d[tx]/d[ty];           
            }
        }
}

void gauss()
{
    int now=1;
    for(int i=1;i<=tot;++i)
    {
        int j;
        for(j=now;!a[j][now] && j<=tot;++j);
        for(int k=1;k<=tot+1;++k)
            swap(a[now][k],a[j][k]);
        for(int j=1;j<=tot;++j)
            if(j!=now)
            {
                double t=a[j][now]/a[now][now];
                for(int k=1;k<=tot+1;++k)
                    a[j][k]-=t*a[now][k];
            }
        ++now;
    }
}

int read()
{
    int ret=0,f=1;char c=getchar();
    while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
    while(isdigit(c)){ret=ret*10+(c^48);c=getchar();}
    return f?ret:-ret;
}

int main()
{
    freopen("BZOJ3270.in","r",stdin);
    freopen("BZOJ3270.out","w",stdout);

    n=read();m=read();A=read();B=read();tot=n*n;
    a[id(A,B)][tot+1]=-1;
    for(int i=1;i<=n;++i)
        e[i].push_back(i);
    for(int i=1;i<=m;++i)
    {
        int u=read(),v=read();
        d[u]++;d[v]++;
        e[u].push_back(v);e[v].push_back(u);
    } 
    for(int i=1;i<=n;++i)
        scanf("%lf",&p[i]);
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
            build(i,j);
	//for(int i=1;i<=tot;++i)
		//for(int j=1;j<=tot;++j)
			//printf("%lf\n",a[i][j]);
    gauss();
    for(int i=1;i<=n;++i)
    {
        int t=id(i,i);
        printf("%.6lf ",a[t][tot+1]/a[t][t]);
    }
    return 0;
}
