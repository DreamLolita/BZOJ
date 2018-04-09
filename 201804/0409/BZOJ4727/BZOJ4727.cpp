#include<bits/stdc++.h>
using namespace std;

const int N=2005;
int n,top,cnt,scc;
int dfn[N],low[N],bl[N],siz[N],du[N];
int st[N],pos[N],nex[N],mp[N][N];
bool vis[N];
vector<int>vec[N];

int cmp(int x,int y)
{
	return du[x]<du[y];
}

void tarjan(int x)
{
    st[++top]=x;vis[x]=1;
    low[x]=dfn[x]=++cnt;
    for(int i=1;i<=n;i++)if(mp[x][i])
    {
        if(!dfn[i])
            tarjan(i),low[x]=min(low[x],low[i]);
        else 
		if(vis[i])
            low[x]=min(low[x],dfn[i]);
    }
    if(dfn[x]==low[x])
    {
        int tmp=st[top--];
        bl[tmp]=++scc;vis[tmp]=0;
        vec[scc].push_back(tmp);siz[scc]++;
        while(tmp!=x)
        {
            tmp=st[top--];
            bl[tmp]=scc;vis[tmp]=0;
            vec[scc].push_back(tmp);siz[scc]++;
        }
    }
}

void insert(int x)
{
    st[++top]=x;
    for(int i=nex[x];i&&i!=x;i=nex[i])
        st[++top]=i;
}

int main()
{
	freopen("BZOJ4727.in","r",stdin);
	freopen("BZOJ4727.out","w",stdout);
	
	scanf("%d",&n);
	for(int i=2;i<=n;++i)
		for(int j=1;j<i;++j)
		{
			scanf("%d",&mp[j][i]);
			mp[i][j]=mp[j][i]^1;
		}
	for(int i=1;i<=n;++i)
		if(!dfn[i])
			tarjan(i);
	for(int i=1;i<=scc;++i)
	{
		int h,r;
		h=r=vec[i][0];
		for(int j=1;j<vec[i].size();++j)
		{
			int t=vec[i][j];
			if(mp[t][h])
				nex[t]=h,h=t;
			else
			if(mp[r][t])
				nex[r]=t,r=t;
			else
			{
				for(int k=h;;k=nex[k])
					if(mp[k][t] && mp[t][nex[k]])
					{
						nex[t]=nex[k];nex[k]=t;
						break;
					}
			}
		}
		r=0;
		for(int j=nex[h];j;j=nex[j])
		{
			if(r)
			{
				for(int k=r,p=h;;p=k,k=nex[k])
				{
					if(mp[j][k])
					{
						nex[p]=nex[h];
						if(p!=h)
							nex[h]=r;
						h=j;r=k;
						break;
					}
					if(k==h)
						break;
				}
			}
			else
			if(mp[j][h])
				r=h,h=j;
		}
		nex[h]=r;
	}
	
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			if(bl[i]!=bl[j] && mp[i][j])
				du[bl[j]]++;
	for(int i=1;i<=scc;++i)
		pos[i]=i,du[i]/=siz[i];
	sort(pos+1,pos+scc+1,cmp);
	for(int i=1;i<=n;++i)
	{
		top=0;insert(i);
		for(int j=1,t;j<=scc;++j)
			if(du[t=pos[j]]>du[bl[i]])
				insert(vec[t][0]);
		printf("%d ",top);
		for(int j=1;j<=top;++j)
			printf("%d ",st[j]);
		printf("\n");
	}
	
	return 0;
}
