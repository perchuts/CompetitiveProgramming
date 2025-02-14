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
    string s; cin >> s;
    int k; cin >> k;
    int n = sz(s);
    vector<vector<int>> occ(26);
    for (int i = 0; i < n; ++i) occ[s[i]-'a'].pb(i);
    vector<string> sexo;
    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < sz(occ[i]); ++j) {
            string cur;
            for (int w = occ[i][j]; w < min(n, occ[i][j]+2*k); ++w) { 
               cur += s[w]; 
                sexo.pb(cur);
            }
        }
    }
    sort(all(sexo));
    sexo.erase(unique(all(sexo)), end(sexo));
    cout << sexo[k-1] << endl;
}
int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
