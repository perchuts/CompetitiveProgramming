#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ii = pair<int,int>;
using iii = tuple<int,int,int>;

const int inf = 2e9+1;
const int mod = 1e9+7;
const int maxn = 2e6+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}
void solve(){
    int n, q; cin >> n >> q;
    vector<int> ptr(n+1);
    vector<pair<int, char>> trie;
    trie.pb({0, 0});
    while (q--) {
        int op; cin >> op;
        if (op == 1) { 
            int x; cin >> x; --x;
            ptr[x] = ptr[n];
        } else if (op == 2) {
            int x; cin >> x;
            string s; cin >> s;
            --x;
            for (auto c : s) {
                trie.pb({ptr[x], c});
                ptr[x] = sz(trie)-1;
            }
        } else {
            int x; cin >> x; --x;
            ptr[n] = ptr[x];
        }
    }
    string ans;
    int cur = ptr[n];
    while (cur) {
        ans += trie[cur].second;
        cur = trie[cur].first;
    }
    reverse(all(ans));
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
