#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

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

ii dp[51][51][51][51][4];
bool vis[51][51][51][51][4];
bool adj[51][51][4];
int translate[300];

void solve() {
    int c, r, e; cin >> c >> r >> e;
    adj[e][1][2] = 1;
    translate['N'] = 0, translate['E'] = 1, translate['S'] = 2, translate['W'] = 3;
    // URDL
    array<int, 3> p1, p2;
    cin >> p1[0] >> p1[1]; char sexo; cin >> sexo; 
    p1[2] = translate[sexo];
    cin >> p2[0] >> p2[1];            cin >> sexo; 
    p2[2] = translate[sexo];
    for (int i = 1; i <= c; ++i) {
        for (int j = 1; j <= r; ++j) {
            if (i != c) adj[i][j][1] = adj[i+1][j][3] = 1;
            if (j != r) adj[i][j][0] = adj[i][j+1][2] = 1;
        }
    }
    {
        int n; cin >> n;
        for (int i = 0; i < n; ++i) {
            int x, y; cin >> x >> y;
            adj[x][y][0] = adj[x][y+1][2] = 0;
        }
    }
    {
        int n; cin >> n;
        for (int i = 0; i < n; ++i) {
            int x, y; cin >> x >> y;
            adj[x][y][1] = adj[x+1][y][3] = 0;
        }
    }
    for (int i = 0; i <= c; ++i) for (int j = 0; j <= r; ++j) for (int x = 0; x <= c; ++x) for (int y = 0; y <= r; ++y) {
        dp[i][j][x][y][0] = dp[i][j][x][y][1] = dp[i][j][x][y][2] = dp[i][j][x][y][3] = {inf, inf};
    }
    // precisa ser uma BFS 0-1?
    // {x1, y1, x2, y2, d}. 
    // x1, y1, x2, y2: 6 bits
    // d = 2 bits
    // 6*4+4 = 26 bits. cabe num int!
    priority_queue<iii, vector<iii>, greater<>> dq;
    dq.push({0, 0, p1[0] + (p1[1] << 6) + (p2[0] << 12) + (p2[1] << 18) + (0 << 24)});
    dp[p1[0]][p1[1]][p2[0]][p2[1]][0] = {0, 0};
    vector<int> d1(4), d2(4), tras(4);
    tras[0] = 3, tras[1] = 0, tras[2] = 1, tras[3] = 2;
    for (int i = 0; i < 4; ++i) d1[i] = (p1[2] + i) % 4, d2[i] = (p2[2] + i) % 4;
    vector<int> dx = {0, 1, 0, -1}, dy = {1, 0, -1, 0};
    while (!dq.empty()) {
        auto [z1, z2, mask] = dq.top(); dq.pop();
        int x1 = mask & 63;
        int y1 = (mask >> 6) & 63;
        int x2 = (mask >> 12) & 63;
        int y2 = (mask >> 18) & 63;
        int d = (mask >> 24) & 3;
        if (vis[x1][y1][x2][y2][d]) continue;
        //cout << x1 << " " << y1 << " " << x2 << " " << y2 << " " << d << " at " << dp[x1][y1][x2][y2][d].first << " " << dp[x1][y1][x2][y2][d].second << endl;
        if (x1 == x2 and y1 == y2) continue;
        vis[x1][y1][x2][y2][d] = 1;
        auto [mv, bt] = dp[x1][y1][x2][y2][d];
        if (ckmin(dp[x1][y1][x2][y2][(d+1)&3],dp[x1][y1][x2][y2][d])) {
            dq.push({z1, z2, x1 + (y1 << 6) + (x2 << 12) + (y2 << 18) + (((d+1)&3)<<24)});
        }
        if (ckmin(dp[x1][y1][x2][y2][tras[d]],dp[x1][y1][x2][y2][d])) {
            dq.push({z1, z2, x1 + (y1 << 6) + (x2 << 12) + (y2 << 18) + (tras[d]<<24)});
        }
        int batidas = 0, nx1, nx2, ny1, ny2;
        if (x1 != e or y1 != 0) {
            batidas += 1-adj[x1][y1][d1[d]];
            nx1 = x1 + dx[d1[d]] * adj[x1][y1][d1[d]];
            ny1 = y1 + dy[d1[d]] * adj[x1][y1][d1[d]];
        } else {
            nx1 = x1;
            ny1 = y1;
        }
        if (x2 != e or y2 != 0) {
            batidas += 1-adj[x2][y2][d2[d]];
            nx2 = x2 + dx[d2[d]] * adj[x2][y2][d2[d]];
            ny2 = y2 + dy[d2[d]] * adj[x2][y2][d2[d]];
        } else {
            nx2 = x2;
            ny2 = y2;
        }
        if (batidas == 2) continue;
        if (batidas == 0) {
            if (ckmin(dp[nx1][ny1][nx2][ny2][d], make_pair(mv+1, bt))) {
                dq.push({z1+1, z2, nx1 + (ny1 << 6) + (nx2 << 12) + (ny2 << 18) + (d<<24)});
            }
        } else {
            if (ckmin(dp[nx1][ny1][nx2][ny2][d], make_pair(mv+1, bt+1))) {
                dq.push({z1+1, z2+1, nx1 + (ny1 << 6) + (nx2 << 12) + (ny2 << 18) + (d<<24)});
            }
        }
    }
    ii ans = {inf, inf};
    for (int i = 0; i < 4; ++i) ckmin(ans, dp[e][0][e][0][i]);
    cout << ans.first << " " << ans.second << endl;
}

int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
    while(t--) solve();
#else
    int t = 1;
    while (true) {
        int my = solve(), ans = brute();
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
