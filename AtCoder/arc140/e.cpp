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


void solve(){
    int p = 23, n = p * p;
    vector<vector<int>> grid(n, vector<int>(n));
    vector<int> pot(n*n, 1), lg(p);
    for (int i = 1; i < n*n; ++i) pot[i] = 5 * pot[i-1] % p;
    for (int i = 0; i < p-1; ++i) lg[pot[i]] = i;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            grid[i][j] = ((i / p) + (j / p) + i * j) % p;
        }
    }
    vector mark(p, vector(n, vector(n, -1)));
    for (int i = 0; i < n; ++i) {
        vector<vector<int>> ids(p);
        for (int j = 0; j < n; ++j) {
            ids[grid[i][j]].pb(j);
        }
        for (int c = 0; c < p; ++c) {
            for (int x = 0; x < sz(ids[c]); ++x) {
                for (int y = x + 1; y < sz(ids[c]); ++y) {
                    if (mark[c][ids[c][x]][ids[c][y]] != -1) {
                        cout << "Wrong answer" << endl;
                        cout << "rows: " << mark[c][ids[c][x]][ids[c][y]] << ' ' << i << endl;
                        cout << "cols: " << ids[c][x] << ' ' << ids[c][y] << endl;
                        exit(0);
                    }
                    mark[c][ids[c][x]][ids[c][y]] = i;
                }
            }
        }
    }
    cout << "Accepted" << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
