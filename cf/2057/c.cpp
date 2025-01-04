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

void solve(){
	int l, r; cin >> l >> r;
	int a = 0, b = 0, c = 0;
	for (int i = 29; ~i; --i) {
		int bl = (l >> i & 1);
		int br = (r >> i & 1);
		if (bl != br)  {
			a += (1 << i);
			if ((l & ((1<<i)-1)) == ((1 << i) - 1)) {
				b += (1 << i);
				a++;
				c = l;
				break;
			}
			b += (1 << i) - 1;
			c += (1 << i) - 1;
			for (int j = i-1; ~j; --j) {
				if (l >> j & 1) {}
				else {
					c -= (1 << j); 
					break;
				}
			}
			break;
		}
		if (bl) a += (1 << i), b += (1 << i), c += (1 << i);
	}
	cout << a << ' ' << b << ' ' << c << endl;
	//cout << (a^b) + (b^c) + (a^c) << endl;
}

int32_t main(){_
  int t = 1; cin >> t;
  while(t--) solve();
}
