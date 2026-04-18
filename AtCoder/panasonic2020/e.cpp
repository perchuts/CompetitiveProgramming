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
    vector<string> v(3);
    for (auto& x : v) cin >> x;
    vector<int> p = {0, 1, 2};
    int N = max({sz(v[0]), sz(v[1]), sz(v[2])});
    vector check(3, vector(3, vector(N+1, false)));
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (i == j) continue;
            for (int s = 0; s <= sz(v[i]); ++s) {
                check[i][j][s] = 1;
                for (int k = 0; k + s < sz(v[i]) and k < sz(v[j]); ++k) {
                    if (v[i][k+s] != '?' and v[j][k] != '?' and v[i][k+s] != v[j][k]) {
                        check[i][j][s] = 0; break;
                    }
                }
            }
        }
    }
    int ans = 3 * N;
    do {
        for (int i = 0; i <= sz(v[p[0]]); ++i) {
            if (check[p[0]][p[1]][i] == false) continue;
            for (int j = i; j <= max(sz(v[p[0]]), i + sz(v[p[1]])); ++j) {
                bool ok = true;
                if (j - i <= sz(v[p[1]])) ok &= check[p[1]][p[2]][j-i];
                if (j <= sz(v[p[0]])) ok &= check[p[0]][p[2]][i];
                if (ok) ckmin(ans, max({sz(v[p[0]]), i + sz(v[p[1]]), j + sz(v[p[2]])}));
            }
        }
    } while (next_permutation(all(p)));
    cout << ans << endl;
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
