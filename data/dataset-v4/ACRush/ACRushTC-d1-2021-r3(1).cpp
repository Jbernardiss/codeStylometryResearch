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

void dfs(int cur,int prev,int mask,vector<VI>& g,string& ret)
{
	ret.push_back('(');
	for (int next:g[cur]) if (CKBIT(mask,next) && next!=prev) dfs(next,cur,mask,g,ret);
	ret.push_back(')');
}
string encode(int mask,vector<VI>& g)
{
	string ret="";
	REP(i,30) if (CKBIT(mask,i))
	{
		string s;
		dfs(i,-1,mask,g,s);
		if (ret.empty() || s<ret) ret=s;
	}
	return ret;
}

int dfs2(int cur,int mask,VI& visited,vector<VI>& g)
{
	int ret=POW2(cur);
	visited[cur]=1;
	for (int next:g[cur]) if (CKBIT(mask,next) && !visited[next]) ret|=dfs2(next,mask,visited,g);
	return ret;
}
int get_degree(int cur,int mask,vector<VI>& g)
{
	int r=0;
	for (int next:g[cur]) if (CKBIT(mask,next)) ++r;
	return r;
}

map<string,int> sg;
int solve(int mask,vector<VI>& g);
int solve2(int mask,vector<VI>& g)
{
	VI visited(30);
	int ret=0;
	REP(i,30) if (!visited[i] && CKBIT(mask,i))
	{
		int mask2=dfs2(i,mask,visited,g);
		ret^=solve(mask2,g);
	}
	return ret;
}
int solve(int mask,vector<VI>& g)
{
	if (mask==0) return 0;
	string code=encode(mask,g);
	if (sg.count(code)) return sg[code];
	unordered_set<int> s;
	REP(key,30) if (CKBIT(mask,key))
	{
		VI cd1;
		VI cd2;
		for (int next:g[key]) if (CKBIT(mask,next))
		{
			if (get_degree(next,mask,g)==1) 
				cd2.push_back(next);
			else
				cd1.push_back(next);
		}
		REP(set,POW2(SIZE(cd1))) REP(l2,SIZE(cd2)+1)
		{
			int new_mask=mask;
			new_mask^=POW2(key);
			REP(i,SIZE(cd1)) if (CKBIT(set,i)) new_mask^=POW2(cd1[i]);
			REP(i,l2) new_mask^=POW2(cd2[i]);
			s.insert(solve2(new_mask,g));
		}
	}
	int x=0;
	for (;s.count(x);++x);
	return sg[code]=x;
}

int n;
vector<VI> g;

class CRandomMother 
{
public:
   void RandomInit(int seed);
   double Random();
   uint BRandom();
   CRandomMother(int seed) {
      RandomInit(seed);}
protected:
   uint x[5];
};

CRandomMother rnd(1028);

uint CRandomMother::BRandom()
{
  uint64 sum;
  sum = (uint64)2111111111UL * (uint64)x[3] +
     (uint64)1492 * (uint64)(x[2]) +
     (uint64)1776 * (uint64)(x[1]) +
     (uint64)5115 * (uint64)(x[0]) +
     (uint64)x[4];
  x[3] = x[2];  x[2] = x[1];  x[1] = x[0];
  x[4] = (uint)(sum >> 32);                  // Carry
  x[0] = (uint)sum;                          // Low 32 bits of sum
  return x[0];
}

double CRandomMother::Random()
{
   return (double)BRandom() * (1./(65536.*65536.));
}

void CRandomMother::RandomInit (int seed)
{
  int i;
  uint s = seed;
  for (i = 0; i < 5; i++) {
    s = s * 29943829 - 1;
    x[i] = s;
  }
  for (i=0; i<19; i++) BRandom();
}


void prepare()
{
	FOR(seed,1,1000000)
	{
		rnd.RandomInit(seed);
		fprintf(stderr,"seed = %d   cache = %d\n",seed,SIZE(sg));
		srand(seed);
		n=30;
		g=vector<VI>(n);

		const int M=2;
		VI d(n);
		FOR(i,1,n)
		{
			int j=rand()%i;
			if (d[j]+1>M) { --i; continue; }
			d[i]=d[j]+1;
			g[i].push_back(j);
			g[j].push_back(i);
		}
		int xg=solve(POW2(n)-1,g);
		fprintf(stderr,"XG = %d\n",xg);
		if (xg==0) break;
	}
}

void solve_one_game()
{
	int local=0;
#ifdef _MSC_VER
	local=1;
#endif
	int mask=POW2(n)-1;
	while (1)
	{
		// fprintf(stderr,"sg1 = %d\n",solve2(mask,g));

		if (mask==0)
		{
			// fprintf(stderr,"win\n");
			break;
		}

		int play=0;
		if (local)
		{
			int i=rand()%n;
			while (!CKBIT(mask,i)) i=rand()%n;
			play=POW2(i);
		}
		else
		{
			int cnt;
			scanf("%d",&cnt);
			if (cnt<0) exit(0);
			REP(i,cnt)
			{
				int idx;
				scanf("%d",&idx); --idx;
				play|=POW2(idx);
			}
			assert((mask&play)==play);
		}

		mask^=play;
		// fprintf(stderr,"sg2 = %d\n",solve2(mask,g));
		int next_play=-1;
		REP(key,n) if (CKBIT(mask,key))
		{
			if (next_play>=0) break;
			VI cd1;
			VI cd2;
			for (int next:g[key]) if (CKBIT(mask,next))
			{
				if (get_degree(next,mask,g)==1) 
					cd2.push_back(next);
				else
					cd1.push_back(next);
			}
			REP(set,POW2(SIZE(cd1))) REP(l2,SIZE(cd2)+1)
			{
				if (next_play>=0) break;
				int new_mask=mask;
				new_mask^=POW2(key);
				REP(i,SIZE(cd1)) if (CKBIT(set,i)) new_mask^=POW2(cd1[i]);
				REP(i,l2) new_mask^=POW2(cd2[i]);
				int tmp=solve2(new_mask,g);
				if (tmp==0)
				{
					next_play=(mask^new_mask);
					break;
				}
			}
		}
		assert(next_play>=0);
		{
			VI c;
			REP(i,n) if (CKBIT(next_play,i)) c.push_back(i);
			printf("%d\n",SIZE(c));
			fflush(stdout);
			for (int i:c) printf("%d ",i+1);
			printf("\n");
			fflush(stdout);
		}
		mask^=next_play;
	}
}

void solve_one_case()
{
	int n;
	scanf("%d",&n);
	REP(i,n) for (int j:g[i]) if (i<j)
	{
		printf("%d %d\n",i+1,j+1);
		fflush(stdout);
	}
	int num_games;
	scanf("%d",&num_games);
	REP(step,num_games)
	{
		solve_one_game();
	}
}

int main()
{
	prepare();
	int testcase;
	scanf("%d",&testcase);
	REP(case_id,testcase) solve_one_case();
	return 0;
}

