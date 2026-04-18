#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
//#define endl '\n'
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
    n = 2*n+1;
    int qu = 0;
    auto ask = [&] (vector<int> v) {
        qu++;
        assert(qu <= 66);
        cout << "? ";
        cout << sz(v) << " ";
        for (auto x : v) cout << x + 1 << " ";
        cout << endl;
        int x; cin >> x;
        if (x % 2 == sz(v) % 2) return 0;
        return 1;
    };
    // se os 3 estao na query, retorna 1. caso contrario retorna 0!
    // encontrar primeira vez q os 3 aparecem
    int l = 2, r = n-1, ult = n-1;
    while (l <= r) { 
        int md = l + (r-l+1)/2;
        vector<int> v(md+1);
        iota(begin(v), end(v), 0);
        if (ask(v)) ult = md, r = md-1;
        else l = md+1;
    }
    l = 0, r = ult-2; int prim = 2;
    while (l <= r) { 
        int md = l + (r-l+1)/2;
        vector<int> v;
        for (int i = ult; i >= md; --i) v.pb(i);
        if (ask(v)) prim = md, l = md+1;
        else r = md-1;
    }
    l = prim+1, r = ult-1;
    int meio = l;
    while (l <= r) {
        int md = l + (r-l+1)/2;
        vector<int> v = {prim, ult};
        for (int i = prim+1; i <= md; ++i) v.pb(i);
        if (ask(v)) meio = md, r = md-1;
        else l = md+1;
    }
    cout << "! " << prim+1 << " " << meio+1 << " " << ult+1 << endl;
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
