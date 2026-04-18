#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define pb push_back
#define int ll

using namespace std;

using ll = long long;

struct trie{
	vector<vector<int>> to;	
	vector<int> term;
	int sz;

	trie(){
		to.pb(vector<int>(26));
		term = vector<int>(26);
		sz = 1;
	}

	void insert(string s){
		int x = 0;
		int n = s.size();
		for (int i = 0; i < n; ++i){
			int c = s[i]-'a';
			if (!to[x][c]){
				to[x][c] = sz++;
				to.pb(vector<int>(26));
				term[c]++;
			}
			x = to[x][c];
		}
	}
};

void solve(int n, int m){
	trie t1, t2;
	vector<string> va(n);
	for (int i = 0; i < n; ++i){
		string x; cin >> x;
		t1.insert(x);
		va[i] = x;
	}
	vector<bool> pres(26);
	for (int i = 0; i < m; ++i){
		string x; cin >> x;
		reverse(x.begin(), x.end());
		t2.insert(x);	
		int c = x[0]-'a';
		pres[c] = true;
	}

	int ans = 0;
	function<void(int)> dfs = [&](int x){
		if (!x) return;
		for (int c = 0; c < 26; ++c){
			if (t1.to[x][c]) dfs(t1.to[x][c]);
			else {
				ans += t2.term[c];
			}
		}
	};
	for (int c = 0; c < 26; ++c) if (t1.to[0][c]) dfs(t1.to[0][c]);

	function<void(int)> dfs2 = [&](int x){
		if (!x) return;
		for (int c = 0; c < 26; ++c){
			if (t1.to[x][c]) {
				if (pres[c]) ans++;
				dfs2(t1.to[x][c]);
			}
		}
	};
	for (int c = 0; c < 26; ++c) if (t1.to[0][c]) dfs2(t1.to[0][c]);

	cout << ans << endl;
}

int32_t main() {_
	while (1){
		int p, s; cin >> p >> s;
		if (p == 0 and s == 0) break;
		solve(p,s);
	}
}
