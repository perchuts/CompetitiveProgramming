#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int long long
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
	int n; cin >> n;
	vector<int> v(n);
	for (auto& x : v) cin >> x;
	int ans = v.back();
	for (int i = n-2; i >= 0; --i) {
		if (v[i] >= v[i+1]) {
			ans = max(ans+1, v[i]);
		} else {
			ans++;
		}
	}
	cout << ans << endl;
}

int solve2(int n, vector<int> v){
	if (n == 1) return v.back();
	int ans = v.back();
	for (int i = n-2; i >= 0; --i) {
		if (v[i] >= v[i+1]) {
			ans = max(ans+1, v[i]);
		} else {
			ans++;
		}
	}
	return ans;
}
mt19937 rng(time(0));

int rnd(int l, int r) {
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}

void gen_tests() {
	int ttt = 1;
	while (true) {
		int n = 10;
		vector<int> v(n);
		for (auto& x : v) x = rnd(1, 15);
		auto tmp = v;
		int tempo = 0;
		while (true) {
			auto tmp2 = tmp;
			bool ok = 1;
			for (auto x : tmp) ok &= (x == 0);
			if (ok) break;
			for (int i = n - 1; i >= 0; --i) {
				if (tmp[i] == 0) continue;
				if (i == n - 1 || tmp[i+1] < tmp[i]) tmp2[i]--;
			}
			tmp = tmp2;
			tempo++;
		}
		int my = solve2(n, v);
		if (my != tempo) {
			cout << "Wrong answer on test " << ttt << endl;
			cout << n << endl;
			for (auto x : v) cout << x << ' ';
			cout << endl;
			cout << "Answer: " << tempo << endl;
			cout << "Your output: " << my << endl;
			exit(0);
		}
		cout << "Accepted on test " << ttt++ << endl;
	}
}
int32_t main(){_
  //gen_tests();
  int t; cin >> t;
  while(t--) solve();
}
