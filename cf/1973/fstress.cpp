#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
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

vector<int> solve(int n, int q, vector<int> a, vector<int> b, vector<int> c, vector<int> queries){
	int base_cost = 0;
	vector<ii> dps;	
	for (int __ = 0; __ < 2; ++__) {
		vector<int> fa, fb;
		for (int ____ = 0; ____ < 2; ++____) {
			for (int j = 1; j * j <= a[0]; ++j) {
				if (a[0] % j) continue;
				fa.pb(a[0] / j);
				if (j * j != a[0]) fa.pb(j);
			}
			swap(a[0], b[0]), swap(fa, fb);
		}
		sort(all(fa)), sort(all(fb));
		int s1 = sz(fa), s2 = sz(fb);
		vector<vector<ii>> freq(s1, vector<ii>(s2, make_pair(0, 0)));
		auto getId = [&] (int x, bool type) {
			if (type == false) return lower_bound(all(fa), x) - begin(fa);
			return lower_bound(all(fb), x) - begin(fb);
		};
		//cout << "origin: ";
		//cout << a[0] << ' ' << b[0] << ' ' << c[0] << endl;
		for (int i = 1; i < n; ++i) {
			// good way first	
			//cout << a[i] << ' ' << b[i] << ' ' << c[i] << endl;
			int na = gcd(a[0], a[i]), nb = gcd(b[0], b[i]);
			int id_a = getId(na, 0), id_b = getId(nb, 1);
			//cout << id_a << ' ' << id_b << endl;
			freq[id_a][id_b].second++;
			id_a = getId(gcd(a[0], b[i]), 0), id_b = getId(gcd(b[0], a[i]), 1);
			//cout << id_a << ' ' << id_b << endl;
			freq[id_a][id_b].second++;
			freq[id_a][id_b].first += c[i];
			int g1 = gcd(gcd(a[0], a[i]), b[i]), g2 = gcd(gcd(b[0], a[i]), b[i]);
			id_a = getId(g1, 0), id_b = getId(g2, 1);
			//cout << id_a << ' ' << id_b << endl;
			freq[id_a][id_b].first -= c[i];
			freq[id_a][id_b].second--;
		}
		//cout << endl;
		//cout << "divs do a:" << endl;
		//for (auto x : fa) cout << x << ' ';
		//cout << endl;
		//cout << "divs do b:" << endl;
		//for (auto x : fb) cout << x << ' ';
		//cout << endl;
		//cout << "freqs (soh frequencia msm):" << endl;
		//for (auto& x : freq) { for (auto& y : x) cout << y.second << ' '; cout << endl; }
		//cout << "freqs (soh custo):" << endl;
		//for (auto& x : freq) { for (auto& y : x) cout << y.first << ' '; cout << endl; }
		auto dp = freq;
		for (int i = 0; i < s1; ++i) {
			for (int j = 0; j < s2; ++j) {
				for (int k = i + 1; k < s1; ++k) {
					if (fa[k] % fa[i]) continue;
					dp[i][j].first += dp[k][j].first;
					dp[i][j].second += dp[k][j].second;
				}
			}
		}
		//cout << "dp (soh freq msm):" << endl;
		//for (auto& x : dp) { for (auto& y : x) cout << y.second << ' '; cout << endl; }
		//cout << "dp (soh custo):" << endl;
		//for (auto& x : dp) { for (auto& y : x) cout << y.first << ' '; cout << endl; }
		auto dp2 = dp;
		for (int i = s1-1; i >= 0; --i) {
			for (int j = s2-1; j >= 0; --j) {
				for (int k = j + 1; k < s2; ++k) {
					if (fb[k] % fb[j]) continue;
					dp2[i][j].first += dp[i][k].first;
					dp2[i][j].second += dp[i][k].second;
				}
				if (dp2[i][j].second == n-1) dps.emplace_back(base_cost + dp2[i][j].first, fa[i] + fb[j]);
			}	
		}
		//cout << "dp2 (soh freq msm):" << endl;
		//for (auto& x : dp2) { for (auto& y : x) cout << y.second << ' '; cout << endl; }
		//cout << "dp2 (soh custo):" << endl;
		//for (auto& x : dp2) { for (auto& y : x) cout << y.first << ' '; cout << endl; }
		swap(a[0], b[0]);
		base_cost += c[0];
		//cout << "END OF ITERATION#################" << endl;
	}
	sort(all(dps));
	vector<ii> ndp;
	for (auto [x, y] : dps) {
		while (!ndp.empty() && ndp.back().second < y && ndp.back().first == x) ndp.pop_back();
		if (ndp.empty() or ndp.back().second < y) ndp.pb({x, y});
	}
	//cout << "DPS:" << endl;
	//for (auto x : dps) cout << x.first << ' ' << x.second << endl;
	swap(ndp, dps);
	vector<int> resps;
	for (auto cost : queries) {
		int ans = lower_bound(all(dps), make_pair(cost+1, 0ll)) - begin(dps) - 1;
		resps.pb(dps[ans].second);
	}
	return resps;
}

mt19937 rng(time(0));

int rnd(int l, int r) {
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}

int32_t main(){_
	int tt = 0;
	while (true) {
		int n = rnd(1, 10), maxval = 10000000;
		vector<int> a(n), b(n), c(n);
		for (auto& x : a) x = rnd(1, maxval);
		for (auto& x : b) x = rnd(1, maxval);
		for (auto& x : c) x = rnd(1, 5);
		vector<ii> dps;
		for (int i = 0; i < (1 << n); ++i) {
			int totcost = 0, g1 = 0, g2 = 0;
			for (int j = 0; j < n; ++j) {
				if ((i>>j)&1) {
					totcost += c[j];
					g1 = gcd(g1, b[j]);
					g2 = gcd(g2, a[j]);
				} else g1 = gcd(g1, a[j]), g2 = gcd(g2, b[j]);	
			}
			dps.pb({totcost, g1 + g2});
		}
		sort(all(dps));
		int qmax = dps.back().first;
		vector<int> q(qmax+1); iota(all(q), 0);
		auto my = solve(n, sz(q), a, b, c, q);
		vector<int> correct;
		for (int i = 0, j = 0; i <= qmax; ++i) {
			int best = 0;
			for (auto [x, y] : dps) {
				if (x > i) break;
				ckmax(best, y);
			}
			correct.pb(best);
		}
		if (correct != my) {
			cout << "Wrong answer on test " << ++tt << endl;
			cout << n << ' ' << sz(q) << endl;
			for (auto x : a) cout << x << ' ';
			cout << endl;
			for (auto x : b) cout << x << ' ';
			cout << endl;
			for (auto x : c) cout << x << ' ';
			cout << endl;
			for (auto x : q) cout << x << ' ';
			cout << endl;
			cout << "Your output: ";
			for (auto x : my) cout << x << ' ';
			cout << endl;
			cout << "Answer: ";
			for (auto x : correct) cout << x << ' ';
			cout << endl;
			cout << "dps: ";
			for (auto [x, y] : dps) cout << x << ' ' << y << endl;
			exit(0);
		}
		cout << "Accepted on test " << ++tt << endl;
	}	
}
