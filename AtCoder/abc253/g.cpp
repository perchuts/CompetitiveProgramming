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
    int n, l, r; cin >> n >> l >> r;
    --l, --r;
    int cur = 0, lx = -1, rx = -1;
    vector<int> ans(n); iota(all(ans), 1);
    auto apply = [&] () {
        if (lx == -1) return;
        auto temp = ans;
        deque<int> dq;
        for (int i = lx; i < n; ++i) dq.pb(ans[i]);
        for (int i = lx; i <= rx; ++i) {
            int x = dq.back(); dq.pop_back(); dq.push_front(x);
        }
        reverse(begin(dq), begin(dq)+rx-lx+1);
        for (int i = lx; i < n; ++i) ans[i] = dq[i-lx];
        lx = rx = -1;
    };
    for (int i = 0; i < n - 1; ++i) {
        int ncur = cur + n - i - 1;
        int inter = max(0LL, min(r, ncur-1) - max(l, cur) + 1);
        if (inter == n - i - 1) {
            if (lx == -1) lx = i;
            rx = i; 
        } else if (inter) {
            apply();
            //cout << cur << ' ' << ncur << ": " << i << endl;
            for (int j = cur; j < ncur; ++j) {
                if (l <= j and j <= r) {
                    swap(ans[i], ans[i+j-cur+1]);
                }
            }
        }
        cur = ncur;
    }
    apply();
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
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
