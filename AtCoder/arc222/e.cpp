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
    int n, m; cin >> n >> m;

    int N = (1 << m);

    vector<int> freq(N), ans(N), caras;

    for (int i = 0; i < n; ++i) {
        int x; cin >> x;
        freq[x]++;
    }

    const int LIM = 16;

    for (int i = 0; i < N; ++i) {
        ans[0] += freq[i] / 2;
        if (freq[i] > LIM) caras.pb(i);
    }

    for (int i = 0; i < sz(caras); ++i) {
        for (int j = i + 1; j < sz(caras); ++j) {
            ans[caras[i] ^ caras[j]] += min(freq[caras[j]], freq[caras[i]]);
        }
    }

    auto fexp = [&] (int b, int e) {
        int r = 1;
        while (e) {
            if (e & 1) r = r * b % mod;
            e /= 2, b = b * b % mod;
        }
        return r;
    };

    auto fwht = [&] (vector<int> &a, bool inv = false) {
        for (int len = 1; len < sz(a); len += len) {
            for (int i = 0; i < sz(a); i += 2 * len) {
                for (int j = 0; j < len; ++j) {
                    int u = a[i + j], v = a[i + j + len];
                    a[i + j] = u + v;
                    if (a[i + j] >= mod) a[i + j] -= mod;
                    a[i + j + len] = u - v;
                    if (a[i + j + len] < 0) a[i + j + len] += mod;
                }
            }
        }
        if (inv) {
            int z = fexp(sz(a), mod-2);
            for (auto& x : a) x = x * z % mod;
        }
    };

    auto conv = [&] (vector<int> &a, vector<int> &b) {
        fwht(a), fwht(b);
        vector<int> c(sz(a));
        for (int i = 0; i < sz(a); ++i) c[i] = a[i] * b[i] % mod;
        fwht(c, true);
        return c;
    };

    {
        vector<int> peq(N), gran(N);
        for (int i = 0; i < N; ++i) {
            if (freq[i] <= LIM) peq[i] = freq[i];
            else gran[i] = 1;
        }
        auto c = conv(peq, gran);
        for (int i = 0; i < N; ++i) {
            ans[i] += c[i];
            if (ans[i] >= mod) ans[i] -= mod;
        }
    }

    // now add 4 extra bits for each value
    vector<int> p(16 * N);

    for (int i = 0; i < N; ++i) {
        if (freq[i] > LIM) continue;
        for (int j = 0; j < freq[i]; ++j) p[16 * i + j] = 1;
    }

    auto q = p;

    auto c = conv(p, q);
    for (auto& x : c) x = x * ((mod+1)/2) % mod;

    for (int i = 16; i < 16 * N; i += 16) {
        ans[i / 16] += c[i];
        if (ans[i / 16] >= mod) ans[i / 16] -= mod;
    }

    int r = 0, pw = 1;
    for (int i = 0; i < N; ++i) {
        r = (r + pw * ans[i]) % mod;
        pw = pw * 10 % mod;
    }
    cout << r << endl;
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
