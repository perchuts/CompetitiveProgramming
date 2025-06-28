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

void solve(){
    int n; cin >> n;
    auto sol = [&] (auto&& self, int N) -> vector<vector<int>> {
        if (N == 1) {
            return {{0}};
        }
        if (N == 2) {
            return {{3, 0}, {2, 1}};
        }
        auto M = self(self, N-2);
        vector<vector<int>> ans(N, vector<int>(N));
        for (int i = 1; i < N-1; ++i) for (int j = 1; j < N-1; ++j) ans[i][j] = M[i-1][j-1];
        int ptr = (N-2) * (N-2);
        for (int i = 1; i < N; ++i) ans[0][i] = ptr++;
        for (int j = 1; j < N; ++j) ans[j][N-1] = ptr++;
        for (int i = N-2; ~i; --i) ans[N-1][i] = ptr++;
        for (int i = N-2; ~i; --i) ans[i][0] = ptr++;
        return ans;
    };
    auto get = [] (vector<vector<int>> ans, int n) {
        int tot = 0;
        for (int i1 = 0; i1 < n; ++i1) {
            for (int j1 = 0; j1 < n; ++j1) {
                for (int i2 = i1; i2 < n; ++i2) {
                    for (int j2 = j1; j2 < n; ++j2) {
                        vector<int> mark(n*n); 
                        for (int a = i1; a <= i2; ++a) for (int b = j1; b <= j2; ++b) mark[ans[a][b]] = 1;
                        int eu = 0;
                        while (eu < n*n and mark[eu]) eu++;
                        tot += eu;
                    }
                }
            }
        }
        return tot;
    };
    auto ans = sol(sol, n);
    for (auto x : ans) {
        for (auto y : x) cout << y << ' ';
        cout << endl;
    }
}

int32_t main(){_
    int t = 1; cin >> t;
    while(t--) solve();
}
