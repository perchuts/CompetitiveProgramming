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
    vector<vector<char>> s(500, vector<char>(500, ' '));
    for (int i = 0; i <= n; ++i) s[250][250+i] = '_';

    for (int i = 1; i <= n; ++i) s[250+i][250-i] = '/';
    // agora a ultima ta em (250+n, 250-n)
    for (int i = 1; i <= n; ++i) s[250+n][250-n+i] = '_';
    // agora a ultima ta em (250+n, 250)
    for (int i = 1; i <= n; ++i) s[250+n+i][250+i] = char(92);
    // agora a ultima ta em (250+2*n, 250+n)

    for (int i = 1; i <= n; ++i) s[250+i][250+n+i] = char(92);
    // agora a ultima ta em (250+n, 250+2n)
    for (int i = 1; i <= n+1; ++i) s[250+n][250+2*n+i] = '_';
    // agora a ultima ta em (250+n, 250+3*n+1)
    for (int i = 0; i < n; ++i) s[250+n+i+1][250+3*n+1-i] = '/';
    // agora a ultima ta em (250+2*n-1, 250+3*n+1-n+1) = (250+2*n, 250+2*n+2)

    for (int i = 1; i <= n+1; ++i) s[250+2*n][250+n+i] = '_';
    
    int min_x = 500, max_x = 0, min_y = min_x, max_y = max_x;

    for (int i = 0; i < 500; ++i) {
        for (int j = 0; j < 500; ++j) {
            if (s[i][j] != ' ') {
                ckmin(min_x, i);
                ckmax(max_x, i);
                ckmin(min_y, j);
                ckmax(max_y, j);
            }
        }
    }
    
    for (int i = min_x; i <= max_x; ++i) {
        int lim = max_y;
        while (s[i][lim] == ' ') lim--;
        for (int j = min_y; j <= lim; ++j) {
            cout << s[i][j];
        }
        cout << endl;
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
