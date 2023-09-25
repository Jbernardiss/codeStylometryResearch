#include <bits/stdc++.h>
using namespace std;

int N, K;
void solve(int t){
	vector<int> perm(N);
	for(int& x : perm){
		cin >> x;
		x--;
	}
	while(true){
		vector<int> c(N, -1);
		vector<int> used(N);
		int k = 0;
		for(int i = 0; i < N; i++){
			if(used[i]) continue;
			if(i == perm[i]){
				used[i] = 1;
				c[i] = k;
				k++;
			}
			vector<int> cycle;
			int cur = i;
			while(true){
				cycle.push_back(cur);
				cur = perm[cur];
				if(cur == i) break;
			}
			for(int x : cycle) used[x] = 1;
			int l = (int)cycle.size();
			if(l <= 10){
				for(int j = 0; j + 2 <= l; j += 2){
					int e = j + 2;
					if(j + 3 == l) e = j + 3;
					for(int f = j; f < e; f++){
						c[cycle[f]] = k;
					}
					k++;
				}
			} else {
				int B = 5;
				for(int j = 0; j < l; j += B){
					for(int z = 0; z < min(B, l-j); z++){
						c[cycle[j + z]] = k;
					}
					k++;
				}
				for(int x : cycle){
					if(c[x] == -1){
						c[x] = k;
						k++;
					}
				}
			}
		}
		for(int i = 0; i < N; i++){
			if(!used[i]){
				c[i] = k;
			}
		}
		k++;
		for(int i = 0; i < N; i++){
			cout << (c[i] + 1) << " \n"[i == N-1];
		}
		cout << flush;
		int done;
		cin >> done;
		if(done == 1) return;
		if(done == -1) exit(0);
		for(int& x : perm){
			cin >> x;
			x--;
		}
	}
}

int main(){
	ios_base::sync_with_stdio(false), cin.tie(nullptr);
	int T;
	cin >> T >> N >> K;
	for(int t = 1; t <= T; t++){
		solve(t);
		cout << flush;
	}
}