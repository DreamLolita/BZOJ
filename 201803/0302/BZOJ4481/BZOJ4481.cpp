#include<bits/stdc++.h>
using namespace std;

typedef long double ldb;
const int N=5e5+5;
int n,m,now,s;
ldb p,w,r,ans;
ldb gl[N],tr[N];

struct Tnode
{
	int x,y;
};
Tnode a[N];

bool cmp(Tnode A,Tnode B)
{
	if(A.x==B.x)
		return A.y<B.y;
	return A.x<B.x;
}

int lowbit(int x)
{
	return x&(-x);
}

void update(int x,ldb v)
{
	for(;x<=n;x+=lowbit(x))
		tr[x]+=v;
}

ldb query(int x)
{
	double ret=0;
	for(;x;x-=lowbit(x))
		ret+=tr[x];
	return ret;
}

int main()
{
	freopen("BZOJ4481.in","r",stdin);
	freopen("BZOJ4481.out","w",stdout);
	
	double t;
	scanf("%d%d%lf",&n,&m,&t);p=t;
	for(int i=1;i<=n;++i)
		scanf("%d%d",&a[i].x,&a[i].y);
	sort(a+1,a+m+1,cmp);

    for(int i=1;i<=m;++i)
    {
        if (a[i].x!=now)
        {
            for(int j=i-1;j&&a[j].x==now;--j) 
				update(a[j].y,gl[j]);
            now=a[i].x;s=0;w=r=1;
            for(s=0;a[i+s].x==now;s++,w*=(1-p));
            w=1-w;
        }
        gl[i]=r*p/w;
        r*=(1-p);
        ans+=gl[i]*(query(n)-query(a[i].y));
    }
    printf("%0.2lf",(double)ans);
	
	return 0;
}
