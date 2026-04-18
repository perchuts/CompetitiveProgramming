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
const int mod = (119<<23)+1;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}
int crivo[10000001]; 
array<int, 4> mx[10000001];

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    vector<int> appear;
    for (int i = 0; i < n; ++i) {
        int cur = a[i];
        while (cur != 1) {
            int cnt = 0, p = crivo[cur];
            appear.pb(p);
            while (crivo[cur] == p) cur /= p, cnt++;
            if (cnt > mx[p][2]) {
                if (cnt >= mx[p][0]) {
                    mx[p][2] = mx[p][0];
                    mx[p][3] = mx[p][1];
                    mx[p][0] = cnt, mx[p][1] = i;
                } else {
                    mx[p][2] = cnt, mx[p][3] = i;
                }
            }
        }
    }
    sort(all(appear));
    appear.erase(unique(all(appear)), end(appear));
    auto fexp = [&] (int b, int e) {
        int ans = 1;
        while (e) {
            if (e&1) ans = ans * b % mod;
            e /= 2, b = b * b % mod;
        }
        return ans;
    };
    int ans = 1;
    for (auto p : appear) {
        for (int i = 0; i < mx[p][0]; ++i) ans = ans * p % mod;
    }
    for (int i = 0; i < n; ++i) {
        int cur = a[i];
        int ansi = ans;
        while (cur != 1) {
            int cnt = 0, p = crivo[cur];
            while (crivo[cur] == p) cur /= p, cnt++;
            if (cnt == mx[p][0] and mx[p][2] != cnt) {
                ansi = ansi * fexp(p, (mx[p][0]-mx[p][2]) * (mod-2)) % mod;
            }
        }
        cout << ansi << ' ';
    }
    cout << endl;
    for (auto p : appear) mx[p] = {0, 0, 0, 0};
}

int32_t main() {_
    int MX = 10000000;
    for (int i = 2; i <= MX; ++i) {
        if (crivo[i]) continue;
        crivo[i] = i;
        for (int j = i * i; j <= MX; j += i) if (crivo[j] == 0) crivo[j] = i;
    }
#ifndef gato
    int t = 1; cin >> t;
    while(t--) solve();
#else
    int t = 1;
    while (true) {
        int my = solve(), ans = brute();
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
