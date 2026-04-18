#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define int ll
#define pb push_back

using namespace std;

using ll = long long;

int32_t main() {_
    int n; cin >> n;
    vector<string> grid(n);
    for (auto& x : grid) cin >> x;
    vector<int> col(n), row(n);
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
        if (grid[i][j] == 'A') {
            col[j] |= 1;
            row[i] |= 1;
        }
        if (grid[i][j] == 'B') {
            col[j] |= 2;
            row[i] |= 2;
        }
    }
    vector<int> fat(n+1, 1);
    vector<vector<int>> ncr(n+1, vector<int>(n+1));
    const int mod = 1e9+7;
    for (int i = 0; i <= n; ++i) for (int j = 0; j <= i; ++j) {
        if (i == j or j == 0) ncr[i][j] = 1;
        else ncr[i][j] = (ncr[i-1][j] + ncr[i-1][j-1]) % mod;
    }
    for (int i = 1; i <= n; ++i) fat[i] = i * fat[i-1] % mod;
    int qtA = 0, qtB = 0;
    int r0 = 0, c0 = 0;
    int ta = 0, tb = 0;
    for (int i = 0; i < n; ++i) {
        if (row[i] == 0) r0++;
        if (col[i] == 0) c0++;
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == 'A' and row[i] == col[j] and row[i] == 1) qtA++;
            if (grid[i][j] == 'B' and row[i] == col[j] and row[i] == 2) qtB++;
            if (grid[i][j] == 'A') ta++;
            if (grid[i][j] == 'B') tb++;
        }
    }
    // at least i L's in A, j L's in B, k L's in A + B
    int ans = 0;
    for (int i = 0; i <= qtA; ++i) {
        for (int j = 0; j <= qtB; ++j) {
            for (int k = 0; k <= min(r0, c0); ++k) {
                int ways = ncr[r0][k] * ncr[c0][k] % mod * fat[k] % mod;
                ways = ways * ncr[qtA][i] % mod * ncr[qtB][j] % mod;
                ways = ways * fat[n-ta-j-k] % mod * fat[n-tb-i-k] % mod;
                if ((i+j+k) % 2 == 0) ans = (ans + ways) % mod;
                else ans = (ans + mod - ways) % mod;
            }
        }
    }
    cout << ans << endl;
}
