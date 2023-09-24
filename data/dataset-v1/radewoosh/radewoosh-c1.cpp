//~ while (clock()<=69*CLOCKS_PER_SEC)
//~ #pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("O3")
//~ #pragma GCC target ("avx2")
//~ #pragma GCC optimize("Ofast")
//~ #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
//~ #pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

template <typename T>
using ordered_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define sim template < class c
#define ris return * this
#define dor > debug & operator <<
#define eni(x) sim > typename \
  enable_if<sizeof dud<c>(0) x 1, debug&>::type operator<<(c i) {
sim > struct rge { c b, e; };
sim > rge<c> range(c i, c j) { return rge<c>{i, j}; }
sim > auto dud(c* x) -> decltype(cerr << *x, 0);
sim > char dud(...);
struct debug {
#ifdef LOCAL
~debug() { cerr << endl; }
eni(!=) cerr << boolalpha << i; ris; }
eni(==) ris << range(begin(i), end(i)); }
sim, class b dor(pair < b, c > d) {
  ris << "(" << d.first << ", " << d.second << ")";
}
sim dor(rge<c> d) {
  *this << "[";
  for (auto it = d.b; it != d.e; ++it)
    *this << ", " + 2 * (it == d.b) << *it;
  ris << "]";
}
#else
sim dor(const c&) { ris; }
#endif
};
#define imie(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "

#define shandom_ruffle random_shuffle

using ll=long long;
using pii=pair<int,int>;
using pll=pair<ll,ll>;
using vi=vector<int>;
using vll=vector<ll>;
const int nax=1000*1007;
const int inf=1e9;
const int limit=1000*1000;

using T = int;
struct Flow {
  struct E {
    int dest;
    T orig, *lim, *rev;
  };
  int zr, uj, n = 0;
  vector<unique_ptr<T>> ts;
  vector<vector<E>> graf;
  vector<int> ptr, odl;
  void vert(int v) {
    n = max(n, v + 1);
    graf.resize(n);
    ptr.resize(n);
    odl.resize(n);
  }
  bool iszero(T v) {
    return !v; // Zmienić dla doubli.
  }
  void bfs() {
    fill(odl.begin(), odl.end(), 0);
    vector<int> kol = {zr};
    odl[zr] = 1;
    for (int i = 0; i < (int) kol.size(); i++) {
      for (E& e : graf[kol[i]]) {
        if (!odl[e.dest] and !iszero(*e.lim)) {
          odl[e.dest] = odl[kol[i]] + 1;
          kol.push_back(e.dest);
        }
      }
    }
  }
  T dfs(int v, T lim) {
    if (v == uj) return lim;
    T ret = 0, wez;
    for (int& i = ptr[v]; i < (int) graf[v].size(); i++) {
      E& e = graf[v][i];
      if (odl[e.dest] == odl[v] + 1 and !iszero(*e.lim) and
          !iszero(wez = dfs(e.dest, min(*e.lim, lim)))) {
        ret += wez;
        *e.lim -= wez;
        *e.rev += wez;
        lim -= wez;
        if (iszero(lim)) break;
      }
    }
    return ret;
  }
  void add_edge(int u, int v, T lim, bool bi = false /* bidirectional? */) {
    vert(max(u, v));
    T *a = new T(lim), *b = new T(lim * bi);
    ts.emplace_back(a);
    ts.emplace_back(b);
    graf[u].push_back(E{v, lim,      a, b});
    graf[v].push_back(E{u, lim * bi, b, a});
  }
  T dinic(int zr_, int uj_) {
    zr = zr_; uj = uj_;
    vert(max(zr, uj));
    T ret = 0;
    while (true) {
      bfs();
      fill(ptr.begin(), ptr.end(), 0);
      const T sta = dfs(zr, numeric_limits<T>::max());  // Dla doubli można dać
      if (iszero(sta)) break;                           // infinity() zamiast
      ret += sta;                                       // max().
    }
    return ret;
  }
  vector<int> cut() {
    vector<int> ret;
    bfs();
    for (int i = 0; i < n; i++)
      if (odl[i])
        ret.push_back(i);
    return ret;
  }
  map<pair<int, int>, T> get_flowing() {  // Tam gdzie plynie 0 może nie być
    map<pair<int, int>, T> ret;           // krawędzi.
    for (int i = 0; i < n; i++)
      for (E& e : graf[i])
        if (*e.lim < e.orig)
          ret[make_pair(i, e.dest)] += e.orig - *e.lim;
    for (auto& i : ret) {
      const pair<int, int> rev{i.first.second, i.first.first};
      const T x = min(i.second, ret[rev]);
      i.second -= x;
      ret[rev] -= x;
    }
    return ret;
  }
};

int n, m;

pii kra[nax];

int ide[nax];
int ode[nax];

vector<pii> graf[nax];
int bylo[nax];

void nope()
{
	printf("IMPOSSIBLE\n");
}

void dfs1(int v)
{
	if (bylo[v])
		return;
	bylo[v]=1;
	for (pii i : graf[v])
		dfs1(i.first);
}

vi stos;

void dfs2(int v)
{
	while(!graf[v].empty())
	{
		int u=graf[v].back().first;
		int id=graf[v].back().second;
		graf[v].pop_back();
		dfs2(u);
		stos.push_back(u);
	}
}

void test()
{
	scanf("%d%d", &n, &m);
	for (int i=1; i<=n; i++)
	{
		ide[i]=ode[i]=0;
		graf[i].clear();
		bylo[i]=0;
	}
	for (int i=1; i<=m; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		ode[a]++;
		ide[b]++;
		kra[i]={a, b};
		graf[a].push_back({b, 0});
	}
	dfs1(1);
	for (int i=1; i<=n; i++)
	{
		if (!bylo[i])
		{
			nope();
			return;
		}
	}
	for (int i=1; i<=n; i++)
		graf[i].clear();
	Flow janusz;
	for (int i=1; i<=m; i++)
		janusz.add_edge(kra[i].first, n+kra[i].second, inf);
	for (int i=1; i<=n; i++)
	{
		if (!ide[i] || !ode[i])
		{
			nope();
			return;
		}
	}
	int sta=0;
	for (int i=1; i<=n; i++)
		sta=max(sta, max(ide[i], ode[i]));
	sta=limit/n;
	for (int i=1; i<=n; i++)
	{
		janusz.add_edge(0, i, sta-ode[i]);
		janusz.add_edge(n+i, n+n+1, sta-ide[i]);
	}
	int jest=m;
	while(sta*n<=limit)
	{
		jest+=janusz.dinic(0, n+n+1);
		//~ debug() << sta*n << " " << jest;
		if (jest==sta*n)
		{
			int id=0;
			for (int i=1; i<=m; i++)
			{
				id++;
				graf[kra[i].first].push_back({kra[i].second, id});
			}
			for (int i=1; i<=n; i++)
			{
				for (auto &j : janusz.graf[i])
				{
					if (j.dest>n)
					{
						for (int l=1; l<=(*j.rev); l++)
						{
							id++;
							graf[i].push_back({j.dest-n, id});
						}
					}
				}
			}
			stos.clear();
			dfs2(1);
			stos.push_back(1);
			printf("%d\n", (int)stos.size());
			reverse(stos.begin(), stos.end());
			//~ debug() << stos;
			for (int i : stos)
				printf("%d ", i);
			printf("\n");
			return;
		}
		for (auto &i : janusz.graf[0])
			(*i.lim)++;
		for (auto &i : janusz.graf[n+n+1])
			(*i.rev)++;
		sta++;
	}
	nope();
	//~ exit(0);
}

int main()
{
	int t;
	scanf("%d", &t);
	for (int i=1; i<=t; i++)
	{
		printf("Case #%d: ", i);
		test();
	}
	return 0;
}
