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
vector<int> primes;
void solve(){
    int n; cin >> n;
    ++n;
    while (true) {
        bool ok = true;
        for (auto p : primes) {
            if (n % p == 0) {
                if (n == p) break;
                else {
                    ok = false;
                    break;
                }
            }
        }
        if (ok) break;
        n++;
    }
    cout << n << endl;
}
int crivo[4*maxn];
int32_t main(){_
    for (int i = 2; i <= 1e6; ++i) {
        if (crivo[i]) continue;
        primes.pb(i);
        for (int j = i * i; j <= 1e6; j += i) crivo[j] = 1;
    }
    int t = 1; cin >> t;
    while(t--) solve();
}
