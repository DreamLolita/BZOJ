#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int INF=1e9;
const int N=4e5+10;
LL n,nw,k,ans;
int f[N];

LL read()
{
    LL ret=0,f=1;char c=getchar();
    while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
    while(isdigit(c)){ret=(ret<<1ll)+(ret<<3ll)+(c^48);c=getchar();}
    return f?ret:-ret;
}

struct Cir
{
    LL x,y,r;
}c[N];

struct Tpoint
{
    LL num,x,k;
}b[N];

set<Tpoint>S;

LL sqr(LL x)
{
    return x*x;
}

bool cmp(const Tpoint &A,const Tpoint &B)
{
    return A.x<B.x;
}

bool operator <(Tpoint A,Tpoint B)
{
    double tx=c[A.num].y+A.k*sqrt(sqr(c[A.num].r)-sqr(nw-c[A.num].x));
    double ty=c[B.num].y+B.k*sqrt(sqr(c[B.num].r)-sqr(nw-c[B.num].x));
    if(tx!=ty)
		return tx<ty;
    return A.k<B.k;
}

int main()
{
    freopen("BZOJ4561.in","r",stdin);
    freopen("BZOJ4561.out","w",stdout);
    
    n=read();
    for(int i=1;i<=n;++i)
    {
		c[i].x=read();c[i].y=read();c[i].r=read();
		b[++k]=(Tpoint){i,c[i].x-c[i].r,1};
		b[++k]=(Tpoint){i,c[i].x+c[i].r,-1};
    }
    sort(b+1,b+k+1,cmp);
    set<Tpoint>::iterator it;
    for(int i=1;i<=k;++i)
    {
		nw=b[i].x;
		if(b[i].k==1)
		{
		    it=S.upper_bound((Tpoint){b[i].num,0,-1});
		    if(it==S.end())
				f[b[i].num]=1;
		    else
		    {
				if((*it).k==1)
				    f[b[i].num]=-f[(*it).num];
				else
				    f[b[i].num]=f[(*it).num];
		    }
		    S.insert((Tpoint){b[i].num,0,-1});
		    S.insert((Tpoint){b[i].num,0,1});
		}
		else
		{
		    S.erase((Tpoint){b[i].num,0,-1});
		    S.erase((Tpoint){b[i].num,0,1});
		}
    }
    for(int i=1;i<=n;++i)
		ans+=sqr(c[i].r)*(LL)f[i];
    printf("%lld\n",ans);
    return 0;
}

