#include<bits/stdc++.h>
using namespace std;

const int N=2e5+10;
int n,m;
int ans1[N],ans2[N];
bool vis[N],bo[N];
vector<int>a[N],st[N],V,M;
map<int,int>vs[N];
queue<int>q;

struct ACM
{
	int tot,ans;
	int fail[N];
	
	ACM()
	{
		tot=1;
		for(int i=-1;i<=10000;++i)
			vs[0][i]=1;
		fail[1]=0;
	}
	
	void insert(int id)
	{
		int len,x,now=1;
		scanf("%d",&len);
		for(int i=1;i<=len;++i)
		{
			scanf("%d",&x);
			if(!vs[now][x])
				vs[now][x]=++tot;
			now=vs[now][x];
		}
		st[now].push_back(id);
	}
	
	void build()
	{
		q.push(1);
		while(!q.empty())
		{
			int now=q.front();q.pop();
			for(map<int,int>::iterator i=vs[now].begin();i!=vs[now].end();++i)
			{
				int t=i->first,k=fail[now];
				while(!vs[k][t])
					k=fail[k];
				fail[i->second]=vs[k][t];
				q.push(i->second);
			}
		}
	}
	
	void query(int id,int x)
	{
		for(int i=x;i;i=fail[i])
			if(!vis[i])
			{
				vis[i]=1;V.push_back(i);
				for(int j=0;j<st[i].size();++j)
					if(!bo[st[i][j]])
					{
						bo[st[i][j]]=1;M.push_back(st[i][j]);
						ans1[st[i][j]]++;
						ans2[id]++;
					}
			}
			else
				break;
	}
	
	void solve(int x)
	{
		int now=1;
		for(int i=0;i<a[x].size();++i)
		{
			int t=a[x][i];
			while(!vs[now][t])
				now=fail[now];
			now=vs[now][t];query(x,now);
		}
		for(int i=0;i<V.size();++i)
			vis[V[i]]=0;
		for(int i=0;i<M.size();++i)
			bo[M[i]]=0;
		V.clear();M.clear();
	}
};
ACM tr;

int main()
{
	freopen("BZOJ2754.in","r",stdin);
	freopen("BZOJ2754.out","w",stdout);
	
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
	{
		int len,x;
		scanf("%d",&len);
		while(len--)
			scanf("%d",&x),a[i].push_back(x);
		a[i].push_back(-1);
		scanf("%d",&len);
		while(len--)
			scanf("%d",&x),a[i].push_back(x);
	}
	for(int i=1;i<=m;++i)
		tr.insert(i);
	tr.build();
	for(int i=1;i<=n;++i)
		tr.solve(i);
	for(int i=1;i<=m;++i)
		printf("%d\n",ans1[i]);
	for(int i=1;i<=n;++i)
		printf("%d ",ans2[i]);
	
	return 0;
}
