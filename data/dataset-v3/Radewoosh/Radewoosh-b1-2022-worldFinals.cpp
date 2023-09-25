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

int n, m, s;

pll gspo[nax];
ll kspo[nax];

vi graf[nax];
vi farg[nax];

int awi[nax];
int bwi[nax];
pll gdz[nax];
ll kied[nax];

int kaczka[nax];

vi post;
int bylo[nax];

ll odl(pll a, pll b)
{
	ll x=a.first-b.first;
	ll y=a.second-b.second;
	ll ret=x*x+y*y;
	ll w=sqrt(ret);
	while(w*w>ret)
		w--;
	while(w*w<ret)
		w++;
	return w;
}

void kra(int a, int b)
{
	graf[a].push_back(b);
	farg[b].push_back(a);
}

int zgodne(int a, int b)
{
	ll o=odl(gdz[a], gdz[b]);
	ll roz=abs(kied[a]-kied[b]);
	//~ debug() << "kurwa " << imie(o) << imie(roz);
	if (roz<o)
		return 0;
	return 1;
}

void znacz(int v)
{
	if (bylo[v])
		return;
	bylo[v]=1;
	kaczka[v]=1;
	for (int i : graf[v])
		znacz(i);
}

void dfs1(int v)
{
	if (bylo[v])
		return;
	bylo[v]=1;
	for (int i : farg[v])
		dfs1(i);
	post.push_back(v);
}

vi spo[nax];
int spoko[nax];

void dfs2(int v, int li)
{
	if (bylo[v])
		return;
	bylo[v]=li;
	spo[li].push_back(v);
	for (int i : graf[v])
		dfs2(i, li);
}

void test()
{
	scanf("%d%d%d", &n, &m, &s);
	for (int i=1; i<=n; i++)
	{
		graf[i].clear();
		farg[i].clear();
		kaczka[i]=0;
	}
	for (int i=1; i<=m; i++)
	{
		ll x, y, z;
		scanf("%lld%lld%lld", &x, &y, &z);
		gspo[i]={x, y};
		kspo[i]=z;
	}
	for (int i=1; i<=s; i++)
	{
		ll x, y, z;
		scanf("%d%d", &awi[i], &bwi[i]);
		scanf("%lld%lld%lld", &x, &y, &z);
		gdz[i]={x, y};
		kied[i]=z;
		int bsa=1;
		int bsb=m;
		while(bsa<bsb)
		{
			int bss=(bsa+bsb)>>1;
			if (kspo[bss]>=z)
				bsb=bss;
			else
				bsa=bss+1;
		}
		for (int h=max(1, bsa-3); h<=min(m, bsa+3); h++)
		{
			if (odl(gdz[i], gspo[h])>abs(kied[i]-kspo[h]))
			{
				kra(bwi[i], awi[i]);
				break;
			}
		}
	}
	//~ debug();
	//~ for (int i=1; i<=n; i++)
		//~ debug() << i << " " << graf[i];
	for (int i=1; i<=s; i++)
		for (int j=1; j<i; j++)
			if ((awi[i]==awi[j] || awi[i]==bwi[j] || bwi[i]==awi[j] || bwi[i]==bwi[j]) && !zgodne(i, j))
			{
				kaczka[awi[j]]=1;
				//~ debug() << i << " oraz " << j;
			}
	//~ debug() << range(kaczka+1, kaczka+1+n);
	//~ for (int i=1; i<=n)
	
	int ktos=0;
	for (int i=1; i<=n; i++)
		if (kaczka[i])
			ktos=1;
	
	
	if (ktos)
	{
		for (int i=1; i<=n; i++)
			bylo[i]=0;
		for (int i=1; i<=n; i++)
			if (kaczka[i])
				znacz(i);
		int li=0;
		for (int i=1; i<=n; i++)
			li+=kaczka[i];
		printf("%d\n", li);
		return;
	}
	
	post.clear();
	for (int i=1; i<=n; i++)
		bylo[i]=0;
	for (int i=1; i<=n; i++)
		dfs1(i);
	reverse(post.begin(), post.end());
	for (int i=1; i<=n; i++)
		bylo[i]=0;
	int li=0;
	for (int i : post)
	{
		if (!bylo[i])
		{
			li++;
			spo[li].clear();
			spoko[li]=0;
			dfs2(i, li);
		}
	}
	for (int i=1; i<=n; i++)
		for (int j : graf[i])
			if (bylo[i]!=bylo[j])
				spoko[bylo[i]]=1;
	int wyn=n;
	for (int i=1; i<=li; i++)
		if (!spoko[i])
			wyn=min(wyn, (int)spo[i].size());
	printf("%d\n", wyn);
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
