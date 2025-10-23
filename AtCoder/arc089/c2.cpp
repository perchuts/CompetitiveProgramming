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

int pode[303][303][11][11], big[303][303];

void solve(int A, int B, vector<vector<int>> d) {
    cout << "ASD" << endl;
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
    for (int i = 1; i <= A; ++i) for (int j = 1; j <= B; ++j) {
        if (c[i][j] < 0) {
            cout << "Impossible" << endl;
            exit(0);
        }
    }
    int S = 0, cur = 1, s = 299, t = 300;
    for (int i = 1; i <= A; ++i) for (int j = 1; j <= B; ++j) S += a[i][j];
    for (int i = 1; i <= A; ++i) for (int j = 1; j <= B; ++j) S += b[i][j];
    if (S > 298) {
        cout << "Impossible" << endl;
        exit(0);
    }
    cout << "Possible" << endl;
    vector<iii> edg; 
    for (int i = 1; i <= A; ++i) {
        for (int j = 1; j <= B; ++j) {
            int prv = s;
            for (int k = 0; k < a[i][j]; ++k) edg.pb({prv, cur++, -1}), prv = cur-1;
            for (int k = 0; k < b[i][j]; ++k) edg.pb({prv, cur++, -2}), prv = cur-1;
            edg.pb({prv, t, c[i][j]});
        }
    }
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
