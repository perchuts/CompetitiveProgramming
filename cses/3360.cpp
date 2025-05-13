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
bool mark[3000][3000];
void solve(){
    int n, k; cin >> n >> k;
    vector<string> grid(n);
    vector v(k, vector(n, vector<int>()));
    for (auto& x : grid) cin >> x;
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) v[grid[i][j]-'A'][i].pb(j);
    for (int l = 0; l < k; ++l) {
        bool ok = false;
        int reset = -1;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < sz(v[l][i]); ++j) {
                for (int w = j+1; w < sz(v[l][i]); ++w) {
                    if (mark[v[l][i][j]][v[l][i][w]]) {
                        ok = true;
                        break;
                    }
                    mark[v[l][i][j]][v[l][i][w]] = true;
                }
                if (ok) break;
            }
            if (ok) { reset = i; break; }
        }
        if (!ok) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < sz(v[l][i]); ++j) {
                    for (int w = j+1; w < sz(v[l][i]); ++w) {
                        mark[v[l][i][j]][v[l][i][w]] = false;
                    }
                }
            }
         cout << "NO" << endl;
        }
        else {
            for (int i = 0; i <= reset; ++i) {
                for (int j = 0; j < sz(v[l][i]); ++j) {
                    for (int w = j+1; w < sz(v[l][i]); ++w) {
                        mark[v[l][i][j]][v[l][i][w]] = false;
                    }
                }
            }
            cout << "YES" << endl;
        }
    }
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
