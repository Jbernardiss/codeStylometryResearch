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

int n;
int tab[nax][2];
vi wcho[nax];

vi spina[nax];

int sto[nax];

void nope()
{
	printf("IMPOSSIBLE\n");
}

const int dost=13;
string bierz="ACDEHIJKMORST";

vi kol;
int wyn[nax];
int zak[dost];

void test()
{
	scanf("%d", &n);
	for (int i=1; i<=n; i++)
		wcho[i].clear();
	for (int h=0; h<2; h++)
		for (int i=1; i<=n; i++)
			scanf("%d", &tab[i][h]);
	for (int i=1; i<=n; i++)
		for (int j=0; j<2; j++)
			wcho[tab[i][j]].push_back(i);
	for (int i=1; i<=n; i++)
	{
		for (int a=0; a<2; a++)
		{
			for (int b=0; b<2; b++)
			{
				if (tab[tab[i][a]][b]==i)
				{
					nope();
					return;
				}
			}
		}
	}
	kol.clear();
	for (int i=1; i<=n; i++)
	{
		spina[i].clear();
		for (int a=0; a<2; a++)
			spina[i].push_back(tab[i][a]);
		for (int a=0; a<2; a++)
			for (int b=0; b<2; b++)
				spina[i].push_back(tab[tab[i][a]][b]);
		for (int j : wcho[i])
		{
			spina[i].push_back(j);
			for (int l : wcho[j])
				spina[i].push_back(l);
		}
		sort(spina[i].begin(), spina[i].end());
		spina[i].resize(unique(spina[i].begin(), spina[i].end())-spina[i].begin());
		sto[i]=spina[i].size();
	}
	for (int i=1; i<=n; i++)
	{
		if (sto[i]<dost)
			kol.push_back(i);
	}
	for (int i=0; i<n; i++)
	{
		assert((int)kol.size()>i);
		int v=kol[i];
		for (int j : spina[v])
		{
			sto[j]--;
			if (sto[j]+1==dost)
				kol.push_back(j);
		}
	}
	reverse(kol.begin(), kol.end());
	for (int i=1; i<=n; i++)
		wyn[i]=-1;
	for (int i : kol)
	{
		for (int j=0; j<dost; j++)
			zak[j]=0;
		for (int j : spina[i])
			if (wyn[j]>=0)
				zak[wyn[j]]=1;
		wyn[i]=0;
		while(zak[wyn[i]])
			wyn[i]++;
	}
	for (int i=1; i<=n; i++)
		printf("%c", bierz[wyn[i]]);
	printf("\n");
}

int main()
{
	int t;
	scanf("%d", &t);
	for (int i=1; i<=t; i++)
	{
		printf("Case #%d: ", i);
		test();
		fflush(stdout);
	}
	return 0;
}
