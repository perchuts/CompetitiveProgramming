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
// n faco ideia do que esta errado

void solve() {
    int n, q; cin >> n >> q;
    string s; cin >> s;
    vector<int> sexo(1000);
    vector<int> v(n);
    sexo['R'] = 0;
    sexo['G'] = 1;
    sexo['B'] = 2;
    for (int i = 0; i < n; ++i) v[i] = sexo[s[i]];
    vector<char> rev(3);
    rev[0] = 'R';
    rev[1] = 'G';
    rev[2] = 'B';
    vector<int> p(11, 1);
    for (int i = 1; i <= 10; ++i) p[i] = 3 * p[i-1];
    vector<array<int, 3>> qu(q);
    auto tle = [&] () {
        cout << "bicicleta" << endl;
        exit(0);
    };
    for (int i = 0; i < q; ++i) {
        int l, r; cin >> l >> r; --l, --r;
        r = min(r, n-1);
        qu[i][0] = l, qu[i][1] = r, qu[i][2] = i;
    }
    sort(all(qu), [&] (auto xx, auto yy) { return xx[1]-xx[0] < yy[1]-yy[0]; });
    vector<int> ans(q);
    int height = 0;
    auto go_up = [&] (int x) {
        height += p[x];
        for (int i = n-1; i >= height; --i) {
            v[i] += v[i-p[x]];
            if (v[i] >= 3) v[i] -= 3;
        }
    };
    const int mvkaio = 6;
	// lkkkkkk acabou sendo o ncr
	vector<vector<int>> lucas(p[mvkaio], vector<int>(p[mvkaio]));
	for (int i = 0; i < p[mvkaio]; ++i) {
		for (int j = 0; j <= i; ++j) {
			if (i == j) lucas[i][j] = 1;
			else lucas[i][j] = (lucas[i-1][j] + lucas[i-1][j-1]) % 3;
		}
	}
    for (auto arr : qu) {
        while (arr[1] - arr[0] >= height + p[mvkaio]) go_up(mvkaio);
		int tot = 0;
		int d = arr[1] - arr[0] - height;
		for (int i = arr[1] - d; i <= arr[1]; ++i) {
			tot += lucas[d][i - arr[1] + d] * v[i];
			if (tot >= 3) tot -= 3;
		}
		if ((arr[1] - arr[0]) & 1) tot = (3 - tot) % 3;
		ans[arr[2]] = tot;
    }
    for (auto x : ans) cout << rev[x] << endl;
}


int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
    while(t--) solve();
#else
    int t = 1;
    while (true) {
        int my = solve(), ans = brute();
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}

