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

void solve(int A, int B, vector<vector<int>> d) {
    vector<vector<int>> a = d, b = d;
    auto faz_o_l = [] () {
        cout << "Impossible" << endl;
        exit(0);
    };
    for (int i = 1; i <= A; ++i) {
        for (int j = 1; j <= B; ++j) {
            if (i != 1 and d[i][j] - d[i-1][j] > 1) {
                faz_o_l();
            }
            if (j != 1 and d[i][j] - d[i][j-1] > 1) {
                faz_o_l();
            }
            if (d[i][j] != d[min(i, j)][min(i, j)]) {
                faz_o_l();
            }
        }
    }

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
