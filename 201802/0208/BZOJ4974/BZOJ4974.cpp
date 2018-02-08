#include<bits/stdc++.h>
using namespace std;

const int N=1e5+10;
int nxt[N];
int ch[N];

int read()
{
	int re=0;
	char ch='`';
	while (ch<'0'||ch>'9') ch=getchar();
	while (ch>='0'&&ch<='9')
	{
		re=re*10+ch-'0';
		ch=getchar();
	}
	return re;
}

int main()
{
	freopen("BZOJ4974.in","r",stdin);
	freopen("BZOJ4974.out","w",stdout);
	
	int n=read();
	for (int i=0;i<n;i++)
		nxt[i]=i-read();
		
	ch[0]=0;
	for (int i=1;i<n;i++)
	{
		for (int j=0;j<26;j++)
		{
			int k=nxt[i-1];
			ch[i]=j;
			while (k!=-1&&ch[i]!=ch[k+1]) k=nxt[k];
			if (ch[i]==ch[k+1]) k++;
			if (k==nxt[i])
				break;
		}
	}
	
	for (int i=0;i<n;i++)
		printf("%c",(char)ch[i]+'a');
	printf("\n"); 
		
	return 0;
} 

