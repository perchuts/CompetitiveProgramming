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
const int maxn = 2e6;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

vector<int> vals;

void solve(){
    int n; cin >> n;
    // vou precisar de no maximo 4
    int it = lower_bound(all(vals), n) - begin(vals);
    if (it < sz(vals) and vals[it] == n) {
        cout << 1 << endl;
        return;
    }
    // como vejo se preciso de 2?
    int i = 0, j = sz(vals)-1; 
    while (i <= j) {
        while (i <= j and vals[i] + vals[j] > n) --j;
        if (vals[i] + vals[j] == n) {
            cout << 2 << endl;
            return;
        }
        i++;
    }
    cout << 3 << endl;
}


int32_t main(){_
    for (int s = 1, i = 2; s <= 1e12 ; s += i, i++) vals.pb(s);
    int t = 1; cin >> t;
    while(t--) solve();
}
