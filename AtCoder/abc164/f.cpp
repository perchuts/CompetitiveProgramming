#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ull
//#define gato

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

void solve(int n, vector<int> s, vector<int> t, vector<int> u, vector<int> v){
    if (n == 1) {
        if (u[0] == v[0]) cout << v[0] << endl;
        else cout << "-1" << endl;
        return;
    }
    vector<vector<int>> ans(n, vector<int>(n));
    for (int i = 0; i < 64; ++i) {
        vector<vector<int>> a(n, vector<int>(n, 0)), foi = a;
        int x = 0, y = 0, c1 = 0, c2 = 0;
        for (int j = 0; j < n; ++j) {
            if (s[j] ^ (u[j] >> i & 1)) {
                c1++;
                if (s[j]) x |= 1;
                else x |= 2;
                for (int k = 0; k < n; ++k) {
                    if (foi[j][k] and a[j][k] != (s[j]^1)) {
                        cout << "-1" << endl;
                        exit(0);
                    }
                    foi[j][k] = 1;
                    a[j][k] = s[j] ^ 1;
                }
            }
            if (t[j] ^ (v[j] >> i & 1)) {
                c2++;
                if (t[j]) y |= 1;
                else y |= 2;
                for (int k = 0; k < n; ++k) {
                    if (foi[k][j] and a[k][j] != (t[j]^1)) {
                        cout << "-1" << endl;
                        exit(0);
                    }
                    foi[k][j] = 1;
                    a[k][j] = t[j] ^ 1;
                }
            }
        }
        if (x&y) {
            //cout << "tipo1" << endl;
            assert(x == y and x < 3);
            for (int j = 0; j < n; ++j) for (int k = 0; k < n; ++k) if (!foi[j][k]) a[j][k] = (x==1);
        } else if (c1 == n-1) {
            //cout << "tipo2" << endl;
            int tipo = (foi[0][0] ? a[0][0] : a[1][0]);
            for (int j = 0; j < n; ++j) {
                if (foi[j][0]) continue;
                bool ok = false;
                for (int k = 0; k < n; ++k) {
                    int choice;
                    if (t[k] == tipo) choice = s[j];
                    else choice = t[k];
                    a[j][k] = choice;
                    if (choice == s[j]) ok = true;
                }
                if (!ok) {
                    cout << "-1" << endl;
                    exit(0);
                }
            }
        } else if (c2 == n-1) {
            //cout << "tipo3" << endl;
            int tipo = (foi[0][0] ? a[0][0] : a[0][1]);
            for (int j = 0; j < n; ++j) {
                if (foi[0][j]) continue;
                bool ok = false;
                for (int k = 0; k < n; ++k) {
                    int choice;
                    if (s[k] == tipo) choice = t[j];
                    else choice = s[k];
                    a[k][j] = choice;
                    if (choice == t[j]) ok = true;
                }
                if (!ok) {
                    cout << "-1" << endl;
                    exit(0);
                }
            }
        } else {
            //cout << "tipo4" << endl;
            for (int j = 0; j < n; ++j) for (int k = 0; k < n; ++k) if (!foi[j][k]) a[j][k] = (j + k) % 2;
        }
        for (int j = 0; j < n; ++j) for (int k = 0; k < n; ++k) if (a[j][k]) ans[j][k] += 1ULL<<i;
        //for (int j = 0; j < n; ++j) for (int k = 0; k < n; ++k) cout << a[j][k] << " \n"[k==n-1];
    }
    for (int i = 0; i < n; ++i) {
        int x = ans[i][0], y = ans[0][i];
        if (s[i] == 0) for (int j = 0; j < n; ++j) x &= ans[i][j];
        else for (int j = 0; j < n; ++j) x |= ans[i][j];
        if (t[i] == 0) for (int j = 0; j < n; ++j) y &= ans[j][i];
        else for (int j = 0; j < n; ++j) y |= ans[j][i];
        if (u[i] != x or v[i] != y) {
            cout << "-1" << endl;
            exit(0);
        }
    }
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) cout << ans[i][j] << " \n"[j==n-1];
}
bool brute(int n, vector<int> s, vector<int> t, vector<int> u, vector<int> v){
    for (int a = 0; a < 16; ++a) for (int b = 0; b < 16; ++b) for (int c = 0; c < 16; ++c) for (int d = 0; d < 16; ++d) {
        vector<vector<int>> ans = {{a, b}, {c, d}};
        bool ok = 1;
        for (int i = 0; i < n; ++i) {
            int x = ans[i][0], y = ans[0][i];
            if (s[i] == 0) for (int j = 0; j < n; ++j) x &= ans[i][j];
            else for (int j = 0; j < n; ++j) x |= ans[i][j];
            if (t[i] == 0) for (int j = 0; j < n; ++j) y &= ans[j][i];
            else for (int j = 0; j < n; ++j) y |= ans[j][i];
            if (u[i] != x or v[i] != y) {
                ok = 0;
                break;
            }
        }
        if (ok) {
            cout << "certificate: " << endl;
            cout << a << ' ' << b << endl << c << ' ' << d << endl;
            return 1;
        }
    }
    return 0;
}
int32_t main(){_
#ifndef gato
    int n; cin >> n;
    vector<int> s(n), t(n), u(n), v(n);
    for (auto& x : s) cin >> x;
    for (auto& x : t) cin >> x;
    for (auto& x : u) cin >> x;
    for (auto& x : v) cin >> x;
    solve(n, s, t, u, v);
#else
    while (true) {
        int n = 2;
        vector<int> s(n), t(n), u(n), v(n);
        for (auto& x : s) x = rnd(0, 1);
        for (auto& x : t) x = rnd(0, 1);
        for (auto& x : u) x = rnd(0, 15);
        for (auto& x : v) x = rnd(0, 15);
        if (!brute(n, s, t, u, v)) continue;
        cout << n << endl;
        for (auto& x : s) cout << x << ' ';
        cout << endl;
        for (auto& x : t) cout << x << ' ';
        cout << endl;
        for (auto& x : u) cout << x << ' ';
        cout << endl;
        for (auto& x : v) cout << x << ' ';
        cout << endl;
        cout << endl;
        solve(n, s, t, u, v);
    }
#endif
}
