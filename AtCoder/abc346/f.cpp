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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}

void solve(){
	int n; cin >> n;
	string s, t; cin >> s >> t;
	int l = 1, r = sz(s) * n, ans = 0, m = sz(s);
	vector<vector<int>> freq(m+1, vector<int>(26));
	for (int i = 1; i <= m; ++i) for (int j = 0; j < 26; ++j) {
		if (s[i-1] - 'a' == j) freq[i][j] = 1 + freq[i-1][j];
		else freq[i][j] = freq[i-1][j];
	}
	auto get_index = [&] (int c, int pos, int k) {
		int l1 = pos, r1 = m, go = m;
		while (l1 <= r1) {
			int md = l1 + (r1-l1+1)/2;
			if (freq[md][c] - freq[pos-1][c] >= k) go = md, r1 = md-1;
			else l1 = md+1;
		}
		return go;
	};
	auto possible = [&] (int k) {
		int copy = 1, pos = 1;
		for (auto C : t) {
			if (copy > n) return false;
			int c = C - 'a';
			if (freq[m][c] == 0) return false;
			int go = get_index(c, pos, k); 
			//cout << C << " " << pos << ' ' << copy << ' ' << go << endl;
			if (go < m and freq[go][c] - freq[pos-1][c] == k) {
				pos = go+1;
				continue;
			}
			int falta = k - (freq[m][c] - freq[pos-1][c]);
			int full = falta / freq[m][c];
			if (falta % freq[m][c]) {
				copy += full + 1;
				//cout << copy << endl;
				if (copy > n) return false;
				pos = get_index(c, 1, falta % freq[m][c]) + 1;
			} else if (falta) {
				copy += full;
				if (copy > n) return false;
				pos = get_index(c, 1, freq[m][c])+1;
				if (pos == m+1) pos = 1, copy++;
			} else copy++, pos = 1;
		}
		return true;
	};
	//possible(3);
	//return;
	while (l <= r) {
		int md = l + (r-l+1)/2;
		if (possible(md)) ans = md, l = md+1;
		else r = md-1;
	}
	cout << ans << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
