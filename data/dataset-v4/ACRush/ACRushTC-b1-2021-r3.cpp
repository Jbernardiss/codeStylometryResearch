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

int64 solve_one_case()
{
	int n,m;
	cin>>n>>m;
	VI s(m),t(m);
	REP(i,m) cin>>s[i]>>t[i];
	VI a(n);
	REP(i,n) { cin>>a[i]; --a[i]; }
	int64 ret=0;
	REP(i,n)
	{
		VI c(m);
		int bad=0;
		REP(l,n-1)
		{
			int w=a[(i+l)%n];
			if (c[w]>0 && (c[w]<s[w] || c[w]>t[w])) --bad;
			++c[w];
			if (c[w]>0 && (c[w]<s[w] || c[w]>t[w])) ++bad;
			if (l>0 && bad==0) ++ret;
		}
	}
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
		int64 ret=solve_one_case();
		printf("Case #%d: %lld\n",case_id,ret);
	}
	return 0;
}

