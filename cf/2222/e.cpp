#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
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
    int tot = 0;
    int n; cin >> n;
    auto I = [&] (int x) {
        tot++;
        assert(tot <= n+3);
        cout << "I " << x << endl;
        int res; cin >> res;
        return res;
    };
    auto Q = [&] (int x) {
        tot++;
        assert(tot <= n+3);
        cout << "Q " << x << endl;
        int res; cin >> res;
        return res;
    };
    cout << 0 << endl;
    int x1 = I(0);
    if (x1 == 1) {
        // sei que temos AND
        int val = 0;
        int cur_tam = 1;
        for (int i = n-1; ~i; --i) {
            int pot = (1LL << i);
            int q = I(pot);
            if (q > cur_tam) val += pot;
            cur_tam = q;
        }
        cout << "A " << 1 << " " << val << endl;
    } else {
        // sei que temos {0, c} no set! eh OR ou XOR
        int val = 0;
        bool nice = 1;
        for (int i = n-1; ~i; --i) {
            int pot = (1LL << i);
            int q = Q(val + pot);
            if (q) val += pot;
            else nice = 0;
        }
        if (nice) {
            int q = I(1);
            int k = (q == 2 ? 2 : 3);
            cout << "A " << k << " " << val << endl;
        } else if (__builtin_popcountll(val) != 1) {
            int pot;
            for (int i = 0; i < n; ++i) {
                if (val >> i & 1) pot = (1LL << i); 
            }
            int q = I(pot);
            int k = (q == 2 ? 2 : 3);
            cout << "A " << k << " " << val << endl;
        } else {
            int pot;
            for (int i = 0; i < n; ++i) {
                if (val >> i & 1) {}
                else pot = (1LL << i);
            }
            int q1 = I(pot);
            int q2 = I(val+pot);
            int k = (q2 == 3 ? 2 : 3);
            cout << "A " << k << " " << val << endl;
        }
    }
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
