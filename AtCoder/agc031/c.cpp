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
    int n, A, B; cin >> n >> A >> B;
    auto gray_code = [] (int n) {
        vector<int> ret(1<<n);
        for (int i = 0; i < (1<<n); i++) ret[i] = i^(i>>1);
        return ret;
    };
    int k = __builtin_popcount(A^B);
    if (k % 2 == 0) {
        cout << "NO" << endl;
        exit(0);
    }
    auto get = [&] (auto&& self, int N, int K) -> vector<int> {
        if (K == 1) return gray_code(N);
        auto v = self(self, N-2, K-2);
        vector<int> ans;
        int p1 = (1 << (N-2));
        int p2 = 2 * p1;
        for (int i = 0; i < sz(v)-2; i += 2) {
            int x = v[i], y = v[i+1];
            ans.pb(x), ans.pb(x+p1), ans.pb(x+p1+p2), ans.pb(x+p2);
            ans.pb(y+p2), ans.pb(y+p1+p2), ans.pb(y+p1), ans.pb(y);
        }
        int i = sz(v)-2;
        int x = v[i], y = v[i+1];
        ans.pb(x), ans.pb(x+p1), ans.pb(x+p1+p2), ans.pb(x+p2);
        ans.pb(y+p2), ans.pb(y), ans.pb(y+p1), ans.pb(y+p1+p2);
        return ans;
    };
    auto v = get(get, n, k);
    vector<int> bits_xor, bits_lst, o1, o2;
    for (int i = 0; i < n; ++i) {
        if ((A ^ B) >> i & 1) bits_xor.pb(i);
        else o1.pb(i);
        if (v.back() >> i & 1) bits_lst.pb(i);
        else o2.pb(i);
    }
    vector<int> f(n);
    assert(sz(bits_xor) == sz(bits_lst));
    for (int i = 0; i < k; ++i) f[bits_lst[i]] = bits_xor[i];
    for (int i = 0; i < n-k; ++i) f[o2[i]] = o1[i];
    auto transform = [&] (int x) {
        int fx = 0;
        for (int i = 0; i < n; ++i) {
            if (x >> i & 1) fx += (1 << f[i]);
        }
        return fx;
    };
    for (auto& x : v) x = transform(x);
    for (auto& x : v) x ^= A;
    assert(v[0] == A);
    assert(v.back() == B);
    for (int i = 1; i < sz(v); ++i) assert(__builtin_popcount(v[i]^v[i-1]) == 1);
    cout << "YES" << endl;
    for (auto x : v) cout << x << " ";
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
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
