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
    n += 2;
    int cur = 1;
    vector<ii> caras = {{cur, 1}};
    int lst_1 = 0;
    vector<int> cor(n*n+10);
    vector<ii> children(n*n+10);
    vector<ii> pos(n*n+10);
    cor[1] = 1;
    auto ask = [&] (int p) {
        //cout << "asked for " << p << ": " << pos[p].first << " " << pos[p].second << "(" << cor[p] << ")" << endl;
        //return cor[p];
        cout << "? " << p << endl;
        int x; cin >> x; return x;
    };
    for (int i = 2; i < n; ++i) {
        int x = ask(cur+i-1);
        cur += i-1;
        if (x == 0) cur++;
        caras.pb({cur, i});
        if (x == 1) lst_1 = sz(caras)-1;
    }
    int l = lst_1+1, r = sz(caras)-1, ans = caras[lst_1].first;
    //cout << "now to binary search" << endl;
    while (l <= r) {
        int md = l+(r-l+1)/2;
        auto [id, lvl] = caras[md];
        //cout << id << " " << lvl << endl;
        int x = ask(id);
        if (x == 1) ans = id, l = md+1;
        else r = md-1;
    }
    //for (int i = 1; i <= n; ++i) {
        //for (int j = 0; j < i; ++j) cout << cor[pt++] << " ";
        //cout << endl;
    //}
    cout << "! " << ans << endl;
    //auto [i, j] = children[ans];
    //cout << cor[ans] << " " << cor[i] << " " << cor[j] << endl;
    //if (cor[ans] == 0 or cor[i] == 1 or cor[j] == 1) {
    //    exit(0);
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
