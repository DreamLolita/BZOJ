#include<bits/stdc++.h>
using namespace std;

const int N=2e5+10;
int n,m,qs,tim,top;
int ans[N],del[N],fa[N],stk1[N<<5],stk2[N<<5];

struct Tway
{
	int u,v;
};
Tway e[N];

struct Tquery
{
	int cnt,id;
	int c[5];
};
Tquery q[N];

int findf(int x)
{
	if(fa[x]==x)
		return x;
	int y=findf(fa[x]);
	if(fa[x]!=y)
		stk1[++top]=x,stk2[top]=fa[x];
	return fa[x]=y;
}

void merge(int x,int y)
{
	int fx=findf(x),fy=findf(y); 
	if(fx!=fy)
		stk1[++top]=fx,stk2[top]=fa[fx],fa[fx]=fy;
}

void solve(int l,int r)
{
	int Top=top,mid=(l+r)>>1;
	if(l==r)
	{
		ans[l]=1;
		for(int i=1;i<=q[l].cnt;++i)
			ans[l]*=(findf(e[q[l].c[i]].u)==findf(e[q[l].c[i]].v));
		while(top!=Top)
			fa[stk1[top]]=stk2[top],top--;
		return;
	}

	++tim;
	for(int i=l;i<=mid;++i)
		for(int j=1;j<=q[i].cnt;++j)
			del[q[i].c[j]]=tim;
	for(int i=mid+1;i<=r;++i)
		for(int j=1;j<=q[i].cnt;++j)
		{
			int es=q[i].c[j];
			if(del[es]^tim)
				merge(e[es].u,e[es].v);
		}
	solve(l,mid);
	while(top!=Top)
		fa[stk1[top]]=stk2[top],top--;
		
	++tim;
	for(int i=mid+1;i<=r;++i)
		for(int j=1;j<=q[i].cnt;++j)
			del[q[i].c[j]]=tim;
	for(int i=l;i<=mid;++i)
		for(int j=1;j<=q[i].cnt;++j)
		{
			int es=q[i].c[j];
			if(del[es]^tim)
				merge(e[es].u,e[es].v);
		}
	solve(mid+1,r);
}

int main()
{
	freopen("BZOJ3237.in","r",stdin);
	freopen("BZOJ3237.out","w",stdout);
	
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
		fa[i]=i;
	for(int i=1;i<=m;++i)
		scanf("%d%d",&e[i].u,&e[i].v);
	scanf("%d",&qs);tim=1;
	for(int i=1;i<=qs;++i)
	{
		scanf("%d",&q[i].cnt);
		for(int j=1;j<=q[i].cnt;++j)
			scanf("%d",&q[i].c[j]),del[q[i].c[j]]=tim;
	}
	for(int i=1;i<=m;++i)
		if(del[i]!=tim)
			merge(e[i].u,e[i].v);

	solve(1,qs);
	for(int i=1;i<=qs;++i)
		puts(ans[i]?"Connected":"Disconnected");
	return 0;
}
