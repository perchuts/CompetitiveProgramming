#include <bits/stdc++.h>
using namespace std;

#define int long long
#define PI pair<int,int>
#define f first
#define s second
#define pb push_back
#define szo(x) ((int)x.size())

int32_t main(){
    ios_base::sync_with_stdio(false); cin.tie(0);

    int n; cin >> n;
    vector<int> p(n);
    for (auto& x : p) cin >> x;
    vector<tuple<int, int, int>> pts;
    for (int i = 1; i <= n; ++i) {
        // colocar na esquerda
        if (i <= p[i-1]) pts.pb({i, 0, n + 1 + i - p[i-1]});
        if ((n+1-i) <= p[i-1] and p[i-1] != n) pts.pb({p[i-1] + i - n - 1, 1, i});
    }
    // tem que ser nao decrescente no x, nao crescente no y
    // inverta a dimensao 2 e faz nao decrescente
    vector<int> coords;
    for (auto& [x, t, y] : pts) y *= -1, coords.pb(y);
	sort(begin(pts), end(pts));
    sort(begin(coords), end(coords));
    coords.erase(unique(begin(coords), end(coords)), end(coords));
    int N = coords.size();
    vector<int> bit(N+1);
    auto add = [&] (int x, int y) {
        while (x <= N) bit[x] = max(bit[x], y), x += x & (-x);
    };
    auto query = [&] (int x) {
        int ans = 0;
        while (x) ans = max(ans, bit[x]), x -= x & (-x);
        return ans;
    };
    int ans = n, lst = -1;
	vector<pair<int, int>> cum;
    for (auto [x, t, y] : pts) {
		if ((t or x != lst) and !cum.empty()) {
			for (auto [a, b] : cum) add(a, b);
			cum.clear();
		}
		lst = x;
        y = lower_bound(begin(coords), end(coords), y) - begin(coords) + 1;
        int eu = query(y-t) + 1;
        ans = min(ans, n - eu);
		if (t == 0) cum.pb({y, eu});
		else add(y, eu);
    }
    cout << ans << endl;
}
