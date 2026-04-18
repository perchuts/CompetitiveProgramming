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

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

void brute(int n) {
    map<vector<int>, vector<vector<int>>> mp;
    set<vector<vector<int>>> vis;
    auto op = [&] (vector<vector<int>> v, int x) {
        swap(v[1][x], v[1][x+2]);
        swap(v[0][x], v[2][x+2]);
        swap(v[0][x+2], v[2][x]);
        swap(v[0][x+1], v[2][x+1]);
        return v;
    };

    queue<vector<vector<int>>> q;
    vector<vector<int>> can(3, vector<int>(n));
    int z = 0;
    for (int i = 0; i < n; ++i) for (int j = 0; j < 3; ++j) can[j][i] = z++;
	auto v = can;
    //cout << "canonico:" << endl;
	//for (int j = 0; j < 3; ++j) {
	//	for (int i = 0; i < n; ++i) {
	//		cout << v[j][i] << " ";
	//	}
	//	cout << endl;
	//}
	//cout << endl;
    mp[can[1]] = can;
    vis.insert(can);
	q.push(can);
	bool st = 0;
    int qt = 0;
    while (!q.empty()) {
        auto v = q.front(); q.pop();
        bool ok = 1;
        for (int i = 0; i < n; ++i) {
            ok &= (v[0][i] % 3 == 0);
        }
        if (ok) {
            for (int j = 0; j < 3; ++j) {
                for (int i = 0; i < n; ++i) {
                    cout << v[j][i] << " ";
                }
                cout << endl;
            }
            cout << endl;
        }
            qt += ok;
		st = 1;
        for (int i = 0; i < n-2; ++i) {
            auto g = op(v, i);
            if (vis.find(g) == end(vis)) {
				vis.insert(g), q.push(g);
			}
        }
    }
    cout << qt << endl;
}

void solve() {
    int n; cin >> n;
    vector<vector<int>> v(3, vector<int>(n));
    for (auto& x : v) for (auto& y : x) cin >> y, --y;
    vector<vector<int>> can(3, vector<int>(n));
    int z = 0;
    for (int i = 0; i < n; ++i) for (int j = 0; j < 3; ++j) can[j][i] = z++;
    for (int i = 0; i < n; ++i) if (v[1][i] % 3 != 1) {
        cout << "No" << endl;
        exit(0);
    }
    vector<int> par(3*n), mid(3*n);
    for (int i = 0; i < n; ++i) par[can[0][i]] = can[2][i], par[can[2][i]] = can[0][i], mid[can[0][i]] = mid[can[2][i]] = can[1][i];
    for (int i = 0; i < n; ++i) {
        if (v[2][i] != par[v[0][i]] or v[1][i] != mid[v[0][i]]) {
            cout << "No" << endl;
            exit(0);
        }
    }
    int inv = 0, flip = 0;
    for (int p = 0; p < 2; ++p) {
        vector<int> bit(3*n+1);
        auto insert = [&] (int x) {
            while (x <= 3*n) bit[x]++, x += x & (-x);
        };
        auto query = [&] (int x) {
            int ans = 0;
            while (x) ans += bit[x], x -= x & (-x);
            return ans;
        };
        for (int i = p; i < n; i += 2) {
            flip += (v[0][i] % 3 != 0);
            inv += i/2 - query(v[0][i]);
            insert(v[0][i]+1);
        }
    }
    if (inv % 2 != flip % 2) {
        cout << "No" << endl;
        exit(0);
    }
}

int32_t main() {_
    brute(6);
    exit(0);
#ifndef gato
    int t = 1; //cin >> t;
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
