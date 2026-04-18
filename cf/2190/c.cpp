#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
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
vector<int> P;
vector<int> solve(int n) {
    int qq = 0;
    auto ask = [&] (int i, int j) {
        if (j >= n) return 1LL;
        qq++;
        assert(qq <= 3*n);
#ifndef gato
        cout << "? " << i+1 << " " << j+1 << endl;
        int x; cin >> x;
        return x;
#else
    return (P[i] < P[j] ? 1LL : 0LL); 
#endif
    };
    int lst = -1, pos = -1, menor = n-1;
    int foi = 0;
    for (int i = n-2; ~i; --i) {
        int k = ask(i, i+1);
        if (k == 1 and lst == 0) {
            pos = i+1;
            break;
        }
        if (k == 0 and foi == 0) {
            foi = 1;
            menor = i+1;
        }
        lst = k;
    }
    if (pos == -1) {
        return {};
    }
    int dir = pos+1;
    // primeiro cara maior
    int pus = 0;
    vector<int> ordem;
    ordem.pb(menor);
    int i = menor-1, j = menor+1;
    while (i >= pos) {
        int x = ask(i, j);
        if (x == 0) ordem.pb(j++);
        else ordem.pb(i--);
    }
    vector<int> ans(n), used(n); iota(all(ans), 0);
    for (int i = pos-1; i < j; ++i) ans[i] = -1;
    for (int i = 0; i < sz(ordem); ++i) {
        int x = ordem[i];
        if (ask(pos-1, x)) {
            ordem.insert(begin(ordem)+i, pos-1);
            ans[pos-1] = x;
            used[x] = pus = 1;
            break;
        }
    }
    assert(pus);
    int idx = pos;
    for (int i = 0; i < sz(ordem); ++i) {
        if (!used[ordem[i]]) ans[idx++] = ordem[i];
    }
    return ans;
}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
    while(t--) {
        int n; cin >> n;
        auto ans = solve(n);
        if (ans.empty()) {
            cout << "! -1" << endl;
            continue;
        }
    cout << "! ";
    for (auto x : ans) cout << x + 1 << " ";
    cout << endl;
    }
#else
    int t = 1;
    while (true) {
        int n = rnd(2, 8);
        P.resize(n);
        iota(all(P), 0);
        shuffle(all(P), rng);
        vector<int> z(n); iota(all(z), 0);
        vector<int> q;
auto revP = P;
reverse(all(revP));
        do {
            auto zz = z;
            reverse(all(zz));

            if (z > P and zz > revP) {
                if (q.empty()) q = z;
                else ckmin(q, z);
            }
        } while (next_permutation(all(z)));
        vector<int> invp(n), r(n);
        if (q.empty()) {
            r.clear();
        } else {
            for (int i = 0; i < n; ++i) invp[P[i]] = i;
            for (int i = 0; i < n; ++i) r[i] = invp[q[i]];
        }
        for (auto x : P) cout << x + 1 << " ";
        cout << endl;
        auto my = solve(n);
        if (my != r) {
            cout << "WA " << t << endl;
            for (auto x : P) cout << x + 1 << " ";
            cout << endl;
            cout << "Q = ";
            for (auto x : q) cout << x + 1 << " ";
            cout << endl;
            cout << "R = ";
            for (auto x : r) cout << x + 1 << " ";
            cout << endl;
            cout << "Your output: ";
            for (auto x : my) cout << x + 1 << " ";
            cout << endl;
            exit(0);
        }
        cout << "AC " << t++ << endl;
    }
#endif
}
