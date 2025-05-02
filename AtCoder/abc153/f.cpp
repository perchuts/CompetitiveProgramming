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
    int n, d, a; cin >> n >> d >> a;
    vector<int> pos(n), h(n);
    for (int i = 0; i < n; ++i) cin >> pos[i] >> h[i];
    vector<int> ord(n); iota(all(ord), 0); sort(all(ord), [&] (int x, int y) { return pos[x] < pos[y]; });
    ord.pb(n);
    int ans = 0, atv = 0, ptr = 0;
    vector<int> des(n+1);
    for (auto i : ord) {
        if (i == n) break;
        atv -= des[i];
        int left = (max(0LL, h[i] - a * atv)+a-1)/a;
        while (ptr < n and pos[ord[ptr]] <= pos[i]+2*d) ptr++;
        des[ord[ptr]] += left, ans += left, atv += left;
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
