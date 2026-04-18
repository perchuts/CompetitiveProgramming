#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll
//#define gato


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

int solve(int n, int m, vector<int> a, vector<int> b) {
    sort(all(a)), sort(rbegin(b), rend(b));
    vector<int> lx(n), rx(n);
    auto possible = [&] (int x) {
        bool ok = true;
        for (int i = 0; i < n; ++i) ok &= ((a[i] + b[i]) % m <= x);
        if (ok) return true;
        int l = 0, r = n-1, opt = -1;
        while (l <= r) {
            int md = l + (r-l+1)/2;
            ok = true;
            for (int i = 0; i <= md; ++i) ok &= (a[i] + b[n-1-md+i] <= x);
            if (ok) opt = md, l = md+1;
            else r = md-1;
        }
        if (opt == n-1) return true;
        if (opt == -1) return false;
        int j1 = n-1, j2 = 0;
        for (int i = n-1; ~i; --i) {
            while (j1 >= 0 and a[i] + b[j1] < m) j1--;
            rx[i] = j1;
        }
        for (int i = 0; i < n; ++i) {
            while (j2 < n and a[i] + b[j2] > m + x) j2++;
            lx[i] = j2;
        }
        int lp = -inf, rp = inf;
        for (int i = n-1; i; --i) { 
            ckmax(lp, i - rx[i]), ckmin(rp, i - lx[i]);
			if (lp > rp) break;
            if (i <= opt+1 and lp <= i and i <= rp) return true;
        }
        return false;
    };
    int l = 0, r = m-1, ans = r;
    while (l <= r) {
        int md = l + (r-l+1)/2;
        if (possible(md)) r = md-1, ans = md;
        else l = md+1;
    }
    return ans;
}

int brute(int n, int m, vector<int> a, vector<int> b) {
    sort(all(a)), sort(rbegin(b), rend(b));
    int ans = m;
    for (int i = 0; i < n; ++i) {
        int opt = 0;
        for (int j = 0; j < n; ++j) ckmax(opt, (a[(i+j)%n] + b[j]) % m);
        ckmin(ans, opt);
    }
    return ans;
}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
    while(t--) {
        int n, m; cin >> n >> m;
        vector<int> a(n), b(n);
        for (auto& x : a) cin >> x;
        for (auto& x : b) cin >> x;
        cout << solve(n, m, a, b) << endl;
    }
#else
    int t = 1;
    while (true) {
        int n = rnd(1, 100), m = rnd(1, 1000000);
        vector<int> a(n), b(n);
        for (int i = 0; i < n; ++i) a[i] = rnd(0, m-1), b[i] = rnd(0, m-1);
        auto my = solve(n, m, a, b);
        auto ans = brute(n, m, a, b);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << " " << m << endl;
            for (auto x : a) cout << x << " ";
            cout << endl;
            for (auto x : b) cout << x << " ";
            cout << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
