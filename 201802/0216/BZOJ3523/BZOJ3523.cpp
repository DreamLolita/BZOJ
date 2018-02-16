#include<bits/stdc++.h>
using namespace std;

const int N=1e6+10;

int n,m,st,en;
int ans[N];

struct Tnode
{
	int c,w;
	bool operator <(const Tnode&A)const
	{
		if(w!=A.w)	return w<A.w;
		if(c==en)	return false;
		return true;
	}
};
priority_queue<Tnode>q;

int main()
{
	freopen("BZOJ3523.in","r",stdin);
	freopen("BZOJ3523.out","w",stdout);
	
	scanf("%d%d%d",&n,&st,&en);
	for(int i=1;i<=n;++i)
	{
		Tnode x;
		scanf("%d",&x.w);
		m+=x.w;x.c=i;
		if(i==st)
			--x.w;
		if(i==en)
			--x.w;
		if(x.w<0)
		{
			puts("0");
			return 0;
		}
		q.push(x);
	}
	ans[1]=st;ans[m]=en;
	for(int i=2;i<m;++i)
	{
		Tnode x=q.top(),tmp;q.pop();
		bool flag=false;
		if(x.c==st)
		{
			tmp=x;
			if(!q.empty())
				x=q.top();
			else
			{
				puts("0");
				return 0;
			}
			q.pop();flag=true;
		}
		st=ans[i]=x.c;
		if(x.w>1)
			q.push((Tnode){x.c,x.w-1});
		if(flag)
			q.push(tmp);
	}
	if(ans[m]==ans[m-1])
	{
		puts("0");
		return 0;
	}
	for(int i=1;i<=m;++i)
		printf("%d ",ans[i]);
	printf("\n");
	
	return 0;
}
