#include <bits/stdc++.h>
using namespace std;

//#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'

typedef long long ll;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3f;

const int MAX = 3e5 + 10069;

int lca(int i, int j) {
  while (i != j) {
    if (i > j) i /= 2;
    else j /= 2;
  }
  return i;
}
// quantos vertices tem ENTRE i, j
int dist(int i, int j) {
  if (i < j) swap(i, j);
  int d = 0;
  while (i != j) i /= 2, d++;
  return d;
}

int k, n; 
map<int, vector<pair<int, int>>> virt;

int build_virt(vector<int> v) {
  v.push_back(1);
  auto cmp = [&] (int i, int j) {
	  int ret = 0;
	  if (i > j) swap(i, j), ret = 1;
	  int diff = __builtin_clz(i) - __builtin_clz(j);
	  int w = (j>>diff);
	  if (w == i) return (i<j)^ret;
	  return (i<w)^ret;
  };	
  sort(begin(v), end(v), cmp);
  for (int i = v.size() - 1; i; --i) v.push_back(lca(v[i], v[i-1]));
  sort(begin(v), end(v), cmp);
  v.erase(unique(begin(v), end(v)), end(v));
  for (int i = 1; i < v.size(); ++i) {
    int parent = lca(v[i-1], v[i]);
    int d = dist(parent, v[i]);
    virt[parent].emplace_back(v[i], d);
  }
  return v[0];
}

double ans = 0;
bitset<1073741825> foi, exist;

double dp[100][100][100], pot[100];

double brute(int x, bool add) {
	if (x >= (1<<k)) return 0;
    int cur = x / 2, height = 0, qnt = 1;
	double resp = 0;
    while (cur) {
       if (exist[cur]) break;
       height++, qnt += (foi[cur] == 0);
       resp += pot[height-(cur==1)]/(add?(double)1:(double)qnt);
       cur /= 2;
    }
    if (x == 1) resp++;
    exist[x] = add;
	return resp;
}

void dfs(int u, int lst) {
	int children = 0, d = dist(u, 1), d2 = (lst == 0 ? -1 : dist(lst, 1));
	for (auto [v, w] : virt[u]) {
		children++;
		ans += dp[d+1][d+w-1][d2+1];
		if (exist[v]) dfs(v, v);
		else dfs(v, lst);
	}
	if (children == 0) {
		if (exist[u]) ans += (dp[d+1][d+1][d2+1]*2 - brute(2*u, 0)) * 2;
		else ans += dp[d][d][d2+1]*2 - brute(u, 0);
	} else if (children == 1) {
		if (exist[u]) ans += dp[d+1][d+1][d2+1]*2 - brute(2*u, 0);
		else ans += dp[d][d][d2+1];
	} else if (exist[u] == 0) ans += brute(u, 0);

}

int32_t main() {
  fast_io;
  cin >> k >> n;
  using ii = pair<int, int>;
  vector<ii> p(n);
  auto convert = [&] (int layer, int ind) {
     --layer;
     int tam = (1 << layer), id = 1;
     for (int i = 0; i < layer; ++i) {
        tam /= 2;
        if (ind <= tam) id = 2 * id;
        else id = 2 * id + 1, ind -= tam;
     }
     return id;
  };
  vector<int> nodes;
  pot[0] = 1;
  for (int i = 1; i < k; ++i) pot[i] = pot[i-1] / 2;
  for (auto& [layer, ind] : p) {
    cin >> layer >> ind;
    layer = k - layer + 1;
    nodes.push_back(convert(layer, ind));
    foi[nodes.back()] = 1;
  }
  for (auto x : nodes) ans += brute(x, 1);
  for (int fim = 0; fim < k; ++fim) {
	  for (int i = fim; i < k; ++i) {
		  for (int j = i; j < k; ++j) {
			  if (j) dp[i][j][fim] = dp[i][j-1][fim];
			  for (int layer = j; layer < k; ++layer) {
				  double cur = 0;
				  for (int morre = layer-1; morre >= max(1, fim); --morre) {
					cur += pot[layer-morre] / (double)(layer-morre+1);
				  }
				  if (fim == 0) cur += pot[max(0, layer-1)]/(double)(layer+1);
				  dp[i][j][fim] += cur * (1<<(max(0,layer-j-1)));
			  }
		  }
	  }
  }
  int root = build_virt(nodes);
  dfs(root, exist[root]);
  cout << fixed << setprecision(10) << ans << endl;
}

