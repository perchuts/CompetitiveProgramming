#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
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
    cout << 2 << endl;
    for (int i = 2; i <= n; ++i) cout << i << " ";
    cout << 1 << endl;
    cout << "2 1 ";
    for (int i = 3; i <= n; ++i) cout << i << " ";
    cout << endl;
    vector<int> q(n);
    for (auto& x : q) cin >> x, --x;
    vector<int> p(n), aux(n);
    for (int i = 0; i < n; ++i) p[q[i]] = i;
    vector<int> ans;
    auto shift = [&] () {
        ans.pb(1);
        for (int i = 0; i < n-1; ++i) aux[i] = p[i+1];
        aux[n-1] = p[0];
        swap(aux, p);
    };
    auto swp = [&] () {
        ans.pb(2);
        swap(p[0], p[1]);
    };
    for (int target = n-2; target >= 0; --target) {
        while (p[0] != target) shift();
        while (p[1] != target+1) swp(), shift();
    }
    cout << sz(ans) << ' ';
    for (auto x : ans) cout << x << ' ';
    cout << endl;
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
