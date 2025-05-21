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
    if (n == 1) {
        cout << 1 << endl;
        exit(0);
    } 
    if (n <= 3) {
        cout << "NO SOLUTION" << endl;
        exit(0);
    } 
    // 1 4 2 5 3
    // solucao: 1 3 5 2 4 (repete)
    vector<int> pre;
    int st = 1;
    for (int i = 1; 5 * i <= n - 7; ++i) {
        pre.pb(st);
        pre.pb(st+2);
        pre.pb(st+4);
        pre.pb(st+1);
        pre.pb(st+3);
        st += 5;
    }
    vector<int> p(n-st+1); iota(all(p), st);
    vector<int> ans;
    do {
        bool ok = true;
        for (int i = 1; i < n-st+1; ++i) ok &= (abs(p[i] - p[i-1]) != 1);
        if (ok) {
            if (ans.empty()) ans = p;
            else ckmin(ans, p);
        }
    } while (next_permutation(all(p)));
    for (auto x : ans) pre.pb(x);
    swap(ans, pre);
    for (auto x : ans) cout << x << ' ';
    cout << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
