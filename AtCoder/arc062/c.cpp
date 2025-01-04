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

void solve(){
	int n; cin >> n;

	vector<array<int, 4>> v(n);

	vector<int> pot(4, 1);

	for (int i = 1; i < 4; ++i) pot[i] = 1000 * pot[i-1];

	for (auto& x : v) cin >> x[0] >> x[1] >> x[2] >> x[3];

	map<int, int> freq;

	auto get_mask = [&] (int a, int b, int c, int d) {
		return a + pot[1] * b + pot[2] * c + pot[3] * d;
	};

	auto change = [&] (int pos, int k) {
		int mask = 1e18, cnt = 1; 

		if (v[pos][0] == v[pos][2] and v[pos][1] == v[pos][3]) {
			if (v[pos][0] == v[pos][1]) cnt = 4;
			else cnt = 2;
		}

		for (int i = 0; i < 4; ++i) ckmin(mask, get_mask(v[pos][(i+1)%4], v[pos][i], v[pos][(i+3)%4], v[pos][(i+2)%4]));

		freq[mask] += cnt * k;
	};

	int ans = 0;

	for (int i = 0; i < n; ++i) change(i, 1);
	for (int i = 0; i < n; ++i) {
		change(i, -1);
		for (int j = i+1; j < n; ++j) {
			change(j, -1);
			for (int rot = 0; rot < 4; ++rot) {
				vector<int> vtemp(4);
				vtemp[0] = v[j][(rot+1)%4], vtemp[1] = v[j][rot], vtemp[2] = v[j][(rot+3)%4], vtemp[3] = v[j][(rot+2)%4];
				map<int, int> faces, power;
				for (int k = 0; k < 4; ++k) {
					int val = 1e18;
					vector<int> pts = {v[i][k], v[i][(k+1)%4], vtemp[(k+1)%4], vtemp[k]};
					for (int w = 0; w < 4; ++w) ckmin(val, get_mask(pts[w], pts[(w+1)%4], pts[(w+2)%4], pts[(w+3)%4]));
					faces[val]++;
					if (pts[0] == pts[2] and pts[1] == pts[3]) {
						if (pts[0] == pts[1]) power[val] = 4;
						else power[val] = 2;
					} else power[val] = 1;
				}
				int tot = 1;
				for (auto [x, y] : faces) {
					int pw = power[x];
					for (int k = 0; k < y; ++k) tot *= (freq[x] - k * pw);	
				}
				ans += tot;
			}
			change(j, 1);
		}
		change(i, 1);
	}
	assert(ans % 3 == 0);
	cout << ans / 3 << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
