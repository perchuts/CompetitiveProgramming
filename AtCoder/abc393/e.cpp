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
const int maxn = 1e6+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}
char meb[maxn];

void solve(){
    int n, k; cin >> n >> k;
    vector<int> tem(maxn); 
    vector<int> v(n);
    for (int i = 1; i <= n; ++i) {
        cin >> v[i-1];
        tem[v[i-1]]++;
    }
    //for (auto x : v) cout << x << ' ';
    //cout << endl;
    vector<int> ans(maxn);
    for (int i = 1; i < maxn; ++i) {
        for (int j = 2*i; j < maxn; j += i) tem[i] += tem[j];
        if (tem[i] >= k) {
            for (int j = i; j < maxn; j += i) ans[j] = i; 
        }
    }
    //for (int i = 1; i <= 10; ++i) cout << tem[i] << ' ';
    //cout << endl;
    for (auto x : v) {
        cout << ans[x] << endl;
    }
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
