#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#define endl '\n'
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int short int
using namespace std;

using ll = long long;

int dir[3000][3000][4];
int upds[3000][3000];
int ptr[3000];
int bit[3001];
ll ans[26];
int lim;

inline void insert (int x, int k) {
    while (x <= lim) bit[x] += k, x += x & (-x);
}

inline int query(int x) {
    int ans = 0;
    while (x) ans += bit[x], x -= x & (-x);
    return ans;
}

void solve(){
    int n, k; cin >> n >> k;
    vector<string> grid(n);
    for (auto& x : grid) cin >> x;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == 0 or grid[i][j] != grid[i-1][j]) dir[i][j][0] = 1;
            else dir[i][j][0] = 1 + dir[i-1][j][0];
            if (j == 0 or grid[i][j] != grid[i][j-1]) dir[i][j][1] = 1;
            else dir[i][j][1] = 1 + dir[i][j-1][1];
        }
    }
    for (int i = n-1; ~i; --i) {
        for (int j = n-1; ~j; --j) {
            if (j == n-1 or grid[i][j] != grid[i][j+1]) dir[i][j][2] = 1;
            else dir[i][j][2] = 1 + dir[i][j+1][2];
            if (i == n-1 or grid[i][j] != grid[i+1][j]) dir[i][j][3] = 1;
            else dir[i][j][3] = 1 + dir[i+1][j][3];
        }
    }
    int zero = 0;
    for (int diag = -n+1; diag < n; ++diag) {
        int pos = 0, alive = 0;
        lim = n-abs(diag);
        for (int i = max(zero, diag), j = i - diag; max(i, j) < n; ++i, ++pos, ++j) {
            alive -= ptr[pos] - 1;
            for (int k = 0; k < ptr[pos]; ++k) insert(upds[pos][k], -1);
            insert(pos+1, 1);
            int mx_esq = min(dir[i][j][0], dir[i][j][1]);
            int mx_dir = min(dir[i][j][2], dir[i][j][3]); 
            if (pos+mx_dir <= lim) upds[pos+mx_dir][ptr[pos+mx_dir]++] = (pos+1);
            ans[grid[i][j]-'A'] += alive - query(pos-mx_esq+1);
        }
        for (int i = 0; i <= lim; ++i) ptr[i] = bit[i] = 0;
    }
    for (int i = 0; i < k; ++i) cout << ans[i] << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
