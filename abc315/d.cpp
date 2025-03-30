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
    int n, m; cin >> n >> m;
    vector<string> c(n);
    for (auto& x : c) cin >> x;
    vector<vector<int>> mark(n, vector<int>(m));
    vector<vector<int>> cntr(n, vector<int>(26)), cntc(m, vector<int>(26));
    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) cntr[i][c[i][j]-'a']++, cntc[j][c[i][j]-'a']++;
    while (true) {
        int achou = -1;
        for (int i = 0; i < n; ++i) {
            int mx1 = 0, s = 0;
            for (int j = 0; j < 26; ++j) s += cntr[i][j], ckmax(mx1, cntr[i][j]);
            if (mx1>1 and s == mx1) {
                achou = i;
                break;
            }
        }
        if (achou != -1) {
            cout << "achou linha " << achou << endl;
            for (int j = 0; j < m; ++j) {
                if (!mark[achou][j]) mark[achou][j] = 1, cntr[achou][c[achou][j]-'a']--, cntc[j][c[achou][j]-'a']--;
            }
            continue;
        }
        for (int i = 0; i < m; ++i) {
            int mx1 = 0, s = 0;
            for (int j = 0; j < 26; ++j) s += cntc[i][j], ckmax(mx1, cntc[i][j]);
            if (mx1 and s == mx1) {
                achou = i;
                break;
            }
        }
        if (achou != -1) {
            cout << "achou coluna " << achou << endl;
            for (int i = 0; i < n; ++i) {
                if (!mark[i][achou]) mark[i][achou] = 1, cntr[i][c[i][achou]-'a']--, cntc[achou][c[i][achou]-'a']--;
            }
        } else break;
    }
    int ans = 0;
    for (auto x : mark) for (auto y : x) ans += 1 - y;
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
