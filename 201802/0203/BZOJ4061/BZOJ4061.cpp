#include<bits/stdc++.h>
#define mkp(x,y) make_pair(x,y) 
using namespace std;

typedef long long LL;
typedef pair<LL,int> way;
const int N=1e5+10;
const int INF=0x3f;
int T,n,m;
LL dis[2][N],x[N],y[N],ans;
bool vis[2][N];
vector<way>e[N];
priority_queue<way, vector<way>,greater<way> >q;

int read()
{
    int x=0,t=1;
    char ch=getchar();
    while((ch<'0'||ch>'9')&&ch!='-')
		ch=getchar();
    if(ch=='-')
		t=-1,ch=getchar();
    while(ch>='0'&&ch<='9')
		x=x*10+ch-48,ch=getchar();
    return x*t;
}

void init()
{
	ans=0;
	memset(dis,INF,sizeof(dis));
	memset(vis,0,sizeof(vis));
	
	n=read();m=read();
	for(int i=0;i<n;++i)
		e[i].clear();
	for(int i=1;i<=m;++i)
	{
		int u,v,w;
		u=read();v=read();w=read();
		--u;--v;
		e[u].push_back(mkp(w,v));
		e[v].push_back(mkp(w,u));
	}
}

void solve()
{
	for(int s=0;s<2;++s)
	{
		while(!q.empty())
			q.pop();
			
		dis[s][s]=0;
		q.push(mkp(dis[s][s],s));
		while(!q.empty())
		{
			int u=q.top().second;q.pop();
			if(vis[s][u])
				continue;
			for(int i=0;i<e[u].size();++i)
			{
				int v=e[u][i].second;
				LL w=e[u][i].first;
				if(dis[s][v]>dis[s][u]+w)
				{
					dis[s][v]=dis[s][u]+w;
					q.push(mkp(dis[s][v],v));
				}
			}
/*			for(vector<way>::iterator it = e[u].begin(); it != e[u].end(); ++it)  
            {  
                int &v = it -> second;  
                LL &w = it -> first;  
                if(dis[s][v] > dis[s][u] + w)  
                {  
                    dis[s][v] = dis[s][u] + w;  
                    q.push(mkp(dis[s][v], v));  
                }  
            } */
		}
	}
	
	for(int i=0;i<n;++i)
	{
		x[i]=dis[0][i]+dis[1][i];
		y[i]=dis[0][i]-dis[1][i];
	}
	sort(x,x+n);sort(y,y+n);
	
	LL tx=x[n>>1],ty=y[n>>1];
	for(int i=0;i<n;++i)
		ans+=abs(x[i]-tx)+abs(y[i]-ty);
	printf("%0.12f\n",ans/(2.0*n));
}

int main()
{
	freopen("BZOJ4061.in","r",stdin);
	freopen("BZOJ4061.out","w",stdout);
	
	T=read();
	while(T--)
	{
		init();
		solve();
	}
	
	return 0;
}
