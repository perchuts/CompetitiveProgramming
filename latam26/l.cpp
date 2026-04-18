#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll
//#define gato
//#define debug

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

mt19937 rng(69);

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

vector<bool> brute(int n, int C, int L, vector<int> ini_pos, vector<int> v, int q, vector<int> queries) {
#ifdef debug
    cout << "brute: " << endl;
#endif
    vector<bool> ans;
    for (int x : queries) {
        vector<int> pos;
        for (int i = 0; i < n; ++i) {
            pos.pb(ini_pos[i]+x*v[i]);
#ifdef debug
            cout << pos.back() << " ";
#endif
        }
#ifdef debug
        cout << endl;
#endif
        sort(all(pos));
        int l = n, r = n;
        for (int i = 0; i < n; ++i) {
            if (0 <= pos[i] and pos[i] <= L) {
                ckmin(l, i);
                r = i;
            }
        }
        if (l == n) ans.pb(1);
        else {
            bool ok = (C <= pos[l] or L - pos[r] >= C);
            for (int i = l; i < r; ++i) ok |= (pos[i+1] - pos[i] >= C);
            ans.pb(ok);
        }
    }
    return ans;
}

vector<bool> solve(int n, int C, int L, vector<int> ini_pos, vector<int> v, int q, vector<int> queries) {
    int p_esq = -1, p_dir = -1;

    for (int i = 0; i < n; ++i) {
        if (ini_pos[i] == 0 and v[i] == 0) p_esq = i;
        if (ini_pos[i] == L and v[i] == 0) p_dir = i;
    }
    if (p_esq == -1) ini_pos.pb(0), v.pb(0), p_esq = n++;
    if (p_dir == -1) ini_pos.pb(L), v.pb(0), p_dir = n++;

    int id_esq = p_esq, id_dir = p_dir;

    vector<vector<bool>> dist_ok(n, vector<bool>(n));
    vector<array<int, 5>> ev;

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            dist_ok[j][i] = dist_ok[i][j] = (abs(ini_pos[i] - ini_pos[j]) >= C);
            if (v[i] == v[j]) continue;
            int num = ini_pos[j]-ini_pos[i], den = v[i]-v[j];
            if (num*den > 0) {
                num = abs(num), den = abs(den); int g = gcd(num, den); num /= g, den /= g;
                ev.pb({num, den, 0, i, j});
            }
            int ti = i, tj = j;
            if (v[i] < v[j]) swap(ti, tj);
            int d = ini_pos[ti] - ini_pos[tj], delta = v[ti] - v[tj];
            den = delta;
            num = C-d;
            if (num*delta > 0) {
                num = abs(num), den = abs(den); int g = gcd(num, den); num /= g, den /= g;
                ev.pb({num, den, 1, i, j});
            }
            den = delta;
            num = -C-d;
            if (num*delta >= 0) {
                num = abs(num), den = abs(den); int g = gcd(num, den); num /= g, den /= g;
                ev.pb({num, den, 1, i, j});
            }
        }
    }

    vector<bool> ans(q);

    for (int i = 0; i < q; ++i) { ev.pb({queries[i], 1, 2, i, i}); }
    sort(all(ev), [&] (array<int, 5> o, array<int, 5> p) { int a = o[0], b = o[1], c = p[0], d = p[1]; if (a*d == b*c) return o[2] < p[2]; return (a*d < b*c); });

    vector<int> ord(n), onde(n); iota(all(ord), 0);
    sort(all(ord), [&] (int x, int y) { return pair{ini_pos[x], v[x]} < pair{ini_pos[y], v[y]}; });
    for (int i = 0; i < n; ++i) onde[ord[i]] = i;
    p_esq = onde[id_esq], p_dir = onde[id_dir];


    int valid_count = 0;
    for (int i = 0; i < n-1; ++i) if (p_esq <= i and i < p_dir) valid_count += dist_ok[ord[i]][ord[i+1]];

    vector<vector<int>> label(n, vector<int>(n, -1));
    vector<int> foi_dist(sz(ev));
    for (int lp = 0, rp = 0; lp < sz(ev); lp = rp) {
        while (rp != sz(ev) and ev[lp][0] == ev[rp][0] and ev[lp][1] == ev[rp][1]) rp++;
        int i1 = lp, i2;
        while (i1 < rp and ev[i1][2] == 0) i1++;
        i2 = i1;
        while (i2 < rp and ev[i2][2] <= 1) i2++;
        for (int i = i1; i < i2; ++i) {
            int p1 = onde[ev[i][3]], p2 = onde[ev[i][4]];
            if (dist_ok[ev[i][3]][ev[i][4]] == 1) continue;
            foi_dist[i] = 1;
            dist_ok[ev[i][4]][ev[i][3]] = dist_ok[ev[i][3]][ev[i][4]] = 1;
            if (abs(p1-p2) == 1) {
                if (p_esq <= min(p1, p2) and min(p1, p2) < p_dir) valid_count++;
            }
        }
        for (int i = i2; i < rp; ++i) ans[ev[i][4]] = (valid_count > 0);
        for (int i = lp; i < i1; ++i) {
            label[onde[ev[i][3]]][onde[ev[i][4]]] = label[onde[ev[i][4]]][onde[ev[i][3]]] = lp;
        }
        for (int i = lp; i < i1; ++i) {
            if (label[onde[ev[i][3]]][onde[ev[i][4]]] != lp) continue;
            int l = onde[ev[i][3]], r = onde[ev[i][4]]; 
            if (l > r) swap(l, r);
            while (l and label[l-1][l] == lp) --l;
            while (r < n-1 and label[r][r+1] == lp) ++r;
            for (int j = l-1; j <= r; ++j) {
                if (j < 0 or j == n-1) continue;
                if (p_esq <= j and j < p_dir) valid_count -= dist_ok[ord[j]][ord[j+1]];
            }
            for (int j = l; j <= (l+r)/2; ++j) {
                swap(onde[ord[j]], onde[ord[r-(j-l)]]), swap(ord[j], ord[r-(j-l)]);
            }
            p_esq = onde[id_esq], p_dir = onde[id_dir];
            for (int j = l-1; j <= r; ++j) {
                if (j < 0 or j == n-1) continue;
                if (p_esq <= j and j < p_dir) valid_count += dist_ok[ord[j]][ord[j+1]];
            }
            for (int j = l; j <= r; ++j) for (int k = j+1; k <= r; ++k) label[j][k] = label[k][j] = -1;
        }
        for (int i = i1; i < i2; ++i) {
            int p1 = onde[ev[i][3]], p2 = onde[ev[i][4]];
            if (foi_dist[i]) continue;
            if (abs(p1-p2) == 1) {
                if (p_esq <= min(p1, p2) and min(p1, p2) < p_dir) valid_count--;
            }
            dist_ok[ev[i][4]][ev[i][3]] = dist_ok[ev[i][3]][ev[i][4]] = 0;
        }
    }
    return ans;
}

int32_t main() {_
#ifndef gato
    int n, c, l; cin >> n >> c >> l;
    vector<int> ini_pos(n), v(n);
    for (int i = 0; i < n; ++i) cin >> ini_pos[i] >> v[i];
    int q; cin >> q;
    vector<int> queries(q);
    for (auto& x : queries) cin >> x;
    auto ans = solve(n, c, l, ini_pos, v, q, queries);
    //auto ans = brute(n, c, l, ini_pos, v, q, queries);
    for (auto x : ans) cout << (x ? "Y" : "N") << endl;
#else
    int t = 1;
    int LV = 10;
    while (true) {
        int n = rnd(1, LV*LV), L = rnd(1, LV), C = rnd(1, L);
        vector<int> ini_pos(n), v(n);
        map<ii, int> foi;
        for (int i = 0; i < n; ++i) {
            while (true) { 
                int x = rnd(-LV, LV), y = rnd(-LV, LV);
                if (foi[{x, y}] == 1) continue;
                foi[{x, y}] = 1;
                ini_pos[i] = x, v[i] = y;
                break;
            }
        }
        int q = rnd(1, 300);
        vector<int> queries(q);
        for (auto& x : queries) x = rnd(0, 10*LV);
        sort(all(queries));
        auto my = solve(n, C, L, ini_pos, v, q, queries);
        auto ans = brute(n, C, L, ini_pos, v, q, queries);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << " " << C << " " << L << endl;
            for (int i = 0; i < n; ++i) cout << ini_pos[i] << " " << v[i] << endl;
            cout << q << endl;
            for (auto x : queries) cout << x << endl;
            cout << endl;
            cout << "Solve: ";
            for (auto x : my) cout << "NY"[x];
            cout << endl;
            cout << "Brute: ";
            for (auto x : ans) cout << "NY"[x];
            cout << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
