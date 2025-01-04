#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
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

vector<vector<int>> solve(int n, int k){
	vector<vector<int>> ans;
	if (n % 2 == 0 and k % 2 == 1) {
		return ans;
	}
	if (k == 1) {
		if (n == 1) {
			ans.pb({1});
			return ans;
		}
		return ans;
	}
	if (n <= 10) {
		int fat = 1;
		for (int i = 2; i <= n; ++i) fat *= i;
		if (k > fat or k + 1 == fat) return ans;
	}
	map<vector<int>, bool> foi;
	if (k % 2 == 0) {
		vector<int> p(n); iota(all(p), 1);		
		do {
			if (foi[p] == 0) {
				ans.pb(p);
				vector<int> p2(n);
				for (int i = 0; i < n; ++i) p2[i] = n+1-p[i];
				ans.pb(p2);
				foi[p] = foi[p2] = 1;
				k -= 2;
			}
		} while (next_permutation(all(p)) and k > 0);
		return ans;
	}	
	vector<int> p(n); iota(all(p), 1);		
	foi[p] = 1;
	vector<int> p2(n), p3(n);
	for (int i = 0; i <= n/2; ++i) p2[i] = n/2+1+i;
	for (int i = n/2+1;i < n; ++i) p2[i] = (i-n/2);
	for (int i = 0; i < n; ++i) p3[i] = (3*(n+1))/2 - p[i] - p2[i]; 
	foi[p2] = foi[p3] = 1;
	k -= 3;
	ans.pb(p), ans.pb(p2), ans.pb(p3);
	// agora quero encontrar duas permutacoes boask
	do {
		if (foi[p] == 0) {
			for (int i = 0; i < n; ++i) p2[i] = n+1-p[i];
			if (!foi[p2]) {
				ans.pb(p), ans.pb(p2);
				foi[p] = foi[p2] = 1;
				k -= 2;
			}
		}
	} while (next_permutation(all(p)) and k > 0);
	return ans;
}

void brute(int n, int k) {
	vector<vector<int>> perms;
	vector<int> cur(n);
	iota(all(cur), 1);
	do {
		perms.pb(cur);
	} while (next_permutation(all(cur)));
	vector<vector<int>> ans;
	auto recurse = [&] (auto&& self, vector<vector<int>> &act, int id) -> bool {
		if (sz(act) == k) {
			int s = 0, ok = 1;
			for (int i = 0; i < k; ++i) s += act[i][0];
			for (int i = 1; i < n; ++i) {
				int s2 = 0;
				for (int j = 0; j < k; ++j) s2 += act[j][i];
				ok &= (s2 == s);
				if (!ok) break;
			}
			if (ok) {
				ans = act;
				return true;
			}
			return false;
		}
		if (id == sz(perms)) return false;
		act.pb(perms[id]);
		if (self(self, act, id+1)) return true;
		act.pop_back();
		return self(self, act, id+1);
	};
	vector<vector<int>> tmp;
	recurse(recurse, tmp, 0);
	if (ans.empty()) cout << "L" << endl;
	else {
		for (auto x : ans) {
			for (auto y : x) cout << y << ' ';
			cout << endl;
		}
	}
}

int32_t main(){_
  //brute(n, k);
  //return 0;
	int t = 1;
#ifdef STRESS
	while (t) {
		int n = rnd(1, 10), k = rnd(1, 1000);
		auto ans = solve(n, k);
		if (ans.empty()) continue;
		map<vector<int>, int> mp;
		bool ok = 1;
		int s = 0;
		for (int i = 0; i < k; ++i) s += ans[i][0];
		for (int i = 1; i < n; ++i) {
			int s2 = 0;
			for (int j = 0; j < k; ++j) s2 += ans[j][i];
			ok &= (s2 == s);
			if (!ok) break;
		}
		if (!ok) {
			cout << "WA2: " << n << ' ' << k << endl;
			exit(0);
		}
		for (int i = 0; i < k; ++i) {
			if (mp[ans[i]]) {
				cout << "WA1: " << n << ' ' << k << endl;
				exit(0);
			}
			mp[ans[i]] = 1;
		}
		cout << "Accepted on test " << t << endl;
	}
#endif
  t = 1; cin >> t;
  while (t--) {
		int n, k; cin >> n >> k;
		auto ans = solve(n, k);
		if (ans.empty()) cout << "NO" << endl;
		else {
			cout << "YES" << endl;
			for (auto x : ans) {
				for (auto y : x) cout << y << ' ';
				cout << endl;
			}	
		}				
  }

}
