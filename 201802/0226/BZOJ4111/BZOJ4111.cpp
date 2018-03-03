#include<bits/stdc++.h>
using namespace std;

const int N=55;
const int M=1e4+10;
int r,c,len;
int t[N][N];
bool vis[N][N][M];
char mp[N][N],s[M];

struct Tp
{
	int x,y;
};
Tp a[N][N][4];

struct Mp
{
	int x,y,k,d;
};
queue<Mp>q;


void get_mp()
{
	for(int i=1;i<=r;++i)
		for(int j=1;j<=c;++j)
		{
			for(int k=i-1;k;--k)
				if(mp[k][j]!=mp[i][j])
				{
					a[i][j][t[i][j]++]=(Tp){k,j};
					break;
				}
			for(int k=i+1;k<=r;++k)
          		if(mp[k][j]!=mp[i][j])
          		{
            		a[i][j][t[i][j]++]=(Tp){k,j};
            		break;
          		}
        	for(int k=j-1;k;--k)
	          	if(mp[i][k]!=mp[i][j])
	          	{
	            	a[i][j][t[i][j]++]=(Tp){i,k};
	            	break;
	          	}
        	for(int k=j+1;k<=c;++k)
          		if(mp[i][k]!=mp[i][j])
	          	{
	            	a[i][j][t[i][j]++]=(Tp){i,k};
	            	break;
	          	}	
		}
}

int bfs()
{
	get_mp();
	vis[1][1][0]=1;q.push((Mp){1,1,0,0});
	while(!q.empty())
	{
		Mp u=q.front();q.pop();
		int x=u.x,y=u.y,k=u.k,d=u.d;
//		printf("%d %d %d %d\n",x,y,k,d);
		if(mp[x][y]==s[k+1] && !vis[x][y][k+1])
		{
			vis[x][y][k+1]=1;
			if(k+1==len)
				return d+1;
			q.push((Mp){x,y,k+1,d+1});
		}
		else
		{
			for(int i=0;i<t[x][y];++i)
			{
				int nx=a[x][y][i].x,ny=a[x][y][i].y;
				if(!vis[nx][ny][k])
				{
					vis[nx][ny][k]=1;
					q.push((Mp){nx,ny,k,d+1});
				}
			}
		}
	}
	return -1;
}

int main()
{
	freopen("BZOJ4111.in","r",stdin);
	freopen("BZOJ4111.out","w",stdout);
	
	scanf("%d%d",&r,&c);
	for(int i=1;i<=r;++i)
		scanf("%s",mp[i]+1);
	scanf("%s",s+1);
	len=strlen(s+1);s[++len]='*';
	printf("%d\n",bfs());
	
	return 0;
}
