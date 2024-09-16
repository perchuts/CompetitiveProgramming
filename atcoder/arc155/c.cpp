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
 	int n; cin >> n;
	vector<int> a(n), b(n);
	for (auto& x : a) cin >> x;
	for (auto& x : b) cin >> x;
	auto a2 = a;
	auto b2 = b;
	sort(all(a2)), sort(all(b2));
	if (a2 != b2) {
		cout << "No" << endl;
		return;
	}
	int lst = -3414, mn = 3, ev = 0, lst2 = -3232, mn2 = 3;
	for (int i = 0; i < n; ++i) {
		if (a[i]&1) ckmin(mn, i - lst), lst = i;
		else ev++;
		if (b[i]&1) ckmin(mn2, i - lst2), lst2 = i;
	}
	if (mn2 == 3) {
		goto fim;
	}
	if (mn < 3 && ev >= 3) {
		cout << "Yes" << endl;
		return;
	}
	if (ev < 3) {
		// cant invert evens
		if (mn == 3 or ev == 0) {
			cout << (a == b ? "Yes" : "No") << endl;
			return;
		}
		// so i guess i can do anything between blacks, but order of white ones cant change
		// -> can reach anything except something that i inverted the whites
		if (ev == 1) {
			cout << "Yes" << endl;
			return;
		}
		vector<int> ae, eb;
		for (int i = 0; i < n; ++i) if (a[i] % 2 == 0) ae.pb(a[i]);
		for (int i = 0; i < n; ++i) if (b[i] % 2 == 0) eb.pb(b[i]);
		cout << (ae == eb ? "Yes" : "No") << endl;
		return;
	}	
fim:
	vector<int> aa, bb;
	bool ok = 1;
	for (int i = 0; i < n; ++i) {
		if (a[i]&1) {
			ok &= (a[i] == b[i]);
			if (sz(aa) > 2) sort(all(aa)), sort(all(bb));
			ok &= (aa == bb);
			aa.clear(), bb.clear();
		} else aa.pb(a[i]), bb.pb(b[i]);
	}
	if (sz(aa) > 2) sort(all(aa)), sort(all(bb));
	ok &= (aa == bb);
	cout << (ok ? "Yes" : "No") << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
