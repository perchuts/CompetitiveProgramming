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
    vector<int> a(n);
    int S = 0;
    for (auto& x : a) cin >> x, S += x;
    if (n % 2 == 0) { cout << (S % 2 == 0 ? "Second" : "First") << endl; return; }
    if (n == 1) {
        cout << (a[0] == 1 ? "Second" : "First") << endl;
        return;
    }
    // sei q n >= 3!!
    vector<string> caras = {"First", "Second"};
    int turn = 0;
    while (true) {
        S = 0;
        int mn = inf;
        for (auto x : a) S += x, ckmin(mn, x);
        if (S % 2 == 0) {
            cout << caras[turn] << endl;
            return;
        }
        if (mn == 1) {
            cout << caras[turn^1] << endl;
            return;
        }
        int imp = -1;
        for (int i = 0; i < n; ++i) {
            if (a[i] % 2) {
                if (imp == -1) imp = i;
                else {
                    cout << caras[turn^1] << endl;
                    return;
                }
            }
        }
        a[imp]--;
        int g = 0;
        for (auto x : a) g = gcd(g, x);
        for (auto& x : a) x /= g;
        turn ^= 1;
    }
}

int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
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
