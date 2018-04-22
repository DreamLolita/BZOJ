#include<bits/stdc++.h>
using namespace std;

const int N=5e5+10;
int len,qs,now,stklen;
int stk[N<<1],nex[N<<1];
//stack<int>q,mi[N];

struct Tstack
{
	int tp;
	
	int top()
	{
		return stk[tp];
	}
	
	void pop()
	{
		tp=nex[tp];
	}
	
	void push(int x)
	{
		int tmp=tp;tp=++stklen;
		nex[tp]=tmp;stk[stklen]=x;
	}
	
	bool empty()
	{
		return tp==0;
	}
};
Tstack q,mi[N];

int getpos(int x)
{
	int l=1,r=len,ret=l;
	if(len==0)
		return 0;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(mi[mid].top()<=x)
			l=mid+1,ret=mid;
		else
			r=mid-1;
	}
	return ret;
}

void call_back(int tim)
{
	
	int ned=now-tim;
//cerr<<"ned:"<<ned<<"have:"<<q.size()<<endl;
	while(ned--)
	{
		int u=q.top(),p=getpos(u);
//cerr<<"pop:"<<u<<"pos:"<<p<<"maybe:"<<mi[p].top()<<endl;
		q.pop();mi[p].pop();
		if(mi[p].empty())
			--len;
	}
	now=tim;
}

void update(int x)
{
	int p=getpos(x);
	if(p==0)
		++p,++len;
	else
	if(mi[p].top()<=x && p==len)
		++p,++len;
	else
	if(!mi[p+1].empty())
	{
		if(mi[p+1].top()>x && mi[p].top()<=x)
			++p;
	}
//	cerr<<"push:"<<x<<"in:"<<p<<endl;
	mi[p].push(x);q.push(x);
}

int main()
{
	freopen("LOJ6088.in","r",stdin);
	freopen("LOJ6088.out","w",stdout);
	
	scanf("%d",&qs);
	for(int cas=1;cas<=qs;++cas)
	{
		int opt,x;
		scanf("%d%d",&opt,&x);
		if(opt)
		{
			call_back(x);
			printf("%d\n",len);
		}
		else
		{
			update(x);++now;
			printf("%d\n",len);
		}
//cerr<<cas<<endl;
	}
	
	return 0;
}
