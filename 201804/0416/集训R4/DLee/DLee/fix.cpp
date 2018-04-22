#include<bits/stdc++.h>
using namespace std;

const int N=1e6+10;
int T,siz,n,m,tot;
int a[N],b[N],f[N],g[N];
int las[N],nex[N],ans[N];

inline int read()
{
	int ret=0,opt=1;char ch='.';
	while(ch<'0' || ch>'9')
	{
		ch=getchar();
		if(ch=='-')
			opt=-1;
	}
	while(ch>='0' && ch<='9')
	{
		ret=(ret<<3)+(ret<<1)+(ch-'0');
		ch=getchar();
	}
	return ret*opt;
}

inline void write(int x)
{
	if(x<0)
		putchar('-'),x=-x;
	if(x>9)
		write(x/10);
	putchar(x%10+'0');
}

inline void init()
{
	n=read();m=read();
	for(int i=1;i<=n;++i)
		a[i]=read();
	for(int i=1;i<=m;++i)
		b[i]=read();
		
	memset(las,0,sizeof(las));
	for(int i=1;i<=n;++i)
	{
		if(!las[a[i]])
			f[i]=0;
		else
			f[i]=i-las[a[i]];
		las[a[i]]=i;
	}
	
	memset(las,0,sizeof(las));
	for(int i=1;i<=m;++i)
	{
		if(!las[b[i]])
			g[i]=0;
		else
			g[i]=i-las[b[i]];
		las[b[i]]=i;
	}	
}

inline void KMP()
{
	memset(nex,0,sizeof(nex));memset(las,0,sizeof(las));
	int j=0,x,y;
	for(int i=2;i<=m;++i)
	{
		while(j)
		{
			if(j+1>m) 
				j=las[j];
			x=g[j+1];y=g[i];
			if(y>j) 
				y=0;
			if(x==y) 
				break;
			j=las[j];
		}
		x=g[j+1];y=g[i];
		if(y>j)	
			y=0;
		if(x==y) 
			++j;
		las[i]=j;
	}
	
	j=0;
	for(int i=1;i<=n;++i)
	{
		while(j)
		{
			if(j+1>m) 
				j=las[j];
			x=g[j+1];y=f[i];
			if(y>j) 
				y=0;
			if(x==y) 
				break;
			j=las[j];
		}
		x=g[j+1];y=f[i];
		if(y>j)	
			y=0;
		if(x==y) 
			++j;
		nex[i]=j;
	}	
}

inline void get_ans()
{
	tot=0;
	for(int i=1;i<=n;++i)
		if(nex[i]==m)
			ans[++tot]=i-m+1;
	write(tot);puts("");
	for(int i=1;i<=tot;++i)
		write(ans[i]),putchar(' ');
	puts("");
}

int main()
{
	freopen("fix.in","r",stdin);
	freopen("fix.out","w",stdout);
	
	T=read();siz=read();
	while(T--)
	{
		init();
		KMP();
		get_ans();
	}
	
	return 0;
}
