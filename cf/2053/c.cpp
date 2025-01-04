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
	auto calc = [&] (auto&& self, int l, int r) {
		int tam = r-l+1;
		ii score = {0, 0};
		if (tam < k) return score;	
		int md = (l+r)/2;
		ii le;
		if (tam&1) {
			score.first += md, score.second = 1, le = self(self, l, md-1);
		} else {
			le = self(self, l, md);

		}
		score.second += 2 * le.second;
		score.first += le.first + (r+1) * le.second - le.first;
		return score;

	};
	int ans = 0;
	auto na_mao = [&] (auto&& self, int l, int r) {
		int tam = r-l+1;
		if (tam < k) return;	
		int md = (l+r)/2;
		if (tam&1) ans += md, self(self, l, md-1), self(self, md+1, r);
		else self(self, l, md), self(self, md+1, r);	
	};
	cout << calc(calc, 1, n).first << endl;
	//na_mao(na_mao, 1, n);
	//cout << ans << endl;
}

int32_t main(){_
  int t = 1; cin >> t;
  while(t--) solve();
}
