#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=2e5+10;
int n,m,head,tail;
int w[N];
LL ans,sum;
priority_queue<int>q;
priority_queue<int,vector<int>,greater<int> >p;

struct Tdata
{
	int x,y,typ;
};
Tdata a[N];

bool cmp(Tdata A,Tdata B)
{
	if(A.x==B.x)
		return A.typ<B.typ;
	return A.x<B.x;
}

int main()
{
	freopen("BZOJ4977.in","r",stdin);
	freopen("BZOJ4977.out","w",stdout);
	
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
		scanf("%d",&a[i].x),a[i].typ=0;
	for(int i=1;i<=m;++i)
	{
		++n;
		scanf("%d%d",&a[n].x,&a[n].y);
		a[n].typ=1;a[n].y-=a[n].x;
	}
	sort(a+1,a+n+1,cmp);
	
	head=1;
	for(int i=1;i<=n;++i)
	{
		if(a[i].typ)
			q.push(a[i].y);
		else
		{
			if(q.empty())
			{
				if(head<=tail)
				{
					sum+=a[i].x-w[head++];
					w[++tail]=a[i].x;
				}
			}
			else
			{
				int tmp=q.top();q.pop();
				sum+=a[i].x+tmp;
				p.push(tmp);
				w[++tail]=a[i].x;
			}
		}
	}
	
	ans=sum;
	for(int i=head;i<=tail;++i)
	{
		sum-=p.top()+w[i];
		p.pop();
		ans=max(ans,sum);
	}
	printf("%lld\n",ans);
	
	return 0;
}
