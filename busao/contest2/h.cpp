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

int query(int r, int c) {
	cout << "? " << c << ' ' << r << endl;
	int x; cin >> x;
	return x;
}

int answer(int r, int c) {
	cout << "! " << c << ' ' << r << endl;
	exit(0);
}

void solve(){
	int n; cin >> n;
	if (n == 1) answer(1, 1);
	int B = -1;
	for (int i = 1; i <= n; ++i) {
		if (1+i+(n/i)+(n%i) <= 1000) {
			B = i;
			break;
		}
	}
	assert(B != -1);
	int start = query(1, n), tam = -1;
	vector<int> mark(n+1, -1);
	mark[start] = 0;
	for (int i = 1; i < B; ++i) {
		int x = query(start, i);
		if (x == start) {
			tam = i;
			break;
		}
		assert(mark[x] == -1);
		mark[x] = i; 
	}
	if (tam == -1) {
		for (int i = B; i <= n; i += B) {
			int x = query(start, i);
			if (mark[x] != -1) {
				assert(mark[x] < B);
				tam = i - mark[x];
				break;
			}	
			mark[x] = i;
		}
	}
	if (tam == -1) {
		for (int i = (n/B) * B + 1; i <= n; ++i) {
			int x = query(start, i);
			if (mark[x] != -1) {
				assert(mark[x] == 0);
				tam = i;
				break;
			}
		}
	}
	assert(tam != -1);
	int walk = (tam - start) % tam;
	if (walk < 0) walk += tam;
	if (walk == 0) answer(start, start);
	else answer(query(start, walk), start);
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
