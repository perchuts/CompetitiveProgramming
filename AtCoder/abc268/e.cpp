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
    int n; cin >> n;
    vector<int> p(n), onde(n);
    for (auto& x : p) cin >> x;
    for (int i = 0; i < n; ++i) onde[p[i]] = i;
    int ans = 1e18;
    vector<int> cL(n), cR(n);
    for (int i = 0; i < n; ++i) {
        int st = (onde[i] < i ? i - onde[i] : n - (onde[i] - i));

        if (st > 0) cL[st-1]++;
        st -= n/2 + 1;
        if (n % 2) {
            if (st >= 0) cL[st]--;	
            if (st > 0) cL[st-1]--;
        } else if (st >= 0) cL[st] -= 2;

        st += n/2 + 1;

        if (st < n-1) cR[st+1]++;
        st += n/2 + 1;
        if (n % 2) {
            if (st < n) cR[st]--;	
            if (st < n-1) cR[st+1]--;
        } else if (st < n) cR[st] -= 2;
    }

    for (int i = n-2; i >= 0; --i) cL[i] += cL[i+1];
    for (int i = n-2; i >= 0; --i) cL[i] += cL[i+1];
    for (int i = 1; i < n; ++i) cR[i] += cR[i-1];
    for (int i = 1; i < n; ++i) cR[i] += cR[i-1];

    for (int i = 0; i < n; ++i) ckmin(ans, cL[i] + cR[i]);
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
