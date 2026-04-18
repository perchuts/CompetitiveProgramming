#include <bits/stdc++.h>
#define int ll
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
using namespace std;

using ll = long long;

int dp[102][201][201];
int ans[101][201];

int32_t main() {_
    const int mod = 1e9+7;
    auto add = [&] (int& x, int y) {
        x += y;
        if (x >= mod) x -= mod;
    };
    dp[1][0][0] = 1;
    for (int i = 1; i <= 100; ++i) {
        for (int j = 200; ~j; --j) {
            for (int k = 0; k <= j; ++k) {
                for (int use = 1; use + j <= 200; ++use) add(dp[i][j+use][k+use], dp[i][j][k]);
            }
        }
        for (int j = 0; j <= 200; ++j) {
            for (int k = 0; k <= j; ++k) {
                add(dp[i+1][j][k/2], dp[i][j][k]);
            }
        }
    }
    vector<vector<int>> ncr(400, vector<int>(400));
    for (int i = 0; i < 400; ++i) for (int j = 0; j <= i; ++j) {
        if (i == j or j == 0) ncr[i][j] = 1;
        else ncr[i][j] = (ncr[i-1][j] + ncr[i-1][j-1]) % mod;
    }
    for (int i = 2; i <= 100; ++i) {
        for (int j = 1; j <= 200; ++j) {
            for (int k = 2; k <= j; ++k) {
                add(ans[i][j], dp[i-1][j][k]);
            }
            ans[i][j] = (ncr[j+i-2][j] - ans[i][j] + mod) % mod;
        }
    }
    int s, b; 
    while (cin >> s >> b) {
        cout << ans[b][s] << endl;
    }
}
