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

map<int, int> sq;
void solve(int n){
    int s = (n+1)*n/2;
    if (sq[s]) {
        cout << -1 << endl;
        return;
    }
    s = 0;
    int cur = 1;
    vector<int> foi(n+1), ans;
    for (int i = 0; i < n; ++i) {
        while (foi[cur]) cur++;
        int x = s + cur;
        if (sq[x]) ans.pb(cur+1), foi[cur+1] = 1, s = x+1;
        else ans.pb(cur), foi[cur] = 1, s = x;
    }
    for (auto x : ans) cout << x << ' ';
    cout << endl;
}

int32_t main(){_
    int t = 1; cin >> t;
    for (int i = 1; i <= 1000000; ++i) sq[i*i] = 1;
    while(t--) {
        int x; cin >> x;
        solve(x);
    }
}
