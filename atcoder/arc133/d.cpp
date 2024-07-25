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
const int mod = 998244353;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

void solve(){
	int l, r, v; cin >> l >> r >> v;
	// 4k -> 4k
	// 4k+1 -> 1
	// 4k+2 -> 4k+3
	// 4k+3 -> 0
	int cnt0 = (r+1)/4 - (l-1)/4 + (l == 1);
	int cnt1 = (r+3)/4 - (l+1)/4;
	cnt0 %= mod, cnt1 %= mod;
	if (v == 0) {
		int inv2 = 998244354/2;
		cout << ((cnt0*(cnt0-1+mod))%mod*inv2 + (cnt1*(cnt1-1+mod))%mod*inv2)%mod << endl;
		exit(0);
	} 
	if (v == 1) {
		cout << cnt0*cnt1%mod << endl;
		exit(0);
	}
	// esses sao os unicos casos que quero usar os bicho pequeno
	int use_one = 0;
	if (v % 4 == 0) use_one = (l-1 <= v && v <= r ? cnt0 : 0); 
	if (v % 4 == 1) use_one = (l-1 <= v-1 && v-1 <= r ? cnt1 : 0);
	if (v % 4 == 2) use_one = (l-1 <= v && v <= r ? cnt1 : 0);
	if (v % 4 == 3) use_one = (l-1 <= v-1 && v-1 <= r ? cnt0 : 0);
	if (v % 4 == 1 || v % 4 == 2) {
		cout << use_one << endl;
		return;
	}
	if (r%4==2) r++;
	if (l%4==1) l--;
	int ans = 0;
	vector<int> pot(60, 1);
	for (int i = 1; i < 60; ++i) pot[i] = 2*pot[i-1]%mod;
	for (int a = 59; a >= 1; --a) {
		for (int b = 59; b >= 1; --b) {
			for (int c = 59; c >= 1; --c) {
				bool ok = 1;
				int ways = 1;
				for (int i = 59; i >= min({a,b,c}); --i) {
					int x = (r>>i)&1, y = (l>>i)&1, z = (v>>i)&1;
					int px = 3, py = 3;

					if (i > a) px = (x ? 1 : 2);
					if (i > b) py = (y ? 1 : 2);

					if (i == a) ok &= (x == 1), px = 2;
					if (i == b) ok &= (y == 0), py = 1;

					if (i == c) ok &= ((px&1) && (py&2) && z == 1);
					else if (i > c) {
						int p = ((px&1)&&(py&1)) + ((px&2)&&(py&2));
						ok &= (p != 0 && z == 0), ways = (ways * p) % mod;
					} else {
						if (z == 0) {
							int p = ((px&1)&&(py&1)) + ((px&2)&&(py&2));
							ok &= (p != 0), ways = (ways * p) % mod;
						} else {
							int p = ((px&1)&&(py&2)) + ((px&2)&&(py&1));
							ok &= (p != 0), ways = (ways * p) % mod;
						}
					}
				}
				if (ok) ans = (ans + ways*pot[min({a,b,c})-1])%mod;
			}
		}
	}
	set<ii> corners;
	for (int j = 0; j < 2; ++j) {
		for (int i = l - 3; i < l + 4; ++i) {
			if (i <= 0) continue;
			if (i % 4 == 0 || i % 4 == 3) {
				if ((i ^ l) < 2) {
					int need = (i ^ v);
					if (min(l, r) <= need && need <= max(l, r)) {
						if (min(i, need) > 1) corners.insert({min(i, need), max(i, need)});
					}
				}
			}
		}	
		swap(l, r);
	}
	ans += corners.size();
	cout << (ans + use_one) % mod << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
