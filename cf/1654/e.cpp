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
const int maxn = 4e7+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}
int cnt[maxn];
void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x, cnt[x]++;
    int mx = 0;
    for (int i = 1; i <= 100000; ++i) ckmax(mx, exchange(cnt[i], 0));
    const int block = 320;
    for (int rev = 0; rev < 2; ++rev) {
        for (int b = 1; b * b <= 100000; ++b) {
            int shift = (n-1) * b;
            for (int i = 0; i < n; ++i) cnt[a[i] - i * b + shift]++;
            for (int i = 0; i < n; ++i) ckmax(mx, exchange(cnt[a[i] - i * b + shift], 0));
        }
        for (int i = 0; i < n; ++i) {
            int r = min(n, i+block);
            for (int j = i+1; j < r; ++j) {
                int val = a[j] - a[i];
                if (val > 0 and val % (j-i) == 0) cnt[val/(j-i)]++;
            }
            for (int j = i+1; j < r; ++j) {
                int val = a[j] - a[i];
                if (val > 0) ckmax(mx, exchange(cnt[val/(j-i)], 0)+1);
            }
        }
        reverse(all(a));
    }
    cout << n - mx << endl;
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
