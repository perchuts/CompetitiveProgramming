#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll

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

bool checker(vector<vector<int>> d, vector<iii> edg, int s, int t, int n, int A, int B) {
    vector<vector<ii>> g(n+1);
    for (auto [u, v, w] : edg) g[u].pb({v, w});
    for (int i = 1; i <= A; ++i) {
        for (int j = 1; j <= B; ++j) {
            priority_queue<ii, vector<ii>, greater<>> pq;
            vector<int> dist(n+1, inf);
            pq.push({0, s});
            dist[s] = 0;
            while (!pq.empty()) {
                auto [d, u] = pq.top();
                pq.pop();
                for (auto [v, w] : g[u]) {
                    if (w == -1) w = i;
                    if (w == -2) w = j;
                    if (ckmin(dist[v], d + w)) pq.push({dist[v], v});
                }
            }
            if (dist[t] != d[i][j]) {
                cout << "wrong for i = " << i << ", j = " << j << endl;
                cout << dist[t] << ' ' << d[i][j] << endl;
                return false;
            }
        }
    }
    return true;
}

int pode[303][303][11][11], big[303][303];

void solve(int A, int B, vector<vector<int>> d) {
    vector<vector<int>> a = d, b = d;
    for (int i = 0; i <= 300; ++i) for (int j = 0; j <= 300; ++j) big[i][j] = 0;
    vector<vector<int>> c(A+1, vector<int>(B+1, -1));
    for (int i = 0; i <= 300; ++i) {
        for (int j = 0; i + j <= 300; ++j) {
            for (int ix = 1; ix <= A; ++ix) {
                for (int iy = 1; iy <= B; ++iy) {
                    pode[i][j][ix][iy] = d[ix][iy] - ix * i - iy * j;
                    ckmax(big[i][j], pode[i][j][ix][iy]);
                }
            }
        }
    }
    vector<vector<int>> foi(305, vector<int>(305));
    // dai se quero colocar (i, j) em ix, iy, preciso que max(pode[i][j][-][-]) >= d[ix][iy] - ix * i - iy * j
    for (int ix = 1; ix <= A; ++ix) {
        for (int iy = 1; iy <= B; ++iy) { 
            for (int i = 0; i <= 300; ++i) {
                for (int j = 0; i + j <= 300; ++j) {
                    if (big[i][j] == pode[i][j][ix][iy] and (c[ix][iy] == -1 or a[ix][iy] + b[ix][iy] > i + j)) {
                        a[ix][iy] = i;
                        b[ix][iy] = j;
                        c[ix][iy] = pode[i][j][ix][iy];
                    }
                }
            }
        }
    }
    //cout << "a:" << endl;
    //for (int i = 1; i <= A; ++i) {
    //    for (int j = 1; j <= B; ++j) {
    //        cout << a[i][j] << ' ';
    //    }
    //    cout << endl;
    //}
    //cout << "b:" << endl;
    //for (int i = 1; i <= A; ++i) {
    //    for (int j = 1; j <= B; ++j) {
    //        cout << b[i][j] << ' ';
    //    }
    //    cout << endl;
    //}
    //cout << "c:" << endl;
    //for (int i = 1; i <= A; ++i) {
    //    for (int j = 1; j <= B; ++j) {
    //        cout << c[i][j] << ' ';
    //    }
    //    cout << endl;
    //}
    for (int i = 1; i <= A; ++i) for (int j = 1; j <= B; ++j) {
        if (c[i][j] < 0) {
            cout << "Impossible" << endl;
            exit(0);
        }
    }
    int cur = 1, s = 299, t = 300;
    vector<int> ida(101), idb(101);
    ida[0] = idb[0] = s;
    vector<iii> edg;
    int lst = s;
    for (int i = 1; i <= 100; ++i) ida[i] = cur, edg.pb({lst, cur++, -1}), lst = cur-1;
    idb[0] = cur;
    for (int i = 1; i <= 100; ++i) idb[i] = cur, edg.pb({lst, cur++, -2}), lst = cur-1;
    edg.pb({lst, t, 0});
    foi[100][0] = 1;
    for (int i = 1; i <= A; ++i) {
        for (int j = 1; j <= B; ++j) {
            if (foi[a[i][j]][b[i][j]] == 0) {
                edg.pb({ida[a[i][j]], idb[100-b[i][j]], c[i][j]});
                foi[a[i][j]][b[i][j]] = 1;
            }
        }
    }
    cout << "Possible" << endl;
    cout << 300 << ' ' << sz(edg) << endl;
    for (auto [x, y, z] : edg) {
        cout << x << ' ' << y << ' ';
        if (z == -1) cout << "X" << endl;
        else if (z == -2) cout << "Y" << endl;
        else cout << z << endl;
    }
    cout << s << ' ' << t << endl;
}



int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
    int A, B; cin >> A >> B;
    vector<vector<int>> d(A+1, vector<int>(B+1));
    for (int i = 1; i <= A; ++i) {
        for (int j = 1; j <= B; ++j) {
            cin >> d[i][j];
        }
    }
    solve(A, B, d);
#else
    int t = 1;
    while (true) {
        int A = rnd(2, 10), B = rnd(2, 10);
        vector<vector<int>> d(A+1, vector<int>(B+1));
        for (int i = 1; i <= A; ++i) {
            for (int j = 1; j <= B; ++j) {
                int st = 1;
                if (i != 1) ckmax(st, d[i-1][j]);
                if (j != 1) ckmax(st, d[i][j-1]);
                d[i][j] = rnd(st, 100);
            }
        }
            cout << A << " " << B << endl;
            for (int i = 1; i <= A; ++i) {
                for (int j = 1; j <= B; ++j) {
                    cout << d[i][j] << " ";
                }
                cout << endl;
            }
        if (solve(A, B, d)) {
            t++;
        cout << "#######################################" << endl;
        }
        //t += solve(A, B, d);
        //cout << "Accepted on test " << t++ << endl;
    }
#endif
}

