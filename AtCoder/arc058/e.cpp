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
vector<int> tr[6*maxn], h;
int mark[6*maxn], n, x, y, z;

int encode(deque<int> &dq) {
	int res = 0, sum = (dq.empty()?0:dq[0]), m = sz(dq);
	for (int i = 1; i < m; ++i) res += (1<<sum), sum += dq[i];
	res += (1<<sum);
	return res;
}

int gen(deque<int> vv, int sum) {
	if (sz(vv) > n) return -1;
	while (sum > x+y+z) sum -= vv.front(), vv.pop_front();
	int my = encode(vv);
	if (mark[my]) return min(mark[my], my);
	int m = sz(vv), foi = 2, cur = h[2];
	for (int i = m-1; min(foi, i) >= 0; --i) {
		cur -= vv[i];
		if (cur == 0) {
			--foi;
			if (foi < 0) break;
			cur = h[foi];
		}
		if (cur < 0) break;
	}
	if (foi == -1) return mark[my] = -1; 
	mark[my] = my;
	for (int i = 1; i <= 10; ++i) {
		vv.push_back(i);
		int code = gen(vv, sum + i);
		if (code != -1) tr[my].pb(code);
		vv.pop_back();
	}
	return my;
}

void solve(){
    cin >> n >> x >> y >> z;
    h = {x, y, z};
    gen({}, 0);
    map<int, int> dp;
    dp[1] = 1;
    for (int i = 1; i <= n; ++i) {
        map<int, int> ndp;
        for (auto [vv, val] : dp) { 
            for (auto d : tr[vv]) ndp[d] = (ndp[d] + val) % mod; 
		}
        swap(dp, ndp);
    }
    ll ans = 1;
    for (int i = 0; i < n; ++i) ans = ans * 10 % mod;
    for (auto [a, b] : dp) ans = (ans + mod - b) % mod;
    cout << ans << endl;
    
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
