#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
//#define stress

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ii = pair<int,int>;
using iii = tuple<int,int,int>;

const int inf = 2e9+1;
const int mod = 1e9+7;
const int maxn = 2e5+1;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

ii trie[15+maxn*15*4][10];
ll solve(int n, vector<ll> a){
	ll ans = 0;
	for (auto& x : a) {
		string s = to_string(x);
		for (auto d : s) ans += n * 2 * (d - '0'); 
	}
	vector<vector<int>> digits(n, vector<int>(15));
	for (int i = 0; i < n; ++i) for (ll j = 0, tmp = a[i]; j < 15; ++j, tmp /= 10) digits[i][j] = tmp % 10;
	int h = 15;
	for (int i = 0; i < n; ++i) {
		for (int start = 0; start < 15; ++start) {
			int cur = start;
			for (int j = start; j < 15; ++j) {
				int d = digits[i][j];
				if (trie[cur][d].first == 0) {
					trie[cur][d].first = h++;
				}
				trie[cur][d].second++;
				cur = trie[cur][d].first;
			}
		}
	}
	for (int i = 0; i < n; ++i) {
		ll cr = 0;
		for (int start = 0; start < 15; ++start) {
			for (int d2 = 10 - digits[i][start]; d2 < 10; ++d2) {
				int cur = start;
				cr += trie[cur][d2].second;
				cur = trie[cur][d2].first;
				if (cur == 0) continue;
				for (int j = start+1; j < 15; ++j) {
					cr += trie[cur][9-digits[i][j]].second;
					cur = trie[cur][9-digits[i][j]].first;
					if (cur == 0) break;
				}
			}
		}
		ans -= 9 * cr;
	}
	return ans;
}

int brute(int n, vector<ll> a) {
	int ans = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			ll x = a[i] + a[j];
			string s = to_string(x);
			for (auto c : s) ans += c - '0';
		}
	}
	return ans;
}

int32_t main(){_
#ifdef stress
	int t = 1;
	while (true) {
		int n = rnd(1, 15);
		vector<ll> v(n);
		for (auto& x : v) x = rnd(1, 1e15-1);
		ll my = solve(n, v), br = brute(n, v);
		if (br != my) {
			cout << "Wrong answer on test " << t << endl;
			cout << n << endl;
			for (auto x : v) cout << x << ' ';
			cout << endl;
			cout << "Your output: " << my << endl;
			cout << "Correct answer: " << br << endl;
			exit(0);
		}
		cout << "Accepted on test " << t++ << endl;
	}
#else
	int n; cin >> n;
	vector<ll> a(n);
	for (auto& x : a) cin >> x;
	cout << solve(n, a) << endl;
#endif
}
