//tip:if use RMQ,it will be TLE in BZOJ,but the brute can be AC
#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=1048576;
const int M=500000;
const int P=M+10;
const double pi=acos(-1);
int T,n,m,l,r,ans,tot,len;
int d[P],g[P],pri[P],rev[N];
//LL f[P];
int id[20][P];
LL f[20][P];
bool flag[P];

struct E
{
	double r,i;
	E(){}
	E(double rr,double ii){
		r=rr;i=ii;
	}
	E operator + (E const &A)const{
		return E(r+A.r,i+A.i);
	}
	E operator - (E const &A)const{
		return E(r-A.r,i-A.i);
	}
	E operator * (E const &A)const{
		return E(r*A.r-i*A.i,r*A.i+i*A.r);
	}
}D[N];

void fft(E *a,int f)
{
	for(int i=0;i<n;++i)
		if(i>rev[i])
			swap(a[i],a[rev[i]]);
	for(int i=1;i<n;i<<=1)
	{
		E wn(cos(pi/i),f*sin(pi/i));
		for(int j=0;j<n;j+=(i<<1))
		{
			E w(1,0);
			for(int k=0;k<i;++k,w=w*wn)
			{	
				E x=a[j+k],y=w*a[j+k+i];
				a[j+k]=x+y;a[j+k+i]=x-y;
			}
		}
	}
	if(f==-1)
		for(int i=0;i<n;++i)
			a[i].r/=n;
}

void get_pri()
{
	d[1]=1;
	for(int i=2;i<=M;++i)
	{
		if(!flag[i])
			pri[++tot]=i,d[i]=2,g[i]=1;
		for(int j=1;i*pri[j]<=M && j<=tot;++j)
		{
			flag[i*pri[j]]=1;
			if(i%pri[j])
			{
				d[i*pri[j]]=d[i]*2;
				g[i*pri[j]]=1;
			}
			else
			{
				d[i*pri[j]]=d[i]/(g[i]+1)*(g[i]+2);
				g[i*pri[j]]=g[i]+1;
				break;
			}
		} 
	}
}

void get_f()
{
	for(n=1;n<=M*2;n<<=1)
		++len;
	for(int i=0;i<n;++i)
		rev[i]=(rev[i>>1]>>1)|((i&1)<<(len-1));
	for(int i=1;i<=M;++i)
		D[i].r=d[i];
	
	fft(D,1);
	for(int i=0;i<N;++i)
		D[i]=D[i]*D[i];
	fft(D,-1);
	
//	for(int i=1;i<=M;++i)
//		f[i]=(LL)(D[i].r+0.5);
	for(int i=1;i<=M;++i)
		f[0][i]=(LL)(D[i].r+0.5),id[0][i]=i;
	for(int i=1;i<=19;++i)
		for(int j=1;j<=M;++j)
		{
			int p=min(M,j+(1<<(i-1)));
			if(f[i-1][j]>f[i-1][p])
				f[i][j]=f[i-1][j],id[i][j]=id[i-1][j];
			else
				f[i][j]=f[i-1][p],id[i][j]=id[i-1][p];
		}
}

void init()
{
	get_pri();	
	get_f();	
}

void solve()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&l,&r);
		int t=(r-l+1),p=0;
/*		for(ans=l;l<=r;++l)
			if(f[l]>f[ans])
				ans=l;
		printf("%d %lld\n",ans,f[ans]);*/
		while(t>1)
		{
			p++;
			t>>=1;
		}
		if(l==r)
		{
			printf("%d %lld\n",id[0][l],f[0][l]);
			continue;
		}
		t=r-(1<<(p))+1;
		if(f[p][l]>f[p][t])
			printf("%d %lld\n",id[p][l],f[p][l]);
		else
			printf("%d %lld\n",id[p][t],f[p][t]);
	}
}

int main()
{
	freopen("BZOJ4115.in","r",stdin);
	freopen("BZOJ4115.out","w",stdout);
	
	init();
	solve();	
	
	return 0;
}
