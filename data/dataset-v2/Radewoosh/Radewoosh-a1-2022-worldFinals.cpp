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

int n, m, sa, sb;

vi graf[nax];

int odl[nax];
int odl_dru[nax];

int sto[nax];
int drzewowy[nax];

void forever()
{
	printf("SAFE\n");
}

void bfsuj(int v)
{
	for (int i=1; i<=n; i++)
		odl[i]=-1;
	odl[v]=0;
	queue<int> kol;
	kol.push(v);
	while(!kol.empty())
	{
		v=kol.front();
		kol.pop();
		for (int i : graf[v])
		{
			if (odl[i]==-1)
			{
				odl[i]=odl[v]+1;
				kol.push(i);
			}
		}
	}
}

void test()
{
	scanf("%d%d%d%d", &n, &m, &sa, &sb);
	for (int i=1; i<=n; i++)
	{
		graf[i].clear();
	}
	for (int i=1; i<=m; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		graf[a].push_back(b);
		graf[b].push_back(a);
	}
	bfsuj(sb);
	for (int i=1; i<=n; i++)
		odl_dru[i]=odl[i];
	bfsuj(sa);
	if (odl[sb]==-1)
	{
		forever();
		return;
	}
	for (int i=1; i<=n; i++)
	{
		sto[i]=graf[i].size();
		drzewowy[i]=0;
	}
	queue<int> kol;
	for (int i=1; i<=n; i++)
		if (sto[i]<=1)
			kol.push(i);
	while(!kol.empty())
	{
		int v=kol.front();
		kol.pop();
		drzewowy[v]=1;
		for (int i : graf[v])
		{
			sto[i]--;
			if (sto[i]==1)
				kol.push(i);
		}
	}
	for (int i=1; i<=n; i++)
	{
		if (odl[i]>=0 && odl[i]<odl_dru[i] && !drzewowy[i])
		{
			forever();
			return;
		}
	}
	int wyn=0;
	for (int i=1; i<=n; i++)
	{
		if (odl[i]>=0 && odl[i]<odl_dru[i])
			wyn=max(wyn, odl_dru[i]);
	}
	printf("%d\n", 2*wyn);
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
