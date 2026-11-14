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
    // fixe o ultimo cara. preciso que todos os numeros sejam
    // m = max
    // u = ultimo cara
    // a[i] === 0 mod m-u -> pra todo a[i] > u
    // a[i] === 0 ou u mod m-u caso contrario
    int m = a[n-1];
    vector<int> fat(n+1, 1);
    for (int i = 1; i <= n; ++i) fat[i] = i * fat[i-1] % mod;
    int ans = 0;
    map<int, int> foi;
    map<int, int> tem;
    for (auto x : a) tem[x] = 1;
    int x = 0, y = 0;
    for (int i = 0; i < n-3; ++i) {
        if (i % 2 == 0) y += i/2+1;
        else x++, y -= ((i+1)/2);
    }
    auto test = [&] (int u) {
        if (foi[u] or !tem[u]) return;
        foi[u] = 1;
        int c1 = 1, c2 = 0;
        map<int, int> usei;
        usei[u] = usei[0] = usei[m] = 1;
        for (int i = 0; i < n-3; ++i) {
            int want;
            if (i % 2 == 0) {
                c1++;
                want = (i/2+1)*(m-u);
            } else {
               c2++;
                want = u - ((i+1)/2)*(m-u);
            }
            if (!tem[want] or usei[want]) return;
            usei[want] = 1;
        }
        ans = (ans + fat[c1] * fat[c2]) % mod;
    };
    int aa = x - y + 1, S = 0;
    for (auto x : a) S += x;
    S -= (y+1)*m;
    if (S != 0 or aa != 0) {
        if (S == 0 or aa == 0 or S % aa) {
            cout << 0 << endl;
            return;
        }
        test(S/aa);
        cout << ans << endl;
        return;
    }
    test(a[n-2]);
    for (int i = 1; i * i <= a[n-2]; ++i) {
        if (a[n-2] % i) continue;
        test(m-i);
        test(m-(a[n-2]/i));
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
