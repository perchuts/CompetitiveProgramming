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
    vector<int> t(n), d(n), mx(n+1);
    multiset<int> sexo1, sexo2;
    int ans = 0, cur = 0;
    for (int i = 0; i < n; ++i) cin >> t[i] >> d[i], ckmax(mx[t[i]], d[i]), sexo2.insert(-d[i]);
    for (int i = 0; i < k; ++i) {
        auto z = *begin(sexo2);
        cur += -z;
        sexo2.erase(sexo2.find(z));
        sexo1.insert(z);
    }
    sort(rbegin(mx), rend(mx));
    ans = cur;
    for (int z = 0; z < k; ++z) {
        auto x = *rbegin(sexo1);
        sexo1.erase(sexo1.find(x));
        int y = -mx[z];
        if (y == 0) break;
        if (x == y) {}
        else {
            sexo2.insert(x);
            cur += -y;
            cur -= -x;
            if (sexo2.find(y) != end(sexo2)) {
                sexo2.erase(sexo2.find(y));
            } else {
                sexo1.erase(sexo1.find(y));
                int w = *begin(sexo2);
                sexo2.erase(sexo2.find(w));
                sexo1.insert(w);
                cur -= -y; 
                cur += -w;
            }
        }
        ckmax(ans, cur + (z+1)*(z+1));
    }
    cout << ans << endl;

}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
