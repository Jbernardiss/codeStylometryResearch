#include <bits/stdc++.h>
using namespace std;

namespace std {

template<class Fun>
class y_combinator_result {
	Fun fun_;
public:
	template<class T>
	explicit y_combinator_result(T &&fun): fun_(std::forward<T>(fun)) {}

	template<class ...Args>
	decltype(auto) operator()(Args &&...args) {
		return fun_(std::ref(*this), std::forward<Args>(args)...);
	}
};

template<class Fun>
decltype(auto) y_combinator(Fun &&fun) {
	return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}

} // namespace std

template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T _x=0, T _y=0) : x(_x), y(_y) {}
	bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
	bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
	P operator+(P p) const { return P(x+p.x, y+p.y); }
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	P operator*(T d) const { return P(x*d, y*d); }
	P operator/(T d) const { return P(x/d, y/d); }
	T dot(P p) const { return x*p.x + y*p.y; }
	T cross(P p) const { return x*p.y - y*p.x; }
	T cross(P a, P b) const { return (a-*this).cross(b-*this); }
	T dist2() const { return x*x + y*y; }
	double dist() const { return sqrt((double)dist2()); }
	// angle to x-axis in interval [-pi, pi]
	double angle() const { return atan2(y, x); }
	P unit() const { return *this/dist(); } // makes dist()=1
	P perp() const { return P(-y, x); } // rotates +90 degrees
	P normal() const { return perp().unit(); }
	// returns point rotated 'a' radians ccw around the origin
	P rotate(double a) const {
		return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << "," << p.y << ")"; }
};

using ll = int64_t;
using P = Point<ll>;

ll sq(ll x){
	return x * x;
}

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
// typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

vi val, comp, z, cont;
int Time, ncomps;
template<class G, class F> int dfs(int j, G& g, F& f) {
	int low = val[j] = ++Time, x; z.push_back(j);
	trav(e,g[j]) if (comp[e] < 0)
		low = min(low, val[e] ?: dfs(e,g,f));

	if (low == val[j]) {
		do {
			x = z.back(); z.pop_back();
			comp[x] = ncomps;
			cont.push_back(x);
		} while (x != j);
		f(cont); cont.clear();
		ncomps++;
	}
	return val[j] = low;
}
template<class G, class F> void scc(G& g, F f) {
	int n = sz(g);
	val.assign(n, 0); comp.assign(n, -1);
	Time = ncomps = 0;
	rep(i,0,n) if (comp[i] < 0) dfs(i, g, f);
}


void solve(int test_case){
	int N, L, S;
	cin >> N >> L >> S;
	vector<P> locs(L);
	vector<ll> C(L);
	for(int i = 0; i < L; i++){
		cin >> locs[i].x >> locs[i].y;
		cin >> C[i];
	}
	vector<tuple<int, int, P, ll> > statements(S);
	for(auto& [a, b, p, t] : statements){
		cin >> a >> b >> p.x >> p.y >> t;
		a--; b--;
	}
	vector<int> okay(S, true);
	for(int s = S-1; s >= 0; s--){
		auto [a, b, p, t] = statements[s];
		for(int s2 = s; s2 < S; s2++){
			auto [a2, b2, p2, t2] = statements[s2];
			if(a == a2 || a == b2 || b == a2 || b == b2){
				if((p - p2).dist2() > sq(t - t2)){
					okay[s] = false;
				}
			}
		}
	}
	vector<int> forced_duck(N, false);
	for(int s = 0; s < S; s++){
		auto [a, b, p, t] = statements[s];
		if(!okay[s]){
			forced_duck[a] = true;
		}
	}
	vector<vector<int> > edges(N);
	for(int s = 0; s < S; s++){
		auto [a, b, p, t] = statements[s];
		int r = int(lower_bound(C.begin(), C.end(), t) - C.begin());
		bool conflict = false;
		if(r < L && (p - locs[r]).dist2() > sq(t - C[r])) conflict = true;
		if(r > 0 && (p - locs[r-1]).dist2() > sq(t - C[r-1])) conflict = true;
		if(conflict){
			edges[b].push_back(a);
		}
	}
	queue<int> q;
	for(int i = 0; i < N; i++) if(forced_duck[i]) q.push(i);
	while(!q.empty()){
		int v = q.front();
		q.pop();
		for(int w : edges[v]){
			if(forced_duck[w]) continue;
			forced_duck[w] = true;
			q.push(w);
		}
	}
	int ans = 0;
	for(int x : forced_duck) ans += x;
	if(ans == 0){
		ans = N + 1;
		scc(edges, [&](vector<int> scc) -> void {
			set<int> vvert;
			for(int v : scc) vvert.insert(v);
			bool leaf = true;
			for(int v : scc){
				for(int w : edges[v]){
					if(!vvert.count(w)) leaf = false;
				}
			}
			if(leaf) ans = min(ans, (int)scc.size());
		});
	}
	cout << "Case #" << test_case << ": ";
	cout << ans << '\n';
}

int main(){
	ios_base::sync_with_stdio(false), cin.tie(nullptr);
	int T;
	cin >> T;
	for(int t = 1; t <= T; t++){
		solve(t);
		cout << flush;
	}
}