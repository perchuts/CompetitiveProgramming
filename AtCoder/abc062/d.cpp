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
    vector<int> a(3*n);
    for (auto& x : a) cin >> x;
    vector<multiset<int>> sexo(4);
    int ans = -1e18, cur = 0;
    for (int i = 0; i < n; ++i) sexo[0].insert(a[i]), cur += a[i];
    for (int i = n; i < 3*n; ++i) sexo[2].insert(a[i]);
    for (int i = 0; i < n; ++i) {
        auto x = *begin(sexo[2]);
        sexo[2].erase(sexo[2].find(x));
        sexo[3].insert(x);
        cur -= x;
    }
    ans = cur;
    for (int i = n; i < 2*n; ++i) {
        if (sexo[2].find(a[i]) != end(sexo[2])) {
            sexo[2].erase(sexo[2].find(a[i]));
        } else {
            assert(sexo[3].find(a[i]) != end(sexo[3]));
            sexo[3].erase(sexo[3].find(a[i]));
            cur += a[i];
            auto x = *begin(sexo[2]);
            sexo[2].erase(sexo[2].find(x));
            cur -= x;
            sexo[3].insert(x);
        }
        if (a[i] > (*begin(sexo[0]))) {
            int x = *begin(sexo[0]);
            sexo[0].erase(sexo[0].find(x));
            cur -= x;
            sexo[1].insert(x);
            sexo[0].insert(a[i]);
            cur += a[i];
        } 
        ckmax(ans, cur);
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
