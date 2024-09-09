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


int32_t main(){_
	int n, m, q; cin >> n >> m >> q;
	vector<ii> vote(n);
	for (auto& [x, y] : vote) cin >> x >> y;
	vector<vector<int>> g(m);
	for (int i = 0; i < m; ++i) {
		int l; cin >> l;
		for (int j = 0; j < l; ++j) {
			int x; cin >> x;
			if (x < 0) x = -x + n;
			g[i].pb(x-1);
		}
	}	
	// basicamente tenho uma arvore muito esquisita
	// com certeza vou precisar manter o custo minimo pra flipar o resultado dela
	// se eh uma folha, temos trivalmente isso!
	// se eu tenho varias folhas como filho:
	// o problema esta em termos x+1 caras iguais antes do prefixo 2x+1.
	// ideia gulosa: vai varrendo o array. se tu achou alguem com x+1 caras, flipar o com menor custo
	// se eu flipei o x, sei que ele jah eh maioria no array. entao so vou flipar ele ate o final (possivelmente vou ter q flipar o 
	// ultimo elemento tambem, exemplo: xxx!x!x)
	// entao posso fazer unbiased essa coisa de nao deixar ninguem pegar maioria, exceto na ultima posicao, onde possivelmente vou
	// flipar ou nao dependendo de quem quero q venca. ent seja X o resultado do algoritmo inicial e Y o valor na ultima posicao
	// pra mudar pra Y, o custo eh X. pra mudar pra !Y, o custo eh X + custo de mudar o ultimo elemento.
	// agora posso generalizar isso e transformar vertices maquina em vertices comuns, fazendo a[vertice] = Y e b[vertice] = custo de mudar o ultimo elemento.
	// mas vou ter que pagar X regardless do caso.
	while (q--) {
		int x, a, b; cin >> x >> a >> b;
		--x;
		vote[x] = {a, b};
	}
}
