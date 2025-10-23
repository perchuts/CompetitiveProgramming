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
    int n, k; cin >> n >> k;
    vector<int> p(n), pp(n), ord(n), novo(n), seta(n), onde(n);
    for (int i = 0; i < n; ++i) cin >> p[i], --p[i], pp[p[i]] = i;
    auto go = [&] (auto&& self, int l, int r) -> void {
        if (l == r) {
            ord[l] = l;
            onde[pp[l]] = l;
            return;
        }
        int md = (l+r)/2;
        self(self, l, md), self(self, md+1, r);
        int ptr = md;
        for (int i = r; i > md; --i) {
            while (l <= ptr and pp[ptr] >= pp[ord[i]]+k) ptr--;
            seta[ord[i]] = ptr;
        }
        for (int i = md+2; i <= r; ++i) ckmax(seta[i], seta[i-1]);
        int p1 = l, p2 = md+1, turn = 0;
        while (p1 != md+1 or p2 != r+1) {
            if (p1 == md+1) novo[turn] = pp[p2++];
            else if (p2 == r+1) novo[turn] = pp[p1++];
            else {
                if (seta[p2] < p1) novo[turn] = pp[p2++];
                else novo[turn] = pp[p1++];
            }
            turn++;
        }
        for (int i = 0; i < r-l+1; ++i) pp[i+l] = novo[i], ord[onde[novo[i]]] = i+l;
        p1 = l, p2 = md+1, turn = 0;
        while (p1 != md+1 or p2 != r+1) {
            if (p1 == md+1) novo[turn] = ord[p2++];
            else if (p2 == r+1) novo[turn] = ord[p1++];
            else {
                if (pp[ord[p2]] < pp[ord[p1]]) novo[turn] = ord[p2++];
                else novo[turn] = ord[p1++];
            }
            turn++;
        }
        for (int i = 0; i < r-l+1; ++i) ord[i+l] = novo[i], onde[pp[novo[i]]] = i+l;
    };
    go(go, 0, n-1);
    for (int i = 0; i < n; ++i) p[pp[i]] = i;
    for (auto x : p) cout << x + 1 << ' ';
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
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
