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
const int mod = (119<<23)+1;
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
    vector<int> lx(n), rx(n);
    for (int i = 0; i < n; ++i) cin >> lx[i] >> rx[i];
    vector<int> only_a(n+3), only_b(n+3), both(n+3);
    for (int i = 0; i < n; ++i) {
        // K, N-K
        // L <= N-K <= R
        // K <= N-L
        // N-R <= K
        // N-R <= K <= N-L
        int l2 = n-rx[i], r2 = n-lx[i];
        int il = max(l2, lx[i]), ir = min(rx[i], r2);
        //cout << lx[i] << " " << rx[i] << " " << l2 << " " << r2 << endl;
        if (il <= ir) {
            //cout << "1" << endl;
            both[il]++;
            both[min(ir, n)+1]--;
        }
        if (l2 < lx[i]) {
            //cout << "2a" << endl;
            only_b[l2]++;
            only_b[min(lx[i]-1, r2)+1]--;
        }
        if (lx[i] < l2) {
            //cout << "2b" << endl;
            only_a[lx[i]]++;
            only_a[min(l2-1, rx[i])+1]--;
        }
        if (r2 < rx[i]) {
            //cout << "3a" << endl;
            only_a[max(lx[i], r2+1)]++;
            only_a[rx[i]+1]--;
        }
        if (rx[i] < r2) {
            //cout << "3b" << endl;
            only_b[max(rx[i]+1, l2)]++;
            only_b[r2+1]--;
        }
        //cout << "finish" << endl;
    }
    vector<int> fat(n+1, 1), ifat(n+1);
    for (int i = 1; i <= n; ++i) fat[i] = i * fat[i-1] % mod;
    auto fexp = [&] (int b, int e) {
        int ans = 1;
        while (e) {
            if (e&1) ans = ans * b % mod;
            e /= 2, b = b * b % mod;
        }
        return ans;
    };
    ifat[n] = fexp(fat[n], mod-2);
    auto ncr = [&] (int a, int b) {
        if (min(a, b) < 0 or b > a) return 0LL;
        return fat[a] * ifat[b] % mod * ifat[a-b] % mod;
    };
    for (int i = n-1; ~i; --i) ifat[i] = (i+1) * ifat[i+1] % mod;
    int ans = 0;
    int a = 0, b = 0, ambos = 0;
    for (int i = 0; i <= n; ++i) {
        a += only_a[i], b += only_b[i], ambos += both[i];
        //cout << a << " " << b << " " << ambos << endl;
        if (a+b+ambos == n and 1 <= i and i < n) ans = (ans + ncr(ambos, i-a)) % mod;
    }
    cout << ans << endl;
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
