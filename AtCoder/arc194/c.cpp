#include <bits/stdc++.h>
#define endl '\n'
#define pb push_back
#define int ll
#define _ ios_base::sync_with_stdio(0);cin.tie(0);

using namespace std;

using ll = long long;

int32_t main() {_

    int n; cin >> n;
    vector<int> a(n), b(n), c(n);

    for (auto& x : a) cin >> x;
    for (auto& x : b) cin >> x;
    for (auto& x : c) cin >> x;

    array<array<vector<int>, 2>, 2> v;
    array<array<int, 2>, 2> S{};

    for (int i = 0; i < n; ++i) v[a[i]][b[i]].pb(i), S[a[i]][b[i]] += c[i];

    for (int i = 0; i < 2; ++i) for (int j = 0; j < 2; ++j) sort(begin(v[i][j]), end(v[i][j]), [&] (int x, int y) {
        return c[x] < c[y];
    });

    reverse(begin(v[1][1]), end(v[1][1])), reverse(begin(v[1][0]), end(v[1][0]));
    array<array<vector<int>, 2>, 2> ps;

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            ps[i][j].pb(0);
            for (auto k : v[i][j]) ps[i][j].pb(ps[i][j].back() + c[k]);
        }
    }

    int cur = 0, ans;

    for (auto i : v[1][0]) S[1][0] -= c[i], cur += S[1][1] + S[1][0];
    S[0][1] = 0;
    for (auto i : v[0][1]) S[0][1] += c[i], cur += S[1][1] + S[0][1];
    for (auto i : v[1][0]) S[1][0] += c[i];

    ans = cur;

    int p01 = v[0][1].size(), p10 = 0, t01 = v[0][1].size(), t10 = v[1][0].size();


    for (auto i : v[1][1]) {
        int eu = c[i];
        S[1][1] -= eu;
        cur += 2 * S[1][1] + eu;
        while (p01 and c[v[0][1][p01-1]] >= eu) --p01;
        while (p10 < v[1][0].size() and c[v[1][0][p10]] >= eu) ++p10;
        cur += ps[1][0].back() - ps[1][0][p10];
        cur += ps[0][1][p01];
        cur -= ((t10 - p10) + p01) * eu;
        ans = min(ans, cur);
    }

    cout << ans << endl;
}

