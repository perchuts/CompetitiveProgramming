#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll
//#define stress

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

int solve(string s, int l, int r){
	string R = to_string(r), L = to_string(l);
	string zz;
	while (sz(zz) + sz(L) < sz(R)) zz += '0';
	zz += L, swap(zz, L);
	int common = 0;
	while (common < sz(R) and L[common] == R[common]) common++;
	vector<int> pot(18, 1);
	for (int i = 1; i < 18; ++i) pot[i] = 10 * pot[i-1];
	int ans = 0;
	for (int i = 0; i + sz(s) <= sz(R); ++i) {
		for (int j = common; j <= sz(R); ++j) {
			bool ok = 1;
			for (int k = 0; k < j; ++k) {
				if (i <= k and k <= i + sz(s) - 1) ok &= (s[k-i] == R[k]);
			}
			int cur = 1;
			if (i <= j and j <= i + sz(s) - 1) {
				if (j == common) ok &= (L[j] < s[j-i] and s[j-i] < R[j]); 
				else ok &= (s[j-i] < R[j]);
			}
			else if (j < sz(R)) {
				if (j == common) cur *= (R[j] - L[j] - 1);
				else cur *= (R[j] - '0'); 
			}
			for (int k = 0; k < sz(R); ++k) {
				if ((k < i or k > i + sz(s) - 1) and k > j) cur *= 10;
			}
			if (ok) ans += cur;
		}
		for (int j = common+1; j <= sz(R); ++j) {
			bool ok = 1, soh_zero = (s[0] == '0');
			for (int k = 0; k < j; ++k) {
				if (i <= k and k <= i + sz(s) - 1) ok &= (s[k-i] == L[k]);
			}
			for (int k = 0; k < i; ++k) {
				if (k < j) soh_zero &= (L[k] == '0');
				else soh_zero = 0;
			}
			if (soh_zero) continue;
			int cur = 1;
			if (i <= j and j <= i + sz(s) - 1) ok &= (s[j-i] > L[j]);
			else if (j != sz(R)) cur *= ('9' - L[j]); 
			for (int k = 0; k < sz(R); ++k) {
				if ((k < i or k > i + sz(s) - 1) and k > j) cur *= 10;
			}
			if (ok) ans += cur;
		}
	}
	return ans;
}

int brute(string s, int l, int r) {
	int ans = 0;
	for (int i = l; i <= r; ++i) {
		string x = to_string(i);
		for (int j = 0; j + sz(s) <= sz(x); ++j) {
			int ok = 1;
			for (int k = j; k < j + sz(s); ++k) ok &= (x[k] == s[k-j]);
			ans += ok;
		}
	}
	return ans;
}
int32_t main(){_
#ifndef stress
  int t = 1; cin >> t;
  while(t--) {
	  string s; int l, r; cin >> s >> l >> r;
	  cout << solve(s, l, r) << endl;
  }
#else 
	int t = 1;
 	while (true) {
		int l = rnd(1, 100000), r = rnd(l, 100000);
		string s = "";
		while (true) {
			int y = rnd(1, 2);
			if (y == 2 and sz(s)) break;
			s += char('0'+rnd(0, 9));
		}
		int my = solve(s, l, r), ans = brute(s, l, r);
		if (my != ans) {
			cout << "Wrong answer on test " << t << endl;
			cout << s << ' ' << l << ' ' << r << endl;
			cout << "Your output: " << my << endl;
			cout << "Answer: " << ans << endl;
			exit(0);
		}
		cout << "Accepted on test " << t++ << endl;
	}
#endif
}
