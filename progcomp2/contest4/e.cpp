#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll
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

vector<ii> solve(int n, vector<int> a) {
    auto A = a;
    auto b = a; sort(all(b));
    vector<int> p(n, -1), vis(n);
    vector<ii> ans;
    for (int i = n-1; ~i; --i) {
        vector<int> smol;
        for (int j = 0; j < i; ++j) if (A[j] > A[i]) smol.pb(j);
        smol.pb(i);
        auto pp = smol;
        sort(all(smol), [&] (int x, int y) { return a[x] < a[y]; });
        if (sz(smol) == 1) continue;
        auto temp = a;
        int m = sz(smol);
        for (int j = 0; j < m; ++j) p[pp[j]] = smol[j];
        vector<ii> act;
        for (int j = m-1; ~j; --j) {
            if (vis[pp[j]] != i and p[pp[j]] != pp[j]) {
                int cur = pp[j];
                while (vis[cur] != i) {
                    if (cur != i) act.pb({cur, i});
                    vis[cur] = i, cur = p[cur];
                }
            }
        }
        reverse(all(act));
        for (auto x : act) ans.pb(x);
        for (int j = 0; j < m; ++j) a[pp[j]] = temp[smol[j]];
    }
    return ans;
}

int32_t main() {_
#ifndef gato
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    auto ans = solve(n, a);
    cout << sz(ans) << endl;
    for (auto [x, y] : ans) cout << x + 1 << ' ' << y + 1 << endl;
#else
    int t = 1;
    while (true) {
        int n = rnd(1, 20);
        vector<int> a(n);
        for (auto& x : a) x = rnd(1, n);
        auto my = solve(n, a);
        auto A = a;
        vector<ii> inv;
        for (int i = 0; i < n; ++i) for (int j = i+1; j < n; ++j) if (a[i] > a[j]) inv.pb({i, j});
        sort(all(inv)); auto myy = my; sort(all(my));
        for (auto [x, y] : my) swap(A[x], A[y]);
        auto fail = [&] () {
            cout << "Wrong answer on test " << t << endl;
            cout << n << endl;
            for (auto x : a) cout << x << ' ';
            cout << endl;
            cout << "Your output: ";
			cout << sz(my) << endl;
            for (auto [x, y] : my) cout << x+1 << ' ' << y+1 << endl;
            cout << endl;
            exit(0);
        };
        if (inv != myy) fail();
        for (int i = 0; i < n-1; ++i) {
            if (A[i] > A[i+1]) fail();
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
