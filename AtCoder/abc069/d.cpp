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
    int sexo_n, sexo_m; cin >> sexo_n >> sexo_m;
    int sexoo; cin >> sexoo;
    vector<int> sexo_a(sexoo);
    for (auto& sexo_x : sexo_a) cin >> sexo_x;
    vector<vector<int>> sexo_ans(sexo_n, vector<int>(sexo_m));
    int sexo_ptr = 0;
    for (int sexo_i = 0; sexo_i < sexo_n; ++sexo_i) {
        if (sexo_i % 2) {
            for (int sexo_j = 0; sexo_j < sexo_m; ++sexo_j) {
                if (sexo_a[sexo_ptr] == 0) sexo_ptr++;
                sexo_ans[sexo_i][sexo_j] = sexo_ptr+1;
                sexo_a[sexo_ptr]--;
            }
        } else {
            for (int sexo_j = sexo_m-1; ~sexo_j; --sexo_j) {
                if (sexo_a[sexo_ptr] == 0) sexo_ptr++;
                sexo_ans[sexo_i][sexo_j] = sexo_ptr+1;
                sexo_a[sexo_ptr]--;
            }
        }
    }
    for (int sexo_i = 0; sexo_i < sexo_n; ++sexo_i) for (int sexo_j = 0; sexo_j < sexo_m; ++sexo_j) cout << sexo_ans[sexo_i][sexo_j] << " \n"[sexo_j==sexo_m-1];
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
