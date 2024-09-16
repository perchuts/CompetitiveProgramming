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

void solve(){
 	int n, k; cin >> n >> k;
	vector<int> v(n), freq(1001), lixo;
	for (auto& x : v) cin >> x, freq[x]++;
	for (int i = 0; i <= 1000; ++i) {
		if (freq[i]&1) lixo.push_back(i);
	}
	swap(v, lixo);
	n = sz(v);
	vector<int> dp(2001), pot(100);

	pot[0] = dp[0] = 1;

	for (int i = 1; i < 100; ++i) pot[i] = pot[i-1] * n % 2;

	int ans = 0, pp = __builtin_popcountll(k);
	for (int bit = 0; bit < 60; ++bit) {
		vector<int> ndp(2001);
		pp -= (k>>bit)&1;
		for (int sum = 0; sum <= 2000; ++sum) {
			if ((k>>bit)&1)	{
				for (auto val : v) {
					int nsum = (val + sum)/2;
					ndp[nsum] ^= dp[sum];
					if ((val+sum)&1) {
						ans ^= (1ll<<bit)*(dp[sum]*pot[pp]);
					}
				}

			} else {
				int nsum = sum/2;
				ndp[nsum] ^= dp[sum];
				if (sum&1) {
					ans ^= (1ll<<bit)*(dp[sum]*pot[pp]);
				}
			}
		}	
		swap(ndp, dp);
	}

	cout << ans << endl;
	
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
