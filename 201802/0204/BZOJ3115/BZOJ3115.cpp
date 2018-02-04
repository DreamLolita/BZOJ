#include<bits/stdc++.h>
using namespace std;

const int N=50010;
const int S=256;
const int K=120;  
const char cla[K][10]=  
{  
     "h", "he", "li", "be",  "b",  "c",  "n",  "o",  "f", "ne",  
    "na", "mg", "al", "si",  "p",  "s", "cl", "ar",  "k", "ca",  
    "sc", "ti",  "v", "cr", "mn", "fe", "co", "ni", "cu", "zn",  
    "ga", "ge", "as", "se", "br", "kr", "rb", "sr",  "y", "zr",  
    "nb", "mo", "tc", "ru", "rh", "pd", "ag", "cd", "in", "sn",  
    "sb", "te",  "i", "xe", "cs", "ba", "hf", "ta",  "w", "re",  
    "os", "ir", "pt", "au", "hg", "tl", "pb", "bi", "po", "at",  
    "rn", "fr", "ra", "rf", "db", "sg", "bh", "hs", "mt", "ds",  
    "rg", "cn", "fl", "lv", "la", "ce", "pr", "nd", "pm", "sm",  
    "eu", "gd", "tb", "dy", "ho", "er", "tm", "yb", "lu", "ac",  
    "th", "pa",  "u", "np", "pu", "am", "cm", "bk", "cf", "es",  
    "fm", "md", "no", "lr"  
};  

int T,n;
char s[N];
bool f[N],a[S][S];

void init()
{
	for(int i=0;i<K;++i)
		a[(int)cla[i][0]][(int)cla[i][1]]=1;
}

int main()
{
//	freopen("BZOJ3115.in","r",stdin);
//	freopen("BZOJ3115.out","w",stdout);
	
	init();
	scanf("%d",&T);
	while(T--)
	{
		memset(f,0,sizeof(f));
		scanf("%s",s+1);
		n=strlen(s+1);
		
		f[0]=1;
		for(int i=1;i<=n;++i)
		{
			if(i>1)
				f[i]|=a[(int)s[i-1]][(int)s[i]]&f[i-2];
			f[i]|=a[(int)s[i]][0]&f[i-1];
		}
		puts(f[n]?"YES":"NO");
	}
	
	return 0;
}
