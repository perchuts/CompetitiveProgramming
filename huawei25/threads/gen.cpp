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
    for (int i = 0; i < 7; ++i) {
        int li = rnd(1, 30);
        cout << li << ' ';
        for (int j = 0; j < li; ++j) cout << rnd(1, 20) << " ";
        cout << endl;
    }
    for (int i = 0; i < 20; ++i) {
        int bi = rnd(1, 128);
        cout << bi << ' ';
        for (int j = 0; j < bi; ++j) cout << rnd(1, 50) << " ";
        cout << endl;
    }
    for (int i = 0; i < 8; ++i) cout << rnd(1, 100) << " ";
    cout << endl;
    cout << rnd(1, 32) << " " << rnd(1, 20) << " " << 20 << endl;
    for (int t = 1; t <= 5; ++t) {
        int n = rnd(1, 300);
        cout << n << endl;
        for (int i = 0; i < n; ++i) {
            int arrive = rnd(1, 1000);
            int type = rnd(1, 7);
            int timeout = rnd(1, 1e5);
            int w = rnd(0, 255);
            cout << i+1 << " " << arrive << " " << type << " " << timeout << " " << w << endl;
        }
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
