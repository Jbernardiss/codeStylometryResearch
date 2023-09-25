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
using VVI=vector<VI>;

void solve_one_case()
{
	int n;
	cin>>n;
	VI p1(n),p2(n);
	REP(i,n) { cin>>p1[i]; --p1[i]; }
	REP(i,n) { cin>>p2[i]; --p2[i]; }
	vector<VI> g(n);
	auto add=[&](int x,int y) {
		g[x].push_back(y);
		g[y].push_back(x);
	};
	REP(i,n)
	{
		add(i,p1[i]);
		add(i,p2[i]);
		for (int j:{p1[i],p2[i]}) 
		{
			add(i,p1[j]);
			add(i,p2[j]);
		}
	}
	REP(i,n) for (int j:g[i]) if (i==j)
	{
		printf("IMPOSSIBLE\n");
		return;
	}
	VI c(n);
	REP(i,n)
	{
		VI visited(16);
		for (int j:g[i]) if (j<i) visited[c[j]]=1;
		for (c[i]=0;visited[c[i]];++c[i]);
	}
	string rs="ACDEHIJKMORST";
	string ret;
	REP(i,n) ret+=rs[c[i]];
	printf("%s\n",ret.c_str());
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
		printf("Case #%d: ",case_id);
		solve_one_case();
	}
	return 0;
}

