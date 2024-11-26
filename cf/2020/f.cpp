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
	int n, k, d; cin >> n >> k >> d;
	// quantas folhas existem com valor = x, com T(n, d) fixo?
	// sejam v1, v2, ..., vm os primos de n
	// vms ter q vxi <= vni.
	// preciso tirar vni - vxi termos em d passos
	// stars and bars
	// produtorio de (vni - vxi + d-1, d-1)
	// de certa forma, vamos ter a soma desses produtorios:
	// T(n, d) = sum_over_k(prod_k(vni-k_i+d-1, d-1))
	// certo, agora o que acontece quando eu sei T(n, d) e quero saber T(n^2, d)?
	// T(x, d) = sum(y, d-1), y|x
	// T(p^k, d) = sum T(p^l, d-1)
	// T(p^x * q^y, d) = T(p^x, d) * T(q^y, d)
	// temos uma funcao multiplicativa aqui
	// T(p^x, d) = (d+x, d)
	// T(n, d) = multiplicar (d+vni, d)
	// T(n^k, d) = multiplicar (d+k*vni, d)
	// k=1?
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
