#include<bits/stdc++.h>
using namespace std;

int T,n,cnt[10];
long long mi[20],ans;
char s[40];

void check(bool bo,int len)
{
	long long nw;
	int Cnt[10];
	for (int i=0; i<10; i++) Cnt[i]=cnt[i];
	for (int I=bo; I<10; I++) if (cnt[I])
		for (int j=I+1; j<10; j++) if (cnt[j])
		{
			cnt[I]--,cnt[j]--,nw=(j-I)*mi[--len];
			int len1=len,len2=len;
			for (int i=9; i>=0&&len2; i--) 
				while (len2&&cnt[i])
				{
					len2--,cnt[i]--;
					nw-=mi[len2]*i;
				}
			for (int i=0; i<10; i++) while (cnt[i]) nw+=mi[--len1]*i,cnt[i]--;
			if (nw<ans) ans=nw;
			for (int k=0; k<10; k++) cnt[k]=Cnt[k];
			len++;
		}
}

void dfs(int x,int len)
{
	if (x==-1) {check(0,len); return;}
	if (x==0&&len*2==n) {check(1,len); return;}
	for (int i=0; i<=cnt[x]/2; i++) cnt[x]-=i*2,dfs(x-1,len-i),cnt[x]+=i*2;
}

int main()
{
	mi[0]=1;
	for (int i=1 ;i<=18; i++) mi[i]=10ll*mi[i-1];
	scanf("%d",&T);
	for (int TT=1; TT<=T; TT++)
	{
		printf("Case #%d: ",TT);
		scanf("%s",s),n=strlen(s);
		memset(cnt,0,sizeof(cnt));
		for (int i=1; i<=n; i++) cnt[s[i-1]-'0']++;
		bool bo=0;
		for (int i=0; i<10; i++) if (cnt[i]&1) bo=1;
		if (!bo) {puts("0"); continue;}
		int len1=(n+1)/2,len2=n-len1;
		if (len1>len2)
		{
			for (int i=1; i<10; i++) if (cnt[i]>0) {cnt[i]--; ans=mi[--len1]*i; break;}
			for (int i=9; i>=0&&len2; i--) 
				while (len2&&cnt[i])
				{
					len2--,cnt[i]--;
					ans-=mi[len2]*i;
				}
			for (int i=0; i<10; i++) while (cnt[i]) ans+=mi[--len1]*i,cnt[i]--;
			printf("%lld\n",ans);
			continue;
		}
		ans=mi[18]*9;
		dfs(9,len1);
		printf("%lld\n",ans);
	}
	return 0;
}