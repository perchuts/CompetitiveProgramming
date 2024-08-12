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

const int inf = 2e9+1;
const int mod = 1e9+7;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

int pre[2][2][2][3];

int32_t main(){_
	int n, m; cin >> n >> m;
	vector<vector<int>> grid(n-1, vector<int>(m-1));
	for (auto& x : grid) for (auto& y : x) {
		char c; cin >> c;
		y = c - '0';
	}
	vector<int> p(3); iota(all(p), 0);
	do {
		vector<int> pp(3);
		for (int i = 0; i < 3; ++i) pp[p[i]] = i;
		int a = (pp[0] < pp[1]), b = (pp[0] < pp[2]), c = (pp[1] < pp[2]);
		for (int i = 0; i < 3; ++i) pre[a][b][c][i] = p[(pp[i]+2)%3];
	} while(next_permutation(all(p)));
	vector<vector<int>> ans(n, vector<int>(m));
	vector prox(n, vector<ii>(m, make_pair(-1, -1))), ant = prox;
	ii head = {0, 0};
	if (grid[0][0] == 1) {
		ans[0][0] = 1, ans[0][1] = 2;
		ans[1][0] = 3, ans[1][1] = 4;
	} else if (grid[0][0] == 3) {
		ans[0][0] = 1, ans[0][1] = 3;
		ans[1][0] = 2, ans[1][1] = 4;
	} else {
		ans[0][0] = 1, ans[0][1] = 2;
		ans[1][0] = 4, ans[1][1] = 3;
	}
	ii tmp = head;
	for (int v = 2; v <= 4; ++v) {
		for (int i = 0; i < 2; ++i) {
			for (int j = 0; j < 2; ++j) {
				if (ans[i][j] == v) {
					prox[tmp.first][tmp.second] = {i, j};
					ant[i][j] = tmp;
					tmp = {i, j};
				}
			}
		}
	}
	auto print = [&] () {
		for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) cout << ans[i][j] << " \n"[j==m-1];
	};
	auto upd = [&] (int r, int c, int x) {
		ckmax(c, 2);
		for (int i = 0; i < r; ++i) {
			for (int j = c-2; j < c; ++j) {
				if (ans[i][j] >= x) ans[i][j]++;
			}
		}
	};
	auto UPD = [&] (int x1, int y1, int x2, int y2, int val = -1) {
		ii px = prox[x1][y1];
		prox[x1][y1] = {x2, y2};
		prox[x2][y2] = px;
		ant[x2][y2] = {x1, y1};
		if (px.first != -1) {	
			ant[px.first][px.second] = {x2, y2};
		}
		upd(n, y2+1, (val==-1?ans[x1][y1]+1:val));
		ans[x2][y2] = (val==-1?ans[x1][y1] + 1:val);
	};
	for (int i = 2; i < n; ++i) {
		int h = (ans[i-1][0] < ans[i-1][1]);
		if (grid[i-1][0] == 1) {
			UPD(i-1, h, i, h^1);
			UPD(i, h^1, i, h);
		} else if (grid[i-1][0] == 3) {
			UPD(i-1, h^1, i, h^1);
			UPD(i-1, h, i, h);
		} else {
			UPD(i-1, h, i, h);
			UPD(i, h, i, h^1);
		}
	}
	for (int j = 2; j < m; ++j) {
		int h = (ans[0][j-1] < ans[1][j-1]);
		if (grid[0][j-1] == 1) {
			UPD(h, j-1, h^1, j);
			UPD(h^1, j-1, h, j);
		} else if (grid[0][j-1] == 3) {
			UPD(h, j-1, h^1, j);
			UPD(h^1, j, h, j);
		} else {
			UPD(h, j-1, h, j);
			UPD(h, j, h^1, j);
		}
		for (int k = 2; k < n; ++k) {
			int x = ans[k-1][j], y = ans[k-1][j-1], z = ans[k][j-1];
			int a = (x<y), b = (x<z), c = (y<z);
			int id = pre[a][b][c][grid[k-1][j-1]-1];
			if (id == 0) x = k-1, y = j;
			if (id == 1) x = k-1, y = j-1;
			if (id == 2) x = k, y = j-1;
			auto [x1, y1] = ant[x][y];
			UPD(x1, y1, k, j, ans[x][y]);
		}
		ii cur = head;
		for (int k = 1; k <= j * n + n; ++k) ans[cur.first][cur.second] = k, cur = prox[cur.first][cur.second];
	}	
	print();
}

