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
    int n, x; cin >> n >> x;
    if (x == n) {
        cout << "Yes" << endl;
        for (int i = 1; i < 2*n; ++i) cout << i << endl;
        return;
    }
    auto go = [&] (auto&&self, vector<int> v) -> int {
        if (sz(v) == 1) return v[0];
        vector<int> vv;
        for (int i = 0; i < sz(v)-2; ++i) {
            int a = v[i], b = v[i+1], c = v[i+2];
            vector<int> z = {a, b, c};
            sort(all(z));
            vv.pb(z[1]);
        }
        return self(self, vv);
    };
    vector<int> p(2*n-1);
    if (x == 2*n-1 or x == 1) {
        cout << "No" << endl;
        return;
    }
    cout << "Yes" << endl;
    vector<int> ans(2*n-1), mark(2*n);
    ans[n-1] = x;
    ans[n-2] = x+1;
    ans[n] = x-1;
    if (x == 2*n-2) ans[n-3] = x-2;
    else ans[n+1] = x+2;
    for (auto x : ans) mark[x] = 1;
    int j = 1;
    for (int i = 0; i < 2*n-1; ++i) {
        if (ans[i]) cout << ans[i] << endl;
        else {
            while (mark[j]) j++;
            ans[i] = j;
            cout << j << endl;
            mark[j] = 1;
        }
    }
    //vector<int> p(2*n-1); iota(all(p), 1);
    //vector<vector<int>> cert(2*n);
    //int falta = 2*n-3;
    //do {
    //    int ans = go(go, p);
    //    if (cert[ans].empty()) falta--;
    //    cert[ans] = p;
    //} while (next_permutation(all(p)) and falta);
    //for (int i = 1; i <= 2*n-1; ++i) {
    //    cout << "i = " << i << ": ";
    //    for (auto k : cert[i]) cout << k << " ";
    //    cout << endl;
    //}
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
