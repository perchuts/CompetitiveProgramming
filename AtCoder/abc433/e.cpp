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
    vector<int> row(n), col(m);
    for (auto& x : row) cin >> x, --x;
    for (auto& x : col) cin >> x, --x;
    vector<int> pr(n*m, -1), pc(n*m, -1);
    for (int i = 0; i < n; ++i) {
        if (pr[row[i]] != -1) {
            cout << "No" << endl;
            return;
        }
        pr[row[i]] = i;

    }
    for (int i = 0; i < m; ++i) {
        if (pc[col[i]] != -1) {
            cout << "No" << endl;
            return;
        }
        pc[col[i]] = i;
    }

    vector<vector<int>> ans(n, vector<int>(m, -1));

    vector<int> fr(n), fc(m);

    vector<ii> livres;
    
    for (int i = n*m-1; ~i; --i) {
        if (pc[i] > -1 and pr[i] > -1) {
            assert(ans[pr[i]][pc[i]] == -1);
            assert(fr[pr[i]] == 0);
            assert(fc[pc[i]] == 0);
            ans[pr[i]][pc[i]] = i;
            for (int j = 0; j < n; ++j) {
                if (fr[j] and j != pr[i]) livres.pb({j, pc[i]});
            }
            for (int j = 0; j < m; ++j) {
                if (fc[j] and j != pc[i]) livres.pb({pr[i], j});
            }
            fc[pc[i]] = fr[pr[i]] = 1;
        } else if (pc[i] > -1) {
            assert(fc[pc[i]] == 0);
            bool ok = false;
            int choice = -1;
            for (int j = 0; j < n; ++j) {
                if (fr[j]) {
                    assert(ans[j][pc[i]] == -1);
                    choice = j;
                    ans[j][pc[i]] = i; break;
                }
            }
            if (choice == -1) {
                cout << "No" << endl;
                return;
            }
            for (int j = 0; j < n; ++j) {
                if (fr[j] and j != choice) livres.pb({j, pc[i]});
            }
            fc[pc[i]] = 1;
        } else if (pr[i] > -1) {
            assert(fr[pr[i]] == 0);
            int choice = -1;
            for (int j = 0; j < m; ++j) {
                if (fc[j]) {
                    assert(ans[pr[i]][j] == -1);
                    choice = j;
                    ans[pr[i]][j] = i; break;
                }
            }
            if (choice == -1) {
                cout << "No" << endl;
                return;
            }
            for (int j = 0; j < m; ++j) {
                if (fc[j] and j != choice) livres.pb({pr[i], j});
            }
            fr[pr[i]] = 1;
        } else {
            if (livres.empty()) {
                cout << "No" << endl;
                return;
            }
            if (livres.empty()) {
                cout << "No" << endl;
                return;
            }
            auto [x, y] = livres.back(); livres.pop_back();
            assert(ans[x][y] == -1);
            ans[x][y] = i;
        }
    }
    vector<int> a(n), b(m);
    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) ckmax(a[i], ans[i][j]), ckmax(b[j], ans[i][j]);
    assert(a == row and b == col);
    cout << "Yes" << endl;
    for (auto x : ans) {
        for (auto y : x) cout << y + 1 << ' ';
        cout << endl;
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
