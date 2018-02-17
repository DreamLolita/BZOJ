

#include<iostream>
#include<vector>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>

using namespace std;

inline int read()
{
	int x=0;char ch=getchar();
	while(ch<'0' || '9'<ch)ch=getchar();
	while('0'<=ch && ch<='9')x=x*10+(ch^48),ch=getchar();
	return x;
}

typedef long long ll;
const int N=1e5+9;
const int K=23;
const int M=26;
const int border=319;

int n,m,q,k;
char s[N];

namespace sam
{
	int ch[N<<1][M],fa[N<<1][K],tot,u;
	int len[N<<1],siz[N<<1],id[N<<1];

	inline void init()
	{
		u=tot=1;
	}

	inline void add(int v)
	{
		int now=++tot;
		len[now]=len[u]+1;
		siz[now]=1;

		while(u && !ch[u][v])
			ch[u][v]=now,u=fa[u][0];

		if(!u)
			fa[now][0]=1;
		else
		{
			int q=ch[u][v];
			if(len[q]==len[u]+1)
				fa[now][0]=q;
			else
			{
				int newq=++tot;
				memcpy(ch[newq],ch[q],sizeof(ch[q]));
				len[newq]=len[u]+1;
				fa[newq][0]=fa[q][0];
				fa[q][0]=fa[now][0]=newq;

				while(u && ch[u][v]==q)
					ch[u][v]=newq,u=fa[u][0];
			}
		}
		u=now;
	}

	inline void work()
	{
		static int cnt[N];
		for(int i=1;i<=tot;i++)
			cnt[len[i]]++;
		for(int i=1;i<=n;i++)
			cnt[i]+=cnt[i-1];
		for(int i=1;i<=tot;i++)
			id[cnt[len[i]]--]=i;
		for(int i=tot;i>=1;i--)
			siz[fa[id[i]][0]]+=siz[id[i]];
	}

	inline void build()
	{
		fa[1][0]=0;
		for(int i=1;i<K;i++)
			for(int j=1;j<=tot;j++)
				fa[j][i]=fa[fa[j][i-1]][i-1];
	}

	inline int nxt(int &now,int v,int dir)
	{
		if(ch[now][dir])
		{
			now=ch[now][dir];
			return v+1;
		}
		while(now && !ch[now][dir])
			now=fa[now][0];
		v=len[now];
		if(ch[now][dir])
			v++;
		now=ch[now][dir];
		if(now==0)now=1;	
		return v;
	}

	inline ll query(int now,int val)
	{
		if(len[now]<val)return 0;
		for(int i=K-1;i>=0;i--)
			if(len[fa[now][i]]>=val)
				now=fa[now][i];
		return siz[now];
	}
}

struct query
{
	int l,r;
}qu[N];

namespace mo
{
	using namespace sam;

	struct querys
	{
		int l,r,id;
	}que[N];

	ll ans[N];
	int cnt[border+1][border+1];
	char w[N][border+1];

	bool cmp(const querys &a,const querys &b)
	{
		if(a.l/border==b.l/border)
			return a.r<b.r;
		return a.l/border<b.l/border;
	}

	int main()
	{
		for(int i=1;i<=q;i++)
		{
			scanf("%s",w[i]+1);
			que[i].l=read()+1;
			que[i].r=read()+1;
			que[i].id=i;
		}

		sort(que+1,que+q+1,cmp);

		int l=0,r=0;
		for(int i=1;i<=q;i++)
		{
			while(l<que[i].l)
				cnt[qu[l].l][qu[l].r]--,l++;
			while(que[i].l<l)
				cnt[qu[l-1].l][qu[l-1].r]++,l--;
			while(r<que[i].r)
				cnt[qu[r+1].l][qu[r+1].r]++,r++;
			while(que[i].r<r)
				cnt[qu[r].l][qu[r].r]--,r--;
			for(int s=1;s<=k;s++)
			{
				int now=1;
				for(int t=s;t<=k;t++)
				{
					now=ch[now][w[que[i].id][t]-'a'];
					if(!now)continue;
					ans[que[i].id]+=(ll)cnt[s][t]*siz[now];
				}
			}
		}

		for(int i=1;i<=q;i++)
			printf("%lld\n",ans[i]);
		return 0;
	}
}

namespace ha
{
	char w[N];
	vector<int> wea[N];

	int main()
	{
		sam::build();
		for(int cases=1,l,r;cases<=q;cases++)
		{
			scanf("%s",w+1);
			l=read()+1;r=read()+1;
			
			for(int i=l;i<=r;i++)
				wea[qu[i].r].push_back(qu[i].r-qu[i].l+1);

			ll ans=0;
			int now=1,val=0;
			for(int i=1;i<=k;i++)
			{
				val=sam::nxt(now,val,w[i]-'a');
				for(int j=0;j<wea[i].size();j++)
				{
					if(val<wea[i][j])continue;
					ans+=sam::query(now,wea[i][j]);
				}
				wea[i].clear();
			}

			printf("%lld\n",ans);
		}

		return 0;
	}
}

int main()
{
	freopen("LOJ6031.in","r",stdin);
	freopen("LOJ6031.out","w",stdout);

	n=read();m=read();
	q=read();k=read();

	scanf("%s",s+1);
	sam::init();
	for(int i=1;i<=n;i++)
		sam::add(s[i]-'a');
	sam::work();

	for(int i=1;i<=m;i++)
		qu[i].l=read()+1,qu[i].r=read()+1;
	if(k<border)
		return mo::main();
	else
		return ha::main();
	
	return 0;
}

