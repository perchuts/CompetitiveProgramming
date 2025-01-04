#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
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
const int mod = 998244353;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}

vector<ii> solve(int n, int q, vector<int> v, vector<ii> qu){
	vector<vector<int>> freq(n+1, vector<int>(64));
	for (int i = 1; i <= n; ++i) for (int j = 0; j <= 50; ++j) freq[i][j] = freq[i-1][j] + (v[i] == j);
	vector<ii> answers;
	for (auto [l, r] : qu) {
		vector<ii> dp(64), ndp(64);
		dp[0] = {0, 1};
		if (freq[r][0] - freq[l-1][0]) {
			answers.pb({r-l, freq[r][0] - freq[l-1][0]});
			continue;
		}
		bool ok = 0;
		int ways = 0;
		for (int i = 1; i < 64; ++i) {
			int tot = freq[r][i] - freq[l-1][i];
			if (tot <= 1) continue;
			ok = 1;
			ways += tot * (tot-1) / 2;
			ways %= mod;
		}
		if (ok) {
			answers.pb({r-l-1, ways});
			continue;
		}
		for (int i = 1; i < 64; ++i) {
			int tot = freq[r][i] - freq[l-1][i];
			if (tot == 0) continue;
			for (int j = 0; j < 64; ++j) {
				if (i == j) {
					ndp[j] = {1, tot};
					continue;
				}
				ndp[j] = dp[j];
				ii outro = dp[j^i];
				ndp[j].first += tot-1, ndp[j].second = ndp[j].second * tot;
				outro.first += tot;
				if (ndp[j].first == outro.first) ndp[j].second = (ndp[j].second + outro.second) % mod;
				else if ((outro.first != 0 and outro.second != 0) and (ndp[j].first > outro.first or ndp[j].first == 0)) ndp[j] = outro;
			}
			swap(dp, ndp);
		}
		if (dp[0].first == 0) answers.pb({-1, 0});
		else answers.pb({r-l+1-dp[0].first, dp[0].second});
	}
	return answers;
}

vector<ii> brute(int n, int q, vector<int> v, vector<ii> qu){
	vector<ii> answers;
	for (auto [l, r] : qu) {
		int tam = r-l+1, used = 0, ways = 0;
		for (int i = 1; i < (1 << tam); ++i) {
			int xx = 0, tira = 0;
			for (int j = 0; j < tam; ++j) {
				if (i >> j & 1) xx ^= v[l+j];
				else tira++;
			}
			if (xx == 0) {
				if (used < tira) used = tira, ways = 1;
				else if (used == tira) ways++;
			}
		}
		if (ways == 0) answers.pb({-1, 0});
		else answers.pb({used, ways});
	}
	return answers; 
}
int32_t main(){_
#ifdef STRESS
	int t = 1;
	while (true) {
		int n = rnd(3, 10), q = 100;
		vector<int> v(n+1);
		for (int i = 1; i <= n; ++i) v[i] = rnd(0, 50);
		vector<ii> qu(q);
		for (auto& [x, y] : qu) x = rnd(1, n), y = rnd(1, n);
		for (auto& [x, y] : qu) if (x > y) swap(x, y);
		auto answers = solve(n, q, v, qu);
		auto correct = brute(n, q, v, qu);
		if (answers != correct) {
			cout << "Wrong answer on test " << t << endl;
			cout << n << ' ' << q << endl;
			for (int i = 1; i <= n; ++i) cout << v[i] << ' ';
			cout << endl;
			for (auto [x, y] : qu) cout << x << ' ' << y << endl;
			cout << "Your output:" << endl;
			for (auto [x, y] : answers) {
				if (x == -1) cout << x << endl;
				else cout << x << ' ' << y << endl;
			}
			cout << "Answer:" << endl;
			for (auto [x, y] : correct) {
				if (x == -1) cout << x << endl;
				else cout << x << ' ' << y << endl;
			}
			exit(0);
		}
		cout << "Accepted on test " << t++ << endl;
	}
#else
	int n, q; cin >> n >> q;
	vector<int> v(n+1);
	for (int i = 1; i <= n; ++i) cin >> v[i];
	vector<ii> qu(q);
	for (auto& [x, y] : qu) cin >> x >> y;
	auto ans = solve(n, q, v, qu);
	for (auto [x, y] : ans) {
		if (x == -1) cout << -1 << endl;
		else cout << x << ' ' << y << endl;
	}
#endif
}
