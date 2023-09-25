#include <bits/stdc++.h>
using namespace std;

void solve(int t){
	cout << "Case #" << t << ": ";
	int n;
	cin >> n;
	vector<vector<int> > p(n);
	vector<int> l(n), r(n);
	for(int& x : l) { cin >> x; x--; }
	for(int& x : r) { cin >> x; x--; }
	for(int i = 0; i < n; i++){
		p[i] = {l[i], r[i]};
	}
	vector<set<int> > edges(n);
	vector<set<int> > back_edges(n);
	for(int v = 0; v < n; v++){
		for(int w : p[v]){
			edges[v].insert(w);
			for(int x : p[w]){
				edges[v].insert(x);
			}
		}
		assert(edges[v].size() <= 6);
	}
	for(int v = 0; v < n; v++){
		for(int w : edges[v]){
			if(w == v){
				cout << "IMPOSSIBLE" << '\n';
				return;
			}
			back_edges[w].insert(v);
		}
	}
	vector<int> exist(n, 1);
	queue<int> dfs;
	for(int i = 0; i < n; i++) dfs.push(i);
	vector<vector<int> > prv(n);

	string types = "ACDEHIJKMORST";
	vector<int> ord;
	while(!dfs.empty()){
		int v = dfs.front();
		dfs.pop();
		if(!exist[v]) continue;
		int nsz = (int)edges[v].size() + (int)back_edges[v].size();
		if(nsz <= 12){
			exist[v] = 0;
			ord.push_back(v);
			vector<int> nb;
			for(int x : edges[v]){
				nb.push_back(x);
				back_edges[x].erase(v);
			}
			edges[v] = {};
			for(int x : back_edges[v]){
				nb.push_back(x);
				edges[x].erase(v);
			}
			back_edges[v] = {};
			prv[v] = nb;
			for(int x : nb){
				dfs.push(x);
			}
		}
	}
	reverse(ord.begin(), ord.end());
	vector<int> color(n, -1);
	for(int v : ord){
		vector<int> used(13, 0);
		for(int w : prv[v]){
			assert(color[w] != -1);
			used[color[w]] = 1;
		}
		int i = 0;
		while(used[i]) i++;
		color[v] = i;
	}
	for(int x : color) cout << types[x];
	cout << '\n';
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