#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll
//#define gato

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

int solve(int n, int a1, int b1, int a2, int b2) {
    if (b1 > b2) swap(a1, a2), swap(b1, b2);
    if (b1 == b2) return (a1 == a2 ? n : 0);
    if (a1 > a2) return 0;
    int a = a1, b = b1, c = a2, d = b2;
    if (b == 1) {
        int l = 1, r = n, opt = -1;
        while (l <= r) {
            int md = l + (r-l+1)/2;
            if (a + md >= c + (md/d)) r = md-1, opt = md;
            else l = md+1;
        }
        if (opt == -1 or a+opt > c+(opt/d)) return 0;
        if (opt+1 <= n and a + opt + 1 == c + (opt+1)/d) return 2;
        return 1;
    }
    int t = d * b * (c - a - 1) / (d - b);
    t = max(1LL, t);
    int x = a + (t/b), y = c + (t/d), ans = 0;
    while (y > x) t += (b - (t%b)), x = a + (t/b), y = c + (t/d);
    if (t > n) return 0;
    // agora vou ter coisa do tipo:
    // aqui eh o primeiro t com potencial de acontecer alguma coisa
    // entao eu gostaria de achar de fato o primeiro momento onde ambos ficam iguais
    assert(x == y);
    if (t % b == 0) x--;
    if (t % d == 0) y--;
    assert(x != y or t == 1);
    int l = t, r = n, change = -1;
    while (l <= r) {
        int md = l + (r-l+1)/2;
        int p1 = (b - md%b) % b, tt = md + p1, va = a + tt/b, vc = c + tt/d;
        if (va == vc) change = md, l = md+1;
        else r = md-1;
    }
    l = t, r = n; int change2 = -1;
    while (l <= r) {
        int md = l + (r-l+1)/2;
        int p1 = (d - md%d) % d, tt = md + p1, va = a + tt/b, vc = c + tt/d;
        if (va <= vc) change2 = md, l = md+1;
        else r = md-1;
    }
    // qual eh o primeiro momento onde o P passa o B??
    // P					P					 P						P
    // 			B								B								B
    // LLLLLLLLLWWWWWWWWWWWWLLLLLLLLLLLLLLLLLLLLWLLLLLLLLLLLLLLLLLLLLLLLX
    // o ponto eh que sempre que eu olhar pro proximo P que acontecer, vamos ter que qtd dos dois caras eh igual!!!
    // sum of multiples of x \in [l, r]
    auto get = [&] (int l, int r, int x) { 
		if (l > r) return 0LL;
        int st = l/x, fim = r/x;
        return (l % x == 0 ? l : 0) + x*(st+1+fim)*(fim-st)/2;
    };
    if (change == -1) {
        if (change2 == -1) return min(n, t + (b-(t%b))-1)-t+1;
        change2 = min(n, change2 + (b - (change2%b)));
        int s1 = get(t+1, change2, b);
        int s2 = get(t, change2, d);
		ans = s1-s2;
		if ((a+n/b) == (c+n/d) and n % b) ans += n;
		else if (t == 1) ans--;
		return ans;
    } 
    // qual eh o primeiro momento onde o P passa o B??
    // 		P					P					 P						P
    // 	B					B					B
	assert(t != 1);
	assert(t % b == 0);
	int s1 = get(t, change, b);
	int s2 = get(t, change, d);
	assert(change == n or change % b == 0);
	ans = s2-s1;	
	if (change % b <= change % d) ans += min(n+1, change + b);
	if (change2 == -1 or change + b > n) return ans;
    // o ponto eh que sempre que eu olhar pro proximo P que acontecer, vamos ter que qtd dos dois caras eh igual!!!
    // sum of multiples of x \in [l, r]
	t = change + b;
	change2 = min(n, change2 + (b - (change2%b)));
	s1 = get(t+1, change2, b);
	s2 = get(t, change2, d);
	ans += s1-s2;
	if ((a+n/b) == (c+n/d) and n % b) ans += n+1;
	return ans;
}

int brute(int n, int a1, int b1, int a2, int b2) {
    int ans = 0, x = a1, y = a2;
    int st = -1;
    for (int i = 1; i <= n; ++i) {
        if (i % b1 == 0) x++;
        if (i % b2 == 0) y++;
        if (x == y) {
            if (st == -1) st = i;
            ans++;
        }
    }
    return ans;
}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
    while (t--) {
        int a, b, c, d, n; cin >> n >> a >> b >> c >> d;
        cout << solve(n, a, b, c, d) << endl;
    }
#else
    int t = 1;
    while (true) {
        int lim = 5000;
        int a = rnd(1, lim), b = rnd(1, lim), c = rnd(1, lim), d = rnd(1, lim), n = rnd(1, lim);
        int ans = brute(n, a, b, c, d);
        int my = solve(n, a, b, c, d);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << ' ' << a << ' ' << b << ' ' << c << ' ' << d << endl;
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
