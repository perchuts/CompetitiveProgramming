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
    int cur; cin >> cur;
    if (n == 2) {
        int t; cin >> t;
        cout << (t <= 2*cur ? 2 : -1) << endl;
        return;
    }
    vector<int> v(n-2);
    for (auto& x : v) cin >> x;
    int target; cin >> target;
    sort(all(v));
    while (!v.empty() and v.back() > target) v.pop_back();
    v.pb(target);
    int tot = 1;
    for (int l = 0, r = 0; l != sz(v); l = r) {
        if (v[l] > 2*cur) break;
        while (r != sz(v) and v[r] <= 2*cur) r++;
        cur = v[r-1];
        tot++;
    }
    cout << (cur == target ? tot : -1) << endl;
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
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
