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
    int n, K; cin >> n >> K;
    vector<int> v;
    int cur = K;
    for (int i = 2; i * i <= K; ++i) {
        int cnt = 0;
        while (cur % i == 0) cnt++, cur /= i;
        if (cnt) v.pb(cnt);
    }
    if (cur != 1) v.pb(1);
    auto mult = [] (vector<int> a, vector<int> b) {
        vector<int> c(4);
        c[0] = {a[0] * b[0] + a[1] * b[2]};
        c[1] = {a[0] * b[1] + a[1] * b[3]};
        c[2] = {a[2] * b[0] + a[3] * b[2]};
        c[3] = {a[2] * b[1] + a[3] * b[3]};
        for (auto& x : c) x %= mod;
        return c;
    };
    auto fexp = [&] (vector<int> v, int e) {
        vector<int> ans = {1, 0, 1, 0};
        while (e) {
            if (e&1) ans = mult(ans, v);
            v = mult(v, v), e /= 2;
        }
        return ans;
    };
    int resp = 1;
    auto f = [&] (int N, int k) {
        if (N == 2) return 2 * k + 1;
        auto M = fexp({1, k, 1, 0}, N-3);
        vector<int> base = {k*k + 3*k + 1, 2 * k + 1};
        int eu = (base[0] * M[0] + base[1] * M[1]) % mod;
        return eu;
    };
    for (auto k : v) resp = resp * f(n, k) % mod;
    cout << resp << endl;
}

int32_t main(){_
    int t = 1; cin >> t;
    while(t--) solve();
}
