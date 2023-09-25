#include<bits/stdc++.h>
using namespace std;

const int mod=1000000007;
int T,D,n,a[100010],f[100010][2],val[1000010][2],m2,m5,Mi[100010],sum0;
unsigned long long mi[19];
char str[100010];

inline void add(int &x,int y) {x=(x+y>=mod?x+y-mod:x+y);}

int main()
{
	mi[0]=1;
	for (int i=1; i<=18; i++) mi[i]=mi[i-1]*10;
	scanf("%d",&T);
	for (int TT=1; TT<=T; TT++)
	{
		printf("Case #%d: ",TT),m2=m5=1;
		scanf("%s",str),n=strlen(str),scanf("%d",&D);
		while (D%2==0) m2*=2,D/=2;
		while (D%5==0) m5*=5,D/=5;
		Mi[0]=1%D;
		for (int i=1; i<=n; i++) Mi[i]=10*Mi[i-1]%D;
		for (int i=0; i<D; i++) val[i][0]=val[i][1]=0;
		for (int i=0; i<n; i++) a[i+1]=str[i]-'0';
		f[0][1]=0,f[0][0]=1,sum0=1;
		for (int i=1,pre=0,pre19=0; i<=n; i++)
		{
			pre=(pre*10+a[i])%D;
			bool bo=0;
			f[i][0]=f[i][1]=0;
			unsigned long long nw=0;
			for (int j=i; j>=i-18&&j; j--)
			{
				nw+=mi[i-j]*a[j];
				if (nw%m2==0&&nw%m5==0&&nw%D==0) add(f[i][0],f[j-1][0]),add(f[i][0],f[j-1][1]),add(f[i][1],mod-f[j-1][0]);
				if (nw%m2==0&&nw%m5==0) bo=1; else bo=0;
			}
			if (bo) 
			{
				int p=1ll*Mi[n-i]*pre%D;
				add(f[i][0],val[p][0]),add(f[i][0],val[p][1]),add(f[i][1],mod-val[p][0]);
			}
			add(f[i][1],sum0);
			add(sum0,f[i][0]);
			if (i>=19)
			{
				if (i-19>0) pre19=(pre19*10+a[i-19])%D;
				int p=1ll*Mi[n-(i-19)]*pre19%D;
				add(val[p][0],f[i-19][0]),add(val[p][1],f[i-19][1]);
			}
		}
		add(f[n][0],f[n][1]);
		printf("%d\n",f[n][0]);
	}
	return 0;
}

//f[i][0]=f[satis][0]+f[satis][1]
//f[i][1]=f[any][0]-f[satis][0]