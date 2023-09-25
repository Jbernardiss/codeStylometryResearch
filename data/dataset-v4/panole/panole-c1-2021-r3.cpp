#include<bits/stdc++.h>
using namespace std;

struct P
{
	int x,y;
	long long operator ^(const P& A) {return 1ll*x*A.y-1ll*y*A.x;}
	P operator -(const P& A){return (P){x-A.x,y-A.y};}
}a[110];
int n,T,ans[10010][2],ansn;

int sgn(long long x) {return x>0?1:-1;}

bool inter(P a,P b,P c,P d)
{
	if (sgn((b-c)^(d-c))==sgn((a-c)^(d-c))) return 0;
	if (sgn((c-a)^(b-a))==sgn((d-a)^(b-a))) return 0;
	return 1;
}

int main()
{
	scanf("%d",&T);
	for (int TT=1; TT<=T; TT++)
	{
		printf("Case #%d: ",TT);
		scanf("%d",&n),ansn=0;
		for (int i=1; i<=n; i++) scanf("%d%d",&a[i].x,&a[i].y);
		scanf("%d%d%d%d",&ans[1][0],&ans[1][1],&ans[2][0],&ans[2][1]),ansn=2;
		for (int i=1; i<=n; i++)
			for (int j=i+1; j<=n; j++)
			{
				bool bo=1;
				for (int k=1; k<=ansn; k++)
				{
					if (ans[k][0]>ans[k][1]) swap(ans[k][0],ans[k][1]);
					if (ans[k][0]==i&&ans[k][1]==j) {bo=0; break;}
					if (ans[k][0]==i||ans[k][1]==j||ans[k][0]==j||ans[k][1]==i) continue;
					if (inter(a[i],a[j],a[ans[k][0]],a[ans[k][1]])) 
					{
						bo=0; break;
					}
				}
				if (bo) ans[++ansn][0]=i,ans[ansn][1]=j;
			}
		printf("%d\n",ansn-2);
		for (int i=3; i<=ansn; i++) printf("%d %d\n",ans[i][0],ans[i][1]);
	}
	return 0;
}