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
    auto solve = [&] (int l, int r, int d, int u) {
        int ans = 0;
        for (int i = l; i <= r; ++i) {
            if (i >= u) {
                if (i % 2 == 0) ans += u-d+1;
            } else if (i <= d) {
                ans += (u-d+1+(d%2==0))/2;
            } else {
                if (i % 2 == 0) {
                    ans += i-d+1;
                    ans += (u-(i+1)+1)/2;
                } else {
                    ans += (u-(i+1)+2)/2;
                }
            }
        }
        return ans;
    };
    int l, r, d, u; cin >> l >> r >> d >> u;
    int ans = 0;
    if (l < 0 and 0 < r) {
        if (d < 0 and 0 < u) {
            ans += solve(0, abs(l), 0, abs(d));
            ans += solve(0, abs(l), 0, abs(u));
            ans += solve(0, r, 0, abs(d));
            ans += solve(0, r, 0, u);
        } else {
            if (d >= 0) {
                ans += solve(0, abs(l), d, u);
                ans += solve(0, r, d, u);
            } else {
                ans += solve(0, abs(l), abs(u), abs(d)); 
                ans += solve(0, r, abs(u), abs(d)); 
            }
        }
    } else if (d < 0 and 0 < u) {

    } else {

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
