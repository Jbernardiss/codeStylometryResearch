#include<bits/stdc++.h>
using namespace std;

const int mod=1000000007;
int f[53][65539],g[53][65539],L,n,m,a[53],T,p[53],cnt[65539][53],Cnt[65539][53],lef,Ans[53],C[53][53],S[53],A[53],B[53],D[53];
bool boo[53];

int quickmi(int a,int b)
{
	int t=1;
	for (; b; b>>=1,a=1ll*a*a%mod)
		if (b&1) t=1ll*t*a%mod;
	return t;
}

int calc(int x,int y)
{
	memset(A,0,sizeof(A));
	memset(B,0,sizeof(B));
	memset(D,0,sizeof(D));
	for (int i=0; i<=x; i++) 
	{
		A[i]=C[x][i];
		if ((x-i)&1) A[i]=mod-A[i];
	}
	for (int i=0; i<=y; i++)
	{
		B[i]=C[y][i];
		for (int j=1; j<=y-i; j++) B[i]=1ll*B[i]*(m+1)%mod;
		if (i&1) B[i]=mod-B[i];
	}
	for (int i=0; i<=x; i++)
		for (int j=0; j<=y; j++)
			D[i+j]=(D[i+j]+1ll*A[i]*B[j])%mod;
	int ans=0;
	for (int i=0; i<=x+y; i++) ans=(ans+1ll*S[i]*D[i])%mod;
	return ans;
}

int main()
{
	for (int i=0; i<=50; i++)
	{
		C[i][0]=1;
		for (int j=1; j<=i; j++) C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
	}
	scanf("%d",&T);
	memset(g,-1,sizeof(g));
	for (int TT=1; TT<=T; TT++)
	{
		printf("Case #%d: ",TT);
		scanf("%d%d%d",&n,&m,&L);
		S[0]=m+1;
		for (int i=1; i<=n; i++)
		{
			S[i]=quickmi(m+1,i+1);
			for (int j=0; j<i; j++) S[i]=(S[i]-1ll*C[i+1][j]*S[j])%mod;
			S[i]=1ll*(mod+S[i])*quickmi(i+1,mod-2)%mod;
		}
		S[0]=m;
		memset(boo,0,sizeof(boo)),lef=0;
		for (int i=0; i<(1<<L); i++) scanf("%d",&a[i]),f[i][1]=1,f[i][0]=0,boo[a[i]]=1;
		for (int i=1; i<=n; i++) if (!boo[i]) lef++;
		for (int i=1; i<=n; i++) p[i]=-1;
		for (int i=1; i<L; i++)
		{
			for (int I=(1<<i-1),j=0; j<(1<<L); j+=(I<<1))
			{
				for (int k=j; k<j+I; k++) p[a[k]]=k-j;
				for (int k=0; k<(1<<I); k++) if (f[j][k]!=-1)
					for (int l=0; l<(1<<I); l++) if (f[j+I][l]!=-1)
					{
						bool bo=1;
						for (int m=j+I; m<j+I+I; m++)
							if (p[a[m]]!=-1&&(1&(k>>p[a[m]]))!=(1&(l>>m-j-I))) {bo=0; break;}
						if (bo)
						{
							if (((L-i)&1)&&(!f[j][k]||!f[j+I][l])) g[j][k|(l<<I)]=0; else
							if (!((L-i)&1)&&(!f[j][k]&&!f[j+I][l])) g[j][k|(l<<I)]=0; else
							g[j][k|(l<<I)]=1;
						}
					}
				for (int k=j; k<j+I; k++) p[a[k]]=-1;
			}
			for (int j=0,I=(1<<i); j<(1<<L); j+=I)
				for (int k=0; k<(1<<I); k++) f[j][k]=g[j][k],g[j][k]=-1;
		}
		int P=(1<<L-1);
		memset(boo,0,sizeof(boo));
		for (int k=0; k<P; k++) p[a[k]]=k,boo[a[k]]=1;
		for (int i=0; i<(1<<(1<<L-1)); i++)
			for (int j=0; j<=P; j++) cnt[i][j]=Cnt[i][j]=0;
		for (int i=0; i<(1<<(1<<L-1)); i++) 
			if (f[P][i]!=-1)
			{
				int c=0;
				for (int j=P; j<2*P; j++) 
					if (1&(i>>(j-P))) 
					{
						if (!boo[a[j]]) boo[a[j]]=1,c++;
					}
				Cnt[i][c]=1;
				if (f[P][i]) cnt[i][c]=1;
				memset(boo,0,sizeof(boo));
				for (int j=0; j<P; j++) boo[a[j]]=1;
			}
		for (int i=0; i<P; i++) if (!boo[a[i+P]])
			for (int j=0; j<(1<<(1<<L-1)); j++) if ((j>>i)&1)
				for (int k=0; k<=P; k++)
					cnt[j][k]+=cnt[j^(1<<i)][k],
					Cnt[j][k]+=Cnt[j^(1<<i)][k];
		memset(Ans,0,sizeof(Ans));
		for (int i=0; i<(1<<(1<<L-1)); i++) if (f[0][i]!=-1)
		{
			int nw=(1<<P)-1;
			for (int j=P; j<2*P; j++) if (p[a[j]]!=-1&&!((i>>p[a[j]])&1)) nw^=(1<<j-P);
			memset(boo,0,sizeof(boo));
			int c=0;
			for (int j=0; j<P; j++)
				if (1&(i>>j))
				{
					if (!boo[a[j]]) boo[a[j]]=1,c++;
				}
			for (int j=0; j<=P; j++)
				if (f[0][i]==0) Ans[c+j]=(Ans[c+j]+cnt[nw][j])%mod;
				else Ans[c+j]=(Ans[c+j]+Cnt[nw][j])%mod;
		}
		int ans=0;
		for (int i=0; i<=n-lef; i++)
			ans=(ans+1ll*Ans[i]*calc(n-lef-i,i))%mod;
		for (int i=1; i<=lef; i++) ans=1ll*ans*m%mod;
		printf("%d\n",ans);
	}
	return 0;
}