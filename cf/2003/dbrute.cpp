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

int solve(int n, int m, vector<vector<int>> a){
	map<int, vector<int>> mexdomex;
	int maxk = 0;
	for (auto& x : a) {
		int k = sz(x);
		ckmax(maxk, k);
		vector<int> freq(k+5);
		for (auto& y : x) {
			if (y < k + 5) freq[y] = 1;
		}
		int m1 = -1, m2 = -1;
		for (int i = 0; i < k + 5; ++i) {
			if (freq[i] == 0) {
				if (m1 == -1) {
					m1 = i;
				} else {
					m2 = i;
					break;
				}
			}
		}
		mexdomex[m1].pb(m2);
	}
	// preciso fazer na mao ateh tipo maxk + 5, depois eh garantido q a resposta eh i
	maxk += 5;
	map<int, int> dp;
	int ans = max(0ll, (m-maxk)*(maxk+1+m)/2), bestdp = 0;
	for (int i = maxk; i >= 0; --i) {
		dp[i] = i;
		for (auto x : mexdomex[i]) ckmax(dp[i], dp[x]);
		if (sz(mexdomex[i]) > 1) ckmax(bestdp, dp[i]);
		if (sz(mexdomex[i]) != 0) ckmax(bestdp, i);
	}
	for (int i = 0; i <= min(m, maxk); ++i) ans += max(bestdp, dp[i]);
	return ans;
}
mt19937 rng(time(0));
int rnd(int l, int r) {
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}
int32_t main(){_
	int tt = 0;
	while (true) {
		int n = rnd(1, 3);
		vector<vector<int>> a(n);
		for (auto& x : a) {
			int k = rnd(1, 5);
			x.resize(k);
			for (auto& y : x) y = rnd(0, k);
		}
		int m = rnd(0, 10), sum = 0;
		vector<int> gaba;
		for (int i = 0; i <= m; ++i) {
			vector<int> p(n);
			iota(all(p), 0);
			int ans = i;
			do {
				int cur = i;
				for (int j = 0; j < n; ++j) {
					vector<int> mark(20);
					for (auto x : a[p[j]]) mark[x] = 1;
					mark[cur] = 1;
					for (int k = 0; ; ++k) {
						if (mark[k] == 0) {
							cur = k;
							break;
						}
					}
					ckmax(ans, cur);
				}
			} while (next_permutation(all(p)));
			gaba.pb(ans);
			sum += ans;
		}
		int my = solve(n, m, a);
		if (my != sum) {
			cout << "Wrong answer on test " << tt << endl;
			cout << n << ' ' << m << endl;
			for (auto x : a) {
				cout << sz(x) << ' ';
				for (auto y : x) cout << y << ' ';
				cout << endl;
			}
			cout << "Your output: " << my << endl;
			cout << "Correct answer: " << sum << endl;
			cout << "Sequence of answers: ";
			for (auto x : gaba) cout << x << ' ';
			exit(0);
		} else {
			cout << "Accepted on test " << tt++ << endl;
		}
	}
}
