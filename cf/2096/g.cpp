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

void solve(){
    int n; cin >> n;
    vector<int> mask(n), pot(20, 1);
    int lg = 0;
    for (int i = 1; i < 20; ++i) {
        pot[i] = 3 * pot[i-1]; 
        if (!lg and pot[i] >= n) lg = i;
    }
    vector<int> mark(3*n);
    int id = 0;
    for (int i = 1; id + 1 < n; ++i) {
        if (mark[i]) continue;
        int j = 0, s1 = 0, s2 = 0;
        for (int k = 0; k < lg; ++k) {
            int cara = (i/pot[k]) % 3;
            s1 = (s1 + cara) % 3;
            if (cara == 1) j += 2 * pot[k], s2 = (s2 + 2) % 3;
            else if (cara == 2) j += pot[k], s2 = (s2 + 1) % 3;
        }
        mask[id] = i * 3 + s1, mask[id+1] = j * 3 + s2; id += 2;
        mark[i] = mark[j] = 1;
    }
    vector<vector<int>> qq(lg+1);
    cout << lg + 1 << endl;
    for (int i = 0; i <= lg; ++i) {
        int aa = 0;
        for (int turn = 1; turn < 3; ++turn) {
            for (int j = 0; j < n; ++j) {
                int cara = (mask[j]/pot[i]) % 3;
                if (cara == turn) qq[i].pb(j+1), aa += (turn == 1 ? 1 : -1);
            }
        }
        assert(aa == 0);
        cout << sz(qq[i]) << ' ';
        for (auto x : qq[i]) cout << x << ' ';
        cout << endl;
    }
    string s; cin >> s;
    for (int i = 0; i < n; ++i) {
        int d = 0;
        for (int j = 0; j <= lg; ++j) {
            if (s[j] == '?') continue;
            int val = 0;
            if (s[j] == 'L') val = 1;
            if (s[j] == 'R') val = 2;
            d += (val != (mask[i]/pot[j])%3);
        }
        if (d == 0) {
            cout << i + 1 << endl;
            return;
        }
    }
    assert(false);
}

int32_t main(){_
    int t = 1; cin >> t;
    while(t--) solve();
}
