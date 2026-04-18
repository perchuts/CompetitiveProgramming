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
    int n, m; cin >> n >> m;
    vector<vector<int>> grid(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            char c; cin >> c;
            grid[i][j] = (c == '#');
        }
    }
    --n, --m;
    vector<vector<int>> g(n, vector<int>(m)), up = g;
    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
        g[i][j] = grid[i+1][j+1] ^ grid[i][j] ^ grid[i+1][j] ^ grid[i][j+1];
    }
    vector<int> le(m), ri(m);
    int ans = max(n, m)+1;
    for (int i = 0; i < n; ++i) {
        vector<ii> st;
        st.pb({-1, -1});
        for (int j = 0; j < m; ++j) {
            if (i == 0) up[i][j] = (g[i][j] == 0);
            else if (g[i][j] == 0) up[i][j] = 1 + up[i-1][j];
            else up[i][j] = 0;
            while (st.back().first >= up[i][j]) st.pop_back();
            le[j] = st.back().second;
            st.pb({up[i][j], j});
        }
        st = {{-1, m}};
        for (int j = m-1; ~j; --j) {
            while (st.back().first >= up[i][j]) st.pop_back();
            ri[j] = st.back().second;
            st.pb({up[i][j], j});
            ckmax(ans,(ri[j] - le[j]) * (up[i][j]+1));
        }
    }
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
