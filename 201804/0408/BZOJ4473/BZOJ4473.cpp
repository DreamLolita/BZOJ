#include<bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
const int N=505;
const ull p1=19260817;
const ull p2=998244353;

int n,k1,k2;
int len1[N],len2[N];
ull f1[N][N],f2[N][N],f3[N][N];//common,LU_RD,LD_RU
ull f4[N][N],f5[N][N],f6[N][N],f7[N][N];//U_D,L_R,90,180
ull mp[N][N],fac1[N],fac2[N];
char ch[N][N];

inline void pre(ull (*f)[N])
{
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
		{
			ull t1=f[i-1][j]*p1,t2=f[i][j-1]*p2;
			ull t3=f[i-1][j-1]*p1*p2;
			f[i][j]+=t1+t2-t3;
		}
}

inline void init()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
	{
		scanf("%s",ch[i]+1);
		for(int j=1;j<=n;++j)
			mp[i][j]=ch[i][j]-'0';
	}
	for(int i=1;i<=n;i+=2)
		len1[++k1]=i;
	for(int i=2;i<=n;i+=2)
		len2[++k2]=i;
	
	fac1[0]=fac2[0]=1;
	for(int i=1;i<=n;++i)
		fac1[i]=fac1[i-1]*p1,fac2[i]=fac2[i-1]*p2;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
		{
			f1[i][j]=mp[i][j];
			f2[j][i]=f3[n-j+1][n-i+1]=mp[i][j];
			f4[n-i+1][j]=f5[i][n-j+1]=mp[i][j];
			f6[j][n-i+1]=f7[n-i+1][n-j+1]=mp[i][j];
		}
	pre(f1);pre(f2);pre(f3);
	pre(f4);pre(f5);pre(f6);pre(f7);
}

inline ull get_hash(ull (*a)[N],int x,int y,int len)
{
	int r,c;
	ull t1,t2,t3;
	r=x+len-1;c=y+len-1;
	t1=a[x-1][c]*fac1[len];t2=a[r][y-1]*fac2[len];
	t3=a[x-1][y-1]*fac1[len]*fac2[len];
	return a[r][c]-t1-t2+t3;
}

inline bool check(ull (*a)[N],int lx,int ly,ull (*b)[N],int rx,int ry,int len)
{
	ull ret1=get_hash(a,lx,ly,len);
	ull ret2=get_hash(b,rx,ry,len);
	return ret1==ret2;
}

inline bool check_common(int x,int y,int len)
{
	int r=x+len-1,c=y+len-1;
	return check(f1,x,y,f2,y,x,len) || check(f1,x,y,f3,n-c+1,n-r+1,len) 
			|| check(f1,x,y,f4,n-r+1,y,len) || check(f1,x,y,f5,x,n-c+1,len);
}

inline bool check_90(int x,int y,int len)
{
	int r=x+len-1,c=y+len-1;
	return check(f1,x,y,f6,y,n-r+1,len);
}

inline bool check_180(int x,int y,int len)
{
	int r=x+len-1,c=y+len-1;
	return check(f1,x,y,f7,n-r+1,n-c+1,len);
}

inline bool test_common(int len)
{
	if(!len || len>n)
		return false;
	if(len==1)
		return true;
	int m=n-len+1;
	for(int i=1;i<=m;++i)
		for(int j=1;j<=m;++j)
			if(check_common(i,j,len))
				return true;
	return false;
}

inline bool test_4(int len)
{
	int m=n-len+1;
	for(int i=1;i<=m;++i)
		for(int j=1;j<=m;++j)
			if(check_180(i,j,len) && check_common(i,j,len))
				return true;
	return false;
}

inline bool test_8(int len)
{
	int m=n-len+1;
	for(int i=1;i<=m;++i)
		for(int j=1;j<=m;++j)
			if(check_90(i,j,len) && check_common(i,j,len))
				return true;
	return false;
}

inline bool test_90(int len)
{
	int m=n-len+1;
	for(int i=1;i<=m;++i)
		for(int j=1;j<=m;++j)
			if(check_90(i,j,len))
				return true;
	return false;
}

inline bool test_180(int len)
{
	int m=n-len+1;
	for(int i=1;i<=m;++i)
		for(int j=1;j<=m;++j)
			if(check_180(i,j,len))
				return true;
	return false;
}

inline int solve_4()
{
	int l,r,mid,ans=1;
	l=1;r=k1;
	while(l<=r)
	{
		mid=(l+r)>>1;
		if(test_4(len1[mid]))
			ans=len1[mid],l=mid+1;
		else
			r=mid-1;
	}
	if(!test_4(ans+1))
		return ans;
	l=1;r=k2;
	while(l<=r)
	{
		mid=(l+r)>>1;
		if(test_4(len2[mid]))
			ans=len2[mid],l=mid+1;
		else
			r=mid-1;
	}
	return ans;
}

inline int solve_8()
{
	int l,r,mid,ans=1;
	l=1;r=k1;
	while(l<=r)
	{
		mid=(l+r)>>1;
		if(test_8(len1[mid]))
			ans=len1[mid],l=mid+1;
		else
			r=mid-1;
	}
	if(!test_8(ans+1))
		return ans;
	l=1;r=k2;
	while(l<=r)
	{
		mid=(l+r)>>1;
		if(test_8(len2[mid]))
			ans=len2[mid],l=mid+1;
		else
			r=mid-1;
	}
	return ans;
}

inline int solve_90()
{
	int l,r,mid,ans=1;
	l=1;r=k1;
	while(l<=r)
	{
		mid=(l+r)>>1;
		if(test_90(len1[mid]))
			ans=len1[mid],l=mid+1;
		else
			r=mid-1;
	}
	if(!test_90(ans+1))
		return ans;
	l=1;r=k2;
	while(l<=r)
	{
		mid=(l+r)>>1;
		if(test_90(len2[mid]))
			ans=len2[mid],l=mid+1;
		else
			r=mid-1;
	}
	return ans;
}

inline int solve_180()
{
	int l,r,mid,ans=1;
	l=1;r=k1;
	while(l<=r)
	{
		mid=(l+r)>>1;
		if(test_180(len1[mid]))
			ans=len1[mid],l=mid+1;
		else
			r=mid-1;
	}
	if(!test_180(ans+1))
		return ans;
	l=1;r=k2;
	while(l<=r)
	{
		mid=(l+r)>>1;
		if(test_180(len2[mid]))
			ans=len2[mid],l=mid+1;
		else
			r=mid-1;
	}
	return ans;
}

inline int solve_common()
{
	int l,r,mid,ans=1;
	l=1;r=k1;
	while(l<=r)
	{
		mid=(l+r)>>1;
		if(test_common(len1[mid]))
			ans=len1[mid],l=mid+1;
		else
			r=mid-1;
	}
	if(!test_common(ans+1))
		return ans;
	l=1;r=k2;
	while(l<=r)
	{
		mid=(l+r)>>1;
		if(test_common(len2[mid]))
			ans=len2[mid],l=mid+1;
		else
			r=mid-1;
	}
	return ans;
}

int main()
{
	freopen("BZOJ4473.in","r",stdin);
	freopen("BZOJ4473.out","w",stdout);
	
	init();
	printf("%d %d ",solve_8(),solve_90());
	printf("%d %d %d",solve_4(),solve_180(),solve_common());
	
	return 0;
}
