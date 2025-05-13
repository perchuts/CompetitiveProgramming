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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

void solve(){
}
void brute(int n) {
    vector<int> win(1<<(n*n));
    vector<int> change(n*n);
    auto get = [&] (int x) {
        return pair(x/n, x%n);
    };
    for (int i = 0; i < n*n; ++i) {
        auto [x, y] = get(i);
        int r = min(x, y);
        for (int j = 0; j <= i; ++j) {
            auto [x2, y2] = get(j);
            if (x-r <= x2 and x2 <= x and y-r <= y2 and y2 <= y) change[i] ^= (1 << j);
        }
    }
    auto printGrid = [&] (int i) {
        for (int j = 0; j < n*n; ++j) {
            if (j % n == 0) cout << endl;
            cout << (i>>j&1);
        }
        cout << endl;
    };
    vector<vector<int>> moves(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (min(i, j) == 0) moves[i][j] = 1;
            else {
                int r = min(i, j);
                for (int x = i; x >= i-r; --x) {
                    for (int y = j; y >= j-r; --y) {
                        moves[i][j] ^= moves[x][y];
                    }
                }
                moves[i][j] ^= 1;
            }
        }
    }
    for (auto x : moves) {
        for (auto y : x) cout << y;
        cout << endl;
    }
    for (int i = 0; i < (1<<n*n); ++i) {
        int tot = 0;
        for (int j = 0; j < n*n; ++j) {
            if (i >> j & 1) {
                win[i] |= (win[change[j]^i]^1);
                auto [x, y] = get(j);
                tot ^= moves[x][y];
            }
        }
        if (win[i] != tot) {
            cout << "WA " << i << endl;
            cout << win[i] << ' ' << tot << endl;
            printGrid(i);
            exit(0);
        }
    }
}

void test(int n) {
    vector<vector<int>> moves(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (min(i, j) == 0) moves[i][j] = 1;
            else {
                int r = min(i, j);
                for (int x = i; x >= i-r; --x) {
                    for (int y = j; y >= j-r; --y) {
                        moves[i][j] ^= moves[x][y];
                    }
                }
                moves[i][j] ^= 1;
            }
        }
    }
    for (auto x : moves) {
        for (auto y : x) cout << y;
        cout << endl;
    }
    cout << endl;
    auto get = [&] (auto&& self, int i, int j) -> int {
        if (j == 0) return 0;
        int steps = i/j % 2;
        return self(self, j, i % j) ^ steps;
    };
    // [i][j] = [i-1][j] + [i][j-1] - [i-1][j-1] - [i-j][j] + 1
    // [i][j] := [i][j] + [i-1][j] + [i][j-1] - [i-1][j-1]
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (min(i, j) > 1) {
                int x = max(i, j), y = min(i, j);
                if (x == y) cout << 0;
                else {
                    int eu = get(get, x-1, y-1) ^ get(get, x, y-1) ^ get(get, x-1, y) ^ get(get, x-y, y) ^ 1;
                    if (eu != moves[i-1][j-1]) {
                        cout << "WA: " << i << ' ' << j << ": " << eu << ' ' << moves[i-1][j-1] << endl;
                        cout << get(get, x-1, y-1) << " " <<  get(get, x, y-1) << " " << get(get, x-1, y) << " " << get(get, x-y, y) << " " << 1 << endl;
                        exit(0);
                    }
                    cout << eu;
                }
            } else cout << 1;
        }
        cout << endl;
    }
}
void fast() {
    int n; cin >> n;
    int ans = 0;
    auto get = [&] (auto&& self, int i, int j) -> int {
        if (j == 0) return 0;
        int steps = i/j % 2;
        return self(self, j, i % j) ^ steps;
    };
    for (int i = 0; i < n; ++i) {
        int x, y; cin >> x >> y;
        if (x < y) swap(x, y);
        if (y == 1) ans ^= 1;
        else if (x != y) ans ^= get(get, x-1, y-1) ^ get(get, x, y-1) ^ get(get, x-1, y) ^ get(get, x-y, y) ^ 1;
    }
    cout << (ans ? "FIRST" : "SECOND") << endl;
}
void slow() {
    int nn; cin >> nn;
    int n = 10;
    vector<vector<int>> moves(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (min(i, j) == 0) moves[i][j] = 1;
            else {
                int r = min(i, j);
                for (int x = i; x >= i-r; --x) {
                    for (int y = j; y >= j-r; --y) {
                        moves[i][j] ^= moves[x][y];
                    }
                }
                moves[i][j] ^= 1;
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < nn; ++i) {
        int x, y; cin >> x >> y;
        ans ^= moves[x-1][y-1];
    }
    cout << (ans ? "FIRST" : "SECOND") << endl;
}
int32_t main(){_
    //test(100);
    //slow();
    fast();
}
