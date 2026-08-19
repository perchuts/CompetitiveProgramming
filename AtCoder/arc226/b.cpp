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
    int n, m; cin >> n >> m;
    vector<int> a(m);
    for (auto& x : a) cin >> x;
    // \sum 2^i * a[i] / n
    int ans = 0, ptr = 0, want = (1LL << (m-1)), need = 0;
    for (int i = m-1; ~i; --i) {
        int eu = (1LL << i);
        if (ptr == 0) {
            int k = a[i] / n;
            ans += k * eu;
            a[i] %= n;
            if (a[i]) {
                ans += eu;
                want = need = eu;
                ptr = a[i];
            }
        } else {
            assert(need);
            if (a[i] < need / eu) {
                need -= eu * a[i];
                continue;
            }
            a[i] -= need / eu;
            ptr = (1 + ptr) % n;
            need = want;
            if (ptr == 0) {
                int k = a[i] / n;
                ans += k * eu;
                a[i] %= n;
                if (a[i]) {
                    ans += eu;
                    want = need = eu;
                    ptr = a[i];
                }
            } else {
                int custo = want / eu;
                if ((n - ptr) * custo > a[i]) {
                    ptr += a[i] / custo;
                    a[i] %= custo;
                    need = want - eu * a[i];
                } else {
                    a[i] -= (n - ptr) * custo;
                    ptr = 0;
                    int k = a[i] / n;
                    ans += k * eu;
                    a[i] %= n;
                    if (a[i]) {
                        ans += eu;
                        want = need = eu;
                        ptr = a[i];
                    }
                }
            }
        }
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
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
