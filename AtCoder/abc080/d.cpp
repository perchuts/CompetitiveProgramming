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
    int n, c; cin >> n >> c;
    vector<int> qnt(100050);
    vector<vector<int>> sexo(100005);
    vector<vector<ii>> intr(c);
    for (int i = 0; i < n; ++i) {
        int l, r, x; cin >> l >> r >> x;
        intr[x-1].pb({l, r});
    }
    for (int i = 0; i < c; ++i) {
        sort(all(intr[i]));
        vector<ii> nintr;
        int lst_fim = -inf;
        for (int j = 0; j < sz(intr[i]); ++j) {
            if (lst_fim == intr[i][j].first) nintr.back().second = intr[i][j].second;
            else nintr.pb(intr[i][j]);
            lst_fim = intr[i][j].second;
        }
        for (auto [l, r] : nintr) sexo[l].pb(r);
    }
    int ans = 0, available = 0;
    for (int i = 1; i < 100000; ++i) {
        available += qnt[i];
        for (auto r : sexo[i]) {
            qnt[r+1]++;
            available--;
            if (available == -1) ans++, available++;
        }
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
