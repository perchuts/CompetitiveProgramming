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
	vector<int> a(n);
	for (auto& x : a) cin >> x;
	vector<int> ord(n); iota(all(ord), 0);
	sort(all(ord), [&] (int x, int y) {
		return a[x] < a[y];
	});
	vector<int> at(n, n), fr(n);
	set<int> foi;
	for (auto x : ord) {
		int z = x-a[x]+1;
		if (!foi.empty()) {
			auto it = begin(foi);
			if ((*it) < z) at[x] = *it;
		}
		z = a[x] + x - 1;
		if (!foi.empty()) {
			auto it2 = (prev(end(foi)));
			if (*it2 > z) fr[x] = (*it2);
		}
		foi.insert(x);
	}
	vector<int> pr(n), suf(n, n);
	for (int i = 0; i < n; ++i) {
		if (i == 0) pr[i] = fr[i];
		else pr[i] = max(pr[i-1], fr[i]);
	}
	for (int i = n-1; i >= 0; --i) {
		if (i == n-1) suf[i] = at[i];
		else suf[i] = min(suf[i+1], at[i]);
	}
	int ans = 0;
	multiset<int> atras, frente;
	for (int i = 0; i < n; ++i) frente.insert(i - a[i]);	
	for (int i = 0; i < n; ++i) {
		bool ok = 1;
		frente.extract(i - a[i]);
		if (!atras.empty()) {
			auto x = *begin(atras);
			ok &= (i + 1 <= x);
		}
		if (!frente.empty()) {
			auto x = *(prev(end(frente)));
			ok &= (x <= i-1);
		}
		//for (int j = i+1; j < n; ++j) {
		//	for (int k = i-1; k >= 0; --k) {
		//		ok &= (j-k+1 <= max(a[j], a[k]));
		//	}
		//}
		atras.insert(a[i] + i);
		ok &= ((i == 0 or pr[i-1] < i) and (i == n-1 or suf[i+1] > i));
		ans += ok;
	}
	cout << ans << endl;
}

int32_t main(){_
  int t = 1; cin >> t;
  while(t--) solve();
}
