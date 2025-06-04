#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
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

void solve() {
    auto dup = [] (vector<vector<int>> mini) {
        int n = mini.size();
        vector<vector<int>> sol(2*n, vector<int>(2*n));
        for (int i = 0; i < 2*n; ++i) {
            for (int j = 0; j < 2*n; ++j) {
                sol[i][j] = mini[i%n][j%n] + ((i >= n) ^ (j >= n)) * n;
            }
        }
        return sol;
    };
    vector<vector<int>> sexo = {{2, 3, 1, 1, 1},
        {1, 5, 5, 3, 3},
        {2, 3, 5, 2, 4},
        {5, 4, 5, 4, 1},
        {2, 3, 4, 4, 2}};
    auto sexo2 = dup(sexo);
    auto check = [] (vector<vector<int>> sol) {
        set<int> s;
        int n = sz(sol);
        for (int i = 0; i < n; ++i) {
            int v1 = 0, v2 = 0;
            for (int j = 0; j < n; ++j) {
                cout << sol[i][j] << " \n"[j==n-1];
                v1 += sol[i][j], v2 += sol[j][i];
            }
            s.insert(v1);
            s.insert(v2);
        }
        cout << sz(s) << endl;
        return (sz(s) == 2*n);
    };
    cout << (check(sexo2) ? "YES" : "NO") << endl;
    
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
