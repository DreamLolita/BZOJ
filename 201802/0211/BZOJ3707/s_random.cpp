#include<bits/stdc++.h> 
#define inf 1000000000
#define ll long long
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int n,block,cnt;
double ans=1e60;
struct P{double x,y;}p[1005];
P operator -(P a,P b){return (P){a.x-b.x,a.y-b.y};}
double cross(P a,P b){return a.x*b.y-a.y*b.x;}
bool operator <(P a,P b)
{
	return a.x<b.x||(a.x==b.x&&a.y<b.y);
}
P rotate(P a,double x)
{
	return (P){a.x*cos(x)-a.y*sin(x),a.y*cos(x)+a.x*sin(x)};
}
void cal(int a,int b)
{
	for(int i=a;i<=b-2;i++)
		for(int j=i+1;j<=b-1;j++)
			for(int k=j+1;k<=b;k++)
			    ans=min(ans,abs(cross(p[i]-p[k],p[j]-p[k]))/2);
}
void solve()
{
	double t=rand()/10000;
    for(int i=1;i<=n;i++)
		p[i]=rotate(p[i],t);
	sort(p+1,p+n+1);
	for(int i=1;i<=cnt;i++)
	{
		int t1=block*(i-1)+1,t2=block*i;
		t2=min(t2,n);
		cal(t1,t2);
	}
}
int main()
{
	//freopen("land.in","r",stdin);
	//freopen("land.out","w",stdout);
	n=read();srand(time(0));
	block=sqrt(n)+10;
	cnt=n/block+(n%block!=0);
	for(int i=1;i<=n;i++)
		p[i].x=read(),p[i].y=read();
	for(int i=1;i<=50;i++)
		solve();
	printf("%.2lf",ans);
	return 0;
}
