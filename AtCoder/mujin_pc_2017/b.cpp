#include <bits/stdc++.h>
#define endl '\n'
#define pb push_back
#define int ll
#define _ ios_base::sync_with_stdio(0);cin.tie(0);

using namespace std;

using ll = long long;

int32_t main() {_
    int n; cin >> n;
    vector<string> s(n);
    for (auto& x : s) cin >> x;
    vector<vector<int>> grid(n, vector<int>(n));
    int ct = 0;
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) grid[i][j] = (s[i][j] == '#'), ct += grid[i][j];
    if (ct == 0) {
        cout << -1 << endl;
        return 0;
    }
    int bad = 0;
    for (int i = 0; i < n; ++i) {
        bool ok = 1;
        for (int j = 0; j < n; ++j) ok &= grid[j][i];
        if (!ok) bad++;
    }
    int ans = 2 * n;
    for (int i = 0; i < n; ++i) {
        bool ok = 0;
        for (int j = 0; j < n; ++j) ok |= (grid[j][i]);
        int ct = 0;
        for (int j = 0; j < n; ++j) ct += (grid[i][j] == 0);
        if (ok) ans = min(ans, bad + ct);
        else ans = min(ans, bad + ct + 1);
    }
    cout << ans << endl;
}

