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
	int b, c, d; cin >> b >> c >> d;
	// bits de A que nao estao ligados no C + bits de B que nao estao ligados no A = D
	// entao posso particionar D como duas coisas: alguns bits de A + alguns bits de B
	// D&C tem que estar no B
	// os bits de D que nao estao no C -> ponho no A?
	// (d&(!c)|b) = d
	int x = (d&c), y = (b - (b&d));
	// preciso ligar todos de Y no a!! pois caso contrario o b vai zoar o d
	// e de certa forma o c tem que ter y
	if ((x&b) != x or (y&c) != y) cout << -1 << endl;
	else {
		int a = ((d-x)|y);
		if ((a|b) - (a&c) != d) cout << -1 << endl;
		else cout << a << endl;
	}
}

int32_t main(){_
  int t = 1; cin >> t;
  while(t--) solve();
}
