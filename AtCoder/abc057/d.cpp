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
    int n, a, b; cin >> n >> a >> b;
    vector<int> v(n);
    map<int, int> freq;
    for (auto& x : v) cin >> x, freq[x]++;
    sort(rbegin(v), rend(v));
    ii ans = {0, 1};
    int sum = 0;
    vector<vector<int>> ncr(n+1, vector<int>(n+1));
    for (int i = 0; i <= n; ++i) for (int j = 0; j <= i; ++j) {
        if (i == j or j == 0) ncr[i][j] = 1;
        else ncr[i][j] = ncr[i-1][j] + ncr[i-1][j-1];
    }
    vector<int> ps(n+1);
    for (int i = 0; i < a-1; ++i) sum += v[i];
    for (int i = a-1; i < b; ++i) {
        sum += v[i];
        ps[i+1] = sum;
        if (ans.first * (i+1) <= ans.second * sum) ans = {sum, i+1};
    }
    int tot = 0;
    for (int i = a; i <= b; ++i) {
        if (ans.first * i != ans.second * ps[i]) continue;
        int used = 0;
        for (int j = i-1; ~j; --j) {
            if (v[j] != v[i-1]) break;
            used++;
        }
        tot += ncr[freq[v[i-1]]][used];
    }
    cout << fixed << setprecision(10) << (double)ans.first/ans.second << endl;
    cout << tot << endl;

}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
