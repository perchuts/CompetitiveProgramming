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
	int l = -1, r = -1;
	for (int i = 0; i < n; ++i) {
		if (l == -1 && s[i] == '1') l = i;
		if (s[i] == '1') r = i;
	}
	if (l == -1) {
		int mx = 0, cur = 0;
		for (int i = 0; i < n; ++i) {
			if (s[i] == '?') cur++;
			else {
				if ((mx == k && cur == k) || (cur > k)) {
					cout << "No" << endl;
					return;
				}
				ckmax(mx, cur);
				cur = 0;
			}
		}
		if ((mx == k && cur == k) || (cur > k)) {
			cout << "No" << endl;
			return;
		}
		ckmax(mx, cur);
		if (mx == k) cout << "Yes" << endl;
		else cout << "No" << endl;
		return;
	}
	for (int i = l+1; i <= r; ++i) {
		if (s[i] == '0') {
			cout << "No" << endl;
			return;
		}
	}	
	int tot = r-l+1, lx = 0, rx = 0;
	for (int j = l - 1; j >= 0; --j) {
		if (s[j] != '?') break;
		lx++;
	}
	for (int j = r + 1; j < n; ++j) {
		if (s[j] != '?') break;
		rx++;
	}
	if (tot == k) {
		cout << "Yes" << endl;
		return;
	}
	if (tot + lx + rx < k || tot > k) cout << "No" << endl;
	else {
		// tem pelo menos uma solucao
		int s1 = min(lx, k - tot);
		int s2 = k - tot - min(rx, k - tot);
		if (s1 == s2) cout << "Yes" << endl;
		else cout << "No" << endl;
	}
}

int32_t main(){_
  int t = 1; cin >> t;
  while(t--) solve();
}
