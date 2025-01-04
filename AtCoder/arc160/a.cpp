#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

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
	int n, k; cin >> n >> k;
	vector<int> p(n), sm(n);
	for (auto& x : p) cin >> x;
	sm[n-1] = p.back();
	for (int i = n-2; i >= 0; --i) sm[i] = min(sm[i+1], p[i]);
	vector<int> ans;
	for (int i = 0; i < n; ++i) {
		int tem_eu = (n-1-i)*(n-i-2)/2+n, menor_q_eu = 0;
		for (int j = i + 1; j < n; ++j) menor_q_eu += (p[j] < p[i]);
		if (sm[i] != p[i] and k <= menor_q_eu) {
			vector<int> sobra;
			int l = i, r = -1;
			for (int j = i+1; j < n; ++j) sobra.pb(p[j]);	
			sort(all(sobra));
			for (int j = 0; j < n; ++j) if (p[j] == sobra[k-1]) r = j;
			reverse(begin(p)+l, begin(p)+r+1);
			break;
		}
		k -= menor_q_eu;
		if (k > tem_eu) {
			k -= tem_eu;
			vector<int> sobra;
			int l = i, r = -1;
			for (int j = i+1; j < n; ++j) if (p[j] > p[i]) sobra.pb(p[j]);	
			sort(all(sobra));
			for (int j = 0; j < n; ++j) if (p[j] == sobra[k-1]) r = j;
			reverse(begin(p)+l, begin(p)+r+1);
			break;
		}
	}
	for (auto x : p) cout << x << ' ';
	cout << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
