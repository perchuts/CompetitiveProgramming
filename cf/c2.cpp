#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
//#define endl '\n'
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

int solve(int n, vector<int> v){
	vector<int> eq(n, 1);
	for (int i = n-2; i >= 0; --i) {
		if (v[i] == v[i+1]) eq[i] = eq[i+1]+1;
		else eq[i] = 1;
	}
	int ans = 0, tam = __lg(n);
	vector bl(tam, vector(n, 0));
	for (int p = 0; p < tam; ++p) {
		for (int i = 0; i + (1 << p) < n; ++i) {
			if (p == 0) bl[0][i] = abs(v[i] - v[i+1]);
			else {
				bl[p][i] = gcd(bl[p-1][i], bl[p-1][i+(1<<(p-1))]);
			}	
		}
	}
	for (int i = 0; i < n; ++i) {
		ans += eq[i];
		int g = 0, pos = i + eq[i] - 1;
		for (int j = tam-1; j >= 0 && pos < n-1; --j) {
			int k = gcd(g, bl[j][pos]);
			if (__builtin_popcount(k) > 1 && pos + (1 << j) < n) {
				g = k;
				pos += (1 << j);
			}
		}
		if (pos < n-1) {
			g = gcd(bl[0][pos], g);
			if (__builtin_popcount(g) == 1) ans += n - pos - 1; 
		}
	}
	return ans;
}

mt19937 rng(time(0));

int rnd(int l, int r) {
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}
int32_t main(){_
	int ttt = 1;
	while (true) {
		int n = rnd(1, 10);
		vector<int> v(n);
		for (auto& x : v) x = rnd(1, 100000000);
		int my = solve(n, v);
		int ans = 0;
		for (int i = 0; i < n; ++i) {
			vector<int> vv;
			for (int j = i; j < n; ++j) {
				vv.pb(v[j]);
				sort(all(vv)); vv.erase(unique(all(vv)), end(vv));
				int g = 0;
				for (int k = 0; k < sz(vv)-1; ++k) g = gcd(g, vv[k+1]-vv[k]);
				ans += (__builtin_popcount(g) <= 1);
			}
		}
		if (ans != my) {
			cout << "Wrong answer on test " << ttt << endl;
			cout << n << endl;
			for (auto x : v) cout << x << ' ';
			cout << endl;
			cout << "Your output: " << my << endl;
			cout << "Correct answer: " << ans << endl;
			exit(0);
		} else {
			cout << "Accepted on test " << ttt << endl;
		}
		++ttt;
	}
}
