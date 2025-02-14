#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ii = pair<int,int>;
using iii = tuple<int,int,int>;

const int inf = 2e9+1;
const int mod = 1e9+7;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}

void solve(){
	vector<string> grid(9);
	for (auto& x : grid) cin >> x;
	vector<string> sexo(3, string(3, '.'));
	bool ok = 0;
	auto solve = [&] (vector<string> s, bool mark = true) {
		int unfinished = 0;
		for (int i = 0; i < 3; ++i) {
			if (s[i][0] == '.') unfinished = 1;
			if (s[i][1] == '.') unfinished = 1;
			if (s[i][2] == '.') unfinished = 1;
			if (s[i][0] != '.' and s[i][0] == s[i][1] and s[i][1] == s[i][2]) return s[i][1];
			if (s[0][i] != '.' and s[0][i] == s[1][i] and s[1][i] == s[2][i]) return s[1][i];
		}
		if (s[0][0] != '.' and s[0][0] == s[1][1] and s[1][1] == s[2][2]) return s[0][0];
		if (s[0][2] != '.' and s[0][2] == s[1][1] and s[1][1] == s[2][0]) return s[0][2]; 
		if (unfinished and mark) ok = 1;
		return '.';
	};
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			vector<string> ss;
			for (int k = 0; k < 3; ++k) ss.push_back(grid[3*i+k].substr(3*j, 3));
			sexo[i][j] = solve(ss);
		}
	}
	char ans = solve(sexo, 0);
	if (ans == 'X') cout << "XENIYA" << endl;
	else if (ans == 'O') cout << "OLGA" << endl;
	else if (ok == 1) cout << "UNFINISHED" << endl;
	else cout << "DRAW" << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
