#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll
//#define STRESS

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

string encode(string s) {
	int n = sz(s);
	vector<int> pref(n+1);
	for (int i = 1; i <= n; ++i) pref[i] = (s[i-1] == '(' ? 1 : -1) + pref[i-1];	
	vector<int> ord(n); iota(all(ord), 0);
	sort(all(ord), [&] (int x, int y) { 
			if (pref[x] == pref[y]) return x > y;
			return pref[x] < pref[y];
			});
	string ans;
	for (auto x : ord) ans += s[x];
	return ans;
}

string decode(string s){
	int n = sz(s), topo = 0;
	vector<vector<int>> g(n+1);
	queue<int> abres, prox_abres;
	for (int i = 1; i <= n; ++i) {
		if (s[i-1] == ')') {
			if (abres.empty()) swap(abres, prox_abres);
			topo = abres.front();
			abres.pop();
		} else {
			//cout << topo << " -> " << i << endl;
			g[topo].pb(i), prox_abres.push(i);
		}
	}
	string ans;
	auto dfs = [&] (auto&& self, int u) -> void {
		if (u) ans += "("; 
		reverse(all(g[u]));
		for (auto v : g[u]) self(self, v);
		if (u) ans += ")";
	};
	dfs(dfs, 0);
	return ans;
}

int32_t main(){_
#ifdef STRESS
	int t = 1;
	while (true) {
		int n = 2 * rnd(1, 30);
		string s; 
		int balance = 0, ok = 1;
		for (int i = 0; i < n; ++i) {
			s += (rnd(0, 1) ? "(" : ")");
			if (s.back() == '(') balance++;
			else balance--;
			ok &= (balance >= 0);
		}
		if (ok == 0 or balance != 0) continue;
		if (decode(encode(s)) != s) {
			cout << "Wrong answer on test " << t << endl;
			cout << encode(s) << endl;
			cout << "Your output: " << decode(encode(s)) << endl;
			cout << "Correct answer: " << s << endl;
			exit(0);
		}
		cout << "Accepted on test " << t++ << endl;
	}
#endif
	string s; cin >> s;
	cout << decode(s) << endl;
}
