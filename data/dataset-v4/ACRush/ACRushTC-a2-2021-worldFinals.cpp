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

VI bfs(int n,const vector<VI>& g,int src)
{
	VI d(n,-1);
	d[src]=0;
	VI q;
	q.push_back(src);
	REP(cl,SIZE(q))
	{
		int cur=q[cl];
		for (int next:g[cur]) if (d[next]<0)
		{
			d[next]=d[cur]+1;
			q.push_back(next);
		}
	}
	return d;
}
int solve_one_case()
{
	int n,m,p1,p2;
	cin>>n>>m>>p1>>p2;
	--p1;
	--p2;
	vector<VI> g(n);
	REP(i,m)
	{
		int x,y;
		cin>>x>>y;
		--x; --y;
		g[x].push_back(y);
		g[y].push_back(x);
	}
	VI d(n);
	REP(i,n) d[i]=SIZE(g[i]);
	VI q;
	REP(i,n) if (d[i]<=1) q.push_back(i);
	REP(cl,SIZE(q)) for (int x:g[q[cl]])
	{
		--d[x];
		if (d[x]==1) q.push_back(x);
	}
	VI c(n);
	REP(i,n) c[i]=(d[i]>=2);
	VI d1=bfs(n,g,p1);
	VI d2=bfs(n,g,p2);
	if (d1[p2]<0 || d2[p1]<0) return -1;
	REP(i,n) if (c[i] && d1[i]>=0 && d1[i]<d2[i]) return -1;
	assert(!c[p1]);
	int ret=0;
	REP(i,n) if (!c[i] && d1[i]>=0 && d1[i]<d2[i]) ckmax(ret,d2[i]*2);
	return ret;
}

int main()
{
#ifdef _MSC_VER
	freopen("input.txt","r",stdin);
#endif
	std::ios::sync_with_stdio(false);
	int testcase;
	cin>>testcase;
	FOR(case_id,1,testcase+1)
	{
		int ret=solve_one_case();
		if (ret<0)
			printf("Case #%d: SAFE\n",case_id);
		else
			printf("Case #%d: %d\n",case_id,ret);
	}
	return 0;
}

