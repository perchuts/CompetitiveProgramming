#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
//#define gato

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ii = pair<int,int>;
using iii = tuple<int,int,int>;

const int inf = 2e9+1;
const int mod = 1e9+7;
const int maxn = 2e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(69);

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}


void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    if (n == 2) {
        cout << ((a[0]^a[1])&max(a[0], a[1])) << endl;
        return;
    }
    vector<int> ps(n);
    for (int i = 0; i < n; ++i) ps[i] = (i == 0 ? a[i] : ps[i-1] ^ a[i]);
    vector<int> sl(n), sr(n);
    vector<ii> stk;
    stk.pb({inf, -1});
    for (int i = 0; i < n; ++i) {
        while (stk.back().first <= a[i]) stk.pop_back();
        sl[i] = stk.back().second;
        stk.pb({a[i], i});
    }
    stk = {{inf, n}};
    for (int i = n-1; ~i; --i) {
        while (stk.back().first <= a[i]) stk.pop_back();
        sr[i] = stk.back().second;
        stk.pb({a[i], i});
    }
    int ans = 0;
    for (auto x : ps) cout << x << " ";
    cout << endl;
    vector<int> seta(n, -1);
    for (int bit = 17; ~bit; --bit) {
        ans += (1 << bit);
        map<int, vector<int>> mp;
        map<int, int> id;
        mp[0].pb(-1);
        for (int i = 0; i < n; ++i) mp[ps[i] & ans].pb(i), seta[i] = -1;
        vector<iii> bons;
        for (int i = 0; i < n; ++i) {
            if ((a[i] & ans) == ans) bons.pb({sl[i], i, sr[i]-1});
        }
        vector<ii> pp;
        for (auto [x, v1] : mp) {
            if ((x^ans) < x) continue;
            auto v2 = mp[x^ans];
            int i = 0, j = 0;
            if (v1.empty() or v2.empty()) continue;
            while (i != sz(v1) and j != sz(v2)) {
                if (v1[i] < v2[j]) {
                    seta[v1[i++]] = v2[j];
                } else {
                    seta[v2[j++]] = v1[i];
                }
            }
            // parear qualquer par aqui dentro da certo!!
            // entao quero encontrar um par de caras tal que o maximo dentro seja tudooo 1
            //
        }
        sort(all(bons), [&] (iii x, iii y) {
            auto [x1, x2, x3] = x;
            auto [y1, y2, y3] = y;
            if (x1 != y1) return x1 < y1;
            return x2 > y2;
        });
        multiset<int> mt;
        for (int l = 0, r = 0; r != sz(bons); l = r) {
            while (r != sz(bons) and get<1>(bons[r]) < get<1>(bons[l])) r++;
            for (int i = get<0>(bons[l]); i < get<1>(bons[l]); ++i) if (seta[i] != -1) mt.insert(seta[i]);

        }
    }
    cout << ans << endl;
}

int brute(int n, vector<int> a) {
    int ans = 0;
    for (int l = 0; l < n; ++l) {
        int xx = 0, mx = 0;
        for (int r = l; r < n; ++r) {
            xx ^= a[r];
            ckmax(mx, a[r]);
            if (r != l) ckmax(ans, xx&mx);
        }
    }
    return ans;
}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
    while(t--) solve();
#else
    int t = 1;
    while (true) {
        int n = rnd(2, 3);
        vector<int> a(n);
        for (auto& x : a) x = rnd(0, 15);
        int mx = *max_element(all(a));
        int ans = brute(n, a);
        if ((ans&mx) != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << endl;
            for (auto x : a) cout << bitset<4>(x) << " ";
            cout << endl;
            cout << "solution: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
