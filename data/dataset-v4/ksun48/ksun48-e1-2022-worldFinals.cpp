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

using ld = long double;

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
	ld dist() const { return sqrt((ld)dist2()); }
	// angle to x-axis in interval [-pi, pi]
	ld angle() const { return atan2(y, x); }
	P unit() const { return *this/dist(); } // makes dist()=1
	P perp() const { return P(-y, x); } // rotates +90 degrees
	P normal() const { return perp().unit(); }
	// returns point rotated 'a' radians ccw around the origin
	P rotate(ld a) const {
		return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << "," << p.y << ")"; }
};

template <class P>
bool onSegment(const P& s, const P& e, const P& p) {
	P ds = p-s, de = p-e;
	return ds.cross(de) == 0 && ds.dot(de) <= 0;
}
template<class P> int segInter(P a, P b, P c, P d) {
	auto oa = c.cross(d, a), ob = c.cross(d, b),
	     oc = a.cross(b, c), od = a.cross(b, d);
	// Checks if intersection is single non-endpoint point.
	if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0) return 2;
	set<P> s;
	if (onSegment(c, d, a)) s.insert(a);
	if (onSegment(c, d, b)) s.insert(b);
	if (onSegment(a, b, c)) s.insert(c);
	if (onSegment(a, b, d)) s.insert(d);
	return (int)s.size();
}

using ll = __int128_t;

using P = Point<ll>;

void solve(int t){
	int N;
	cin >> N;
	vector<P> pts(N);
	for(int i = 0; i < N; i++){
		int x, y;
		cin >> x >> y;
		pts[i].x = x;
		pts[i].y = y;
	}
	vector<vector<int> > best;
	auto inside = [&](vector<P> t1, vector<P> t2) -> bool {
		for(P p : t2){
			for(int idx1 = 0; idx1 < 3; idx1++){
				P x = t1[idx1];
				P y = t1[(idx1+1)%3];
				int sgnz = sgn(x.cross(y, t1[(idx1+2)%3]));
				if(sgn(x.cross(y, p)) * sgnz == -1) return false;
			}
		}
		return true;
	};
	y_combinator(
		[&](auto self, vector<vector<int> > taken) -> void {
			if(!taken.empty()){
				vector<int> i1 = taken.back();
				for(vector<int> i2 : taken){
					vector<P> t1, t2;
					for(int i : i1) t1.push_back(pts[i]);
					for(int i : i2) t2.push_back(pts[i]);
					if(t1[0].cross(t1[1], t1[2]) == 0) return;
					if(t2[0].cross(t2[1], t2[2]) == 0) return;
					if(i1 == i2) continue;
					for(int idx1 = 0; idx1 < 3; idx1++){
						for(int idx2 = 0; idx2 < 3; idx2++){
							if(segInter(t1[idx1], t1[(idx1+1)%3], t2[idx2], t2[(idx2+1)%3]) == 2) return;
						}
					}
					if(inside(t1, t2)) continue;
					if(inside(t2, t1)) continue;
					bool works = false;
					for(int j = 0; j < 2; j++){
						for(int idx1 = 0; idx1 < 3; idx1++){
							bool ok = true;
							P x = t1[idx1];
							P y = t1[(idx1+1)%3];
							int sgnz = sgn(x.cross(y, t1[(idx1+2)%3]));
							for(int idx2 = 0; idx2 < 3; idx2++){
								if(sgn(x.cross(y, t2[idx2])) == sgnz){
									ok = false;
								}
							}
							if(ok) works = true;
						}
						swap(t1, t2);
					}
					if(works) continue;
					return;
				}
				if(taken.size() > best.size()) best = taken;
			}
			vector<int> used(N, 0);
			for(auto x : taken){
				for(int i : x) used[i] = 1;
			}
			int nxt = 0;
			for(auto x : taken){
				nxt = max(nxt, x[0]);
			}
			for(int a = nxt; a < N; a++){
				if(used[a]) continue;
				for(int b = a+1; b < N; b++){
					if(used[b]) continue;
					for(int c = b+1; c < N; c++){
						if(used[c]) continue;
						vector<vector<int> > ntaken = taken;
						ntaken.push_back({a, b, c});
						self(ntaken);
					}
				}
			}
		}
	)(vector<vector<int>>{});
	cout << "Case #" << t << ": ";
	cout << best.size() << '\n';
	for(auto x : best){
		cout << (x[0] + 1) << ' ' << (x[1] + 1) << ' ' << (x[2] + 1) << '\n';
	}
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