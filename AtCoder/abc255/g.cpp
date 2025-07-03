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

bool brute(int n, int m, vector<int> a, vector<ii> rs){
    int lim = 30;
    vector<int> nim(lim);
    map<ii, int> mp;
    for (auto& [x, y] : rs) mp[{x, y}] = 1;
    for (int i = 1; i < lim; ++i) {
        vector<int> mark(i+1);
        for (int j = 1; j <= i; ++j) {
            if (mp[{i, j}]) continue;
            mark[nim[i-j]] = 1;
        }
        for (int j = 0; ; ++j) {
            if (!mark[j]) {
                nim[i] = j;
                break;
            }
        }
    }
    int ans = 0;
    for (auto x : a) ans ^= nim[x];
    return (ans != 0);
}

bool solve(int n, int m, vector<int> a, vector<ii> rs){
    for (auto& [x, y] : rs) y = x - y;
    int mex = 0, lst = -1, ans = 0;
    sort(all(rs));
    vector<iii> normie;
    map<int, int> cnt, exotico;
    for (int l = 0, r = 0; l < m; l = r) {
        if (lst < rs[l].first-1) normie.pb({lst+1, rs[l].first-1, mex}), mex += rs[l].first-lst-1;
        while (r < m and rs[r].first == rs[l].first) r++;
        map<int, int> rem;  
        for (int i = l; i < r; ++i) {
            int j = lower_bound(all(normie), tuple(rs[i].second+1, -1, -1)) - begin(normie) - 1;
            if (j >= 0 and get<1>(normie[j]) >= rs[i].second) {
                auto [lx, rx, beg] = normie[j];
                rem[beg + rs[i].second - lx]++;
            } else {
                rem[exotico[rs[i].second]]++;
            }
        }
        int eu = -1;
        for (auto [x, y] : rem) {
            // invariante: cnt[x] = cnt real - 1
            if (y == cnt[x] + 1) { eu = x; break; }
        }
        if (eu == -1) {
			//cout << rs[l].first << ' ' << mex << endl;
            if (normie.empty() or get<1>(normie.back()) != rs[l].first-1) normie.pb({rs[l].first, rs[l].first, mex++});
            else {
                auto& [lx, rx, beg] = normie.back();
                rx++, mex++;
            }
        } else {
			//cout << rs[l].first << ' ' << eu << endl;
            cnt[eu]++;
            exotico[rs[l].first] = eu;
        }
        lst = rs[l].first;
    }
    normie.pb({lst+1, 2e18, mex});
    for (auto x : a) {
        if (exotico.count(x)) ans ^= exotico[x];
        else {
            int j = lower_bound(all(normie), tuple(x+1, -1, -1)) - begin(normie) - 1;
            if (j >= 0 and get<1>(normie[j]) >= x) {
                auto [lx, rx, beg] = normie[j];
                ans ^= (beg + x - lx);
            }
        }
    }
    return (ans != 0);
}

int32_t main(){_
#ifndef gato
    int n, m; cin >> n >> m;
    vector<int> a(n); 
    for (auto& x : a) cin >> x;
    vector<ii> rs(m);
    for (auto& [x, y] : rs) cin >> x >> y;
    cout << (solve(n, m, a, rs) ? "Takahashi" : "Aoki") << endl;
#else
    int t = 1;
    while (true) {
        int n = rnd(1, 5), m = rnd(1, 50);
        int lim = 29;
        vector<int> a(n);
        for (auto& x : a) x = rnd(1, lim);
        vector<ii> rs(m);
        for (auto& [x, y] : rs) {
            x = rnd(1, lim), y = rnd(1, lim);
            if (x < y) swap(x, y);
        }
		sort(all(rs));
		rs.erase(unique(all(rs)), end(rs));
		m = sz(rs);
        int my = solve(n, m, a, rs), ans = brute(n, m, a, rs);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << ' ' << m << endl;
            for (auto x : a) cout << x << ' ';
            cout << endl;
            for (auto [x, y] : rs) cout << x << ' ' << y << endl;
            cout << "Your output: " << (my ? "Takahashi" : "Aoki") << endl;
            cout << "Answer: " << (ans ? "Takahashi" : "Aoki") << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
