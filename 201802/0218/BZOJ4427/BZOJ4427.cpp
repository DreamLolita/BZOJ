#include<bits/stdc++.h>
using namespace std;

const int N=1005;
int n,m,top;
int col[N];
queue<int>qs;

struct Tpoint
{
	int x,y;
	Tpoint(){
		x=y=0;
	}
	Tpoint(int xx,int yy){
		x=xx;y=yy;
	}
};
Tpoint s[N];

struct Tline
{
	Tpoint a,b;
	Tline(){
		a=b=Tpoint(0,0);
	}
	Tline(Tpoint aa,Tpoint bb){
		a=aa;b=bb;
	}
};
Tline q[N];

struct Tway 
{   
	int to;Tway *next;  
};
Tway e[N*N],*prev[N];

void add(int u,int v) 
{   
	e[++top].to=v;e[top].next=prev[u];prev[u]=&e[top];  
}

Tpoint operator +(Tpoint A,Tpoint B){   
	return Tpoint(A.x+B.x,A.y+B.y); 
}

Tpoint operator -(Tpoint A,Tpoint B){
	return Tpoint(A.x-B.x,A.y-B.y); 
}

double operator *(Tpoint A,Tpoint B){   
	return A.x*B.y-A.y*B.x; 
}

bool operator !=(Tpoint A,Tpoint B){   
	return A.x!=B.x || A.y!=B.y;  
}

bool operator ==(Tpoint A,Tpoint B){   
	return A.x==B.x && A.y==B.y;  
}

int sqr(int x){   
	return x*x; 
}

int unit(int x){   
	return !x?0:(x>0?1:-1); 
}

bool inter(Tpoint a,Tpoint b,Tpoint c,Tpoint d)  
{   
	return (unit((b-a)*(c-a))*unit((b-a)*(d-a))<0) &&
		(unit((d-c)*(a-c))*unit((d-c)*(b-c))<0);    
}

int main()
{
	freopen("BZOJ4427.in","r",stdin);
	freopen("BZOJ4427.out","w",stdout);
	
	scanf("%d%d",&n,&m);
	int w,x,y;
    for(int i=1;i<=n;++i)
		scanf("%d%d",&x,&y),s[i]=Tpoint(x,y);
    for(int i=1;i<=m;++i)
		scanf("%d%d%d",&w,&x,&y),q[i].b=Tpoint(x,y),q[i].a=s[w];
    for(int i=1;i<=m;++i)  
		for(int j=i+1;j<=m;++j)
        	if((inter(q[i].a,q[i].b,q[j].a,q[j].b) || q[i].b==q[j].b) &&
					(q[i].a!=q[j].b&&q[i].b!=q[j].a  && q[i].a!=q[j].a)) 
						add(i,j),add(j,i);					

    for(int i=1;i<=m;++i)
    {
        if(col[i]) 
			continue;
        qs.push(i);col[i]=1;
        while (!qs.empty())
        {
            int x=qs.front();qs.pop();
            for(Tway *i=prev[x];i;i=i->next)
                if(col[i->to]==col[x]) 
					return puts("impossible"),0;
                else    
				if(!col[i->to])    
					col[i->to]=col[x]==1?2:1,qs.push(i->to);
        }
    }
    puts("possible");
	
	return 0;
}
