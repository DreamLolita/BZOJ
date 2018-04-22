#include<bits/stdc++.h>
using namespace std;

const int N=6e5+10;
int n,tot,mx;
int cnt[N],cnt2[N];
int a[N],b[N],c[N];

inline int read()
{
	int ret=0,f=1;char ch='.';
	while(ch<'0' || ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0' && ch<='9'){ret=(ret<<3)+(ret<<1)+(ch-'0');ch=getchar();}
	return ret*f;
}

int main()
{
	freopen("2463.in","r",stdin);
	freopen("2463.out","w",stdout);
	
	n=read();
	for(register int i=1;i<=n;++i)
	{
		a[i]=read();b[i]=read();
		c[++tot]=a[i];c[++tot]=b[i];
	}
	sort(c+1,c+tot+1);
	tot=unique(c+1,c+tot+1)-c-1;
	for(register int i=1;i<=n;++i)
	{
		a[i]=lower_bound(c+1,c+tot+1,a[i])-c;
		b[i]=lower_bound(c+1,c+tot+1,b[i])-c;
		cnt[a[i]]++;cnt2[a[i]]++;cnt[b[i]]+=!(a[i]==b[i]);
	}
	sort(a+1,a+n+1);
	int t=unique(a+1,a+n+1)-a-1;
	for(register int i=1;i<=t;++i)
		if(cnt[a[i]]>n/2 && cnt2[a[i]]>mx)
			mx=cnt2[a[i]];
	if(mx<(n+1)/2 && mx)
		printf("%d\n",(n+1)/2-mx);
	else
	if(mx>(n+1)/2)
		puts("0");
	else
		puts("Impossible");
	
	return 0;
}
