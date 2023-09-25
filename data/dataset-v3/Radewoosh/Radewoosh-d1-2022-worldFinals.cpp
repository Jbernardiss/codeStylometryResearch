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
const int nax=5007;
const int vax=107;
const ll mod=1000*1000*1000+7;

int n;

char wcz[nax];
int tab[nax];

int jest[nax];

int pasuje(int w, int poz)
{
	if (w && wcz[poz]=='.')
		return 0;
	if (!w && wcz[poz]=='C')
		return 0;
	return 1;
}

int czas;
int ost[vax][nax];
ll dp[vax][nax];

ll rek(int v)
{
	if (v==n)
	{
		if (jest[v] && jest[tab[v]])
			return 1;
		return 0;
	}
	int ha=0;
	for (int i=max(1, v-5); i<=min(n, v+5); i++)
		ha=2*ha+jest[i];
	if (ost[v][ha]==czas)
		return dp[v][ha];
	ll ret=0;
	int g=v+6;
	for (int h=0; h<2; h++)
	{
		if (pasuje(h, g))
		{
			jest[g]=h;
			if (jest[v] && !jest[tab[v]])
			{
				jest[v]=0;
				jest[tab[v]]=1;
				ret+=rek(v+1);
				jest[v]=1;
				jest[tab[v]]=0;
			}
			else
			{
				ret+=rek(v+1);
			}
		}
	}
	jest[g]=-1;
	ost[v][ha]=czas;
	return dp[v][ha]=ret%mod;
}

void test()
{
	scanf("%d", &n);
	scanf("%s", wcz+1);
	for (int i=1; i<=n; i++)
		scanf("%d", &tab[i]);
	for (int i=n+1; i<=n+10; i++)
		wcz[i]='C';
	for (int i=1; i<=n; i++)
		jest[i]=-1;
	int r=min(n, 6);
	ll wyn=0;
	czas++;
	for (int i=0; i<(1<<r); i++)
	{
		int ok=1;
		for (int j=1; j<=r; j++)
		{
			int w=(i>>(j-1))&1;
			if (!pasuje(w, j))
				ok=0;
			jest[j]=w;
		}
		if (ok)
			wyn+=rek(1);
	}
	wyn%=mod;
	printf("%lld\n", wyn);
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
