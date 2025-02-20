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
    vector<int> a(n), b(n), tot(n);
    for (auto& x : a) cin >> x;
    for (auto& x : b) cin >> x;
    auto pi = [&] (string s) {
        int n = sz(s);
        vector<int> p(n);
        for (int i = 1, j = 0; i < n; ++i) {
            while (j and s[j] != s[i]) j = p[j-1];
            if (s[i] == s[j]) j++;
            p[i] = j;
        }
        return p;
    };
    for (int turn = 0; turn < 2; ++turn) {
        for (int bit = 0; bit < 30; ++bit) {
            string s; cin >> s;
            for (auto x : b) s += char('0' + (x>>bit&1));
            s += '#';
            for (auto x : a) s += char('0' + (x>>bit&1));
            for (auto x : a) s += char('0' + (x>>bit&1));
            auto p = pi(s);
            for (int i = 2*n; i < 3*n; ++i) tot[i-2*n] += (p[i] == n);
        }
        for (auto& x : a) x ^= ((1 << 30) - 1);
    }
    for (int i = 0; i < n; ++i) {
        if (tot[i] == 30) {
            cout << i << ' ' << (b[0] ^ a[i]) << endl;
        }
    }
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
