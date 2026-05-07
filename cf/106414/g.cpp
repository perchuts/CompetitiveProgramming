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
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    map<int, int> me, md;
    set<ii> esq, dir;
    for (int i = 0; i < n; ++i) me[a[i]]++;
    for (auto [x, y] : me) esq.insert({y, x});
    int ans = 0;
    for (int i = 0; i < n-1; ++i) {
        esq.erase({me[a[i]], a[i]});
        if (md[a[i]]) dir.erase({md[a[i]], a[i]});
        me[a[i]]--;
        md[a[i]]++;
        if (me[a[i]]) esq.insert({me[a[i]], a[i]});
        dir.insert({md[a[i]], a[i]});
        auto it1 = end(esq);
        for (int x = 0; x < 2; ++x) {
            if (x == sz(esq)) break;
            it1 = prev(it1);
            auto it2 = end(dir);
            for (int y = 0; y < 2; ++y) {
                if (y == sz(dir)) break;
                it2 = prev(it2);
                auto [x1, x2] = *it1;
                auto [y1, y2] = *it2;
                //cout << x1 << " " << x2 << " " << y1 << " " << y2 << endl;
                if (x2 != y2) ckmax(ans, x1+y1);
            }
        }
        //cout << endl;
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
