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
    int n, k; cin >> n >> k;
    vector<vector<int>> bichos(20);
    vector<int> p(n), q(n);
    for (auto& x : p) cin >> x, --x;
    for (auto& x : q) cin >> x, --x;
    bichos[0] = {1}, bichos[1] = {2};
    auto get_inv = [&] (vector<int> a) {
        vector<int> b(n);
        for (int i = 0; i < n; ++i) b[a[i]] = i;
        return b;
    };
    auto compose = [&] (vector<int> a, vector<int> b) {
        vector<int> resp(n);
        for (int i = 0; i < n; ++i) resp[i] = a[b[i]];
        return resp;
    };
    auto print = [] (vector<int> p, bool flag = 0) {
        for (auto x : p) cout << x + 1 << " ";
        cout << endl;
        if (flag) exit(0);
    };
    if (k == 1) print(p, 1);
    if (k == 2) print(q, 1);
    if (k == 3) print(compose(q, get_inv(p)), 1);
    k -= 4;
    int vezes = k / 6;
    auto bicho = compose(get_inv(p), compose(get_inv(q), compose(p, q)));
    vector<int> ans(n); iota(all(ans), 0);
    while (vezes) {
        if (vezes & 1) ans = compose(ans, bicho);
        bicho = compose(bicho, bicho), vezes /= 2;
    }
    auto naive = [&] (int x) {
        if (x == 1) return p;
        if (x == 2) return q;
        auto a = q;
        auto b = p;
        for (int i = 3; i <= x; ++i) {
            auto c = compose(a, get_inv(b));
            b = a;
            a = c;
        }
        return a;
    };
    vector<int> a(n), b(n);
    bicho = compose(q, ans);
    b = compose(bicho, compose(get_inv(p), get_inv(bicho)));
    a = compose(bicho, compose(get_inv(p), compose(get_inv(q), compose(p, get_inv(bicho)))));
    print(b);
    print(a);
    print(naive(4));
    print(naive(5));
    k %= 6;
    if (k == 0) print(b, 1);
    if (k == 1) print(a, 1);
    k--;
    while (k--) {
        auto c = compose(a, get_inv(b));
        b = a;
        a = c;
    }
    print(a, 1);
    // a -a a -a
    //for (int i = 2; i < 20; ++i) {
    //    bichos[i] = bichos[i-1];
    //    auto temp = bichos[i-2];
    //    reverse(all(temp));
    //    for (auto x : temp) bichos[i].pb(-x);
    //    vector<int> v2;
    //    for (auto x : bichos[i]) {
    //        if (!v2.empty() and v2.back() == -x) {
    //            v2.pop_back();
    //        } else v2.push_back(x);
    //    }
    //    swap(v2, bichos[i]);
    //    cout << "a_" << i << ": ";
    //    for (auto x : bichos[i]) {
    //        cout << x << " ";
    //    }
    //    cout << endl;
    //}
    //cout << "sizes: " << endl;
    //for (int i = 2; i < 20; ++i) cout << "i = " << i << ": " << sz(bichos[i]) << endl;

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
