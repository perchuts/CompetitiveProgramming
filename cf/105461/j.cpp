#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
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

string query(string s) {
    cout << "? " << s << endl;
    string ans; cin >> ans;
    return ans;
}

void solve(){
    int n; cin >> n;
    int pot = 1, turn = 0;
    vector<string> v;
    while (pot < n) {
        string s;
        for (int i = 0; i < n; ++i) {
            int cur = i;
            for (int j = 0; j < turn; ++j) cur /= 26;
            s += char('a'+(cur%26));
        }
        v.pb(query(s));
        pot *= 26, turn++;
    }
    vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        int val = 0;
        for (int j = 0, pp = 1; j < sz(v); ++j, pp *= 26) val += pp*(v[j][i] - 'a');
        p[val] = i;
    }
    cout << "! ";
    for (auto x : p) cout << x+1 << ' ';
    cout << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
