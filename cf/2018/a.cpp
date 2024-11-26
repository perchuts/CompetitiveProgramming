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
	int n, k; cin >> n >> k;
	vector<int> v(n); 
	int big = 0, S = 0;
	for (auto& x : v) cin >> x, ckmax(big, x), S += x;
	// se o deck vai ter tamanho m, preciso ter um multiplo de m de cartas
	// e quando que da pra dividir?
	// se tenho m*x cartas, vou dividir em x decks.
	// a maior frequencia n pode ser maior q x
	int ans = 1;
	for (int m = 1; m <= n; ++m) {
		// preciso achar o menor numero de cartas pra comprar de forma que (n+a) eh multiplo de m E (n+a)/m eh no maximo
		int mn = max((S + m - 1) / m * m, big * m);
		if (k >= mn - S) ckmax(ans, m);
	}
	cout << ans << endl;

}

int32_t main(){_
  int t = 1; cin >> t;
  while(t--) solve();
}