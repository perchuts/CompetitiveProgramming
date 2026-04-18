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

void solve() {
    int p, q; cin >> p >> q;
    if (3*p >= 2*q and p < q) {
        cout << "Bob" << endl;
        return;
    }
	cout << "Alice" << endl;
}

int32_t main() {_
    //vector<vector<array<int, 2>>> brute(1000, vector<array<int, 2>>(1000));
    //for (int i = 0; i < 1000; ++i) {
    //    for (int j = 1; j < 1000; ++j) {
    //        if (3 * i == 2*j) {
    //            brute[i][j][0] = 1;
    //            brute[i][j][1] = 1;
    //            continue;
    //        }
    //        if (i == 0 or j == 1) {
    //            brute[i][j][0] = brute[i][j][1] = 0;
    //            continue;
    //        }
    //        if (brute[i][j-1][1] == 1 and brute[i-1][j][1] == 1) brute[i][j][0] = 1;
    //        else brute[i][j][0] = 0;
    //        if (brute[i][j-1][0] == 0 and brute[i-1][j][0] == 0) brute[i][j][1] = 0;
    //        else brute[i][j][1] = 1;
    //    }
    //}
	//for (int j = 1; j < 1000; ++j) {
	//	for (int i = 0; i < 1000; ++i) {
	//		if((3*i >= 2*j and i < j) != brute[i][j][0]) {
	//			assert(false);
	//		}
	//		if (brute[i][j][0]) {

	//			cout << i << " " << j << " " << (brute[i][j][0] ? "Bob" : "Alice") << endl;
	//		}
	//	}
	//}
	//exit(0);
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
