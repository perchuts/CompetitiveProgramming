#include <bits/stdc++.h>
    #define gato
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
//#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
//#define gato
//#define int ll

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ii = pair<int,int>;
using iii = tuple<int,int,int>;

const int inf = 2e9+1;
const int mod = (119<<23)+1;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

int dp[305][305][305], two[305];

int brute(int n, vector<int> p) {
    vector<int> sexo(n); iota(all(sexo), 1);
    int tot = 0;
    do {
        if (sexo <= p) continue;
        bool ok = 0;
        for (int i = 0; i < n and !ok; ++i) for (int j = i + 1; j < n and !ok; ++j) for (int k = j + 1; k < n and !ok; ++k) for (int l = k + 1; l < n; ++l) {
            if (sexo[i] > sexo[j] and sexo[j] > sexo[k] and sexo[k] > sexo[l]) { ok = 1; break; }
        }
        if (ok == 0) tot++;
    } while (next_permutation(all(sexo)));
    return tot;
}

int solve(int n, vector<int> p) { 
	auto add = [&] (int& x, int y) { x += y; if (x >= mod) x-= mod; };
    // quero que todos os valores entre 1 e N - i sejam disponiveis (e que o restante esteja entre 1 e N - i)
    // dai a transicao tem que ser trivial: vou saber quando vou estar transicionando de cada elemento.
    // so preciso manter onde estou no maximo e no 
    
    vector<int> foi(n+1);
    vector<int> sexo(n); iota(all(sexo), 1);
    int mx = 0, lst = 0, ans = 0;
    for (int i = 0; i < n; ++i) {
        int mex = 1, h = 1;
        for (int j = 1; j <= n; ++j) { 
            if (foi[j] == 0) {
                if (h == 1) mex = j;
                h++;
            }
        }
        int j = 0, k = 0;
        for (int tr = mex+1; tr <= n; ++tr) {
            if (foi[tr]) continue;
            if (lst < tr and tr < mx) j++;
            else if (mx < tr) k++;
        }
        int _j = j, _k = k;
        for (int tr = mex; tr <= n; ++tr) {
            if (foi[tr]) continue;
            int addd = 0;
            if (tr == mex) {
                if (j + k == n - i - 1) {
                    if (j + k == 0) addd = 1;
                    else if (j != 0) addd = dp[n-i-1][j-1][k];
                    else addd = dp[n-i-1][j][k-1];
                } else addd = dp[n-i-1][j][k];
            } else {
                assert(mex < tr);
                // recalcular a qtd de cada termo
                if (mx != 0 and lst < tr and tr < mx) addd = dp[n-i-1][--_j][k];
                else if (mx < tr) addd = dp[n-i-1][j++][--_k];
            }
            if (p[i] < tr) add(ans, addd);
        }
        foi[p[i]] = 1;
        if (p[i] != mex and !ckmax(mx, p[i]) and !ckmax(lst, p[i])) break;
    }
    return ans;
}

int xd1[303][303][303], xd2[303][303][303];

int32_t main() {_
	dp[0][0][0] = 1;
    //#warning: trocar o N
	int N = 301;
	//int n; cin >> n;
	auto add = [&] (int& x, int y) { x += y; if (x >= mod) x-= mod; };
	for (int i = 1; i <= N; ++i) {
		for (int j = 0; j < i; ++j) {
			// dp[i][j][k] = i elementos faltando, posso enfiar o proximo 2o cara em j elementos, e o proximo 3o cara em k elementos
			for (int k = 0; j + k < i; ++k) {
				// mex
				if (j + k == i-1) {
					if (j + k == 0) dp[i][j][k] = 1;
					else if (j != 0) dp[i][j][k] = dp[i-1][j-1][k];
					else dp[i][j][k] = dp[i-1][j][k-1];
				} else dp[i][j][k] = dp[i-1][j][k];
                if (j) add(dp[i][j][k], xd1[i-1][j-1][k]);
                if (k) add(dp[i][j][k], xd2[i-1][j+k-1][k-1]);
				//for (int w = 0; w < j; ++w) add(dp[i][j][k], dp[i-1][w][k]);
				//for (int w = 0; w < k; ++w) add(dp[i][j][k], dp[i-1][j+k-1-w][w]);
                xd1[i][j][k] = dp[i][j][k];
                if (j) add(xd1[i][j][k], xd1[i][j-1][k]);
			}
		}
        for (int k = 0; k < i; ++k) {
            for (int j = 0; j + k < i; ++j) {
                xd2[i][j+k][k] = dp[i][j][k];
                if (k) add(xd2[i][j+k][k], xd2[i][j+k][k-1]);
            }
        }
	}
	//cout << dp[n][0][n-1] << endl;
#ifndef gato
    int t = 1; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<int> p(n);
        for (auto& x : p) cin >> x;
        cout << solve(n, p) << endl;
    }
#else
    int t = 1;
    while (true) {
        int n = rnd(1, 8);
        vector<int> p(n); iota(all(p), 1);
        shuffle(all(p), rng);
        int my = solve(n, p), ans = brute(n, p);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << endl;
            for (auto x : p) cout << x << ' ';
            cout << endl;
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
