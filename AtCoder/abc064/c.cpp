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
    vector<int> tem(9), v(n);
    for (auto& x : v) {
        cin >> x;
        if (x <= 399) tem[0] = 1;
        else if (x <= 799) tem[1] = 1;
        else if (x <= 1199) tem[2] = 1;
        else if (x <= 1599) tem[3] = 1;
        else if (x <= 1999) tem[4] = 1;
        else if (x <= 2399) tem[5] = 1;
        else if (x <= 2799) tem[6] = 1;
        else if (x <= 3199) tem[7] = 1;
        else tem[8]++;
    }
    int mn = 0, mx = 0;
    for (int i = 0; i < 8; ++i) mn += tem[i], mx += tem[i];
    mx += tem[8];
    mn = max(mn, 1LL);
    cout << mn << ' ' << mx << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
