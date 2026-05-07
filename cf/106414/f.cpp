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
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    vector<int> ord(n); iota(all(ord), 0); sort(all(ord), [&] (int x, int y) { return a[x] < a[y]; });
    while (!ord.empty() and a[ord.back()] > 2*m) ord.pop_back();
    if (sz(ord) >= 3) {
        int i = 0;
        while (i != sz(ord) and a[ord[i]] < m) i++;
        if (i != sz(ord) and a[ord[i]] + a[ord[0]] + a[ord[1]] <= 2*m) {
            cout << ord[0] + 1 << " " << ord[1] + 1 << " " << ord[i] + 1 << endl;
            return;
        }
        while (sz(ord) != i) ord.pop_back();
    }
    if (sz(ord) < 3) {
        cout << -1 << endl;
        return;
    }
    int s_min = a[ord[0]] + a[ord[1]] + a[ord[2]];
    int s_max = a[ord[sz(ord)-3]] + a[ord[sz(ord)-2]] + a[ord[sz(ord)-1]];
    if (2*m < s_min or s_max < m) {
        cout << -1 << endl;
        return;
    }
    if (m <= s_min) {
        cout << ord[0] + 1 << " " << ord[1] + 1 << " " << ord[2] + 1 << endl;
        return;
    }
    if (s_max <= 2*m) {
        cout << ord[sz(ord)-3] + 1 << " " << ord[sz(ord)-2] + 1 << " " << ord.back() + 1 << endl;
        return;
    }
    assert(s_min < m and 2*m < s_max);
    // todos os elementos sao menores que M!
    int s1 = a[ord[0]] + a[ord[1]] + a[ord.back()];
    int s2 = a[ord[0]] + a[ord.back()] + a[ord[sz(ord)-2]];
    if (m <= s1 and s1 <= 2*m) {
        cout << ord[0] + 1 << " " << ord[1] + 1 << " " << ord.back() + 1 << endl;
    } else {
        assert(m <= s2 and s2 <= 2*m);
        cout << ord[0] + 1 << " " << ord[sz(ord)-2] + 1 << " " << ord.back() + 1 << endl;
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
