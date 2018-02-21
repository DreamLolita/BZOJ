#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=2005;
int R,C,ret;
LL n,x,y;
char f[N][N],vis[N][N];

void solve(int d,LL i)
{
	if(d==0)x+=i,++y;
	if(d==1)y-=i,++x;
	if(d==2)x-=i,--y;
	if(d==3)y+=i,--x;
}

LL mo(LL a,LL b)
{
	return (a%b+b)%b;
}

void col(int x,int y,int c)
{
	if(!vis[x][y])
	{
		vis[x][y]=1;
		f[x][y]=c;
		ret--;
	}
}
void moveup(int x,int l,int r,int c)
{
	for(int i=l;i<=r;i++)
		col(x,i,c);
}

void moveright(int y,int l,int r,int c)
{
	for(int i=l;i<=r;i++)
		col(i,y,c);
}

void walk(LL X,LL Y,LL xx,LL yy,int c)
{
	if(X==xx)
	{
		if(Y>yy)
			swap(Y,yy);
		LL k=yy-Y+1;
		Y=mo(Y,C);
		if(k>=C)
			moveup(mo(X,R),0,C-1,c);
		else
		{
			if(Y+k-1<C)
				moveup(mo(X,R),Y,Y+k-1,c);
			else
			{
				moveup(mo(X,R),Y,C-1,c);
				moveup(mo(X,R),0,mo(yy,C),c);
			}
		}
	}
	else
	{
		if(X>xx)
			swap(X,xx);
		LL k=xx-X+1;
		X=mo(X,R);
		if(k>=R)
			moveright(mo(Y,C),0,R-1,c);
		else
		{
			if(X+k-1<R)
				moveright(mo(Y,C),X,X+k-1,c);
			else
			{
				moveright(mo(Y,C),X,R-1,c);
				moveright(mo(Y,C),0,mo(xx,R),c);
			}
		}
	}
}

void solve2(LL n, int d,int c)
{
	LL xx=x,yy=y;
	if(d==0)x+=n;// rgt
	if(d==1)y-=n;// down
	if(d==2)x-=n;// lft
	if(d==3)y+=n;// up

	walk(xx,yy,x,y,c);
	if(d==0)++y;// rgt
	if(d==1)++x;// down
	if(d==2)--y;// lft
	if(d==3)--x;// up
}


int main()
{
	freopen("BZOJ5122.in","r",stdin);
	freopen("BZOJ5122.out","w",stdout);
	
	scanf("%d%d",&R,&C);
	scanf("%lld%lld%lld",&x,&y,&n);

	x=R-x+1;--x;--y;
	swap(x,y);swap(R,C);
	x%=R;y%=C;

	LL A=n/4,B=n%4;
	x+=-2*A+1;y+=-2*A;
	x%=R;y%=C;
	for(int i=0;i<B;++i)
	{
		solve((i+3)%4,A*4+i);
		x%=R;y%=C;
	}
	
	for(int i=0;i<R;++i)
		for(int j=0;j<C;++j)
		{
			f[i][j]='.';
			ret++;
		}
		
	if(n%4==0)
		col(mo(x-1,R),mo(y,C),'@');
	if(n%4==1)
		col(mo(x,R),mo(y+1,C),'@');
	if(n%4==2)
		col(mo(x+1,R),mo(y,C),'@');
	if(n%4==3)
		col(mo(x,R),mo(y-1,C),'@');
	
	for(LL i=n;i;--i)
	{
		solve2(i-1,i%4,(i-1+26)%26+'A');
		x%=R;y%=C;
		if(!ret)
			break;
	}
	for(int j=C-1;~j;--j)
	{
		for(int i=0;i<R;i++)
			putchar(f[i][j]);
		puts("");
	}

	return 0;
}
