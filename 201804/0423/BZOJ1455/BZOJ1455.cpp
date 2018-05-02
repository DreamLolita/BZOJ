#include<bits/stdc++.h>
using namespace std;

const int N=1e6+10;
int n,m;
int fa[N],l[N],r[N],dep[N],key[N];
bool die[N];

int read()
{
	int ret=0,f=1;char c='.';
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c-'0');c=getchar();}
	return ret*f;
}

int findf(int x)
{
	return fa[x]==x?x:fa[x]=findf(fa[x]);
}

int merge(int x,int y)
{
	if(!x || !y)
		return x+y;
	if(key[x]>key[y])
		swap(x,y);
	r[x]=merge(r[x],y);
	if(dep[r[x]]>dep[l[x]])
		swap(r[x],l[x]);
	dep[x]=dep[r[x]]+1;
	return x;
}

int main()
{
	freopen("BZOJ1455.in","r",stdin);
	freopen("BZOJ1455.out","w",stdout);
	
	n=read();
	for(int i=1;i<=n;++i)
		key[i]=read(),fa[i]=i;
	dep[0]=-1;
	m=read();
	while(m--)
	{
		char op[2];int x,y;
		scanf("%s",op);
		if(op[0]=='M')
		{
			x=read();y=read();
			if(die[x] || die[y])
				continue;
			int fx=findf(x),fy=findf(y);
			if(fx^fy)
			{
				int t=merge(fx,fy);
				fa[fx]=fa[fy]=t;
			}
		}
		else
		{
			x=read();
			if(die[x])
				puts("0");
			else
			{
				int fx=findf(x);die[fx]=1;
				printf("%d\n",key[fx]);
				fa[fx]=merge(l[fx],r[fx]);
				fa[fa[fx]]=fa[fx];
			}
		}
	}
	
	return 0;	
}
