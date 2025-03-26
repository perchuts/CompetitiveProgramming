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
    int n, m, L; cin >> n >> m >> L;
    vector<int> pos(n), tams(m);
    for (auto& x : pos) cin >> x;
    for (auto& x : tams) cin >> x;
    sort(all(pos));
    sort(all(tams));
    tams.pb(-1);
    int l = 0, r = m-1, ans = m;
    while (l <= r) {
        int md = l + (r-l+1)/2;
        bool ok = 1;
        for (int i = 1; i < n; ++i) ok &= (pos[i] - pos[i-1] <= 2*tams[md]);
        ok &= (pos[0] <= tams[md]);
        ok &= (L - pos.back() <= tams[md]);
        if (ok) ans = md, r = md-1;
        else l = md+1;
    }
    cout << tams[ans] << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
