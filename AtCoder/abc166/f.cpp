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
    int n, a, b, c; cin >> n >> a >> b >> c;
    vector<string> tipo(n);
    for (auto& x : tipo) cin >> x;
    vector<int> caras = {a, b, c};
    vector<char> ans;
    vector<int> quem(290); quem['A'] = 0, quem['B'] = 1, quem['C'] = 2;
    if (a+b+c != 2) {
        for (int i = 0; i < n; ++i) {
            int x = quem[tipo[i][0]], y = quem[tipo[i][1]];
            if (caras[x] <= caras[y]) caras[x]++, caras[y]--, ans.pb(tipo[i][0]);
            else caras[x]--, caras[y]++, ans.pb(tipo[i][1]);
            if (min(caras[x], caras[y]) == -1) {
                cout << "No" << endl;
                exit(0);
            }
        }
    } else {
        vector<vector<int>> bixos = {{2, 0, 0}, {0, 2, 0}, {0, 0, 2}, {1, 1, 0}, {0, 1, 1}, {1, 0, 1}};
        vector<vector<int>> dp(n+1, vector<int>(6)), tr = dp;
        auto getId = [&] (vector<int> x) {
            for (int i = 0; i < 6; ++i) if (bixos[i] == x) return i;
            assert(false);
        };
        dp[0][getId(caras)] = 1;
        for (int i = 0; i < n; ++i) {
            int x = quem[tipo[i][0]], y = quem[tipo[i][1]];
            for (int j = 0; j < 6; ++j) {
                auto cc = bixos[j];
                if (cc[x] >= 1) {
                    cc[x]--, cc[y]++;
                    if (dp[i][getId(cc)]) tr[i+1][j] = tipo[i][0], dp[i+1][j] = 1;
                    cc[x]++, cc[y]--;
                } 
                if (cc[y] >= 1) {
                    cc[x]++, cc[y]--;
                    if (dp[i][getId(cc)]) tr[i+1][j] = tipo[i][1], dp[i+1][j] = 1;
                    cc[x]--, cc[y]++;
                }
            }
        }
        for (int j = 0; j < 6; ++j) {
            if (dp[n][j]) {
                auto cc = bixos[j];
                for (int i = n; i; --i) {
                    int x = quem[tipo[i-1][0]], y = quem[tipo[i-1][1]];
                    ans.pb(tr[i][getId(cc)]);
                    if (char(tr[i][getId(cc)]) == tipo[i-1][0]) cc[x]--, cc[y]++;
                    else cc[x]++, cc[y]--;
                    assert(min(cc[x], cc[y]) >= 0);
                }
                reverse(all(ans));
                break;
            }
        }
        if (ans.empty()) {
            cout << "No" << endl;
            exit(0);
        }
    }
    cout << "Yes" << endl;
    for (auto x : ans) cout << x << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
