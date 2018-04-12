#include<bits/stdc++.h>
#define lc p<<1
#define rc p<<1|1
using namespace std;

const int maxn = 100000 + 10;

char s[maxn];
int n,Q;
int sa[maxn],cnt[maxn],orix[maxn],oriy[maxn],hei[maxn],*x=orix,*y=oriy;
int idr[maxn][20],llg2[maxn];

struct que{
	int l,k,id,ans;
}q[maxn];

struct pr{
	int x,y;
	pr(){}
	pr(int X,int Y){x=X;y=Y;}
	bool operator < (const pr &s) const
	{
		return !(x==s.x?y<s.y:x<s.x);
	}
};

struct Segmenttree{
	int x,d,nt[maxn<<2];
	
	void add(int p,int tl,int tr)
	{
		if(x<=tl && tr<=x+1) {nt[p]+=d;return;}
		
		int mid=tl+tr>>1;
		if(x<mid) add(lc,tl,mid);
		else      add(rc,mid,tr);
		nt[p]=nt[lc]+nt[rc];//printf("node (%d,%d) %d\n",tl,tr,nt[p]);
	}
	
	int get(int p,int tl,int tr)
	{
		if(tl==tr-1) return tl;
		int mid=tl+tr>>1;
		//printf("in (%d,%d,%d) lc=%d\n",tl,mid,tr,nt[lc]);
		if(nt[lc]>=x) return get(lc,tl,mid);
		x-=nt[lc];
		return get(rc,mid,tr);
	}
	inline void Add(int X){x=X;d=1;/*printf("Add %d\n",x);*/add(1,0,n+1);}
	inline void Mis(int X){x=X;d=-1;/*printf("Mis %d\n",x);*/add(1,0,n+1);}
	inline int Get(int X){x=X;return get(1,0,n+1);}
}T;

priority_queue<pr> H,I;
set<int> S;

inline int read()
{
	int x=0;char c=getchar();
	for(;c<'0'||c>'9';c=getchar());
	for(;c>='0'&&c<='9';c=getchar()) x=(x<<3)+(x<<1)+(c^48);
	return x;
}

bool cmpl(que a,que b){return a.l<b.l;}
void input()
{
	int i;
	
	scanf("%s",s);n=strlen(s);Q=read();
	for(i=0;i<Q;i++)
	{
		q[i].l=read();q[i].k=read();q[i].id=i;
	}
	sort(q,q+Q,cmpl);
}

bool same(int *r,int len,int x,int y)
{
	if((x+len<n)!=(y+len<n) || r[x]!=r[y]) return false;
	return (x+len<n) ? r[x+len]==r[y+len] : true; 
}
void suffix()
{
	int i,j,t,len,m=26;
	for(i=0;i<m;i++) cnt[i]=0;
	for(i=0;i<n;i++) cnt[x[i]=s[i]-'a']++;
	for(i=1;i<m;i++) cnt[i]+=cnt[i-1];
	for(i=0;i<n;i++) sa[ --cnt[x[i]] ]=i;
	for(len=1;len==1||m<n;len<<=1)
	{
		t=0;
		for(i=n-1;i>=n-len;i--) y[t++]=i;
		for(i=0;i<n;i++) if(sa[i]>=len) y[t++]=sa[i]-len;
		for(i=0;i<m;i++) cnt[i]=0;
		for(i=0;i<n;i++) cnt[x[y[i]]]++;
		for(i=1;i<m;i++) cnt[i]+=cnt[i-1];
		for(i=n-1;i>=0;i--) sa[ --cnt[x[y[i]]] ]=y[i];
		m=1;swap(x,y);x[sa[0]]=0;
		for(i=1;i<n;i++) x[sa[i]]=(same(y,len,sa[i-1],sa[i])?m-1:m++); 
	}
	
	t=0;
	for(i=0;i<n;i++)
	{
		idr[x[i]][0]=i;//if(x[i]<=15) cerr<<i<<endl;
		if(t) t--;
		if(!x[i]) continue;
		j=sa[x[i]-1];
		while(j+t<n && i+t<n && s[i+t]==s[j+t]) t++;
		hei[x[i]]=t;H.push(pr(t,x[i]));
	}
}

void rmq_pre()
{
	int i,j;
	
	llg2[1]=llg2[0]=0;
	for(i=2;i<maxn;i++) llg2[i]=llg2[i>>1]+1;
	
	for(i=1;(1<<i)<=n;i++) 
	{
		for(j=0;j+(1<<i)<=n;j++) idr[j][i]=min(idr[j][i-1],idr[j+(1<<i-1)][i-1]);
	}
}

int rmq(int l,int r)
{
	int d=llg2[r-l];
	return min(idr[l][d],idr[r-(1<<d)+1][d]);
}

void ins(int len)
{
	pr t;
	while(!H.empty())
	{
		t=H.top();
		if(t.x>=len) break;
		H.pop();
		S.insert(t.y);T.Add(t.y);//printf("Add %d\n",t.y);
		I.push(pr(n-sa[t.y],t.y));//cout<<sa[t.y]<<endl;
	}
	while(!I.empty())
	{
		t=I.top();//cout<<"|||"<<t.x<<endl;
		if(t.x>=len) break;
		I.pop();
		T.Mis(t.y);
	}
}

void solve()
{
	int i,j,l,r;
	
	T.Add(0);S.insert(0);I.push(pr(n-sa[0],0));
	T.Add(n);S.insert(n);
	for(i=0;i<Q;i=j)
	{
		ins(q[i].l);
		for(j=i;q[j].l==q[i].l;j++)
		{
			l=T.Get(q[j].k);
			if(l==n) {q[j].ans=-1;continue;}
			r=*S.upper_bound(l);r--;
			//printf("ask %d %d  l=%d r=%d\n",q[j].l,q[j].k,l,r);
			q[j].ans=rmq(l,r);
		}
	}
}

bool cmpi(que a,que b){return a.id<b.id;}
void output()
{
	int i;
	sort(q,q+Q,cmpi);
	for(i=0;i<Q;i++) 
	{
		if(q[i].ans==-1) printf("Not found\n");
		else printf("%d\n",q[i].ans);
	}
}

int main()
{
	freopen("2440.in","r",stdin);
	freopen("2440.out","w",stdout);
	
	input();
	suffix();
	rmq_pre();
	solve();
	output();
	
	return 0;
}
