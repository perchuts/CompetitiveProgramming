#include <iostream>     // Input/output stream objects
#include <fstream>      // File stream objects
#include <string>       // String class and functions
#include <vector>       // Dynamic array

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define ll long long
#define pb push_back

using namespace std;

int caso[26*26][26*26];
int opt[26*26][26*26];
int last_node[26*26];
int queue[26*26*26*26 + 10];
int N = 26 * 26;
double d[26*26 + 100];

int cnt[26*26], inq[26*26];

int nodes[26*26], m;
pair<int, int> exist[100050];

vector<pair<int, int> > g[26*26];

const double INF = 1e18;

bool spfa(double k) {
	int qq = 0, itr = 0;
	for (int i = 0; i < N; ++i) queue[qq++] = i, cnt[i] = 0, inq[i] = 0, d[i] = 0;	
	while (itr < qq) {
		int u = queue[itr++];
		inq[u] = 0;
		for (int i = 0; i < g[u].size(); ++i) {
			int v = g[u][i].first, w = g[u][i].second;
			double ww = (w ? -w + k : 0);
			if (d[u] + ww < d[v]) {
				d[v] = d[u] + ww;
				if (!inq[v]) {
					inq[v] = 1;
					queue[qq++] = v;
					cnt[v]++;
					if (cnt[v] >= N) return true;
				}
			}
		}
	}
	return false;
}

char buffer[1050];

int main() {_
	int n; 
	int T = 1;
	while (true) {
		scanf("%d", &n);
		if (n == 0) break;
		int nh = 0, ne = 0;
		for (int i = 0; i < n; ++i) {
			scanf("%s", buffer);
			int tam = 0;
			while (buffer[tam] != '\0') tam++;
			if (tam == 1) continue;
			int a = buffer[0] - 'a', b = buffer[1] - 'a', c = buffer[tam-2] - 'a', D = buffer[tam-1] - 'a';
			int U = 26 * a + b, V = (26 * c + D);

			if (caso[U][V] != T) exist[ne++] = make_pair(U, V);
			if (last_node[U] != T) nodes[nh++] = U, last_node[U] = T;
			if (last_node[V] != T) nodes[nh++] = V, last_node[V] = T;

			if (caso[U][V] != T or opt[U][V] < tam) {
				caso[U][V] = T;
				opt[U][V] = tam;
			}
		}

		for (int i = 0; i < ne; ++i) g[exist[i].first].pb(make_pair(exist[i].second, opt[exist[i].first][exist[i].second]));
		if (spfa(0) == false) {
			printf("No solution.\n");
		} else {
			double l = 0, r = 1000;
			for (int __ = 0; __ < 17; ++__) {
				double md = (l+r)/2;
				if (spfa(md) == true) l = md;
				else r = md;
			}
			printf("%.2f\n", l);
		}
		for (int i = 0; i < nh; ++i) g[nodes[i]].clear();
		T++;
	}
}
