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
const int mod = 1e9;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

vector<int> pw;

void solve() {
    int x; cin >> x;
    // there is exactly one solution < A^K s.t. n^n mod A^K === X, X coprime with A
    // n^n mod 10^k === X
    // what about 10^{k+1}?
    // n^n = x * 10^k + X
    // => want x to be a multiple of 10
    // i know that n mod 10^k is uniquely determined.
    // then i take the answer found earlier, and sum x*10^{k} to check if it works
    // => all 4 alternatives must be distinct.
    auto fexp = [&] (int b, int e, int m) {
        int ans = 1;
        while (e) {
            if (e&1) ans = ans * b % m;
            e /= 2, b = b * b % m;
        }
        return ans;
    };
    int lst = -1;
        for (int j = 1; j < 100; ++j) {
                if (j % 5 and j % 2 and fexp(j, j, 100) == (x%100)) lst = j;
        }
    for (int i = 3; i < 10; ++i) {
        int want = x % pw[i];
        for (int j = 0; j < 10; ++j) {
            int z = j * pw[i-1] + lst;
            if (fexp(z, z, pw[i]) == want) {
                lst = z;
                break;
            }
        }
    }
    cout << lst << endl;
}

int32_t main() {_
    pw.resize(10), pw[0] = 1;
    for (int i = 1; i < 10; ++i) pw[i] = 10 * pw[i-1];
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
