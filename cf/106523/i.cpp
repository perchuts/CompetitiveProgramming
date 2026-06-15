#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
//#define endl '\n'
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
const int mod = (119<<23)+1;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(69);

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

vector<int> solve(int n, vector<int> v) {
    vector<int> ord(n); 
    iota(all(ord), 0); 
    sort(all(ord), [&] (int x, int y) {
        return v[x] < v[y];
    });
    const int P = 100019;
    vector<int> pw(n+1, 1);
    for (int i = 1; i <= n; ++i) pw[i] = P * pw[i-1] % mod;
    auto get_hash = [&] (vector<int>& a) {
        int h = 0;
        for (int i = 0; i < sz(a); ++i) {
            h = (h + pw[n - i] * v[a[i]]) % mod;
        }
        return h;
    };
    // teste tudo dos 5 primeiros caras; algum tem que dar certo
    vector<int> ans;

    vector<int> mark(n);
    auto tentar = [&] (vector<int>& a) {
        for (auto x : a) mark[x] = 1;
        vector<int> b;
        for (int j = 0; j < n; ++j) if (mark[j] == 0) b.pb(j);
        for (auto x : a) mark[x] = 0;
        return get_hash(a) < get_hash(b);
    };
    vector<vector<int>> best(n);
    for (int i = n-2; i >= 0; --i) {
        best[i] = best[i+1];
        best[i].pb(i+1);
        sort(all(best[i]), [&] (int x, int y) {
            return v[x] < v[y];
         });
        if (sz(best[i]) > 4) best[i].pop_back();
    }
    for (int l = 0, r = 0; l < min(n, 4LL); l = r) {
        vector<int> act;
        while (r != n and v[ord[l]] == v[ord[r]]) r++;
        //cout << l << " " << r << endl << flush;
        auto search = [&] (auto&& self, vector<int> bichos, int pos) -> vector<int> {
            bichos.pb(pos);
            //for (auto x : bichos) /cout << x << " ";
            //cout << endl;
            //cout << flush;
            if (tentar(bichos)) {
                for (auto& x : bichos) x = v[x];
                return bichos;
            }
            auto& oo = best[pos];
            sort(all(oo), [&] (int x, int y) { return v[x] < v[y]; });
			vector<int> opt;
            for (int lx = 0, rx = 0; lx < min(sz(oo), 4LL); ++lx) {
                while (rx != sz(oo) and v[oo[lx]] == v[oo[rx]]) rx++;
                for (int j = lx; j < rx; ++j) {
                    auto z = self(self, bichos, oo[j]);
                    if (z.empty()) continue;
                    if (opt.empty()) opt = z;
                    else ckmin(opt, z);
                }
                if (!opt.empty()) break;
            }
			return opt;
        };

        for (int i = l; i < r; ++i) {
            auto choice = search(search, vector<int>(), ord[i]);
            if (!choice.empty()) {
                if (ans.empty()) ans = choice;
                else ckmin(ans, choice);
            }
        }
        if (!ans.empty()) break;
    }
    return ans;
}

vector<int> brute(int n, vector<int> v) {
    const int P = 100019;
    vector<int> pw(n+1, 1);
    for (int i = 1; i <= n; ++i) pw[i] = P * pw[i-1] % mod;
    auto get_hash = [&] (vector<int> a) {
        int h = 0;
        for (int i = 0; i < sz(a); ++i) {
            h = (h + pw[n - i] * v[a[i]]) % mod;
        }
        return h;
    };
    // teste tudo dos 5 primeiros caras; algum tem que dar certo
    vector<int> ans;
    auto tentar = [&] (vector<int> a) {
        vector<int> mark(n);
        for (auto x : a) mark[x] = 1;
        vector<int> b;
        for (int j = 0; j < n; ++j) if (mark[j] == 0) b.pb(j);
        return get_hash(a) < get_hash(b);
    };
    for (int i = 1; i < (1 << n); ++i) {
        vector<int> a;
        for (int j = 0; j < n; ++j) {
            if (i >> j & 1) a.pb(j);
        }
        if (tentar(a)) {
            for (auto& x : a) x = v[x];
            if (ans.empty()) ans = a;
            else ckmin(ans, a);
        }
    }
    return ans;
};

int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    auto ans = solve(n, a);
    if (ans.empty()) {
        cout << -1 << endl;
    } else {
        for (auto x : ans) cout << x << " ";
        cout << endl;
    }
#else
    int t = 1;
    while (true) {
        int n = rnd(1, 8);
        vector<int> v(n);
        for (auto& x : v) x = rnd(1, 10);
		cout << n << endl;
		for (auto x : v) cout << x << " ";
		cout << endl;
        auto my = solve(n, v);
        auto ans = brute(n, v);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << endl;
            for (auto x : v) cout << x << " ";
            cout << endl;
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
#endif
}
