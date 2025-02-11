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
int n, p; 

inline void add(int& x, int y) {
	assert(y < p);
	x += y;
	if (x >= p) x %= p;
}
void solve(){
	cin >> n >> p;
	int M = n*(n-1)/2;
	vector dp(2, vector(n/2+1, vector(n/2+1, vector(M+1, vector(n/2+1, 0LL)))));
	vector dp1(n/2+1, vector(n/2+1, vector(M+1, 0LL)));
	vector ncr(M+1, vector(M+1, 0LL));
	for (int i = 0; i <= M; ++i) for (int j = 0; j <= i; ++j) {
		if (i == j or j == 0) ncr[i][j] = 1;
		else ncr[i][j] = (ncr[i-1][j] + ncr[i-1][j-1]) % p;
	}
	for (int i = 1; i <= n/2; ++i) {
		dp1[i][0][0] = 1;
		for (int j = 1; j <= n/2; ++j) {
			for (int fora = j; fora <= i*j; ++fora) {
				for (int eu = 1; eu <= min(fora, i); ++eu) {
					int k = dp1[i][j-1][fora-eu] * ncr[i][eu] % p;
					add(dp1[i][j][fora], k);
				}
			}
		}
		for (int j = 1; j <= n/2; ++j) {
			int sexo = j * (j-1)/2;
			for (int soma = i*j + sexo; soma >= j; --soma) {
				for (int dentro = 1; soma-dentro >= j; ++dentro) {
					int k = dp1[i][j][soma-dentro] * ncr[sexo][dentro] % p;
					add(dp1[i][j][soma], k); 
				}
			}
		}
	}
	dp[0][1][0][0][1] = 1;
	for (int lado1 = 1; lado1 <= n/2; ++lado1) {
		for (int lado2 = 1; lado2 <= n/2; ++lado2) {
			for (int tot_edg = lado1+lado2-1; tot_edg <= (lado1+lado2)*(lado1+lado2-1)/2; ++tot_edg) {
				for (int sexo = 0; sexo < 2; ++sexo) {
					for (int last = 1; last <= (sexo?lado1:lado2); ++last) {
						for (int eu = 1; eu <= (sexo?lado2:lado1); ++eu) {
							auto& DP = dp[sexo][lado1][lado2][tot_edg][eu];											
							for (int edg = eu; edg <= min(tot_edg, eu*(eu-1)/2 + eu*last); ++edg) {
								
								int k = dp[sexo^1][(sexo?lado1:lado1-eu)][(sexo?lado2-eu:lado2)][tot_edg-edg][last] * dp1[last][eu][edg] % p;
								k = k * ncr[n-(lado1+lado2-eu)][eu] % p;
								add(DP, k); 
							}
						}
					}
				}
			}
		}
	}
	for (int i = n-1; i <= M; ++i) {
		int ans = 0;
		for (int j = 1; j <= n/2; ++j) add(ans, (dp[0][n/2][n/2][i][j] + dp[1][n/2][n/2][i][j])%p);
		cout << ans << ' ';
	}
	cout << endl;
}

int32_t main(){_
	solve();
}
