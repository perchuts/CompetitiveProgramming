#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
//#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll
//#define gato

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

int solve(int m, int n, vector<int> a, vector<int> f) {
	vector<int> freq(m);
    int A = 0;
    for (auto& x : a) A += x;
	for (auto x : f) freq[x-1]++;
	if (n % A == 0 and n != 0) return -1;
	vector<vector<ii>> pode(n+A+5);
	auto get = [&] (int i) {
		int rx = (freq[i] * A) / a[i] + 1;
		int lx = ((freq[i] + 1) * A + a[i]-1) / a[i];
		return pair(rx-1, lx-1);
	};
    for (int i = 0; i < m; ++i) {
		auto [l, r] = get(i);
		//cout << l << ' ' << r << endl;
		if (l <= n+A) pode[max(n, l)].pb({r, i});
    }
    int ans = -1;
	priority_queue<ii> pq;
	while (n % A or n == 0) {
		for (auto [pt, id] : pode[n]) pq.push({-pt, id});
		if (pq.empty()) return ans;
		auto [pt, id] = pq.top(); pq.pop(); pt *= -1;
		if (pt < n) return ans;
		freq[id]++;
		auto [l, r] = get(id);
		n++, ans++;
		pode[max(n, l)].pb({r, id});
	}
	return -1;
}

int brute(int m, int n, vector<int> a, vector<int> f) {
	vector<int> freq(m);
	for (auto x : f) freq[x-1]++;
	int A = 0, ans = 0;
	for (auto x : a) A += x;
	auto go = [&] (auto&& self, int n_) -> void {
		bool ok = 1;
		for (int i = 0; i < m; ++i) ok &= ((n_ + n)	* a[i] - A < freq[i] * A and freq[i] * A < (n_ + n) * a[i] + A);
		if (!ok) return;
		ckmax(ans, n_);
		if (n_ > n + 100) { ans = -1; return; }
		for (int i = 0; i < m; ++i) {
			freq[i]++;
			self(self, n_+1);
			if (ans == -1) return;
			freq[i]--;
		}
	};
	go(go, 0);
	return ans;
}

int32_t main(){_
#ifndef gato
    int m, n; cin >> m >> n;
    vector<int> a(m), f(n);
    for (auto& x : a) cin >> x;
    for (auto& x : f) cin >> x;
	int ans = solve(m, n, a, f);
	if (ans == -1) cout << "forever" << endl;
	else cout << ans << endl;
#else
	int t = 1;
	while (true) {
		int m = rnd(1, 8), n = rnd(0, 10), A = 0;
		vector<int> a(m), f(n), freq(m);
		for (auto& x : a) x = rnd(1, 30), A += x;
		for (auto& x : f) x = rnd(1, m);
		bool ok = 1;
		int N = n, n_ = 0; n = 0;
		for (int j = 0; j < N; ++j) {
			freq[f[j]-1]++, n++;
			for (int i = 0; i < m; ++i) ok &= ((n_ + n)	* a[i] - A < freq[i] * A and freq[i] * A < (n_ + n) * a[i] + A);
		}
		if (!ok) continue;
		int my = solve(m, n, a, f);
		int ans = brute(m, n, a, f);
		if (my != ans) { 
			cout << "Wrong answer on test " << t << endl;
			cout << m << ' ' << n << endl;
			for (auto x : a) cout << x << ' ';
			cout << endl;
			for (auto x : f) cout << x << ' ';
			cout << endl;
			cout << "Your output: ";
			if (my == -1) cout << "forever" << endl;
			else cout << my << endl;
			cout << "Answer: ";
			if (ans == -1) cout << "forever" << endl;
			else cout << ans << endl;
			exit(0);
		}
		cout << "Accepted on test " << t++ << endl;
	}
#endif
}
