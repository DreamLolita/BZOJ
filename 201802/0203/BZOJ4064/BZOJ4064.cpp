#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=105;
const int M=5e4+5;
int T,n,m,cnt;
pair<LL,LL>h[M];

struct Tline
{
	int a,b,c;
};
Tline l[N];


int main()
{
	freopen("BZOJ4064.in","r",stdin);
	freopen("BZOJ4064.out","w",stdout);
	
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&m);
		cnt=n+1;
		
		for(int i=0;i<n;++i)
		{
			scanf("%d%d%d",&l[i].a,&l[i].b,&l[i].c);
			for(int j=0;j<i;++j)
				cnt+=(l[i].a*l[j].b!=l[j].a*l[i].b);
		}
		
		for(int i=0;i<m;++i)
		{
			int x,y;
			scanf("%d%d",&x,&y);
			
			h[i]={0,0};
			for(int j=0;j<n;++j)
				if(1ll*l[j].a*x+1ll*l[j].b*y+1ll*l[j].c>0)
				{
					if(j<50)
						h[i].first|=1ll<<j;
					else
						h[i].second|=1ll<<(j-50);
				}
		}
		
		sort(h,h+m);
		cnt-=unique(h,h+m)-h;
		puts(cnt?"VULNERABLE":"PROTECTED");
	}
	
	return 0;
}
