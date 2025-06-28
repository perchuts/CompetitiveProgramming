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
    int n, k; cin >> n >> k;
    if (n == 1){ 
        cout << 1 << endl;
        exit(0);
    }
    vector<int> v(n);
    for (auto& x : v) cin >> x;
    int lst = n-1; 
    for (int i = n-2; ~i; --i) {
        if (v[i] > v[i+1]) lst = i;
        if (i + k - 1 <= lst) {
            for (auto x : v) cout << x << ' ';
            cout << endl;
            exit(0);
        }
    }
    int id = n-k;
    vector<int> ans = v;
    sort(begin(ans)+id, end(ans));
    while (id > 0) {
        if (v[id-1] < v[id]) id--;
        else break;
    }
    auto v2 = v;
    sort(begin(v2)+id, begin(v2)+id+k);
    ckmax(ans, v2);
    for (auto x : ans) cout << x << ' ';
    cout << endl;

}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
