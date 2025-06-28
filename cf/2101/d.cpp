#include <bits/stdc++.h>
//#define gato
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

int brute(vector<int> v, int n){
    // [l, r] faz o W se existe l <= i <= r tal que:
    // set de elementos > v[i] eh decrescente em [l, i)
    // set de elementos < v[i] eh crescente em [l, i)
    // set de elementos > v[i] eh crescente em (i, r]
    // set de elementos < v[i] eh decrescente em (i, r]
    int ans = 0;
    for (int l = 0; l < n; ++l) {
        for (int r = l; r < n; ++r) {
            bool achou = false;
            for (int i = l; i <= r; ++i) {
                int x = inf, y = 0, ok = true;
                for (int j = l; j < i; ++j) {
                    if (v[j] < v[i]) {
                        ok &= (y < v[j]);
                        y = v[j];
                    } else {
                        ok &= (v[j] < x);
                        x = v[j];
                    }
                }
                if (!ok) continue;
                x = y = v[i];
                for (int j = i+1; j <= r; ++j) {
                    if (v[j] < v[i]) {
                        ok &= (v[j] < x);
                        x = v[j];
                    } else {
                        ok &= (y < v[j]);
                        y = v[j];
                    }
                }
                if (ok) { achou = true; break; }
            }
            ans += achou;
        }
    }
    return ans;
}
int solve(vector<int> v, int n) {
    auto trampo = [&] (vector<int> a) {
        vector<int> order(n); iota(all(order), 0);
        sort(all(order), [&] (int x, int y) {
            return a[x] > a[y];
        });
        set<int> bad;
        bad.insert(n);
        set<ii> s;
        vector<int> ans(n);
        for (auto i : order) { 
            int j = a[i];
            auto it = s.lower_bound({i, 0});
            if (it != end(s) and it != begin(s)) {
                auto it2 = prev(it);
                if ((it2->second) > (it->second)) bad.erase(it->first);
            }
            if (it != end(s) and (it->second) < j) bad.insert(it->first);
            if (it != begin(s)) {
                it = prev(it);
                if ((it->second) > j) bad.insert(i);
            }
            ans[i] = *bad.upper_bound(i);
            s.insert({i, j});
        }
        return ans;
    };
    vector<vector<int>> setas(4);
    for (int i = 0; i < 4; ++i) {
        setas[i] = trampo(v);
        for (auto& x : v) x *= -1;
        if (i&1) reverse(all(v));
        if (i&2) {
            reverse(all(setas[i]));
            for (auto& x : setas[i]) x = n - 1 - x;
        }
    }
    vector<int> lx(n), rx(n);
    for (int i = 0; i < n; ++i) lx[i] = max(setas[2][i], setas[3][i]) + 1, rx[i] = min(setas[0][i], setas[1][i]) - 1;
    int ans = 0;
    vector<vector<ii>> evs(n+1);
    for (int i = 0; i < n; ++i) {
        evs[lx[i]].pb({1, rx[i]});
        evs[rx[i]+1].pb({-1, rx[i]});
    }
    multiset<int> mt;
    for (int i = 0; i < n; ++i) {
        for (auto [tipo, k] : evs[i]) {
            if (tipo == 1) mt.insert(k);
            else mt.erase(mt.find(k));
        }
        ans += (*prev(end(mt))) - i + 1;
    }
    return ans;
}
int32_t main(){_
    #ifndef gato
    int t = 1;
    cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<int> a(n);
        for (auto& x : a) cin >> x;
        cout << solve(a, n) << endl;
    }
    #else
    auto W = [] (vector<int> p) {
        int n = sz(p);
        int lis = 0, lds = 0;
        vector<int> dp1(n), dp2(n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                if (p[i] < p[j]) ckmax(dp2[i], dp2[j]);
                else ckmax(dp1[i], dp1[j]);
            }
            dp1[i]++, dp2[i]++;
            ckmax(lis, dp1[i]);
            ckmax(lds, dp2[i]);
        }
        return (lis + lds == n+1);
    };
    int t = 1;
    while (true) {
        int n = rnd(4, 30);
        vector<int> p(n); iota(all(p), 1);
        shuffle(all(p), rng);
        int ans = brute(p, n), my = solve(p, n);
        if (ans != my) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << endl;
            for (auto x : p) cout << x << ' ';
            cout << endl;
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
    #endif
}
