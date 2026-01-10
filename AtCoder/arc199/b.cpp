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

vector<int> solve(int n, int k, vector<int> a) {
    auto simulate = [&] (vector<int> v, int pos = 0) {
        vector<int> mask(n);
        for (int i = 0; i < n; ++i) mask[i] = (1LL << i);
        for (auto x : v) mask[x] = mask[x+1] = mask[x] ^ mask[x+1];
        return mask[pos];
    };
    if (k == 0) return {0, 0};
    if (k == a[0]) return {};
    // store min(dim(kernel), 2) ways to reach 0.
    vector<int> basis(60), coord(60), zero;
    for (int i = 0; i < n; ++i) {
        int x = a[i], c = (1LL << i);
        for (int j = 0; j < 60; ++j) {
            if (x >> j & 1) {
                if (basis[j] == 0) {
                    basis[j] = x;
                    coord[j] = c;
                    break;
                }
                c ^= coord[j];
                x ^= basis[j];
            }
        }
        if (x == 0) zero.pb(c);
    }
    // por que nao consigo alcançar 010101010, 101010101?
    int c = 0, cur = k;
    for (int i = 0; i < 60; ++i) {
        if (cur >> i & 1) {
            if (basis[i] == 0) return {-1};
            c ^= coord[i];
            cur ^= basis[i];
        }
    }
    int bad1 = 0, bad2 = 0;
    int choice = 0;
    for (int i = 0; i < n; i += 2) bad1 += (1LL << i);
    for (int i = 1; i < n; i += 2) bad2 += (1LL << i);
	while (sz(zero) > 2) zero.pop_back();
    // 1 o 1 o
    // 3 3 7 3
    for (int j = 0; j < (1 << sz(zero)); ++j) {
        int cc = c;
        for (int w = 0; w < sz(zero); ++w) {
            if (j >> w & 1) cc ^= zero[w];
        }
        if (cc == bad1 or cc == bad2) continue;
        choice = cc;
        break;
    }
    if (choice == 0) return {-1};
    // ok, so lets find the first time such that when scanning two bits at a time, we either read two or zero bits.
    vector<int> ans;
    int i = 0;
    for (; ; ++i) {
        int cnt = (choice >> i & 1) + (choice >> (i + 1) & 1);
        if (cnt == 1) continue;
        int t = ((choice >> i) & 1);
        ans.pb(i);
        if (!t) ans.pb(i);
        for (int j = i-1-t; j >= 0; j -= 2) {
            ans.pb(j+1);
            ans.pb(j+1);
            ans.pb(j);
        }
        if (choice % 2 == 0 and i != 0) ans.pb(0), ans.pb(0);
        for (int j = i; j; --j) ans.pb(j);
        if (i) ans.pb(0), ans.pb(0), ans.pb(1), ans.pb(0);
        break;
    }
    auto M = simulate(ans);
    for (int j = 0; j <= i+1; ++j) assert((M >> j & 1) == (choice >> j & 1));
    i += 2;
    if (i == 2) {
        if (choice >> 2 & 1) {
            if (M % 2) {
                ans.pb(1), ans.pb(0), ans.pb(0), ans.pb(1), ans.pb(0);
            } else {
                ans.pb(0), ans.pb(0);
                ans.pb(1), ans.pb(0);
            }
        }
        i++;
    }
    // quero que a resposta esteja sempre no i-3!
    for (int pos = 0; pos < i-3; ++pos) {
        ans.pb(pos+1), ans.pb(pos+1);
        ans.pb(pos);
    }
    for (; i < n; ++i) {
        if ((choice >> i & 1)) {
            ans.pb(i-2), ans.pb(i-2);
            ans.pb(i-3);
            ans.pb(i-1);
            ans.pb(i-2);
        } else {
            ans.pb(i-2), ans.pb(i-2), ans.pb(i-3);
        }
    }
    i -= 3;
    if (i > 0) {
        ans.pb(i+1), ans.pb(i+1), ans.pb(i);
        for (int j = 0; j < i; ++j) ans.pb(j), ans.pb(j);
        for (int j = i; j >= 0; --j) ans.pb(j);
    }
    for (auto x : ans) a[x] = a[x+1] = (a[x] ^ a[x+1]), assert(0 <= x and x <= n-2);
    assert(a[0] == k);
    assert(sz(ans) <= 10000);
    return ans;
}

int32_t main() {_
    // vamos testar algumas operacoes
#ifndef gato
    int t = 1; cin >> t;
    while(t--) {
        int n, k; cin >> n >> k;
        vector<int> a(n);
        for (auto& x : a) cin >> x;
        auto ans = solve(n, k, a);
        if (!ans.empty() and ans[0] == -1) cout << "No" << endl;
        else {
            assert(sz(ans) < 10000);
            for (auto x : ans) assert(0 <= x and x < n);
            for (auto x : ans) a[x] = a[x+1] = (a[x] ^ a[x+1]);
            cout << "Yes" << endl;
            cout << sz(ans) << endl;
            for (auto x : ans) cout << x + 1 << " ";
            cout << endl;
        }
    }
#else
    int t = 1;
    while (true) {
        int bits = rnd(1, 60);
        int n = rnd(2, 60), k = rnd(0, (1 << bits)-1);
        vector<int> a(n);
        for (auto& x : a) x = rnd(0, (1 << bits) - 1);
        cout << n << " " << k << endl;
        for (auto x : a) cout << x << " ";
        cout << endl;
        auto my = solve(n, k, a);
        cout << (my.empty() ? "No" : "Yes") << endl;
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
