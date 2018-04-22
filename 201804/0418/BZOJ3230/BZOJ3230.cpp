#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=1e5+10;
const int K=17;
int n,q;
LL en[N];
char s[N];

LL read()
{
	LL ret=0,f=1;char ch='.';
	while(ch<'0' || ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0' && ch<='9'){ret=(ret<<3ll)+(ret<<1ll)+(ch-'0');ch=getchar();}
	return ret*f;
}

struct SA
{
	char s[N];
	int len,rank[N],hei[N],sa[N],Ws[N],Log[N],mn[K][N];
	
	void init(char *t)
	{
		strcpy(s+1,t);
		len=strlen(s+1);
	}
	
	bool cmp(int *a,int p1,int p2,int l)
	{
		if(p1+l>len && p2+l>len) return a[p1]==a[p2];
		if(p1+l>len || p2+l>len) return 0;
		return a[p1]==a[p2] && a[p1+l]==a[p2+l]; 
	}
	
	void get_sa()
	{
		int *x=rank,*y=hei,m=0;
		for(int i=1;i<=len;++i)
			Ws[x[i]=s[i]]++,m=max(m,x[i]);
		for(int i=1;i<=m;++i)
			Ws[i]+=Ws[i-1];
		for(int i=len;i;--i)
			sa[Ws[x[i]]--]=i;
		for(int j=1,pos=0;pos<len;j<<=1,m=pos)
		{
			pos=0;
			for(int i=len-j+1;i<=len;++i) y[++pos]=i;
			for(int i=1;i<=len;++i) if(sa[i]>j) y[++pos]=sa[i]-j;
			for(int i=1;i<=m;++i) Ws[i]=0;
			for(int i=1;i<=len;++i) Ws[x[i]]++;
			for(int i=1;i<=m;++i) Ws[i]+=Ws[i-1];
			for(int i=len;i;--i) sa[Ws[x[y[i]]]--]=y[i];
			swap(x,y);pos=1;x[sa[1]]=1;
			for(int i=2;i<=len;++i)	x[sa[i]]=cmp(y,sa[i],sa[i-1],j)?pos:++pos;	
		}
	}
	
	void call_height()
	{
		for(int i=1;i<=len;++i)
			rank[sa[i]]=i;
		for(int i=1,j,k=0;i<=len;hei[rank[i++]]=k)
			for(k?k--:0,j=sa[rank[i]-1];s[j+k]==s[i+k];++k);
	}
	
	void rmq()
	{
		Log[1]=0;
		for(int i=2;i<=len;++i)
			Log[i]=Log[i>>1]+1;
		for(int i=1;i<=len;++i)
			mn[0][i]=hei[i];
		for(int j=1;(1<<j)<=len;++j)
			for(int i=1;i+(1<<j)-1<=len;++i)
				mn[j][i]=min(mn[j-1][i],mn[j-1][i+(1<<(j-1))]);
	}
	
	int query(int l,int r)
	{
		if(l>r) swap(l,r);
		if(l==r) return len-sa[l]+1;
		++l;int t=Log[r-l+1];
		return min(mn[t][l],mn[t][r-(1<<t)+1]);
	}
}s1,s2;

void init()
{
	n=read();q=read();scanf("%s",s);
	s1.init(s);
	for(int i=0;i<(s1.len>>1);++i)
		swap(s[i],s[s1.len-i-1]);
	s2.init(s);
	s1.get_sa();s1.call_height();s1.rmq();
	s2.get_sa();s2.call_height();s2.rmq();
	for(int i=1;i<=n;++i)
		en[i]=n-s1.sa[i]+1-s1.hei[i],en[i]+=en[i-1];
}

void solve()
{
	while(q--)
	{
		LL l=read(),r=read();
		if(l>en[n] || r>en[n])
		{
			puts("-1");
			continue;
		}
		int prel=lower_bound(en+1,en+n+1,l)-en,prer=lower_bound(en+1,en+n+1,r)-en;
		int lenl=n-s1.sa[prel]+1-en[prel]+l,lenr=n-s1.sa[prer]+1-en[prer]+r;
		int a=min(s1.query(prel,prer),min(lenl,lenr));
		int b=min(s2.query(s2.rank[n-s1.sa[prel]-lenl+2],s2.rank[n-s1.sa[prer]-lenr+2]),min(lenl,lenr));
		printf("%lld\n",(LL)a*a+(LL)b*b);
	}
}

int main()
{
	freopen("BZOJ3230.in","r",stdin);
	freopen("BZOJ3230.out","w",stdout);
	
	init();
	solve();
	
	return 0;
}
