#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ii = pair<int,int>;
using iii = tuple<int,int,int>;

const int inf = 2e9+1;
const int mod = 1e9+7;
const int maxn = 2e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(69);

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

int occ[1<<18];

int solve(int n, vector<int> a) {
    if (n == 2) {
        return ((a[0]^a[1])&max(a[0], a[1]));
    }
    vector<int> ps(n), tt(n+1);
    for (int i = 0; i < n; ++i) ps[i] = (i == 0 ? a[i] : ps[i-1] ^ a[i]);
    for (int i = 2; i <= n; ++i) tt[i] = 1 + tt[i/2];

    vector<vector<ii>> st(18, vector<ii>(n));
    for (int i = 0; i < n; ++i) st[0][i] = {a[i], i};

    for (int j = 1; (1<<j) <= n; ++j) {
        for (int i = 0; i + (1 << j) <= n; ++i) {
            st[j][i] = max(st[j-1][i], st[j-1][i+(1<<(j-1))]);
        }
    }
    auto query = [&] (int l, int r) -> int {
        return max(st[tt[r-l+1]][l], st[tt[r-l+1]][r-(1<<tt[r-l+1])+1]).second;
    };

    int ans = 0;
    for (int bit = 17; ~bit; --bit) {
        ans += (1 << bit);
        bool bom = 0;
        auto S = [&] (auto&& self, int l, int r) -> void {
            if (r < l) return;
            int i = query(l, r);
            bool nice = ((a[i] & ans) == ans);
            if (i-l <= r-i) {
                self(self, l, i-1);
                for (int j = l; j < i; ++j) occ[ps[j] & ans]--;
                self(self, i+1, r);
                occ[ps[i] & ans]++;
                for (int j = max(0, l-1); j < i; ++j) {
                    if (nice and occ[(ps[j] & ans) ^ ans] >= 1 + (j == i-1)) bom = 1;
                }
                for (int j = l; j < i; ++j) occ[ps[j]&ans]++;
                return;
            } 
            self(self, i+1, r);
            for (int j = i+1; j <= r; ++j) occ[ps[j] & ans]--;
            self(self, l, i-1);
			if (l) occ[ps[l-1]&ans]++;
            for (int j = i+1; j <= r; ++j) {
                if (nice and occ[(ps[j] & ans) ^ ans] >= 1) bom = 1;
            }
            if (i) occ[ps[i-1]&ans]--;
            if (nice and occ[(ps[i] & ans) ^ ans]) bom = 1;
            if (i) occ[ps[i-1]&ans]++;
			if (l) occ[ps[l-1]&ans]--;
            for (int j = i+1; j <= r; ++j) occ[ps[j]&ans]++;
            occ[ps[i] & ans]++;
        };
        S(S, 0, n-1);
        for (int i = 0; i < n; ++i) occ[ps[i] & ans]--;
        int mx = a[0];
        for (int i = 1; i < n; ++i) {
            ckmax(mx, a[i]);
            if ((ps[i] & mx & ans) == ans) bom = 1;
        }
        if (!bom) ans -= (1 << bit);
    }
    return ans;
}

int brute(int n, vector<int> a) {
    int ans = 0;
    for (int l = 0; l < n; ++l) {
        int xx = 0, mx = 0;
        for (int r = l; r < n; ++r) {
            xx ^= a[r];
            ckmax(mx, a[r]);
            if (r != l and ckmax(ans, (xx&mx))) {}
        }
    }
    return ans;
}
        // solve(l, r) -> take maximum on interval (i)
        // solve(l, i-1)
        // undo left
        // solve(i+1, r) -> largest range!
        // redo left

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<int> a(n);
        for (auto& x : a) cin >> x;
        cout << solve(n, a) << endl;;
    }
#else
    int t = 1;
    while (true) {
        int n = rnd(2, 30);
        vector<int> a(n);
        for (auto& x : a) x = rnd(0, 31);
        int ans = brute(n, a);
        int my = solve(n, a);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << endl;
            for (auto x : a) cout << x << " ";
            cout << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
