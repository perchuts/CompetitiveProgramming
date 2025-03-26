#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ii = pair<int,int>;
using iii = tuple<int,int,int>;

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
    string s, t; cin >> s >> t;

    int k; cin >> k;

    vector<vector<int>> use(26);
    vector<pair<string, string>> caras(k);

    for (int i = 0; i < k; ++i) {
        string a, b; cin >> a >> b;
        caras[i] = {a, b};
        use[a[0]-'a'].pb(i);
    }

    int n = sz(s), m = sz(t);
    const int inf = 1e9;

    vector<vector<int>> dist(26, vector<int>(26, inf));

    for (int i = 0; i < 26; ++i) dist[i][i] = 0;
    for (auto [x, y] : caras) if (sz(x) == 1 and sz(y) == 1) dist[x[0]-'a'][y[0]-'a'] = 1;
    for (int K = 0; K < 26; ++K) for (int i = 0; i < 26; ++i) for (int j = 0; j < 26; ++j) ckmin(dist[i][j], dist[i][K] + dist[K][j]);

    vector dp(k, vector(51, vector(m+1, vector(m+1, inf))));

    for (int l = m; l >= 1; --l) {
        for (int r = l; r <= m; ++r) {
            if (l == r) {
                for (int i = 0; i < k; ++i) {
                    int suf = sz(caras[i].second)-1;
                    int eu = caras[i].second.back() - 'a';
                    ckmin(dp[i][suf][l][r], dist[eu][t[l-1]-'a']);
                }
            }
            for (int i = 0; i < k; ++i) {
                if (sz(caras[i].second) == 1) continue;
                int suf = 0;
                if (caras[i].second[suf] == t[l-1] and l != r) ckmin(dp[i][suf][l][r], dp[i][suf+1][l+1][r]);
                for (auto j : use[caras[i].second[suf]-'a']) {
                    for (int w = l; w < r; ++w) ckmin(dp[i][suf][l][r], dp[j][0][l][w] + dp[i][suf+1][w+1][r] + 1);
                }
            }
            for (int i = 0; i < k; ++i) {
                for (int suf = sz(caras[i].second)-2; suf > 0; --suf) {
                    if (caras[i].second[suf] == t[l-1] and l != r) ckmin(dp[i][suf][l][r], dp[i][suf+1][l+1][r]);
                    for (auto j : use[caras[i].second[suf]-'a']) {
                        for (int w = l; w < r; ++w) ckmin(dp[i][suf][l][r], dp[j][0][l][w] + dp[i][suf+1][w+1][r] + 1);
                    }
                }
            }
            if (l != r) {
                for (int i = 0; i < k; ++i) {
                    int suf = sz(caras[i].second)-1;
                    int eu = caras[i].second.back() - 'a';
                    for (int go = 0; go < 26; ++go) {
                        for (auto j : use[go]) if (sz(caras[j].second) > 1) ckmin(dp[i][suf][l][r], dist[eu][go] + dp[j][0][l][r] + 1);
                    }
                }
            }
        }
    }
    vector<vector<int>> match(n+1, vector<int>(m+1, inf)); match[0][0] = 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (s[i-1] == t[j-1]) ckmin(match[i][j], match[i-1][j-1]);
            for (auto idx : use[s[i-1]-'a']) {
                for (int j2 = 1; j2 <= j; ++j2) ckmin(match[i][j], dp[idx][0][j2][j] + match[i-1][j2-1] + 1);
            }
        }
    }

    cout << (match[n][m] < inf ? match[n][m] : -1) << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
