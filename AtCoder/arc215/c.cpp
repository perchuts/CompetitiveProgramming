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
    vector<array<int, 3>> v(n);
    for (auto& x : v) cin >> x[0] >> x[1] >> x[2], --x[0], --x[1], --x[2];
    // todas as pessoas que me dominam tem que morrer
    // posso escolher a pessoa com maxima coordenada em um dos pontos e matar todos que me dominam.
    // se essa pessoa com maxima coordenada domina todos que eu posso ganhar, L
    // se isso acontece com as tres coordenadas simultaneamente, eh L tambem?
    vector<vector<int>> pts(n);
    for (int i = 0; i < n; ++i) pts[v[i][0]].pb(i);
    vector<array<int, 3>> mx(n), mn(n);
    array<int, 3> cur = {0, 0, 0};
    for (int i = 0; i < n; ++i) {
        for (auto j : pts[i]) {
            for (int w = 0; w < 3; ++w) ckmax(cur[w], v[j][w]);
        }
        mx[i] = cur;
    }
    cur = {n-1, n-1, n-1};
    for (int i = n-1; ~i; --i) {
        for (auto j : pts[i]) {
            for (int w = 0; w < 3; ++w) ckmin(cur[w], v[j][w]);
        }
        mn[i] = cur;
    }
    vector<int> cmp;
    for (int i = 0; i < n; ++i) if (!pts[i].empty()) cmp.pb(i);
    int ans = sz(pts[cmp.back()]);
    for (int i = sz(cmp)-2; i >= 0; --i) {
        int x = cmp[i], y = cmp[i+1];
        if (mx[x][0] < mn[y][0] and mx[x][1] < mn[y][1] and mx[x][2] < mn[y][2]) {
            break;
        }
        ans += sz(pts[x]);
    }
    cout << ans << endl;
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
