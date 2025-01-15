#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
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
	vector<int> szs(n+1);
	int tam = (1 << n);
	for (int i = 1; i < (1LL << tam); ++i) {
		if (__builtin_popcount(__builtin_popcount(i)) != 1) continue;
		cout << i << ' ' << i / (double)(1LL << tam) << endl;
		vector<int> space;
		int tt = 0, mnsize = n;
		for (int j = 0; j < tam; ++j) if (i >> j & 1) {
			space.pb(j);
			if (j) ckmin(mnsize, __builtin_popcount(j));
		}
		vector<int> bits(n);
		for (auto x : space) {
			for (int j = n-1; ~j; --j) {
				if (x == 0) break;
				if (x >> j & 1) {
					if (bits[j]) x ^= bits[j]; 
					else {
						bits[j] = x, tt++;
						break;
					}
				}
			}
		}
		if ((1 << tt) == __builtin_popcount(i) and mnsize == n - tt + 1) {
			szs[tt]++;
		}
			
	}
	for (int i = 1; i <= n; ++i) {
		cout << "conjuntos LI de tamanho " << i << ": " << szs[i] << endl;
	}
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
