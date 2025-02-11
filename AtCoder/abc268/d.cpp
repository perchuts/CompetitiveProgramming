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
    int n, m; cin >> n >> m;
    vector<string> sexo1(n);
    int t = 0;
    for (auto& x : sexo1) cin >> x, t += sz(x);
    map<string, int> id;
    map<string, bool> opa;
    vector<string> sexo2(m);
    for (auto& x : sexo2) {
        cin >> x, opa[x] = true; 
    }
    if (n == 1) {
        // corner engracado
        cout << (opa[sexo1[0]] ? "-1" : (sz(sexo1[0]) >= 3 ? sexo1[0] : "-1")) << endl;
        exit(0);
    }
    vector<int> p(n);
    iota(all(p), 0);
    do {
        auto go = [&] (auto&& self, int cur, int tam, string sexo3) -> void {
            sexo3 += sexo1[p[cur]];
            if (cur == n-1) {
                if (opa.count(sexo3)) return;
                cout << sexo3 << endl;
                exit(0);
            }
            for (int i = 1; tam-i >= n-cur-2; ++i) {
                sexo3 += '_';
                self(self, cur+1, tam-i, sexo3);
            }
        };
        go(go, 0, 16 - t, ""); 
    } while (next_permutation(all(p)));
    cout << -1 << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
