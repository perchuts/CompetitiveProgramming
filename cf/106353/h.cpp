#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ull
//#define sealion

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

int ncr[65][65];

void solve() {
    // quero duas funcoes:
    // dado mascara x, encontre a posicao dela no ciclo
    // dado inteiro x, encontre o vertice do ciclo
	auto get_pos = [] (auto&& self, int n, int k, int m) -> int {
        if (k == 1) {
            for (int j = 0; j < n; ++j) {
                if (m >> j & 1) {
					if (j == 0) return 0;
					return n-j;
				}
            }
            assert(false);
            return -1;
        }
		// [0]110 0
		// [0]101 1
		// [0]011 2
		//
		// [1]100 0
		// [1]001 1
		// [1]010 2
		// v
		// [0]011 3
		// [0]101 4
		// [0]110 5
        if (k == n-1) {
            for (int j = 0; j < n; ++j) {
                if (m >> (n-1-j) & 1) {}
                else return j;
            }
            assert(false);
            return -1;
        }
        if (__builtin_popcountll(m+1) == 1) return 0ULL;
        if (m & 1) return self(self, n-1, k-1, m/2);
        return ncr[n][k] - 1 - self(self, n-1, k, m/2);
    };
    auto get_node = [] (auto&& self, int n, int k, int x) -> int {
        if (k == 1) {
			if (x == 0) return 1ULL;
			int z = n-x;
			return (1ULL << z);
		}
        if (k == n-1) {
            int m = 0;
            for (int j = 0; j < n; ++j) if (n-1-j != x) m += (1ULL << j);
            return m;
        }
        if (x == 0) {
            int m = 0;
            for (int j = 0; j < k; ++j) m += (1ULL << j);
            return m;
        }
        if (x < ncr[n-1][k-1]) return 1+2*self(self, n-1, k-1, x);
        return 2 * self(self, n-1, k, ncr[n-1][k] - 1 - (x - ncr[n-1][k-1]));
    };
	int n, m, k; cin >> n >> m >> k;
    int mask = 0;
    for (int i = 0; i < n*m; ++i) {
        char c; cin >> c;
        if (c == '#') mask += (1ULL << i);
    }
    if ((k & (n*m)) == k) {
        cout << "risky" << endl;
        return;
    }
    // let N = n*m.
    // (N choose k) nodes
    // each node has k*(N - k) neighbors
    // find some perfect matching.
    // solution: find a hamiltonian cycle such that 1111100000, 01111100000, 0011111100.... are consecutive nodes in it
    // by induction you can build it!
    int pos = get_pos(get_pos, n*m, k, mask);
    int match;
    if (pos & 1) match = get_node(get_node, n*m, k, pos-1);
    else match = get_node(get_node, n*m, k, pos+1);
	auto get_move = [&] () {
		int x1, y1, x2, y2;
		for (int i = 0; i < n*m; ++i) {
			int b1 = (mask >> i & 1), b2 = (match >> i & 1);
			if (b1 != b2) {
				if (b1) x1 = i/m, y1 = i % m;
				else    x2 = i/m, y2 = i % m;
			}
		}
		cout << x1+1 << " " << y1+1 << endl;
		cout << x2+1 << " " << y2+1 << endl;
	};
	get_move();
    //for (int i = 0; i < n*m; ++i) {
    //    cout << ".#"[match>>i&1];
    //    if (i % m == m-1) cout << endl;
    //}
}

int32_t main() {_
    for (int i = 0; i <= 64; ++i) for (int j = 0; j <= i; ++j) {
        if (i == j or j == 0) ncr[i][j] = 1;
        else ncr[i][j] = ncr[i-1][j] + ncr[i-1][j-1];
    }
#ifdef sealion
	auto get_pos = [] (auto&& self, int n, int k, int m) -> int {
        if (k == 1) {
            for (int j = 0; j < n; ++j) {
                if (m >> j & 1) {
					if (j == 0) return 0;
					return n-j;
				}
            }
            assert(false);
            return -1;
        }
		// [0]110 0
		// [0]101 1
		// [0]011 2
		//
		// [1]100 0
		// [1]001 1
		// [1]010 2
		// v
		// [0]011 3
		// [0]101 4
		// [0]110 5
        if (k == n-1) {
            for (int j = 0; j < n; ++j) {
                if (m >> (n-1-j) & 1) {}
                else return j;
            }
            assert(false);
            return -1;
        }
        if (__builtin_popcountll(m+1) == 1) return 0ULL;
        if (m & 1) return self(self, n-1, k-1, m/2);
        return ncr[n][k] - 1 - self(self, n-1, k, m/2);
    };
    auto get_node = [] (auto&& self, int n, int k, int x) -> int {
        if (k == 1) {
			if (x == 0) return 1ULL;
			int z = n-x;
			return (1ULL << z);
		}
        if (k == n-1) {
            int m = 0;
            for (int j = 0; j < n; ++j) if (n-1-j != x) m += (1ULL << j);
            return m;
        }
        if (x == 0) {
            int m = 0;
            for (int j = 0; j < k; ++j) m += (1ULL << j);
            return m;
        }
        if (x < ncr[n-1][k-1]) return 1+2*self(self, n-1, k-1, x);
        return 2 * self(self, n-1, k, ncr[n-1][k] - 1 - (x - ncr[n-1][k-1]));
    };
	auto print = [&] (int n, int k) {
		vector<int> ordem(ncr[n][k]);
		for (int i = 0; i < ncr[n][k]; ++i) {
			ordem[i] = get_node(get_node, n, k, i);
			cout << bitset<8>(ordem[i]) << ' ' << get_pos(get_pos, n, k, ordem[i]) << endl;
		}
	};
	auto check = [&] (int n, int k) {
		if ((n & k) == k) return;
		cout << "Checking n = " << n << " k = " << k << ": ";
		vector<int> ordem(ncr[n][k]);
		for (int i = 0; i < ncr[n][k]; ++i) {
			ordem[i] = get_node(get_node, n, k, i);
			int j = get_pos(get_pos, n, k, ordem[i]);
			if (j != i) {
				cout << "failed for i = " << i << endl;
				cout << "node was " << bitset<10>(ordem[i]) << endl;
				cout << "get_pos returned " << j << endl;
				exit(0);
			}
		}
		for (int i = 1; i < ncr[n][k]; ++i) {
			if (__builtin_popcountll(ordem[i]^ordem[i-1]) != 2) {
				cout << "failed for edge (" << i-1 << ", " << i << "): ordem[" << i-1 << "] = " << bitset<10>(ordem[i-1]) << ", ordem[i] = " << bitset<10>(ordem[i]) << endl;
				exit(0);
			}
		}
		cout << "Accepted" << endl;
	};
	for (int n = 1; n <= 25; ++n) {
		for (int k = 1; k < n; ++k) {
			check(n, k);
		}
	}
	exit(0);
#endif
#ifndef gato
    int t = 1; cin >> t;
    while(t--) solve();
#else
    int t = 1;
    while (true) {
        int my = solve(), ans = brute();
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
