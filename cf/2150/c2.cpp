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
    vector<int> a(n), b(n), v(n);
    for (auto& x : v) cin >> x;
    for (auto& x : a) cin >> x, --x;
    for (auto& x : b) cin >> x, --x;
    vector<int> seg(4*n, -1e18);
    auto upd = [&] (auto&& self, int i, int l, int r, int x, int k) -> void {
        if (l == r) {
            seg[i] = k;
            return;
        }
        int md = (l+r)/2;
        if (x <= md) self(self, 2*i, l, md, x, k);
        else self(self, 2*i+1, md+1, r, x, k);
        seg[i] = max(seg[2*i], seg[2*i+1]);
    };
    auto query = [&] (auto&& self, int i, int l, int r, int x, int y) -> int {
        if (r < x or y < l) return -1e18;
        if (x <= l and r <= y) return seg[i];
        int md = (l+r)/2;
        return max(self(self, 2*i, l, md, x, y), self(self, 2*i+1, md+1, r, x, y));
    };
    vector<int> seta(n);
    vector<ii> sexo2;
    sexo2.pb({inf, -1});
    vector<int> onde_b(n), dp(n);
    for (int i = 0; i < n; ++i) onde_b[b[i]] = i;
    for (int i = 0; i < n; ++i) {
        while (sexo2.back().first < onde_b[a[i]]) sexo2.pop_back();
        seta[a[i]] = sexo2.back().second;
        sexo2.pb({onde_b[a[i]], i});
    }
    cout << endl;
    set<ii> sexo;
    int id = 0, ans = 0;
    // ordena os cara
    for (auto i : a) {
        int j = onde_b[i];
        dp[i] = query(query, 1, 0, n-1, max(0LL, seta[i]), id) + v[i];
        if (seta[i] == -1) dp[i] = max(dp[i], v[i]);
        while (!sexo.empty()) {
            auto it = begin(sexo);
            if ((it->first) < j) {
                upd(upd, 1, 0, n-1, it->second, -1e18);
                sexo.erase(it);
            } else break;
        }
        sexo.insert({j, id});
        upd(upd, 1, 0, n-1, id++, dp[i]);
        for (int z = 0; z < n; ++z) cout << query(query, 1, 0, n-1, z, z) << ' ';
        cout << endl;
        ckmax(ans, dp[i]);
    }
    cout << ans << endl;
}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
    while(t--) solve();
#else
    int t = 1;
    while (true) {
        int my = solve(), ans = brute();
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
