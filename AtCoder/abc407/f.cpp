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
const int maxn = 2e5+10;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

ii st[maxn];
int ans[maxn], pr2[maxn], seta[2][maxn], v[maxn];

void solve(){
    int n; cin >> n;
    for (int i = 0; i < n; ++i) cin >> v[i];
    int ptr = 0;
    st[0] = {inf, -1};
    for (int i = 0; i < n; ++i) {
        while (st[ptr].first <= v[i]) ptr--;
        seta[0][i] = st[ptr].second;
        st[++ptr] = {v[i], i};
    }
    ptr = 0;
    st[0] = {inf, n};
    for (int i = n-1; ~i; --i) {
        while (st[ptr].first < v[i]) ptr--;
        seta[1][i] = st[ptr].second;
        st[++ptr] = {v[i], i};
        int esq = i - seta[0][i], dir = seta[1][i] - i - 1;
        pr2[1] += v[i];
        pr2[dir+2] -= v[i];
        pr2[esq+1] -= v[i];
        pr2[esq+dir+2] += v[i];
    }
    int s = 0;
    for (int i = 1; i <= n; ++i) {
        s += pr2[i], ans[i] = ans[i-1] + s;
        cout << ans[i] << endl;
    }
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
