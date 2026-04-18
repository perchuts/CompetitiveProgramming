#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll
//#define gato

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

int brute(int n, string s) {
    vector<vector<int>> dp(n+1, vector<int>(n+1, inf));
    dp[0][0] = 0;
    for (auto c : s) {
        vector<vector<int>> ndp(n+1, vector<int>(n+1, inf));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; i + j < n; ++j) { 
                if (i) ckmin(ndp[i][j], dp[i-1][j] + (c != '('));
                if (j) ckmin(ndp[i][j], dp[i][j-1] + (c != '['));
                ckmin(ndp[i][j], dp[i+1][j] + (c != ')'));
                ckmin(ndp[i][j], dp[i][j+1] + (c != ']'));
            }
        }
        swap(dp, ndp);
    }
    return dp[0][0];
}

int solve(int n, string s) {
    // 1: fixado quem vai ser mexido e qual tipo de bracket eu vou mexer, a solucao vai ser ((((())))), [[[[[[]]]]]]] (mixados)
    //
    // eu adoraria fazer um guloso.
    // vai pegando enquanto da, quando nao da, vc 

    return 0;
}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
    while(t--) {
        int n; string s; cin >> n >> s;
        cout << brute(n, s) << endl;
    }
#else
int t = 1;
    while (true) {
        int n = rnd(1, 5) * 2;
        string s(n, '(');
        vector<char> z = {'(', ')', '[', ']'};
        for (auto& x : s) x = z[rnd(0, 3)];
        int my = solve(n, s), ans = brute(n, s);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << endl << s << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
