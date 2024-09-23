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
 	int n, k; cin >> n >> k;
	string s; cin >> s;
	if (n == k) {
		int ans = 0;
		for (int i = 1; i < n; ++i) {
			ans += (s[i] == s[i-1] && s[i-1] == 'X');
		}
		cout << ans << endl;
		return;
	}
	vector<ii> gaps;
	int gap = 0;
	for (int i = 0; i < n; ++i) {
		if (s[i] == 'Y') {
			if (gap) gaps.pb({(gap==i), gap});
			gap = 0;
		} else gap++;
	}
	if (gap) gaps.pb({1, gap});
	if (gap==n) {
		cout << max(0ll, k-1) << endl;
		return;
	}
	sort(all(gaps));
	int win = 0;
	for (auto [border, x] : gaps) {
		if (x > k) {
			win += k;
			k = 0;
			break;
		}
		k -= x;
		win += x+(border^1);
	}
	int ini = 0;
	for (int i = 0; i < n-1; ++i) ini += (s[i] == s[i+1] && s[i] == 'Y');
	if (k != 0) {
		gap = 0;
		gaps.clear();
		for (int i = 0; i < n; ++i) {
			if (s[i] == 'X') {
				if (gap) gaps.pb({(gap==i), gap});
				gap = 0;
			} else gap++;
		}
		if (gap) gaps.pb({1, gap});
		sort(gaps.rbegin(), gaps.rend());
		for (auto [border, x] : gaps) {
			if (x >= k) {
				win -= k+(border^1);
				k = 0;
				break;
			}
			k -= x;
			win -= x+(border^1);
		}
	}
	cout << ini+win << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
