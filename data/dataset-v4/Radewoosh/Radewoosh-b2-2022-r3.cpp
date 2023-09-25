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
const int nax=1200*1007;
const int n1=(1<<18);
const int inf=1e9;

int n, c;

pii ogr[nax];
int tab[nax];

pii pod[nax];
int narz[nax];

vi wek[nax];

pii daj(int v)
{
	return {pod[v].first+narz[v], pod[v].second};
}

pii lacz(pii a, pii b)
{
	if (a.first==b.first)
		return {a.first, a.second+b.second};
	return min(a, b);
}

void upd(int v)
{
	pod[v]=lacz(daj(2*v), daj(2*v+1));
}

void pisz(int v, int a, int b, int graa, int grab, int w)
{
	if (a>=graa && b<=grab)
	{
		narz[v]+=w;
		return;
	}
	if (a>grab || b<graa)
	{
		return;
	}
	pisz((v<<1), a, (a+b)>>1, graa, grab, w);
	pisz((v<<1)^1, (a+b+2)>>1, b, graa, grab, w);
	upd(v);
}

int daj_dob()
{
	pii wez=daj(1);
	if (!wez.first)
		return wez.second;
	return 0;
}

void test()
{
	scanf("%d%d", &n, &c);
	for (int i=1; i<=c; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		b++;
		if (!a)
			a++;
		ogr[i]={a, b};
	}
	for (int i=1; i<=n; i++)
		scanf("%d", &tab[i]);
	for (int i=1; i<2*n1; i++)
	{
		pod[i]={0, 0};
		narz[i]=0;
	}
	for (int i=1; i<=n1; i++)
		pod[n1-1+i]={0, 1};
	for (int i=n1-1; i; i--)
		upd(i);
	for (int i=1; i<=c; i++)
		wek[i].clear();
	ll wyn=0;
	for (int i=1; i<=2*n; i++)
	{
		int v=i;
		if (v>n)
			v-=n;
		int kol=tab[v];
		vi &tu=wek[kol];
		{
			int r=tu.size();
			if (r)
				pisz(1, 1, n1, 1, tu[r-1], -1);
			if (r>=ogr[kol].first)
				pisz(1, 1, n1, 1, tu[r-ogr[kol].first], 1);
			if (r>=ogr[kol].second)
				pisz(1, 1, n1, 1, tu[r-ogr[kol].second], -1);
		}
		tu.push_back(i);
		{
			int r=tu.size();
			if (r)
				pisz(1, 1, n1, 1, tu[r-1], 1);
			if (r>=ogr[kol].first)
				pisz(1, 1, n1, 1, tu[r-ogr[kol].first], -1);
			if (r>=ogr[kol].second)
				pisz(1, 1, n1, 1, tu[r-ogr[kol].second], 1);
		}
		if (i>n)
		{
			pisz(1, 1, n1, 1, i-n+1, 1);
			pisz(1, 1, n1, i, n1, 1);
			wyn+=daj_dob();
			pisz(1, 1, n1, 1, i-n+1, -1);
			pisz(1, 1, n1, i, n1, -1);
		}
	}
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
		fflush(stdout);
	}
	return 0;
}
