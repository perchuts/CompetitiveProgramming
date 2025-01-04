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
const int mod = (119<<23)+1;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}

void solve(){
	int ans = 0;
	int n; cin >> n;
	// 1 1 2
	// 1 1 3
	// 1 1 4
	// 1 1 5
	// e as 3 permutacoes disso
	// 2 2 2
	// 1 1 1
	//1 2 3
	for (int i = 1; i * i <= n; ++i) {
		ans += 1; // todos iguais a i
		ans += 3 * (n/i) - 3; // todos menos um iguais a i
		// agora, assuma q todos os elementos sao distintos, e q x < y < z
		// note q y <= sqrt(n) tambem! 
		// entao vamos brutar o valor de y...
		int k = n / i;
		if (k > i) ans += 6 * (k-i) * (i-1);
		ans %= mod;
	}
	cout << ans << endl;
}

int32_t main(){_
  int t = 1; cin >> t;
  while(t--) solve();
}
