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
    int S, q; cin >> S >> q;
    vector<array<int, 3>> hist;
    vector<int> divs;
    for (int i = 1; i * i <= S; ++i) {
        if (S % i) continue;
        divs.pb(i);
        if (i * i != S) divs.pb(S/i);
    }
    sort(rbegin(divs), rend(divs));
    int last_x = 0;
    for (auto d : divs) {
        // (d, S/d)
        hist.pb({d, last_x+1, S/d});
        last_x = S/d;
    }
    vector<array<int, 3>> qu(q);
    hist.pb({0, last_x+1, last_x+1});
    vector<int> ps(sz(hist));
    ps[0] = hist[0][0] * (hist[0][2]-hist[0][1]+1);
    for (int i = 1; i < sz(hist); ++i) {
        ps[i] = ps[i-1] + hist[i][0] * (hist[i][2]-hist[i][1]+1);
    }
    //for (auto x : hist) cout <<x[0] << " " << x[1] << " " <<x[2] << endl;
    for (int i = 0; i < q; ++i) {
        cin >> qu[i][0] >> qu[i][1];
        // encontrar o ultimo ponto onde a altura eh >= y
        int l = 0, r = sz(hist)-1, pos_h = 0;
        while (l <= r) {
            int md = l + (r-l+1)/2;
            if (hist[md][0] >= qu[i][1]) pos_h = md, l = md+1;
            else r = md-1;
        }
        // encontrar o ponto onde o r >= x
        l = 0, r = sz(hist)-1; int pos_len = 0;
        while (l <= r) {
            int md = l + (r-l+1)/2;
            if (hist[md][2] <= qu[i][0]) pos_len = md, l = md+1;
            else r = md-1;
        }
        //cout << pos_h << " " << pos_len << " ";
        if (pos_h > pos_len) {
            cout << qu[i][0] * qu[i][1] << endl;
        } else {
            int ans = (hist[pos_h][2]) * qu[i][1] + ps[pos_len] - ps[pos_h];
            ans += (qu[i][0]-hist[pos_len][2])*hist[pos_len+1][0];
            cout << ans << endl;
        }
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
