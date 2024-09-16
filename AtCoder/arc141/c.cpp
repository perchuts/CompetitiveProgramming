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
	vector<int> p(2*n), q(2*n);
	for (auto& x : p) cin >> x, --x;
	for (auto& x : q) cin >> x, --x;
	string s(2*n, '-');
	for (int i = 0; i < n; ++i) {
		if (p[2*i+1] < p[2*i]) {
			s[p[2*i+1]] = ')';
			s[p[2*i]] = '(';
		}
		if (q[2*i+1] > q[2*i]) {
			s[q[2*i]] = '(';
			s[q[2*i+1]] = ')';
		}
	}
	for (auto x : s) {
		if (x == '-') {
			cout << -1 << endl;
			exit(0);
		}
	}
	vector<int> abre, fecha;
	for (int i = 0; i < 2*n; ++i) {
		if (s[i] == '(') abre.pb(i);
		else fecha.pb(i);
	}
	vector<int> p2, q2;
	int a = 0, b = 0;
	for (int i = 0; i < 2 * n; ++i) {
		if (a == b) p2.pb(abre[a++]);
		else if (a != n && (b == n || abre[a] < fecha[b])) p2.pb(abre[a++]);
		else p2.pb(fecha[b++]);
	}
	a = n - 1, b = n - 1;
	for (int i = 0; i < 2 * n; ++i) {
		if (a == b) q2.pb(abre[a--]);
		else if (b != -1 && (a == -1 || abre[a] < fecha[b])) q2.pb(fecha[b--]);
		else q2.pb(abre[a--]);
	}
	if (p2 != p || q2 != q) cout << -1 << endl;
	else cout << s << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
