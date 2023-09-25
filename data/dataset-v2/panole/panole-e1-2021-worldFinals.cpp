#include<bits/stdc++.h>
using namespace std;

const long long inf=1000000000000000000ll;
long long l,r,mid,ans,A,B,nw[61],nww[61];
int T,n,L[61],R[61];

struct mat
{
	long long a[61][61];
	mat()
	{
		for (int i=0; i<=n; i++)
			for (int j=0; j<=n; j++) a[i][j]=0;
	}
	mat operator *(const mat &A)
	{
		mat B;
		for (int i=0; i<=n; i++)
			for (int j=0; j<=n; j++)
				for (int k=0; k<=n; k++) if (A.a[j][k])
					B.a[i][k]=(a[i][j]>(inf-B.a[i][k])/A.a[j][k]?inf:a[i][j]*A.a[j][k]+B.a[i][k]);
		return B;
	}
}a[70];

int main()
{
	scanf("%d",&T);
	for (int TT=1; TT<=T; TT++)
	{
		printf("Case #%d: ",TT);
		scanf("%d%lld%lld",&n,&A,&B);
		a[0]=mat();
		for (int i=0; i<=n; i++) a[0].a[i][0]=1;
		for (int i=1; i<=n; i++) scanf("%d",&L[i]),a[0].a[i][L[i]]++;
		for (int i=1; i<=n; i++) scanf("%d",&R[i]),a[0].a[i][R[i]]++;
		for (int i=1; i<=60; i++) a[i]=(a[i-1]*a[i-1]);
		memset(nw,0,sizeof(nw));
		nw[1]=1;
		long long dep=0;
		for (int i=60; i>=0; i--)
		{
			memset(nww,0,sizeof(nww));
			for (int j=0; j<=n; j++) if (nw[j])
				for (int k=0; k<=n; k++)
					nww[k]=(a[i].a[j][k]>(inf-nww[k])/nw[j]?inf:nw[j]*a[i].a[j][k]+nww[k]);
			long long ans=0;
			for (int j=0; j<=n; j++) ans=min(ans+nww[j],inf);
			if (ans<B) dep+=(1ll<<i),memcpy(nw,nww,sizeof(nw));
		}
		printf("%lld\n",dep+1);
	}
	return 0;
}