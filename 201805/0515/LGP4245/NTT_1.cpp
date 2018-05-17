#include<bits/stdc++.h>
#define mkp(x,y) make_pair(x,y)
using namespace std;

typedef long long LL;
typedef long double ldb;
typedef pair<int,int> pii;
const int N=262145;
const ldb eps=1e-6;
int n,m,tn,mod,L;
int p[3]={998244353,1004535809,469762049},g[3]={3,3,3};
int rev[N],invg[3],wn[3][2][N];
LL Mod,inv1,inv2,inv3;
LL q1[N],q2[N],c[3][N];
int F[N],G[N];

LL read()
{
	LL ret=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c)){ret=(ret<<1ll)+(ret<<3ll)+(c^48);c=getchar();}
	return f?ret:-ret;
}

LL qpow(LL x,LL y,LL md)
{
	LL ret=1;
	for(;y;y>>=1ll,x=x*x%md)
		if(y&1)
			ret=ret*x%md;
	return ret;
}

void ntt(LL *a,int n,int f,int id)
{
	for(int i=0;i<n;++i)
		if(i>rev[i])
			swap(a[i],a[rev[i]]);
	for(int i=1,tmp=1;i<n;i<<=1,++tmp)
	{
		LL pwn=wn[id][f][tmp];
		for(int j=0;j<n;j+=(i<<1))
		{
			LL w=1;
			for(int k=0;k<i;++k,w=w*pwn%p[id])
			{	
				LL x=a[j+k],y=w*a[j+k+i]%p[id];
				a[j+k]=(x+y)%p[id];a[j+k+i]=(x-y+p[id])%p[id];
			}
		}
	}
	if(f)
		for(int i=0,inv=qpow(n,p[id]-2,p[id]);i<n;++i)	
			a[i]=a[i]*inv%p[id];
}

LL mul(LL a,LL b,LL P)  
{  
    a=(a%P+P)%P,b=(b%P+P)%P;  
    return ((a*b-(LL)((ldb)a/P*b+eps)*P)%P+P)%P;  
}  

void mult(int id)
{
	for(int i=0;i<tn;++i)
	{
		q1[i]=F[i]%p[id];
		q2[i]=G[i]%p[id];
	}
	ntt(q1,tn,0,id);ntt(q2,tn,0,id);
	for(int i=0;i<tn;++i)
		c[id][i]=1ll*q1[i]*q2[i]%p[id];
	ntt(c[id],tn,1,id);
}

void init_mod(int id)
{
	invg[id]=qpow(g[id],p[id]-2,p[id]);
	for(int i=1;i<24;++i)
	{
		wn[id][0][i]=qpow(g[id],(p[id]-1)/(1<<i),p[id]);
		wn[id][1][i]=qpow(wn[id][0][i],p[id]-2,p[id]);
	}
}

void init()
{
	Mod=1ll*p[0]*p[1];  
    inv1=qpow(p[0]%p[1],p[1]-2,p[1]),inv2=qpow(p[1]%p[0],p[0]-2,p[0]),inv3=qpow(Mod%p[2],p[2]-2,p[2]); 
	n=read();m=read();mod=read();
	for(int i=0;i<=n;++i)
		F[i]=read()%mod;
	for(int i=0;i<=m;++i)
		G[i]=read()%mod;
	for(L=0,tn=1;tn<=m+n;tn<<=1)
		++L;
	for(int i=0;i<tn;++i)
		rev[i]=(rev[i>>1]>>1)|((i&1)<<(L-1));
}

void solve(int i)  
{  
    LL C=(mul(1ll*c[0][i]*p[1]%Mod,inv2,Mod)+mul(1ll*c[1][i]*p[0]%Mod,inv1,Mod))%Mod;  
    LL K=1ll*((1ll*c[2][i]-(C%p[2])+p[2])%p[2])*(inv3%p[2])%p[2];  
    c[0][i]=(((K%mod)*(Mod%mod)%mod+(C%mod))%mod);  
}  

void MTT()
{
	for(int i=0;i<3;++i)
		init_mod(i),mult(i);
	for(int i=0;i<=n+m;i++)   
    	solve(i);   
    for(int i=0;i<=n+m;i++)  
    {  
        LL tmp=(c[0][i]+mod)%mod;  
        printf("%lld ",tmp);  
    }  
}

int main()
{
	freopen("LGP4245.in","r",stdin);
	freopen("LGP4245.out","w",stdout);
	
	init();
	MTT();

	return 0;
}

