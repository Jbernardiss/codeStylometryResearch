#include<bits/stdc++.h>
using namespace std;

int T,n,W,x,y,p[110];

int main()
{
	scanf("%d%d%d",&T,&n,&W);
	while (T--)
	{
		bool bo=0;
		printf("1 1\n"),fflush(stdout);
		for (int i=1; i<=2*n; i++) p[i]=0;
		for (int i=1; i<n; i++)
		{
			scanf("%d%d",&x,&y);
			p[x]=y;
			if (x==y)
			{
				int ma=-1,maa;
				for (int i=2; i<=2*n; i++) if (!p[i])
				{
					int cnt=0;
					for (int j=2; j<=2*n; j++) 
						if (p[j]&&((p[j]<i)^(j<i))) cnt++;
					if (cnt>ma) ma=cnt,maa=i;
				}
				p[maa]=maa;
				printf("%d %d\n",maa,maa),fflush(stdout);
			} else
			{
				p[y]=x;
				printf("%d %d\n",y,x),fflush(stdout);
			}
		}
		scanf("%d%d%d",&x,&y,&p[0]);
	}
	return 0;
}