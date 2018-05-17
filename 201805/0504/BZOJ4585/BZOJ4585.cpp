#include<bits/stdc++.h>
#define mkp(x,y) make_pair(x,y)
using namespace std;

typedef long long LL;
typedef long double ldb;
typedef pair<int,int> pii;
const int N=6e5+10;

int n,m,cnt,tot;
int fa[N],len[N],rt[N],du[N];
LL sum,p[N]; 

LL read()
{
	LL ret=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c)){ret=(ret<<1ll)+(ret<<3ll)+(c^48);c=getchar();}
	return f?ret:-ret;
}

struct Tnode
{
	int l,r,dis;
	LL val;
};
Tnode q[N];

int merge(int x,int y)
{
	if(!x || !y) 
		return x+y;
	if(q[x].val<q[y].val) 
		swap(x,y);
	q[x].r=merge(q[x].r,y);
	if(q[q[x].l].dis<q[q[x].r].dis)
		swap(q[x].l,q[x].r);
	q[x].dis=(q[x].r?q[q[x].r].dis+1:0);
	return x;
} 

int pop(int x)
{
	return merge(q[x].l,q[x].r);
}

int main()
{
	freopen("BZOJ4585.in","r",stdin);
	freopen("BZOJ4585.out","w",stdout);
	
	n=read();m=read();
	for(int i=2;i<=n+m;++i)
	{
		fa[i]=read();len[i]=read();
		sum+=len[i];du[fa[i]]++;
	}
	
	for(int i=n+m;i>1;--i)
	{
		LL l=0,r=0;
		if(i<=n)
		{
			while(--du[i])
				rt[i]=pop(rt[i]);
			l=q[rt[i]].val;rt[i]=pop(rt[i]); 
			r=q[rt[i]].val;rt[i]=pop(rt[i]);
		}
		q[++tot].val=l+len[i];q[++tot].val=r+len[i];
		rt[i]=merge(rt[i],merge(tot,tot-1));
		rt[fa[i]]=merge(rt[fa[i]],rt[i]);	
	}
	
	while(du[1]--)
		rt[1]=pop(rt[1]);
	while(rt[1])
		p[++cnt]=q[rt[1]].val,rt[1]=pop(rt[1]);
	for(int i=1;i<=cnt;++i)	
		sum-=p[i];
	printf("%lld\n",sum); 
	
	return 0;
} 
