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

void solve(){
    int n; cin >> n;
    vector<int> v(n);
    for (auto& x : v) cin >> x;
    int tries = 20;
    for (int __ = 0; __ < tries; ++__) {
        int a = rnd(0, n-1), b = a;
        while (b == a) b = rnd(0, n-1);
        int val = abs(v[a]-v[b]);
        auto test = [&] (int m) {
            if (m <= 2) return;
            int freq = 0, cand = -1;
            for (auto x : v) {
                int y = x % m;
                if (y == cand) freq++;
                else freq--;
                if (freq == -1) cand = y, freq = 1;
            }
            freq = 0;
            for (auto x : v) {
                int y = x % m;
                if (y == cand) freq++;
                else freq--;
            }
            if (freq > 0) {
                cout << m << endl;
                exit(0);
            }
        };
        for (int i = 1; i * i <= val; ++i) {
            if (val % i) continue;
            test(i), test(val/i);
        }
    }
    cout << -1 << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
