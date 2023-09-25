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

using ll = int64_t;

ll get_cc(int y, ll cmask, vector<vector<int> > &graph){
	ll r = 0;
	y_combinator(
		[&](auto self, int v) -> void {
			if(!(cmask & (ll(1) << v))) return;
			if(r & (ll(1) << v)) return;
			r |= (ll(1) << v);
			for(int w : graph[v]){
				self(w);
			}
		}
	)(y);
	return r;
}

int solve(vector<vector<int> > graph){
	int n = (int)graph.size();
	ll st = (ll(1) << n) - 1;
	map<ll, int> memo; // value
	auto val = y_combinator(
		[&](auto self, ll v) -> int {
			if(!memo.count(v)){
				set<int> go;
				for(int x = 0; x < n; x++){
					if(v & (ll(1) << x)){
						assert(get_cc(x, v, graph) == v);
						vector<int> active_n;
						for(int y : graph[x]){
							if(v & (ll(1) << y)) active_n.push_back(y);
						}
						int d = (int)active_n.size();
						vector<pair<int, int> > subs;
						for(int y : active_n){
							int n1 = self(get_cc(y, v ^ (ll(1) << x), graph));
							int n2 = 0;
							for(int z : graph[y]){
								n2 ^= self(get_cc(z, v ^ (ll(1) << x) ^ (ll(1) << y), graph));
							}
							subs.push_back({n1, n2});
						}
						assert(d <= 10);
						for(int j = 0; j < (1 << d); j++){
							int res = 0;
							for(int i = 0; i < d; i++){
								res ^= (j & (1 << i)) ? subs[i].second : subs[i].first;
							}
							go.insert(res);
						}
					}
				}
				int c = 0;
				while(go.count(c)) c++;
				memo[v] = c;
			}
			return memo[v];
		}
	);

	int res = val(st);
	return res;
}

void solve_test(){
	int N;
	cin >> N;

	vector<vector<int> > graph(30);
	{
		int a = 10;
		int b = 10;
		int c = 29 - a - b;
		int st = 0;
		int k = 1;
		for(int r : {a, b, c}){
			int lst = st;
			for(int j = 0; j < r; j++){
				graph[lst].push_back(k);
				graph[k].push_back(lst);
				lst = k;
				k++;
			}
		}
	}
	int n = (int)graph.size();
	ll st = (ll(1) << n) - 1;
	map<ll, int> memo; // value
	map<ll, map<int, pair<int, ll> > > to_masks;
	auto val = y_combinator(
		[&](auto self, ll v) -> int {
			if(!memo.count(v)){
				set<int> go;
				for(int x = 0; x < n; x++){
					if(v & (ll(1) << x)){
						vector<int> active_n;
						for(int y : graph[x]){
							if(v & (ll(1) << y)) active_n.push_back(y);
						}
						int d = (int)active_n.size();
						vector<pair<int, int> > subs;
						for(int y : active_n){
							int n1 = self(get_cc(y, v ^ (ll(1) << x), graph));
							int n2 = 0;
							for(int z : graph[y]){
								n2 ^= self(get_cc(z, v ^ (ll(1) << x) ^ (ll(1) << y), graph));
							}
							subs.push_back({n1, n2});
						}
						assert(d <= 10);
						for(int j = 0; j < (1 << d); j++){
							int res = 0;
							for(int i = 0; i < d; i++){
								res ^= (j & (1 << i)) ? subs[i].second : subs[i].first;
							}
							go.insert(res);
							ll move = 0;
							for(int i = 0; i < d; i++){
								if(j & (1 << i)){
									move ^= ll(1) << active_n[i];
								}
							}
							to_masks[v][res] = {x, move};
						}
					}
				}
				int c = 0;
				while(go.count(c)) c++;
				memo[v] = c;
			}
			return memo[v];
		}
	);

	auto get_score = [&](ll state) -> int {
		ll unseen = state;
		vector<ll> masks;
		for(int x = 0; x < n; x++){
			if(!(unseen & (ll(1) << x))) continue;
			ll r = get_cc(x, state, graph);
			assert((unseen & r) == r);
			unseen ^= r;
			masks.push_back(r);
		}
		assert(unseen == 0);
		int score = 0;
		for(ll mask : masks){
			score ^= val(mask);
		}
		return score;
	};

	assert(val(st) == 0);
	for(int i = 0; i < n; i++){
		for(int j : graph[i]){
			if(j > i){
				cout << (i+1) << ' ' << (j+1) << '\n';
			}
		}
	}
	cout << flush;
	int GAMES;
	cin >> GAMES;
	while(GAMES--){
		ll state = (ll(1) << n) - 1;
		while(state){
			int k;
			cin >> k;
			if(k == -1) assert(false);
			for(int i = 0; i < k; i++){
				int a;
				cin >> a;
				a--;
				state ^= (1 << a);
			}
			if(state == 0) exit(0);
			ll unseen = state;
			vector<ll> masks;
			for(int x = 0; x < n; x++){
				if(!(unseen & (ll(1) << x))) continue;
				ll r = get_cc(x, state, graph);
				assert((unseen & r) == r);
				unseen ^= r;
				masks.push_back(r);
			}
			assert(unseen == 0);
			int score = 0;
			for(ll mask : masks){
				score ^= val(mask);
			}
			assert(score > 0);
			assert(score == get_score(state));
			pair<int, ll> mv = {-1, -1};
			for(ll mask : masks){
				int cur = val(mask);
				if(to_masks[mask].count(score ^ cur)){
					mv = to_masks[mask][score ^ cur];
				}
			}
			assert(mv.first >= 0);
			int z = __builtin_popcountll(mv.second) + 1;
			cout << z << '\n';
			cout << (1 + mv.first);
			for(int i = 0; i < n; i++){
				if(mv.second & (ll(1) << i)){
					cout << ' ' << (1 + i);
				}
			}
			cout << '\n';
			cout << flush;

			state ^= ll(1) << mv.first;
			state ^= mv.second;
		}
	}
}

int main(){
	ios_base::sync_with_stdio(false), cin.tie(nullptr);
	int T;
	cin >> T;
	while(T--) solve_test();
}