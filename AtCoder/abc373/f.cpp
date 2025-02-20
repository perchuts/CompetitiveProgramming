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
    int n, W; cin >> n >> W;
    vector<int> w(n), v(n), dp(W+1);
    vector<vector<int>> vals(W+1);
    for (int i = 0; i < n; ++i) cin >> w[i] >> v[i], vals[w[i]].pb(v[i]);
    for (int peso = 1; peso <= W; ++peso) { 
        if (vals[peso].empty()) continue;
        vector<int> used(sz(vals[peso]));
        priority_queue<ii> pq;
        for (int i = 0; i < sz(vals[peso]); ++i) pq.push({vals[peso][i]-1, i});
        int lim = W / peso;
        vector<int> dp2 = {0};
        while (sz(dp2) != lim+1) {
            auto [best, id] = pq.top(); pq.pop();
            dp2.pb(dp2.back()+best);
            used[id]++;
            pq.push({vals[peso][id]-2*used[id]-1, id});
        }
        vector<int> ndp(W+1);
        for (int i = 0; i <= W; ++i) for (int j = 0; j <= i/peso; ++j) ckmax(ndp[i], dp[i-j*peso] + dp2[j]);
        swap(ndp, dp);
    }
    cout << *max_element(all(dp)) << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
