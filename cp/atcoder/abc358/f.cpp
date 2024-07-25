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

void solve(){
	int n, m, k; cin >> n >> m >> k; 
	if (k < n) {
		cout << "No" << endl;
		exit(0);
	}
	// construction is to drop first columns and partially last one
	vector<vector<char>> ans(2*n+1, vector<char>(2*m+1, '+'));
	ans[0][2*m-1] = 'S', ans[2*n][2*m-1] = 'G';
	auto border = [&] (int x1, int y1, int x2, int y2, bool type = 0) {
		if (x1 == x2) {
			if (y1 > y2) swap(y1, y2);
			if (y2 == m || y1 == -1) return;
			ans[1+2*x1][2+2*y1] = (type ? '.' : '|');
		} else {
			assert(y1 == y2);
			if (x1 > x2) swap(x1, x2);
			if (x2 == n || x1 == -1) return;
			ans[2*x1+2][1+2*y1] = (type ? '.' : '-');
		}
	};
	for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
		ans[2*i+1][2*j+1] = 'o';
		border(i, j, i+1, j, 1), border(i, j, i, j+1, 1);
	}
	auto printAns = [&] () {
		cout << "Yes" << endl;
		for (auto x : ans) {
			for (auto y : x) cout << y; 
			cout << endl;
		}
		exit(0);
	};
	if (m == 1) {
		if (k != n) {
			cout << "No" << endl;
			exit(0);
		}	
		printAns();
	}
	if (k % 2 != n % 2) {
		cout << "No" << endl;
		exit(0);
	}
	int p = k % n, faltar = n * m - k;
	if (n % 2 == 0) {
		if (faltar) {
			for (int i = 0; i < n; ++i) {
				if (i < p || p == 0) border(i, faltar/n-1, i, faltar/n);
				else border(i, faltar/n, i, faltar/n+1);
			}
			if (p) border(p-1, faltar/n, p, faltar/n);
		}
		for (int i = 0; i < n-1; ++i) {
			if (i&1) for (int j = m-2; j >= faltar/n+(i>=p&&p!=0); --j) border(i, j, i+1, j);
			else for (int j = m-1; j > faltar/n+(i>=p&&p!=0); --j) border(i, j, i+1, j);
		}
		printAns();
	} else {
		if (p != 1 && p != n-1) {
			if (faltar) {
				for (int i = 0; i < n; ++i) {
					if (i < p || p == 0) border(i, faltar/n-1, i, faltar/n);
					else border(i, faltar/n, i, faltar/n+1);
				}
				if (p) border(p-1, faltar/n, p, faltar/n);
			}
			if (p&1) {
				for (int i = 0; i < p - 2; ++i) {
					if (i&1) for (int j = m-2; j >= faltar/n; --j) border(i, j, i+1, j);
					else for (int j = m-1; j > faltar/n; --j) border(i, j, i+1, j);
				}
				for (int j = faltar/n; j < m - 1; ++j) {
						if (j % 2 == (faltar/n) % 2) border(p-2, j, p-2, j+1);
						else border(p-1, j, p-1, j+1);
				}
				for (int i = p-1; i < n - 1; ++i) {
					if (i % 2 == 0) for (int j = m-2; j >= faltar/n+1; --j) border(i, j, i+1, j);
					else for (int j = m-1; j > faltar/n+1; --j) border(i, j, i+1, j);
				}
			} else {
				for (int i = 0; i < p; ++i) {
					if (i&1) for (int j = m-2; j >= faltar/n; --j) border(i, j, i+1, j);
					else for (int j = m-1; j > faltar/n; --j) border(i, j, i+1, j);
				}
				for (int j = faltar/n+2-(p==0); j < m; ++j) border(n-2, j, n-1, j);
				for (int j = m - 1; j > faltar/n+1-(p==0); --j) {
					if (j % 2 == (m - 1) % 2) for (int i = p; i < n - 2; ++i) border(i, j, i, j-1);
					else for (int i = p + 1; i < n - 1; ++i) border(i, j, i, j-1);
				}
			}
			printAns();
		} else if (p == 1) {
			border(0, m-1, 1, m-1);
			border(1, m-1, 2, m-1);
			border(1, m-2, 1, m-1);
			p++;	
			for (int i = 0; i < n; ++i) {
				if (i < p) border(i, faltar/n-1, i, faltar/n);
				else border(i, faltar/n, i, faltar/n+1);
			}
			border(p-1, faltar/n, p, faltar/n);
			for (int j = m - 2; j > faltar/n+1; --j) {
				if (j % 2 == m % 2) border(0, j, 0, j-1);
				else border(1, j, 1, j-1);
			}
			border(0, faltar/n+1, 1, faltar/n+1);
			for (int i = p-1; i < n - 1; ++i) {
					if (i % 2 == 0) for (int j = m-2; j >= faltar/n+1; --j) border(i, j, i+1, j);
					else for (int j = m-1; j > faltar/n+1; --j) border(i, j, i+1, j);
			}
			printAns();
		} else {
			border(0, m-1, 1, m-1);
			border(1, m-1, 2, m-1);
			border(1, m-2, 1, m-1);
			for (int j = m - 2; j >= faltar/n+1; --j) {
				if (j % 2 == m % 2) border(0, j, 0, j - 1);
				else border(1, j, 1, j - 1);
				border(1, j, 2, j);
			}
			p = 2;
			for (int j = faltar/n; j < m - 2; ++j) {
				if (j % 2 == (faltar/n) % 2) for (int i = p; i < n - 1; ++i) border(i, j, i, j + 1);
				else for (int i = p + 1; i < n; ++i) border(i, j, i, j + 1);
			}
			for (int i = p; i < n - 1; ++i) {
				if (i % 2 == p % 2) border(i, m - 2, i + 1, m - 2);
				else border(i, m - 1, i + 1, m - 1);
			}
			printAns();
		}
	}
	assert(false);
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
