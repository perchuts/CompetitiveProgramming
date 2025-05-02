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
    int q; cin >> q;
    map<ii, int> trie;
    vector<int> existo(4*maxn, inf);
    int cur = 0;
    vector<pair<int, string>> v;
    int id = 0;
    int Q = q;
    while (q--) {
        int t; cin >> t;
        string s; cin >> s;
        if (t == 1) {
            int tmp = 0;
            for (auto c : s) {
                if (!trie.count({tmp, c})) trie[{tmp, c}] = ++cur;
                tmp = trie[{tmp, c}];
            }
            ckmin(existo[tmp], id);
        } else v.pb({id, s});
        id++;
    }
    vector<int> add(Q+1);
    for (auto [idx, s] : v) {
        int tmp = 0, mn = Q;
        for (auto c : s) {
            ckmin(mn, existo[tmp]);
            if (!trie.count({tmp, c})) break;
            tmp = trie[{tmp, c}];
        }
        ckmin(mn, existo[tmp]);
        add[idx]++, add[max(idx, mn)]--;
    }
    int ans = 0;
    for (int i = 0; i < Q; ++i) {
        ans += add[i];
        cout << ans << endl;
    }
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
