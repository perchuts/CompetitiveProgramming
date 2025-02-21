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
    string s; cin >> s;
    int x, y; cin >> x >> y;
    int n = sz(s);
    int okei = -1, cur = 0;
    vector<vector<int>> vals(2);
    for (int i = 0; i < n; ++i) {
        if (s[i] == 'F') cur++;
        else {
            if (okei == -1) x -= cur, okei = 1;
            else {
                if (cur) vals[okei].pb(cur);
                okei ^= 1; 
            }
            cur = 0;
        }
    }
    if (okei == -1) {
        cout << (cur == x and y == 0 ? "Yes" : "No") << endl;
        exit(0);
    }
    if (cur) vals[okei].pb(cur);
    for (int c = 0; c < 2; ++c) {
        int s = 0;
        for (auto z : vals[c]) s += z;
        if ((s&1) != (x&1)) {
            cout << "No" << endl;
            exit(0);
        }
        bitset<16005> dp;
        int shift = n;
        dp[shift] = 1;
        for (auto z : vals[c]) dp = ((dp << z) | (dp >> z));
        if (dp[x+shift] == 0) {
            cout << "No" << endl;
            exit(0);
        }
        swap(x, y);
    }
    cout << "Yes" << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
