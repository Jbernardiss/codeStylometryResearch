#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
using db = long double; // or double, if TL is tight
using str = string; // yay python! 

// pairs
using pi = pair<int,int>;
using pl = pair<ll,ll>;
using pd = pair<db,db>;
#define mp make_pair
#define f first
#define s second

#define tcT template<class T
#define tcTU tcT, class U
// ^ lol this makes everything look weird but I'll try it
tcT> using V = vector<T>; 
tcT, size_t SZ> using AR = array<T,SZ>; 
using vi = V<int>;
using vb = V<bool>;
using vl = V<ll>;
using vd = V<db>;
using vs = V<str>;
using vpi = V<pi>;
using vpl = V<pl>;
using vpd = V<pd>;

// vectors
// oops size(x), rbegin(x), rend(x) need C++17
#define sz(x) int((x).size())
#define bg(x) begin(x)
#define all(x) bg(x), end(x)
#define rall(x) x.rbegin(), x.rend() 
#define sor(x) sort(all(x)) 
#define rsz resize
#define ins insert 
#define pb push_back
#define eb emplace_back
#define ft front()
#define bk back()

#define lb lower_bound
#define ub upper_bound
tcT> int lwb(V<T>& a, const T& b) { return int(lb(all(a),b)-bg(a)); }
tcT> int upb(V<T>& a, const T& b) { return int(ub(all(a),b)-bg(a)); }

// loops
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define rep(a) F0R(_,a)
#define each(a,x) for (auto& a: x)

const int MOD = 1e9+7; // 998244353;
const int MX = 2e5+5;
const ll BIG = 1e18; // not too close to LLONG_MAX
const db PI = acos((db)-1);
const int dx[4]{1,0,-1,0}, dy[4]{0,1,0,-1}; // for every grid problem!!
mt19937 rng(1);
template<class T> using pqg = priority_queue<T,vector<T>,greater<T>>;

// bitwise ops
// also see https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html
constexpr int pct(int x) { return __builtin_popcount(x); } // # of bits set
constexpr int bits(int x) { // assert(x >= 0); // make C++11 compatible until USACO updates ...
	return x == 0 ? 0 : 31-__builtin_clz(x); } // floor(log2(x)) 
constexpr int p2(int x) { return 1<<x; }
constexpr int msk2(int x) { return p2(x)-1; }

ll cdiv(ll a, ll b) { return a/b+((a^b)>0&&a%b); } // divide a by b rounded up
ll fdiv(ll a, ll b) { return a/b-((a^b)<0&&a%b); } // divide a by b rounded down

tcT> bool ckmin(T& a, const T& b) {
	return b < a ? a = b, 1 : 0; } // set a = min(a,b)
tcT> bool ckmax(T& a, const T& b) {
	return a < b ? a = b, 1 : 0; } // set a = max(a,b)

tcTU> T fstTrue(T lo, T hi, U f) {
	++hi; assert(lo <= hi); // assuming f is increasing
	while (lo < hi) { // find first index such that f is true 
		T mid = lo+(hi-lo)/2;
		f(mid) ? hi = mid : lo = mid+1; 
	} 
	return lo;
}
tcTU> T lstTrue(T lo, T hi, U f) {
	--lo; assert(lo <= hi); // assuming f is decreasing
	while (lo < hi) { // find first index such that f is true 
		T mid = lo+(hi-lo+1)/2;
		f(mid) ? lo = mid : hi = mid-1;
	} 
	return lo;
}
tcT> void remDup(vector<T>& v) { // sort and remove duplicates
	sort(all(v)); v.erase(unique(all(v)),end(v)); }
tcTU> void erase(T& t, const U& u) { // don't erase
	auto it = t.find(u); assert(it != end(t));
	t.erase(it); } // element that doesn't exist from (multi)set

#define tcTUU tcT, class ...U

inline namespace Helpers {
	//////////// is_iterable
	// https://stackoverflow.com/questions/13830158/check-if-a-variable-type-is-iterable
	// this gets used only when we can call begin() and end() on that type
	tcT, class = void> struct is_iterable : false_type {};
	tcT> struct is_iterable<T, void_t<decltype(begin(declval<T>())),
	                                  decltype(end(declval<T>()))
	                                 >
	                       > : true_type {};
	tcT> constexpr bool is_iterable_v = is_iterable<T>::value;

	//////////// is_readable
	tcT, class = void> struct is_readable : false_type {};
	tcT> struct is_readable<T,
	        typename std::enable_if_t<
	            is_same_v<decltype(cin >> declval<T&>()), istream&>
	        >
	    > : true_type {};
	tcT> constexpr bool is_readable_v = is_readable<T>::value;

	//////////// is_printable
	// // https://nafe.es/posts/2020-02-29-is-printable/
	tcT, class = void> struct is_printable : false_type {};
	tcT> struct is_printable<T,
	        typename std::enable_if_t<
	            is_same_v<decltype(cout << declval<T>()), ostream&>
	        >
	    > : true_type {};
	tcT> constexpr bool is_printable_v = is_printable<T>::value;
}

inline namespace Input {
	tcT> constexpr bool needs_input_v = !is_readable_v<T> && is_iterable_v<T>;
	tcTUU> void re(T& t, U&... u);
	tcTU> void re(pair<T,U>& p); // pairs

	// re: read
	tcT> typename enable_if<is_readable_v<T>,void>::type re(T& x) { cin >> x; } // default
	tcT> void re(complex<T>& c) { T a,b; re(a,b); c = {a,b}; } // complex
	tcT> typename enable_if<needs_input_v<T>,void>::type re(T& i); // ex. vectors, arrays
	tcTU> void re(pair<T,U>& p) { re(p.f,p.s); }
	tcT> typename enable_if<needs_input_v<T>,void>::type re(T& i) {
		each(x,i) re(x); }
	tcTUU> void re(T& t, U&... u) { re(t); re(u...); } // read multiple

	// rv: resize and read vectors
	void rv(size_t) {}
	tcTUU> void rv(size_t N, V<T>& t, U&... u);
	template<class...U> void rv(size_t, size_t N2, U&... u);
	tcTUU> void rv(size_t N, V<T>& t, U&... u) {
		t.rsz(N); re(t);
		rv(N,u...); }
	template<class...U> void rv(size_t, size_t N2, U&... u) {
		rv(N2,u...); }

	// dumb shortcuts to read in ints
	void decrement() {} // subtract one from each
	tcTUU> void decrement(T& t, U&... u) { --t; decrement(u...); }
	#define ints(...) int __VA_ARGS__; re(__VA_ARGS__);
	#define int1(...) ints(__VA_ARGS__); decrement(__VA_ARGS__);
}

inline namespace ToString {
	tcT> constexpr bool needs_output_v = !is_printable_v<T> && is_iterable_v<T>;

	// ts: string representation to print
	tcT> typename enable_if<is_printable_v<T>,str>::type ts(T v) {
		stringstream ss; ss << fixed << setprecision(15) << v;
		return ss.str(); } // default
	tcT> str bit_vec(T t) { // bit vector to string
		str res = "{"; F0R(i,sz(t)) res += ts(t[i]);
		res += "}"; return res; }
	str ts(V<bool> v) { return bit_vec(v); }
	template<size_t SZ> str ts(bitset<SZ> b) { return bit_vec(b); } // bit vector
	tcTU> str ts(pair<T,U> p); // pairs
	tcT> typename enable_if<needs_output_v<T>,str>::type ts(T v); // vectors, arrays
	tcTU> str ts(pair<T,U> p) { return "{"+ts(p.f)+", "+ts(p.s)+"}"; }
	tcT> typename enable_if<is_iterable_v<T>,str>::type ts_sep(T v, str sep) {
		// convert container to string w/ separator sep
		bool fst = 1; str res = "";
		for (const auto& x: v) {
			if (!fst) res += sep;
			fst = 0; res += ts(x);
		}
		return res;
	}
	tcT> typename enable_if<needs_output_v<T>,str>::type ts(T v) {
		return "{"+ts_sep(v,", ")+"}"; }

	// for nested DS
	template<int, class T> typename enable_if<!needs_output_v<T>,vs>::type 
	  ts_lev(const T& v) { return {ts(v)}; }
	template<int lev, class T> typename enable_if<needs_output_v<T>,vs>::type 
	  ts_lev(const T& v) {
		if (lev == 0 || !sz(v)) return {ts(v)};
		vs res;
		for (const auto& t: v) {
			if (sz(res)) res.bk += ",";
			vs tmp = ts_lev<lev-1>(t);
			res.ins(end(res),all(tmp));
		}
		F0R(i,sz(res)) {
			str bef = " "; if (i == 0) bef = "{";
			res[i] = bef+res[i];
		}
		res.bk += "}";
		return res;
	}
}

inline namespace Output {
	template<class T> void pr_sep(ostream& os, str, const T& t) { os << ts(t); }
	template<class T, class... U> void pr_sep(ostream& os, str sep, const T& t, const U&... u) {
		pr_sep(os,sep,t); os << sep; pr_sep(os,sep,u...); }
	// print w/ no spaces
	template<class ...T> void pr(const T&... t) { pr_sep(cout,"",t...); } 
	// print w/ spaces, end with newline
	void ps() { cout << "\n"; }
	template<class ...T> void ps(const T&... t) { pr_sep(cout," ",t...); ps(); } 
	// debug to cerr
	template<class ...T> void dbg_out(const T&... t) {
		pr_sep(cerr," | ",t...); cerr << endl; }
	void loc_info(int line, str names) {
		cerr << "Line(" << line << ") -> [" << names << "]: "; }
	template<int lev, class T> void dbgl_out(const T& t) {
		cerr << "\n\n" << ts_sep(ts_lev<lev>(t),"\n") << "\n" << endl; }
	#ifdef LOCAL
		#define dbg(...) loc_info(__LINE__,#__VA_ARGS__), dbg_out(__VA_ARGS__)
		#define dbgl(lev,x) loc_info(__LINE__,#x), dbgl_out<lev>(x)
	#else // don't actually submit with this
		#define dbg(...) 0
		#define dbgl(lev,x) 0
	#endif

	const clock_t beg = clock();
	#define dbg_time() dbg((db)(clock()-beg)/CLOCKS_PER_SEC)
}

inline namespace FileIO {
	void setIn(str s)  { freopen(s.c_str(),"r",stdin); }
	void setOut(str s) { freopen(s.c_str(),"w",stdout); }
	void setIO(str s = "") {
		cin.tie(0)->sync_with_stdio(0); // unsync C / C++ I/O streams
		// cin.exceptions(cin.failbit);
		// throws exception when do smth illegal
		// ex. try to read letter into int
		if (sz(s)) setIn(s+".in"), setOut(s+".out"); // for old USACO
	}
}

// nonrooted -> select nim value from rooted
// rooted -> generate all possible nim values

struct Info {
	vi children;
	vi rooted_nim;
	int non_rooted_nim = -1;
	int non_rooted_nim_without = -1;
};

V<Info> tree_info;
map<vi, int> tree_iso;

// OK
int make_rooted(vi children) {
	sor(children);
	if (!tree_iso.count(children)) {
		int label = sz(tree_iso);
		tree_info.pb({children});
		tree_iso[children] = label;
	}
	return tree_iso.at(children);
}

// OK
void fill_adj_list(V<vi>& res, int x, int cur) {
	for (int y: tree_info.at(x).children) {
		int nex = sz(res); res.eb();
		res.at(cur).pb(nex);
		res.at(nex).pb(cur);
		fill_adj_list(res, y, nex);
	}
}

// OK
V<vi> construct_adj_list(int x) {
	V<vi> res; res.eb();
	fill_adj_list(res, x, 0);
	return res;
}

int get_root(const V<vi>& adj, int x, int p) {
	vi res;
	for (int y: adj.at(x)) if (y != p) {
		res.pb(get_root(adj, y, x));
	}
	return make_rooted(res);
}

vi get_roots(int x) {
	V<vi> v = construct_adj_list(x);
	vi roots;
	F0R(i,sz(v)) {
		roots.pb(get_root(v, i, -1));
	}
	sor(roots);
	assert(find(all(roots),x) != end(roots));
	return roots;
}

vi operator+(vi a, vi b) {
	vi res;
	for (int x: a) res.pb(x);
	for (int x: b) res.pb(x);
	remDup(res);
	return res;
}

vi operator*(vi a, vi b) {
	vi res;
	for (int x: a) for (int y: b) res.pb(x^y);
	remDup(res);
	return res;
}

vi rooted_nim(int x);

int non_rooted_nim(int x) {
	if (tree_info.at(x).non_rooted_nim != -1) {
		return tree_info.at(x).non_rooted_nim;
	}
	vi roots = get_roots(x);
	vi res;
	for (int y: roots) {
		res = res+rooted_nim(y);
	}
	set<int> dis(all(res));
	int ans = 0;
	while (dis.count(ans)) ++ans;
	for (int r: roots) {
		tree_info.at(r).non_rooted_nim = ans;
	}
	return ans;
}

int non_rooted_nim_without(int x) {
	if (tree_info.at(x).non_rooted_nim_without != -1) {
		return tree_info.at(x).non_rooted_nim_without;
	}
	int res = 0;
	for (int y: tree_info.at(x).children) {
		res ^= non_rooted_nim(y);
	}
	return tree_info.at(x).non_rooted_nim_without = res;
}

vi rooted_nim(int x) {
	if (sz(tree_info.at(x).rooted_nim)) {
		return tree_info.at(x).rooted_nim;
	}
	vi nim_vals{0};
	for (int y: tree_info.at(x).children) {
		int n0 = non_rooted_nim(y);
		int n1 = non_rooted_nim_without(y);
		nim_vals = nim_vals * vi{n0, n1};
	}
	return tree_info.at(x).rooted_nim = nim_vals;
}


/** 
 * Description: Generate various types of trees.
 * Source: Own + Dhruv Rohatgi
 */

////////////// DISTRIBUTIONS

// return int in [L,R] inclusive
int rng_int(int L, int R) { assert(L <= R); 
	return uniform_int_distribution<int>(L,R)(rng);  }
ll rng_ll(ll L, ll R) { assert(L <= R); 
	return uniform_int_distribution<ll>(L,R)(rng);  }

// return double in [L,R] inclusive
db rng_db(db L, db R) { assert(L <= R);
	return uniform_real_distribution<db>(L,R)(rng); }

// http://cplusplus.com/reference/random/geometric_distribution/geometric_distribution/
// flip a coin which is heads with probability p until you flip heads
// mean value of c is 1/p-1
int rng_geo(db p) { assert(0 < p && p <= 1); // p large -> closer to 0
	return geometric_distribution<int>(p)(rng); }

////////////// VECTORS + PERMS

// shuffle a vector
template<class T> void shuf(vector<T>& v) { shuffle(all(v),rng); }

// generate random permutation of [0,N-1]
vi randPerm(int N) { vi v(N); iota(all(v),0); shuf(v); return v; }

// random permutation of [0,N-1] with first element 0
vi randPermZero(int N) { vi v(N-1); iota(all(v),1);
	shuf(v); v.ins(bg(v),0); return v; }

// shuffle permutation of [0,N-1]
vi shufPerm(vi v) {
	int N = sz(v); vi key = randPerm(N);
	vi res(N); F0R(i,N) res[key[i]] = key[v[i]];
	return res;
}

// vector with all entries in [L,R]
vi rng_vec(int N, int L, int R) {
	vi res; F0R(_,N) res.pb(rng_int(L,R));
	return res;
}

// vector with all entries in [L,R], unique
vi rng_vec_unique(int N, int L, int R) {
	set<int> so_far; vi res;
	F0R(_,N) {
		int x; do { x = rng_int(L,R); } while (so_far.count(x));
		so_far.ins(x); res.pb(x);
	}
	return res;
}

////////////// GRAPHS

// relabel edges ed according to perm, shuffle
vpi relabelAndShuffle(vpi ed, vi perm) {
	each(t,ed) {
		t.f = perm[t.f], t.s = perm[t.s];
		if (rng()&1) swap(t.f,t.s);
	}
	shuf(ed); return ed;
}

// shuffle graph with vertices [0,N-1]
vpi shufGraph(int N, vpi ed) { // randomly swap endpoints, rearrange labels
	return relabelAndShuffle(ed,randPerm(N)); }
vpi shufGraphZero(int N, vpi ed) {
	return relabelAndShuffle(ed,randPermZero(N)); }

// shuffle tree given N-1 edges
vpi shufTree(vpi ed) { return shufGraph(sz(ed)+1,ed); }
// randomly swap endpoints, rearrange labels
vpi shufRootedTree(vpi ed) {
	return relabelAndShuffle(ed,randPermZero(sz(ed)+1)); }

void pgraphOne(int N, vpi ed) {
	ps(N,sz(ed));
	each(e,ed) ps(1+e.f,1+e.s);
}

////////////// GENERATING TREES

// for generating tall tree
pi geoEdge(int i, db p) { assert(i > 0); 
	return {i,max(0,i-1-rng_geo(p))}; }

// generate edges of tree with verts [0,N-1]
// smaller back -> taller tree
vpi treeRand(int N, int back) { 
	assert(N >= 1 && back >= 0); vpi ed; 
	FOR(i,1,N) ed.eb(i,i-1-rng_int(0,min(back,i-1)));
	return ed; }

// generate path
vpi path(int N) { return treeRand(N,0); }

// generate tall tree (large diameter)
// the higher the p the taller the tree
vpi treeTall(int N, db p) { assert(N >= 1); 
	vpi ed; FOR(i,1,N) ed.pb(geoEdge(i,p));
	return ed; }

// generate tall tree, then add rand at end
vpi treeTallShort(int N, db p) { 
	assert(N >= 1); int mid = (N+1)/2;
	vpi ed = treeTall(mid,p); 
	FOR(i,mid,N) ed.eb(i,rng_int(0,i-1));
	return ed; }

// lots of stuff connected to either heavy1 or heavy2
vpi treeTallHeavy(int N, db p) { 
	assert(N >= 1); // + bunch of rand
	vpi ed; int heavy1 = 0, heavy2 = N/2;
	FOR(i,1,N) {
		if(i < N/4) ed.eb(i,heavy1);
		else if (i > heavy2 && i < 3*N/4) ed.eb(i,heavy2);
		else ed.pb(geoEdge(i,p));
	}
	return ed;
}

// heavy tall tree + random
// lots of verts connected to heavy1 or heavy2
vpi treeTallHeavyShort(int N, db p) { 
	assert(N >= 1); // + almost-path + rand
	vpi ed; int heavy1 = 0, heavy2 = N/2;
	FOR(i,1,N) {
		if(i < N/4) ed.eb(i,heavy1);
		else if (i <= heavy2) ed.pb(geoEdge(i,p)); // tall -> heavy1
		else if (i > heavy2 && i < 3*N/4) ed.eb(i,heavy2);
		else ed.eb(i,rng_int(0,i-1));
	}
	return ed;
}

int rand_prime(int l, int r) {
	while(1) {
		int x = rng_int(l,r);
		bool bad = 0;
		for (int i = 2; i*i <= x; ++i) if (x%i == 0) bad = 1;
		if (!bad) return x;
	}
}

int N;
vb marked, vis;
V<vi> adj;

vi comp;
int get_root_vis(int x) {
	// dbg("GET ROOT VIS", x, sz(vis));
	assert(!vis.at(x));
	vis.at(x) = true;
	comp.pb(x);
	vi child;
	for (int y: adj.at(x)) if (!vis.at(y)) {
		child.pb(get_root_vis(y));
	}
	return make_rooted(child);
}

void do_tree(vpi edge) {
	// tree_info.clear();
	// tree_iso.clear();
	// dbg("DO TREE");
	adj = V<vi>(N);
	for (auto [a,b]: edge) {
		adj.at(a).pb(b), adj.at(b).pb(a);
		cout << 1+a << " " << 1+b << endl;
	}
	// exit(0);
	auto get_value = [&]() {
		vis = marked;
		int xo = 0;
		// dbg("OH", N, sz(vis));
		F0R(i,N) if (!vis.at(i)) {
			int r = get_root_vis(i);
			xo ^= non_rooted_nim(r);
		}
		return xo;
	};
	auto get_move = [&]() -> vi {
		// dbg("GET MOVE");
		vis = marked;
		V<vi> comps;
		vi nim_vals;
		F0R(i,N) if (!vis.at(i)) {
			comp.clear();
			int r = get_root_vis(i);
			nim_vals.pb(non_rooted_nim(r));
			comps.pb(comp);
		}
		// dbg(comps);
		// dbg(nim_vals);
		int xo = 0; for (int x: nim_vals) xo ^= x;
		assert(xo > 0);
		int i_comp = 0;
		while ((nim_vals.at(i_comp) ^ xo) >= nim_vals.at(i_comp)) ++i_comp;
		const int desired = nim_vals.at(i_comp) ^ xo;
		for (int c: comps.at(i_comp)) {
			vis = marked;
			assert(!vis.at(c));
			int r = get_root_vis(c);
			vi vals = rooted_nim(r);
			if (find(all(vals), desired) != end(vals)) {
				vis = marked;
				vis.at(c) = true;
				vi as;
				V<AR<int,2>> pairs;
				for (int a: adj.at(c)) if (!vis.at(a)) {
					int ra = get_root_vis(a);
					int xo_no = non_rooted_nim(ra);
					int xo_yes = non_rooted_nim_without(ra);
					as.pb(a);
					pairs.pb({xo_no, xo_yes});
				}
				F0R(i,1<<sz(pairs)) {
					vi res{c};
					int v = 0;
					F0R(j,sz(pairs)) {
						if (i&(1<<j)) {
							v ^= pairs.at(j).at(1);
							res.pb(as.at(j));
						} else {
							v ^= pairs.at(j).at(0);
						}
					}
					if (v == desired) return res;
				}
				assert(false);
				return {};
			}
		}
		assert(false);
	};
	// dbg("AA");
	marked = vb(N);
	assert(get_value() == 0);
	// dbg("BB");
	ints(M);
	rep(M) {
		marked = vb(N);
		auto finished = [&]() {
			F0R(i,N) if (!marked.at(i)) return false;
			return true;
		};
		while (!finished()) {
			auto mark = [&](int x) {
				assert(!marked.at(x));
				marked.at(x) = true;
			};
			auto make_move = [&](vi v) {
				cout << sz(v) << endl;
				for (int x: v) {
					cout << x+1 << " ";
					mark(x);
				}
				cout << endl;
			};
			ints(K);
			// dbg("HA", K);
			vi A(K); re(A);
			dbg("READ");
			each(t,A) --t;
			for (int x: A) mark(x);
			make_move(get_move());
			assert(get_value() == 0);
		}
	}
}

V<vpi> edges{{{0, 1}, {0, 3}, {1, 2}, {3, 4}, {4, 5}, {4, 9}, {5, 6}, {6, 7}, {7, 8}, {9, 10}, {10, 11}, {11, 12}, {12, 13}, {12, 16}, {13, 14}, {13, 15}, {16, 17}, {17, 18}, {18, 19}, {19, 20}, {19, 21}, {21, 22}, {22, 23}, {23, 24}, {24, 25}, {25, 26}, {26, 27}, {26, 28}, {26, 29}}, {{0, 1}, {1, 2}, {1, 7}, {2, 3}, {3, 4}, {3, 5}, {5, 6}, {7, 8}, {8, 9}, {9, 10}, {10, 11}, {10, 12}, {10, 15}, {12, 13}, {12, 14}, {15, 16}, {16, 17}, {17, 18}, {18, 19}, {18, 20}, {20, 21}, {21, 22}, {22, 23}, {22, 24}, {24, 25}, {25, 26}, {26, 27}, {27, 28}, {28, 29}, {29, 30}}, {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {3, 9}, {4, 5}, {5, 6}, {5, 7}, {7, 8}, {9, 10}, {10, 11}, {11, 12}, {12, 13}, {12, 14}, {12, 17}, {14, 15}, {14, 16}, {17, 18}, {18, 19}, {19, 20}, {20, 21}, {21, 22}, {22, 23}, {23, 24}, {23, 25}, {25, 26}, {26, 27}, {27, 28}, {27, 29}, {27, 30}, {30, 31}}, {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {3, 8}, {4, 5}, {5, 6}, {5, 7}, {8, 9}, {9, 10}, {10, 11}, {11, 12}, {11, 13}, {11, 16}, {13, 14}, {13, 15}, {16, 17}, {17, 18}, {18, 19}, {19, 20}, {20, 21}, {21, 22}, {22, 23}, {22, 24}, {24, 25}, {25, 26}, {26, 27}, {27, 28}, {28, 29}, {29, 30}, {30, 31}, {31, 32}}, {{0, 1}, {1, 2}, {1, 3}, {3, 4}, {4, 5}, {4, 9}, {5, 6}, {6, 7}, {7, 8}, {9, 10}, {10, 11}, {11, 12}, {12, 13}, {12, 14}, {12, 17}, {14, 15}, {14, 16}, {17, 18}, {18, 19}, {19, 20}, {20, 21}, {20, 22}, {22, 23}, {23, 24}, {24, 25}, {24, 26}, {26, 27}, {27, 28}, {28, 29}, {28, 30}, {28, 31}, {31, 32}, {32, 33}}, {{0, 1}, {1, 2}, {1, 12}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {5, 8}, {6, 7}, {8, 9}, {9, 10}, {10, 11}, {12, 13}, {13, 14}, {14, 15}, {15, 16}, {15, 17}, {17, 18}, {18, 19}, {19, 20}, {20, 21}, {21, 22}, {22, 23}, {22, 24}, {22, 25}, {25, 26}, {26, 27}, {27, 28}, {28, 29}, {29, 30}, {30, 31}, {31, 32}, {32, 33}, {33, 34}}, {{0, 1}, {0, 14}, {0, 17}, {1, 2}, {2, 3}, {3, 4}, {4, 5}, {4, 10}, {5, 6}, {6, 7}, {6, 8}, {8, 9}, {10, 11}, {11, 12}, {12, 13}, {14, 15}, {14, 16}, {17, 18}, {18, 19}, {19, 20}, {20, 21}, {20, 22}, {22, 23}, {23, 24}, {24, 25}, {24, 26}, {26, 27}, {27, 28}, {28, 29}, {29, 30}, {30, 31}, {31, 32}, {32, 33}, {33, 34}, {34, 35}}, {{0, 1}, {1, 2}, {1, 4}, {2, 3}, {4, 5}, {5, 6}, {6, 7}, {7, 8}, {8, 9}, {8, 10}, {10, 11}, {11, 12}, {11, 13}, {11, 19}, {13, 14}, {14, 15}, {15, 16}, {16, 17}, {17, 18}, {19, 20}, {20, 21}, {21, 22}, {21, 24}, {22, 23}, {24, 25}, {25, 26}, {26, 27}, {26, 28}, {28, 29}, {29, 30}, {30, 31}, {31, 32}, {32, 33}, {33, 34}, {34, 35}, {35, 36}}, {{0, 1}, {0, 3}, {1, 2}, {3, 4}, {4, 5}, {4, 9}, {5, 6}, {6, 7}, {7, 8}, {9, 10}, {10, 11}, {11, 12}, {12, 13}, {12, 14}, {12, 17}, {14, 15}, {14, 16}, {17, 18}, {18, 19}, {19, 20}, {20, 21}, {20, 22}, {22, 23}, {23, 24}, {24, 25}, {25, 26}, {26, 27}, {27, 28}, {27, 29}, {27, 30}, {30, 31}, {31, 32}, {32, 33}, {33, 34}, {34, 35}, {35, 36}, {36, 37}}, {{0, 1}, {1, 2}, {2, 3}, {2, 8}, {3, 4}, {4, 5}, {4, 6}, {6, 7}, {8, 9}, {9, 10}, {10, 11}, {11, 12}, {11, 15}, {12, 13}, {12, 14}, {15, 16}, {16, 17}, {17, 18}, {18, 19}, {18, 20}, {20, 21}, {21, 22}, {22, 23}, {22, 24}, {24, 25}, {25, 26}, {26, 27}, {26, 28}, {26, 29}, {29, 30}, {30, 31}, {31, 32}, {32, 33}, {33, 34}, {34, 35}, {35, 36}, {35, 37}, {37, 38}}, {{0, 1}, {1, 2}, {2, 3}, {2, 8}, {3, 4}, {4, 5}, {4, 6}, {6, 7}, {8, 9}, {9, 10}, {10, 11}, {11, 12}, {11, 13}, {11, 16}, {13, 14}, {13, 15}, {16, 17}, {17, 18}, {18, 19}, {19, 20}, {19, 21}, {21, 22}, {22, 23}, {23, 24}, {23, 25}, {25, 26}, {26, 27}, {27, 28}, {27, 29}, {27, 30}, {30, 31}, {31, 32}, {32, 33}, {33, 34}, {34, 35}, {35, 36}, {36, 37}, {37, 38}, {38, 39}}};

void go() {
	re(N);
	do_tree(edges.at(N-30));
	// int trials = 0;
	// while (true) {
	// 	++trials;
	// 	dbg(trials);
	// 	V<vi> adj(N);
	// 	vpi edge;
	// 	FOR(i,1,N) {
	// 		int dif = rng()%min(i,3);
	// 		int j = i-1-dif;
	// 		adj.at(i).pb(j), adj.at(j).pb(i);
	// 		edge.pb({i,j});
	// 	}
	// 	int root = get_root(adj, 0, -1);
	// 	int aa = non_rooted_nim(root);
	// 	// dbg(non_rooted_nim(root));
	// 	if (N > 1) {
	// 		int root2 = get_root(adj, 1, -1);
	// 		int bb = non_rooted_nim(root2);
	// 		assert(aa == bb);
	// 		dbg(aa, bb, sz(tree_iso));
	// 	}
	// 	if (aa == 0) {
	// 		do_tree(edge);
	// 		break;
	// 	}
	// }
}

int main(int, char* argv[]) {
	// int tc; sscanf(argv[1],"%d",&tc); // test case #
	// sscanf(argv[2],"%d",&b); // random seed
	// sscanf(argv[3],"%d",&c); // also random seed
	// srand(b);
	// setIO();
	// V<vpi> edges;
	// FOR(N,30,41) {
	// 	while (true) {
	// 		V<vi> adj(N);
	// 		vpi edge;
	// 		FOR(i,1,N) {
	// 			int dif = rng()%min(i,3);
	// 			int j = i-1-dif;
	// 			adj.at(i).pb(j), adj.at(j).pb(i);
	// 			edge.pb({i,j});
	// 		}
	// 		int root = get_root(adj, 0, -1);
	// 		int aa = non_rooted_nim(root);
	// 		// dbg(non_rooted_nim(root));
	// 		if (N > 1) {
	// 			int root2 = get_root(adj, 1, -1);
	// 			int bb = non_rooted_nim(root2);
	// 			assert(aa == bb);
	// 			dbg(aa, bb, sz(tree_iso));
	// 		}
	// 		if (aa == 0) {
	// 			dbg(N);
	// 			edges.pb(edge);
	// 			dbg(edge);
	// 			break;
	// 		}	
	// 	}
	// }
	// dbg(edges);
	ints(T);
	rep(T) go();
}
