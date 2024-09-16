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

void solve(){
	int n, m; cin >> n >> m;
	vector<int> v(2*n);
	for (auto& x : v) cin >> x;
	map<int, int> freq;
	int ok = 0, sum = 0;
	for (auto& x : v) freq[x%m]++, sum = (sum + x) % m;
	int tot = 0;
	for (auto [x, y] : freq) {
		ok |= (y % 2 == 1), tot += (y % 2 == 1);
	}
	if (ok == 0) {
		cout << "Bob" << endl;
		return;
	}
	if (m % 2 == 1 || sum % 2 == 1) {
		cout << "Alice" << endl;
		return;
	}
	int pares = 0;
	for (auto [x, y] : freq) {
		if (y % 2) { 
			if (freq[x+m/2] % 2) freq[x+m/2]++, freq[x]++, pares++; 
		}
	}
	if (pares == tot/2 && pares % 2 == 0) {
		cout << "Bob" << endl;
		return;
	}
	cout << "Alice" << endl;
}
int32_t main(){_	
	solve();
//	int ttt = 0; 
//	while (true) {
//		ttt++;
//		int n = 5, m = rnd(1, 20);
//		vector<int> v(2*n);
//		for (auto& x : v) x = rnd(0, m-1);
//		int ans = brute(n, m, v), my = solve(n, m, v);
//		if (ans != my) {
//			cout << "Wrong answer on test " << ttt << endl;
//			cout << n << ' ' << m << endl;
//			for (auto x : v) cout << x << ' ';
//			cout << endl;
//			cout << ans << ' ' << my << endl;
//			exit(0);
//		}
//		cout << "Accepted on test " << ttt << endl;
//	}
}
