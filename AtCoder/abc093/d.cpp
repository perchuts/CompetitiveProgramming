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

vector<int> solve(vector<ii> queries){
    vector<int> sexo;
    for (auto [a, b] : queries) {
        int eu = a*b;
        auto get_best = [&] (int lx, int rx, int st) {
            if (rx < lx) return 0LL;
            int l = 0, r = rx-lx, ans = lx * st;
            while (r-l > 2) {
                int m1 = l + (r-l)/3;
                int m2 = r - (r-l)/3;
                if ((lx+m1)*(st-m1) < (lx+m2)*(st-m2)) l = m1;
                else r = m2;
            }
            for (int i = l; i <= r; ++i) ckmax(ans, (lx+i)*(st-i));
            return ans;
        };
        auto possible = [&] (int x) {
            int fim = min(x, a-1), resp = 0, foi = 0, aum = (x >= b);
            if (aum and x+2-fim <= b) {
                int quem = x+2-b;
                foi = 1;
                ckmax(resp, get_best(1, quem-1, x+1));
                ckmax(resp, get_best(quem, fim, b-1));
            } else ckmax(resp, get_best(1, fim, x+aum));
            if (x < a) return (resp < eu);
            if (aum and !foi) {
                int quem = x+3-b;
                ckmax(resp, get_best(a+1, quem-1, x-a+2));
                ckmax(resp, get_best(quem, x+1, b-1));
            } else ckmax(resp, get_best(a+1, x+1, x-a+1));
            return (resp < eu);
        };
        int l = 1, r = 3*sqrt(eu)+maxn, ans = 0;
        while (l <= r) {
            int md = l + (r-l+1)/2;
            if (possible(md)) ans = md, l = md+1;
            else r = md-1;
        }
        sexo.pb(ans);
    }
    return sexo;
}

int brute(int a, int b) {
    auto possible = [&] (int x) {
        vector<int> v1, v2;
        for (int i = 1; i <= x; ++i) if (i != a) v1.pb(i);
        if (sz(v1) != x) v1.pb(x+1);
        for (int i = 1; i <= x; ++i) if (i != b) v2.pb(i);
        if (sz(v2) != x) v2.pb(x+1);
        reverse(all(v2));
        int ans = 0;
        for (int i = 0; i < x; ++i) ckmax(ans, v1[i] * v2[i]);
        return (ans < a*b);
    };
    int l = 1, r = 3*sqrt(a*b)+maxn, ans = 0;
    while (l <= r) {
        int md = l + (r-l+1)/2;
        if (possible(md)) ans = md, l = md+1;
        else r = md-1;
    }
    return ans;
}
int32_t main(){_
#ifndef gato
    int q; cin >> q;
    vector<ii> qu(q);
    for (auto& [x, y] : qu) cin >> x >> y;
    auto my = solve(qu);
    for (auto x : my) cout << x << endl;
#else
    int t = 1;
    while (true) {
        int x = rnd(1, 10), y = rnd(1, 10);
        if (solve({{x, y}})[0] != brute(x, y)) {
            cout << "Wrong answer on test " << t << endl;
            cout << x << ' ' << y << endl;
            cout << "Your output: " << solve({{x, y}})[0] << endl;
            cout << "Correct answer: " << brute(x, y) << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
