#include <bits/stdc++.h>

using namespace std;

#define _ ios_base::sync_with_stdio(0); cin.tie(0);
#define endl '\n'
#define pb push_back
//#define gato

typedef long long ll;

mt19937 rng(time(0));

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}
using ii = pair<int, int>;

const int maxn = 1e5 + 1e4 + 69;
int mv[maxn];

vector<int> solve(int n, int q, vector<int> v, vector<array<int, 3>> qq) {
    int m = sqrt(n);
    vector<deque<ii>> sexo(n/m+1), edg(n/m+1);
    vector<int> resp, add(n/m+1);
    auto destroy = [&] (int k) {
        int big = 0;
        for (auto [x, y] : sexo[k]) mv[y] = x + add[k], big = max(big, mv[y]);
        for (int i = (int) edg[k].size() - 1; i >= 0; --i) mv[edg[k][i].first] = mv[edg[k][i].second];
        sexo[k].clear(), edg[k].clear(), add[k] = 0;
        for (int i = m * k; i < min(m * k + m, n); ++i) v[i] = mv[v[i]];
        return big;
    };
    auto seek = [&] (int k) {
        for (int i = m * k; i < min(m * k + m, n); ++i) sexo[k].pb({v[i], v[i]});
        sort(begin(sexo[k]), end(sexo[k])), sexo[k].erase(unique(begin(sexo[k]), end(sexo[k])), end(sexo[k]));
    };
    for (int i = 0; i <= n/m; ++i) seek(i);
    for (auto op : qq) {
        int l = op[1], r = op[2];
        int lx = l / m, rx = r / m, mx = destroy(lx);
        if (rx != lx) mx = max(mx, destroy(rx));
        if (op[0] == 0) { // add
            for (int i = lx+1; i < rx; ++i) add[i]++;
            if (lx == rx) for (int i = l; i <= r; ++i) v[i]++;
            else {
                for (int i = l; i < lx*m + m; ++i) v[i]++;
                for (int i = rx*m; i <= r; ++i) v[i]++;
            }
        } else if (op[0] == 1) { // query
            int ans = 0;
            for (int i = lx+1; i < rx; ++i) ans = max(ans, add[i] + sexo[i].back().first);
            if (lx == rx) for (int i = l; i <= r; ++i) ans = max(ans, v[i]);
            else {
                for (int i = l; i < lx*m + m; ++i) ans = max(ans, v[i]);
                for (int i = rx*m; i <= r; ++i) ans = max(ans, v[i]);
            }
            resp.pb(ans);
        } else { // reset
            for (int i = 0; i <= n/m; ++i) {
                if (sexo[i].empty()) continue;
                mx = max(mx, add[i] + sexo[i].back().first);
            }
            for (int i = lx+1; i < rx; ++i) {
                if (add[i] + sexo[i].back().first != mx) continue;
                auto [a, b] = sexo[i].back(); sexo[i].pop_back();
                if (!sexo[i].empty() and sexo[i][0].first == -add[i]) edg[i].pb({b, sexo[i][0].second});
                else sexo[i].push_front({-add[i], b});
            }
            if (lx == rx) for (int i = l; i <= r; ++i) v[i] = (v[i] == mx ? 0 : v[i]);
            else {
                for (int i = l; i < lx*m + m; ++i) v[i] = (v[i] == mx ? 0 : v[i]);
                for (int i = rx*m; i <= r; ++i) v[i] = (v[i] == mx ? 0 : v[i]);
            }
        }
        seek(lx);
        if (lx != rx) seek(rx);
    }
    return resp;
 }

vector<int> brute(int n, int q, vector<int> v, vector<array<int, 3>> qq) {
    vector<int> ans;
    for (auto vv : qq) {
        if (vv[0] == 0) {
            for (int i = vv[1]; i <= vv[2]; ++i) v[i]++;
        } else if (vv[0] == 1) {
            int resp = 0;
            for (int i = vv[1]; i <= vv[2]; ++i) resp = max(resp, v[i]);
            ans.pb(resp);
        } else {
            int mx = *max_element(begin(v), end(v));
            for (int i = vv[1]; i <= vv[2]; ++i) if (v[i] == mx) v[i] = 0;
        }
    }
    return ans;
}

int32_t main() {
#ifndef gato
    int n, q; cin >> n >> q;
    vector<int> v(n);
    for (auto& x : v) cin >> x;
    vector<array<int, 3>> qu(q);
    for (auto& vv : qu) {
        char c; int l, r; cin >> c >> l >> r;
        if (c == 'A') vv[0] = 0;
        else if (c == 'Q') vv[0] = 1;
        else vv[0] = 2;
        --l, --r;
        vv[1] = l, vv[2] = r;
    }
    auto ans = solve(n, q, v, qu);
    for (auto x : ans) cout << x << endl;
#else
    int t = 1;
    while (true) {
        int n = rnd(1, 30), q = rnd(1, 500);
        vector<int> v(n);
        for (auto& x : v) x = rnd(1, 5);
        vector<array<int, 3>> qu(q);
        for (auto& vv : qu) {
            vv[0] = rnd(0, 6);
            if (vv[0] < 3) vv[0] = 0;
            if (vv[0] > 3) vv[0] = 2;
            if (vv[0] == 3) vv[0] = 1;
            vv[1] = rnd(0, n-1), vv[2] = rnd(0, n-1);
            if (vv[1] > vv[2]) swap(vv[1], vv[2]);
        }
        auto my = solve(n, q, v, qu);
        auto ans = brute(n, q, v, qu);
        vector<char> al = {'A', 'Q', 'R'};
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << ' ' << q << endl;
            for (auto x : v) cout << x << ' ';
            cout << endl;
            for (auto v : qu) cout << al[v[0]] << ' ' << v[1]+1 << ' ' << v[2]+1 << endl;
            cout << "Your output: ";
            for (auto x : my) cout << x << ' ';
            cout << endl;
            cout << "Answer: ";
            for (auto x : ans) cout << x << ' ';
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}

