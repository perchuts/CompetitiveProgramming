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

void solve() {
    int n; cin >> n;
    vector<int> p(1<<n);
    for (auto& x : p) cin >> x, --x;
    auto sorta = [&] (auto&& self, int l, int r) -> void {
        if (l == r) return;
        vector<int> nv;
        int md = (l+r)/2;
        self(self, l, md), self(self, md+1, r);
        if (p[l] > p[md+1]) {
            for (int i = l; i <= md; ++i) swap(p[i], p[md+1+i-l]);
        }
    };
    sorta(sorta, 0, (1<<n)-1);
    for (auto x : p) cout << x + 1 << ' ';
    cout << endl;
}

int32_t main() {_
    int t = 1; cin >> t;
    while(t--) solve();
}
