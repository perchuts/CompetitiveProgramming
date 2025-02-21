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

int ans[100050], crivo[100050];

void solve(){
    int l, r; cin >> l >> r;
    cout << ans[r] - (l == 1 ? 0 : ans[l-2]) << endl;
}

int32_t main(){_
    int t = 1; cin >> t;
    const int sexo = 100000;
    for (int i = 2; i <= sexo; ++i) {
        if (crivo[i]) continue;
        for (int j = 2*i; j <= sexo; j += i) crivo[j] = 1;
    }
    for (int i = 3; i <= sexo; i += 2) {
        if (crivo[i] == 0 and crivo[(i+1)/2] == 0) ans[i] = 1;
        ans[i] += (i == 1 ? 0 : ans[i-2]);
    }
    while(t--) solve();
}
