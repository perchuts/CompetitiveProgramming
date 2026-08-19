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
    int k; cin >> k;
    vector<int> aa(7), a(8);
    int S = 0, base = 0;
    for (auto& x : aa) cin >> x, S += x;

    {
        a[1] = aa[0], a[2] = aa[1], a[4] = aa[2];
        a[3] = aa[3], a[5] = aa[5], a[6] = aa[4];
        a[7] = aa[6];
    }

    base = a[1] / k + a[2] / k + a[4] / k;

    a[1] %= k, a[2] %= k, a[4] %= k;


    // usando x, y, z, preciso que k * (x + y + z) >= S
    // inicialmente, eh obvio que podemos fazer x -= a[1] / k, a[1] %= k.
    // A ab
    // B bc
    // C ac
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
