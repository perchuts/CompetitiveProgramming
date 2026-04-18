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

vector<int> solve(int n, int k) {
    auto rec = [&] (auto&& self, int x, int tam) -> vector<int> {
        if (x == 0) return vector<int>();
        if (tam == 1) return {x};
        --x;
        int block = 1;
        for (int j = 0; j < tam; ++j) block *= n;
        block = (block-1) / (n-1);
        int i = 1;
        while (x >= block) x -= block, i++;
        auto ans = self(self, x, tam-1);
        vector<int> aans = {i};
        for (auto z : ans) aans.pb(z);
        return aans;
    };
    if (n == 1) return vector<int>((k+1)/2, 1);
    // A com tamanho entre 1 e K
    // 1 <= A[i] <= N
    // N + N^2 + N^3 + ... + N^K
    // (N^{K+1}-N)/(N-1)
    // (N^K-1)/(N-1)
    if (n % 2 == 0) {
        vector<int> ans(k, n);
        ans[0] = n/2;
        return ans;
        cout << (n/2) << " ";
        for (int i = 0; i < k-1; ++i) cout << n << " ";
        cout << endl;
        exit(0);
    }
    // (N^K-N)/(N-2)
    int lim = 0, c = n;
    while (1e12 >= c) c *= n, lim++;
    // b >= lim => k < N^i
    vector<int> ans;
    ans.pb((n+1)/2);
    for (int i = k-1; i >= 1; --i) {
        // b >= (N^i-1)/(N-1)
        // bN - b + 1 >= N^i
        // kN >= bN - b + 1
        // k >= N^(i-1)
        if (i <= lim) {
            int b = k - i;
            int block = 1;
            for (int j = 0; j < i; ++j) block *= n;
            block = (block-1) / (n-1);
            int tot = block*n;
            int want = (tot-b+1)/2;
            auto z = rec(rec, want, i);
            for (auto x : z) ans.pb(x);
            break;
        } else ans.pb((n+1)/2);
    }
    return ans;
}

vector<int> brute(int n, int k) {
    auto rec = [&] (auto&& self, int x, int tam) -> vector<int> {
        if (x == 0) return vector<int>();
        if (tam == 1) return {x};
        --x;
        int block = 1;
        for (int j = 0; j < tam; ++j) block *= n;
        block = (block-1) / (n-1);
        int i = 1;
        while (x >= block) x -= block, i++;
        auto ans = self(self, x, tam-1);
        vector<int> aans = {i};
        for (auto z : ans) aans.pb(z);
        return aans;
    };
    int tam = 1, tot = 0;
    for (int i = 1; i <= k; ++i) tam *= n, tot += tam;
    auto aans = rec(rec, (tot+1)/2, k);
    return aans;
}

int32_t main() {_
#ifndef gato
    int k, n; cin >> n >> k;
    auto ans = solve(n, k);
    for (auto x : ans) cout << x << " ";
    cout << endl;
#else
    int t = 1;
    for (int n = 2; n <= 1000; ++n) {
        int pot = 1;
        for (int k = 1; ; ++k) {
            pot *= n;
            if (pot > 1e15) break;
            auto my = solve(n, k);
            auto ans = brute(n, k);
            if (my != ans) {
                cout << "Wrong answer on test " << t << endl;
                cout << "Solve: ";
                for (auto x : my) cout << x << " ";
                cout << endl;
                cout << "Brute: ";
                for (auto x : ans) cout << x << " ";
                cout << endl;
                exit(0);
            }
            cout << "Accepted on test " << t++ << endl;
        }
    }
#endif
}
