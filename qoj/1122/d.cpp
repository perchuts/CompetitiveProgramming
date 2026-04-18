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
    vector<int> z(290);
    z['A'] = 0, z['T'] = 1, z['G'] = 2, z['C'] = 3;
    string s; cin >> s;
    int n = sz(s);
    vector<vector<int>> ps(4, vector<int>(n+1));
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < 4; ++j) ps[j][i] = ps[j][i-1];
        ps[z[s[i-1]]][i]++;
    }
    int q; cin >> q;
    while (q--) {
        int l, r; cin >> l >> r;
        vector<int> qt(4);
        for (int i = 0; i < 4; ++i) qt[i] = ps[i][r] - ps[i][l-1];
        string t = "ACGT";
        sort(all(t), [&] (char c1, char c2) {
            if (qt[z[c1]] == qt[z[c2]]) return z[c1] < z[c2];
            return qt[z[c1]] > qt[z[c2]];
        });
        cout << t << endl;
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
