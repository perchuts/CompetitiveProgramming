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

int solve(int n, vector<int> a){
    if (n == 1) return (a[0] == a[1] and a[1] == a[2]);
    // entao eu posso ignorar os 3 bichos adicionais q apareceram, fazer +1 em todas as dps se os 3 caras consecutivos q apareceram sao iguais
    // => sempre vai ser optimal fazer isso! 
    // ent podemos ignorar sequencias de 3 bichos iguais e reconstruir o array
    vector<vector<int>> dp(n+1, vector<int>(n+1, -inf));
    dp[n][n] = 0;
    for (int i = 0; i < 5; ++i) {
        ckmax(dp[a[i]][n], 0);
        ckmax(dp[n][a[i]], 0);
        for (int j = i+1; j < 5; ++j) {
            int cara = -1;
            bool ok = 1; 
            for (int k = 0; k < 5; ++k) {
                if (k == i or k == j) continue;
                if (cara == -1) cara = a[k];
                else ok &= (a[k] == cara);
            }
            ckmax(dp[a[i]][a[j]], ok);
            ckmax(dp[a[j]][a[i]], ok);
            ckmax(dp[a[i]][n], ok);
            ckmax(dp[a[j]][n], ok);
            ckmax(dp[n][a[i]], ok);
            ckmax(dp[n][a[j]], ok);
            ckmax(dp[n][n], ok);
        }
    }
    //cout << "a: ";
    //for (auto x : a) cout << x << ' ';
    //cout << endl;
	//cout << "bichos: " << a[0] << ' ' << a[1] << ' ' << a[2] << ' ' << a[3] << ' ' << a[4] << endl;
	//for (int i = 0; i <= n; ++i) {
	//	for (int j = 0; j <= n; ++j) {
	//		cout << dp[i][j] << " \n"[j==n];
	//	}
	//}
    int add = 0;
    for (int step = 1; 2+3*step+2 < sz(a)-1; ++step) {
		//cout << "bichos: " << a[2+3*step] << ' ' << a[3+3*step] << ' ' << a[4+3*step] << endl;
        map<int, int> cnt;
        cnt[a[2+3*step]]++;
        cnt[a[2+3*step+1]]++;
        cnt[a[2+3*step+2]]++;
        vector<iii> upds;
        for (auto [val, occ] : cnt) {
            // eu posso fazer o W, e imediatamente dps trocar pra um cara daqui
            if (occ == 3) {
                add++;
                continue;
            }
            if (occ == 2) {
                // aqui eh o caso facil -> tenho 2 opcoes
                upds.pb({val, val, dp[n][n]});
                for (int i = 0; i <= n; ++i) {
                    upds.pb({i, n, dp[i][val]+1});
                    upds.pb({n, i, dp[val][i]+1});
                    upds.pb({i, val, dp[i][n]});
                    upds.pb({val, i, dp[n][i]});
                    // posso tambem fazer o W com o a[i], e trocar imediatamente pelo outro bicho
                    for (auto [val2, occ2] : cnt) {
                        if (val2 != val) {
                            upds.pb({val2, i, dp[val][i]+1});
                            upds.pb({i, val2, dp[i][val]+1});
                        }
                    }
                }
            } else {
                assert(occ == 1);
                // unico estado valido eh o [val][val]
                upds.pb({n, n, dp[val][val]+1});
                int x1 = -1, x2 = -1;
                for (auto [val2, occ2] : cnt) {
                    if (val2 != val) {
                        if (occ2 == 2) assert(max(x1, x2) == -1), x1 = x2 = val2;
                        else if (x1 == -1) x1 = val2;
                        else assert(x2 == -1), x2 = val2;
                    }
                }
                for (int i = 0; i <= n; ++i) {
                    upds.pb({i, val, dp[i][n]});
                    upds.pb({val, i, dp[n][i]});
                }
				upds.pb({val, x1, dp[n][n]});
				upds.pb({x1, val, dp[n][n]});
				upds.pb({x2, val, dp[n][n]});
				upds.pb({val, x2, dp[n][n]});
                upds.pb({x1, n, dp[val][val]+1}), upds.pb({n, x1, dp[val][val]+1});
                upds.pb({x2, n, dp[val][val]+1}), upds.pb({n, x2, dp[val][val]+1});
                upds.pb({x1, x2, dp[val][val]+1}), upds.pb({x2, x1, dp[val][val]+1});
            }
        }
        for (auto [i, j, k] : upds) ckmax(dp[i][j], k);
		//for (int i = 0; i <= n; ++i) {
		//	for (int j = 0; j <= n; ++j) {
		//		cout << dp[i][j] << " \n"[j==n];
		//	}
		//}
    }
    //cout << add << endl;
    int ans = dp[a.back()][a.back()]+1;
    for (int i = 0; i <= n; ++i) for (int j = 0; j <= n; ++j) ckmax(ans, dp[i][j]);
    return ans+add;
}

int brute(int n, vector<int> a) {
    if (n == 1) return (a[0] == a[1] and a[1] == a[2]);
    vector<vector<int>> dp(n, vector<int>(n, -inf));
    for (int i = 0; i < 5; ++i) for (int j = 0; j < 5; ++j) {
        if (i != j) {
            int mn = n, mx = 0;
            for (int k = 0; k < 5; ++k) if (k != i and k != j) ckmax(mx, a[k]), ckmin(mn, a[k]);
            dp[a[i]][a[j]] = (mn == mx);
        }
    }
    for (int step = 2; step <= n-1; ++step) {
        vector<vector<int>> ndp(n, vector<int>(n, -inf));
        for (int v1 = 0; v1 < n; ++v1) for (int v2 = 0; v2 < n; ++v2) {
            vector<int> tmp = {v1, v2, a[3*step-1], a[3*step], a[3*step+1]};
            for (int i = 0; i < 5; ++i) for (int j = 0; j < 5; ++j) {
                if (i != j) {
                    int mn = n, mx = 0;
                    for (int k = 0; k < 5; ++k) if (k != i and k != j) ckmax(mx, tmp[k]), ckmin(mn, tmp[k]);
                    ckmax(ndp[tmp[i]][tmp[j]], dp[v1][v2] + (mn == mx));
                }
            }
        }
        swap(dp, ndp);
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) ckmax(ans, dp[i][j] + (i == j and j == a.back()));
    return ans;
}

int32_t main(){_
#ifndef gato
    int n; cin >> n;
    vector<int> a(3*n);
    for (auto& x : a) cin >> x, --x;
    cout << solve(n, a) << endl;
#else
    int t = 1;
    while (true) {
        int n = rnd(1, 30);
        vector<int> a(3*n);
        for (auto& x : a) x = rnd(1, n)-1;
        int my = solve(n, a), ans = brute(n, a);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << endl;
            for (auto x : a) cout << x + 1 << ' ';
            cout << endl;
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
