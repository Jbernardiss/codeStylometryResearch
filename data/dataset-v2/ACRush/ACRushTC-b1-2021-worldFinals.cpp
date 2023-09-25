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

struct Event
{
	int x;
	int y;
	int t;
};
struct Claim
{
	int claimer;
	int target;
	Event event;
};
int ck(const Event& a,const Event& b)
{
	int64 dt=abs(a.t-b.t);
	int64 dx=abs(a.x-b.x);
	int64 dy=abs(a.y-b.y);
	return sqr(dx)+sqr(dy)<=sqr(dt);
}

int solve_one_case()
{
	int n;
	int m;
	int h;
	cin>>n>>m>>h;
	vector<Event> duck_events(m);
	REP(i,m)
	{
		auto& d=duck_events[i];
		cin>>d.x>>d.y>>d.t;
	}
	vector<Claim> c(h);
	REP(i,h)
	{
		auto& w=c[i];
		cin>>w.claimer;
		cin>>w.target;
		--w.claimer;
		--w.target;
		auto& e=w.event;
		cin>>e.x>>e.y>>e.t;
	}
	{
		VI is_duck(n);
		REP(round,n+h)
		{
			REP(i,h) FOR(j,i+1,h) 
				for (int x:{c[i].claimer,c[i].target}) for (int y:{c[j].claimer,c[j].target})
					if (x==y && !ck(c[i].event,c[j].event))
						is_duck[c[i].claimer]=1;
			REP(i,h)
				if (is_duck[c[i].target])
					REP(j,m)
						if (!ck(c[i].event,duck_events[j]))
							is_duck[c[i].claimer]=1;
		}
		int cnt=0;
		REP(i,n) if (is_duck[i]) ++cnt;
		if (cnt>0) return cnt;
	}

	int ret=n;
	REP(key,n)
	{
		VI is_duck(n);
		is_duck[key]=1;
		REP(round,n+h)
		{
			REP(i,h)
				if (is_duck[c[i].target])
					REP(j,m)
						if (!ck(c[i].event,duck_events[j]))
							is_duck[c[i].claimer]=1;
		}
		int cnt=0;
		REP(i,n) if (is_duck[i]) ++cnt;
		ckmin(ret,cnt);
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
		int ret=solve_one_case();
		printf("Case #%d: %d\n",case_id,ret);
	}
	return 0;
}

