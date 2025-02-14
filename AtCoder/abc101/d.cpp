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
    int k; cin >> k;
    auto f = [&] (int n) {
        string s = to_string(n);
        int t = 0;
        for (auto x : s) t += (x - '0');
        return t;
    };
    auto get_prox = [&] (int n) {
        int s = f(n);
        if (f(n+1) > s) return n+1;
        int ans = n+1, pot = 1;
        while (n % 10 == 9) ans += 9 * pot, pot *= 10, n /= 10;
        return ans;
    };
    vector<int> v = {1};
    cout << 1 << endl;
    while (sz(v) < k) {
        int cur = v.back()+1;
        vector<int> cand = {cur};
        while (f(get_prox(cur)) <= 135) {
            cur = get_prox(cur);
            cand.pb(cur);
        }
        sort(all(cand), [&] (int x, int y) { 
            int a = f(y) * x, b = f(x) * y;
            if (a == b) return x < y;
            return a < b;
        });
        v.pb(cand[0]);
        cout << v.back() << endl;
    }
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
