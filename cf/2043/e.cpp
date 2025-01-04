#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
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

bool solve(int n, int m, vector<vector<int>> a, vector<vector<int>> b){
	for (int bit = 0; bit < 30; ++bit) {
		vector<vector<int>> g(n+m); 
		vector<int> ops(n+m), deg(n+m);
		queue<int> q;
		for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
			if (!(a[i][j] >> bit & 1) and (b[i][j] >> bit & 1)) ops[n+j] = 1;
			if ((a[i][j] >> bit & 1) and !(b[i][j] >> bit & 1)) ops[i] = 1;
		}
		for (int i = 0; i < n+m; ++i) if (ops[i]) q.push(i);
		while (!q.empty()) {
			auto u = q.front(); q.pop();
			if (u < n) {
				for (int j = 0; j < m; ++j) if (b[u][j] >> bit & 1) {
					if (ops[n+j] == 0) ops[n+j] = 1, q.push(n+j);
				}
			} else {
				for (int i = 0; i < n; ++i) if (!(b[i][u-n] >> bit & 1)) {
					if (ops[i] == 0) ops[i] = 1, q.push(i);
				}
			}
		}
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				if (ops[i] and ops[n+j]) {
					if (b[i][j] >> bit & 1) {
						g[i].pb(n+j);
						deg[n+j]++;
					} else {
						g[n+j].pb(i), deg[i]++;
					}
				}
			}
		}
		// 11110
		// 00100
		//
		// 11111
		// 00001
		//
		// ops = { 1, 1, 1, 1, 1, 1, 1}
		// 
		// 11110
		// 00001
		//
		//
		for (int i = 0; i < n+m; ++i) if (deg[i] == 0) q.push(i);
		int vis = 0;
		while (!q.empty()) {
			auto u = q.front(); q.pop();
			vis++;
			for (auto v : g[u]) {
				deg[v]--;
				if (deg[v] == 0) q.push(v);
			}
		}
		if (vis < n+m) return false;
	}
	return true;
}

int rnd(int l, int r) {
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}

bool joaozao(int n, int m, vector<vector<int>> a, vector<vector<int>> b) {

    // posso fazer AND nas linhas e OR nas colunas
    // a -> b, AND vai apagar bits e OR vai acender bits
    // eu olho linha a[i] e b[i], se a[i][0] tem algum bit que b[i][0] nao tem, tenho que apagar ele
    // isso vale pra todo j entre 0 e m-1
    // primeiro apago tudo, agora olho pras colunas acendendo? 

    auto fix_rows = [&] () {
        for (int i = 0; i < n; i++) {
            int op = 0;
            for (int j = 0; j < m; j++) {
                for (int bit = 0; bit < 30; bit++) {
                    bool on_a = (a[i][j] >> bit) & 1;
                    bool on_b = (b[i][j] >> bit) & 1;
                    if (on_a && !on_b) {
                        op |= (1 << bit);
                    }
                }
            }
            op = ~op;
            for (int j = 0; j < m; j++) {
                a[i][j] &= op;
            }
        }
    };
    auto fix_cols = [&] () {
        for (int j = 0; j < m; j++) {
            int op = 0;
            for (int i = 0; i < n; i++) {
                for (int bit = 0; bit < 30; bit++) {
                    bool on_a = (a[i][j] >> bit) & 1;
                    bool on_b = (b[i][j] >> bit) & 1;
                    if (!on_a && on_b) {
                        op |= (1 << bit);
                    }
                }
            }
            for (int i = 0; i < n; i++) {
                a[i][j] |= op;
            }
        }
    };
    for (int cnt = 0; cnt < 40; cnt++) {
        fix_rows();
        fix_cols();
    }
	return (a == b);
}
int32_t main(){_
  int t = 1;
  while (true) {
	int nn = rnd(1, 1000), mm = rnd(1, 1000);
	vector<vector<int>> a_(nn, vector<int>(mm)), b_ = a_;
	for (auto& x : a_) for (auto& y : x) y = rnd(0, 1);
	for (auto& x : b_) for (auto& y : x) y = rnd(0, 1);
	if (solve(nn, mm, a_, b_) != joaozao(nn, mm, a_, b_)) {
		cout << "Wrong answer on test " << t << endl;
		cout << nn << ' ' << mm << endl;
		for (auto x : a_) {
			for (auto y : x) cout << y << ' ';
			cout << endl;
		}
		cout << endl;
		for (auto x : b_) {
			for (auto y : x) cout << y << ' ';
			cout << endl;
		}
		cout << "Your output: ";
		cout << (solve(nn, mm, a_, b_) ? "Yes" : "No") << endl;
		cout << "Answer: ";
		cout << (joaozao(nn, mm, a_, b_) ? "Yes" : "No") << endl;
		exit(0);
	}
	cout << "Accepted on test " << t++ << endl;
  }	
}
