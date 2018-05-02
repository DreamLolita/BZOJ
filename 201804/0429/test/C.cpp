#include<bits/stdc++.h>
using namespace std;

const int INF=1e9;
const int N=1e5+10;
int n,m,cl,ce,vs,qs,ans;
int a[N],b[N];

int read()
{
	int ret=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c^48);c=getchar();}
	return f?ret:-ret;
}

int main()
{
	freopen("C.in","r",stdin);
	freopen("C.out","w",stdout);

	n=read();m=read();cl=read();ce=read();vs=read();
	for(int i=1;i<=cl;++i)
		a[i]=read();
	sort(a+1,a+cl+1);
	for(int i=1;i<=ce;++i)
		b[i]=read();
	sort(b+1,b+ce+1);
	qs=read();
	while(qs--)
	{
		int x=read(),y=read(),r=read(),c=read();
		if(x==r)
		{
			printf("%d\n",abs(y-c));
			continue;
		}
		ans=INF;
		if(cl)
		{
			int rs=lower_bound(a+1,a+cl+1,y)-a,ls=rs-1;
			if(ls)
				ans=min(ans,abs(a[ls]-c)+abs(a[ls]-y)+abs(r-x));
			if(rs<=cl)
				ans=min(ans,abs(a[rs]-c)+abs(a[rs]-y)+abs(r-x));
//printf("stair:%d %d\n",ls,rs);
		}
		if(ce)
		{
			int rs=lower_bound(b+1,b+ce+1,y)-b,ls=rs-1;
			int t=(abs(r-x)+vs-1)/vs;
			if(ls)
				ans=min(ans,abs(b[ls]-c)+abs(b[ls]-y)+abs(t));
			if(rs<=ce)
				ans=min(ans,abs(b[rs]-c)+abs(b[rs]-y)+abs(t));
//printf("ele:%d %d\n",ls,rs);
		}
		printf("%d\n",ans);
	}

	return 0;
}

