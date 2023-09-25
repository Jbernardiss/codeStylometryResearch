#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <bits/stdc++.h>

using namespace std;

#define POW2(X) (1<<(X))
#define CKBIT(S,X) (((S)&POW2(X))!=0)
const double pi=acos(-1.0);
const double eps=1e-11;
template<class T> inline void ckmin(T &a,T b){ a=min(a,b); }
template<class T> inline void ckmax(T &a,T b){ a=max(a,b); }
template<class T> inline T sqr(T x){ return x*x; }
#define SIZE(A) ((int)A.size())
#define LENGTH(A) ((int)A.length())
#define MP(A,B) make_pair(A,B)
#define PB(X) push_back(X)
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,a) for(int i=0;i<(a);++i)
#define ALL(A) A.begin(),A.end()
using uint=unsigned int;
using int64=long long;
using uint64=unsigned long long;
using ipair=pair<int,int>;
using VI=vector<int>;
using VD=vector<double>;

VI op(VI a)
{
	int n=SIZE(a);
	REP(i,n) 
	{
		if (i>0) printf(" ");
		printf("%d",a[i]+1);
	}
	printf("\n");
	fflush(stdout);
	int val;
	scanf("%d",&val);
	VI r;
	if (val!=0)
		r.push_back(val);
	else
	{
		r=VI(n);
		REP(i,n) scanf("%d",&r[i]);
	}
	return r;
}

void solve_one_case(int n)
{
	VI a(n);
	REP(i,n) scanf("%d",&a[i]);
	REP(i,n) --a[i];
	int count=0;
	while (1)
	{
		++count;
		int c=0;
		REP(i,n) if (a[i]==i) ++c;
		// fprintf(stderr,"c = %d\n",c);
		VI r(n,-1);
		int cnt=0;
		VI v(n);
		REP(i,n) if (!v[i])
		{
			VI q;
			for (int j=i;!v[j];j=a[j]) v[j]=1,q.push_back(j);
			if (SIZE(q)==1)
			{
				r[q[0]]=(cnt++);
				continue;
			}
			for (int j=0;j<SIZE(q);)
			{
				int s=SIZE(q)-j;
				int c=3;
				if (s==2 || s==4) c=2;
				FOR(k,j,j+c) r[q[k]]=cnt;
				++cnt;
				assert(j+c<=SIZE(q));
				j+=c;
			}
		}
		// REP(i,n) fprintf(stderr,"%d ",r[i]); fprintf(stderr,"\n");
		a=op(r);
		// fprintf(stderr,"SZ = %d\n",SIZE(a));
		if (SIZE(a)<n) 
		{
			if (a[0]<0) exit(0);
			break;
		}
		REP(i,n) --a[i];
	}
	// fprintf(stderr,"DONE %d\n",count);
}

int main()
{
	int testcase;
	int n;
	int k;
	scanf("%d%d%d",&testcase,&n,&k);
	REP(case_id,testcase) solve_one_case(n);
	return 0;
}

