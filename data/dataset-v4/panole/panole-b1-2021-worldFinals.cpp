#include<bits/stdc++.h>
using namespace std;

int n,m,q,cntx[30010],cnty[30010],Cntx,Cnty,l,r,d,T,x[300010],y[300010],e;
map<pair<int,int>,int> ma;
char s[3];

int main()
{
	scanf("%d",&T);
	for (int TT=1; TT<=T; TT++)
	{
		printf("Case #%d: ",TT);
		scanf("%d%d%d",&n,&m,&q),ma.clear();
		for (int i=1 ;i<=m; i++) scanf("%d%d",&x[i],&y[i]),ma[make_pair(x[i],y[i])]=i;
		for (int i=1; i<=n; i++) cntx[i]=cnty[i]=0;
		Cntx=Cnty=n,e=0;
		while (q--)
		{
			scanf("%s",s);
			scanf("%d%d%d",&l,&r,&d);
			if (l%d!=0) l+=d-l%d;
			if (s[0]=='E')
			{
				for (int i=l; i<=r; i+=d) 
					Cntx-=!cntx[x[i]],cntx[x[i]]++,Cnty-=!cnty[y[i]],cnty[y[i]]++,e++;
			} else
			{
				for (int i=l; i<=r; i+=d)
					cntx[x[i]]--,Cntx+=!cntx[x[i]],cnty[y[i]]--,Cnty+=!cnty[y[i]],e--;
			}
			if (e==n-1&&Cntx==1&&Cnty==1)
			{
				int px,py;
				for (int i=1; i<=n; i++) 
				{
					if (!cntx[i]) px=i;
					if (!cnty[i]) py=i;
				}
				int ans=ma[make_pair(px,py)];
				if (ans) printf("%d ",ans); else printf("X ");
			} else printf("X ");
		}
		puts("");
	}
	return 0;
}