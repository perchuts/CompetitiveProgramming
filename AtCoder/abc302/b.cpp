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
	int h, w; cin >> h >> w;
	vector<string> grid(h);
	for (auto& x : grid) cin >> x;
	string sexoooo = "snuke";
	for (int i = 0; i < h; ++i) {
		for (int j = 0; j < w; ++j) {
			if (j + 4 < w) {
				string sexo = grid[i].substr(j, 5);
				if (sexo == sexoooo) {
					cout << i+1 << ' ' << j+1 << endl;
					cout << i+1 << ' ' << j+2 << endl;
					cout << i+1 << ' ' << j+3 << endl;
					cout << i+1 << ' ' << j+4 << endl;
					cout << i+1 << ' ' << j+5 << endl;
					exit(0);
				}
				reverse(all(sexo));
				if (sexo == sexoooo) {
					cout << i+1 << ' ' << j+5 << endl;
					cout << i+1 << ' ' << j+4 << endl;
					cout << i+1 << ' ' << j+3 << endl;
					cout << i+1 << ' ' << j+2 << endl;
					cout << i+1 << ' ' << j+1 << endl;
					exit(0);	
				}
			}
			if (i + 4 < h) {
				string sexo; sexo += grid[i][j]; sexo += grid[i+1][j]; sexo += grid[i+2][j]; sexo += grid[i+3][j]; sexo += grid[i+4][j];
				if (sexo == sexoooo) {
					cout << i+1 << ' ' << j+1 << endl;
					cout << i+2 << ' ' << j+1 << endl;
					cout << i+3 << ' ' << j+1 << endl;
					cout << i+4 << ' ' << j+1 << endl;
					cout << i+5 << ' ' << j+1 << endl;
					exit(0);
				}
				reverse(all(sexo));
				if (sexo == sexoooo) {
					cout << i+5 << ' ' << j+1 << endl;
					cout << i+4 << ' ' << j+1 << endl;
					cout << i+3 << ' ' << j+1 << endl;
					cout << i+2 << ' ' << j+1 << endl;
					cout << i+1 << ' ' << j+1 << endl;
					exit(0);	
				}
			}
			if (i + 4 < h and j + 4 < w) {
				string sexo; sexo += grid[i][j]; sexo += grid[i+1][j+1]; sexo += grid[i+2][j+2]; sexo += grid[i+3][j+3]; sexo += grid[i+4][j+4];
				if (sexo == sexoooo) {
					cout << i+1 << ' ' << j+1 << endl;
					cout << i+2 << ' ' << j+2 << endl;
					cout << i+3 << ' ' << j+3 << endl;
					cout << i+4 << ' ' << j+4 << endl;
					cout << i+5 << ' ' << j+5 << endl;
					exit(0);
				}
				reverse(all(sexo));
				if (sexo == sexoooo) {
					cout << i+5 << ' ' << j+5 << endl;
					cout << i+4 << ' ' << j+4 << endl;
					cout << i+3 << ' ' << j+3 << endl;
					cout << i+2 << ' ' << j+2 << endl;
					cout << i+1 << ' ' << j+1 << endl;
					exit(0);	
				}
			}
			if (i + 4 < h and j >= 4) {
				string sexo; sexo += grid[i][j]; sexo += grid[i+1][j-1]; sexo += grid[i+2][j-2]; sexo += grid[i+3][j-3]; sexo += grid[i+4][j-4];
				if (sexo == sexoooo) {
					cout << i+1 << ' ' << j+1 << endl;
					cout << i+2 << ' ' << j << endl;
					cout << i+3 << ' ' << j-1 << endl;
					cout << i+4 << ' ' << j-2 << endl;
					cout << i+5 << ' ' << j-3 << endl;
					exit(0);
				}
				reverse(all(sexo));
				if (sexo == sexoooo) {
					cout << i+5 << ' ' << j-3 << endl;
					cout << i+4 << ' ' << j-2 << endl;
					cout << i+3 << ' ' << j-1 << endl;
					cout << i+2 << ' ' << j << endl;
					cout << i+1 << ' ' << j+1 << endl;
					exit(0);	
				}

			}
		}
	}
	assert(false);
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
