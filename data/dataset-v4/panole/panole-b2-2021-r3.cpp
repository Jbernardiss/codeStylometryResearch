#include<bits/stdc++.h>
	using namespace std;
	
	int n,m,T,a[110],b[110],ans[110][110],id[110];
	
	bool cmp(int x,int y) {return b[x]>b[y];}
	
	int main()
	{
		scanf("%d",&T);
		for (int TT=1; TT<=T; TT++)
		{
			printf("Case #%d: ",TT);
			scanf("%d%d",&n,&m);
			for (int i=1; i<=n; i++) scanf("%d",&a[i]);
			for (int i=1; i<=m; i++) scanf("%d",&b[i]);
			memset(ans,0,sizeof(ans));
			for (int i=1; i<=n; i++)
			{
				for (int k=1; k<=m; k++) id[k]=k;
				sort(id+1,id+1+m,cmp);
				for (int k=1; k<=a[i]; k++) b[id[k]]--,ans[i][id[k]]=1;
			}
			bool hassol=1;
			for (int i=1; i<=m; i++) if (b[i]) {hassol=0; break;}
			if (!hassol) {puts("IMPOSSIBLE"); continue;}
			puts("POSSIBLE");
			while (1)
			{
				bool bo=0;
				for (int i=1; i<n; i++)
				{
					for (int j=1; j<m; j++) if (ans[i][j]==1&&ans[i][j+1]==0)
					{
						for (int k=i+1; k<=n; k++) if (ans[k][j]==0&&ans[k][j+1]==1)
						{
							ans[i][j]=ans[k][j+1]=0;
							ans[i][j+1]=ans[k][j]=1;
							bo=1;
							break;
						}
						if (bo) break;
					}
					if (bo) break;
				}
				if (!bo) break;
			}
			for (int i=1; i<=n; i++,putchar('\n'))
				for (int j=1; j<=m; j++) putchar(ans[i][j]?'/':'\\');
		}
		return 0;
	}