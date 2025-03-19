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
    vector<ii> pts(n);
    vector<vector<int>> caras(maxn, {maxn, -2});
    for (auto& [x, y] : pts) {
        cin >> x >> y;
        caras[x].pb(y);
    }
    set<ii> mark;
    for (int i = 0; i < maxn; ++i) sort(all(caras[i]));
    int tot = maxn+1;
    queue<iii> q;
    q.push({-1, -2, maxn});
    while (!q.empty()) {
        auto [x, l, r] = q.front(); q.pop();
        for (int t = -1; t < 2; ++t) {
            int xx = x + t;
            if (xx != x and xx >= 0 and xx < maxn) {
                int i = upper_bound(all(caras[xx]), l) - begin(caras[xx]) - 1;
                while (i < sz(caras[xx]) - 1 and caras[xx][i] < r-1) {
                    int lx = caras[xx][i], rx = caras[xx][++i];
                    if (lx == rx-1) continue;
                    if (rx > l+1) {
                        if (mark.find(make_pair(xx, i)) == end(mark)) {
                            mark.insert(make_pair(xx, i));
                            q.push({xx, lx, rx});
                            tot += rx-lx-1;
                        }
                    }
                }
            }
        }
    }
    int unmarked = (maxn+1)*(maxn+1) - tot - n;
    cout << unmarked << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

