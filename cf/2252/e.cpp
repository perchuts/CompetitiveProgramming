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
    int t = 0;
    int N = 12345;
    int pw = 1;
    // 01 11
    // 10 10
    // 11 01
    // a, a + c, a + 2c
    // a ^ (a + 2c) = a + c
    // x ^ y = (x + y) / 2
    // (x + y) / 2 = (x | y) - (x & y)
    // 110
    // 101
    // 011
    // 000
    // 0001
    // 1010
    // 1011
    //
    // 01 - 2^p
    // 10
    // 11 + 2^p
    //
    // 0110
    // 1001 
    // 1111
    for (int i = 1; i < N; ++i) {
        if (pw == i) pw *= 2;
        for (int j = pw - i; i + 2 * j <= N; j += 2) {
            int a = i, b = i + j, c = i + 2 * j;
            if ((a ^ b ^ c) == 0) {
                t++;
            }
        }
    }
    cout << t << endl;
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
