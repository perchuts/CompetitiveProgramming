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
    int n, q; cin >> n >> q;
    vector<int> a(n);
    int S = 0;
    for (auto& x : a) cin >> x, S += x;
    sort(all(a));
    vector<int> ps(n+1);
    for (int i = 1; i <= n; ++i) ps[i] = ps[i-1] + a[i-1];
    while (q--) {
        int x; cin >> x;
        if (x > a[n-1]) {
            cout << -1 << endl;
            continue;
        }
        // quero selecionar x caras dentre S
        // quero ver se min(a[i], x-1) >= y
        int l = 1, r = n, pos = 0;
        while (l <= r) {
            int md = l + (r-l+1)/2;
            if (a[md-1] >= x) r = md-1, pos = md;
            else l = md+1;
        }
        cout << (ps[pos-1] + (n-pos+1) * (x-1)) + 1 << endl;
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
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
