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
    int n, q; cin >> n >> q;
    string s, t; cin >> s >> t;
    vector<vector<int>> ps(n+1, vector<int>(4));
    for (int i = 1; i <= n; ++i) { 
        ps[i] = ps[i-1];
        if (s[i-1] == '0' and t[i-1] == '0') ps[i][0]++;
        if (s[i-1] == '0' and t[i-1] == '1') ps[i][1]++;
        if (s[i-1] == '1' and t[i-1] == '0') ps[i][2]++;
        if (s[i-1] == '1' and t[i-1] == '1') ps[i][3]++;
    }
    while (q--) {
        int l, r; cin >> l >> r; 
        // q00, q01, q10, q11
        int q00 = ps[r][0] - ps[l-1][0];
        int q01 = ps[r][1] - ps[l-1][1];
        int q10 = ps[r][2] - ps[l-1][2];
        int q11 = ps[r][3] - ps[l-1][3];

        int s1 = q00 + q01 - q10 - q11;
        int s2 = q00 - q01 + q10 - q11;

        if (s1 * s2 >= 0) {
            cout << "YES" << endl;
            continue;
        }

        if (s1 < 0) swap(q01, q10), swap(s1, s2);

        int score = s1 - q00 - min(q01, q00);

        cout << (score <= 0 ? "YES" : "NO") << endl;


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
