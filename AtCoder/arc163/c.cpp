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

void solve(int n){
    if (n == 2) {
        cout << "No" << endl;
        return;
    }
    if (n == 1) { 
        cout << "Yes\n1" << endl;
        return;
    }
    set<int> ans;
    for (int i = 1; i < n; ++i) ans.insert(i*(i+1));
    int cur = n;
    while (ans.find(cur) != end(ans)) {
        ans.erase(cur);
        cur /= 2;
    }
    ans.insert(cur);
    vector<int> resp;
    for (auto x : ans) resp.pb(x);
    while (sz(resp) != n) {
        for (auto& x : resp) x *= 2;
        resp.pb(2);
    }
    cout << "Yes" << endl;
    for (auto x : resp) cout << x << ' ';
    cout << endl;
}

int32_t main(){_
    int t = 1; cin >> t;
    while (t--) {
        int n; cin >> n;
        solve(n);
    }
}
