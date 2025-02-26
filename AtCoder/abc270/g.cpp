#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
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

int solve(int p, int a, int b, int s, int g){
    if (a == 0) {
        if (s == g) return 0;
        else if (b == g) return 1; 
        return -1;
    }
    auto fexp = [&] (int bb, int e) {
        int ans = 1;
        while (e) {
            if (e&1) ans = ans * bb % p;
            e /= 2, bb = bb * bb % p;
        }
        return ans;
    };
    if (a == 1) {
        if (b == 0) return (s == g ? 0 : -1); 
        g = (g - s + p) % p; 
        g = g * fexp(b, p-2) % p;
        return g;
    }
    int block = sqrt(p);
    map<int, int> pos;
    int inva = fexp(a-1, p-2), ablock = fexp(a, block), inva2 = fexp(a, p-2);
    int cur_a = 1, cur_inv = 1;
	//cout << "preprocess: " << endl;
    for (int i = 0; i < block; ++i) {
        int frac = b * (cur_a - 1) % p * inva % p;
        int num = (g - frac + p) % p;
        num = num * cur_inv % p;
        if (!pos.count(num)) pos[num] = i;
		//cout << num << ' ' << i << endl;
        cur_inv = cur_inv * inva2 % p, cur_a = cur_a * a % p;
    }
    cur_a = 1;
	//cout << "blocks: " << endl;
    for (int i = 0; i < p; i += block) {
        int xi = ((cur_a * s) % p + (b * (cur_a-1) % p * inva)) % p;
		//cout << i << ' ' << xi << endl;
        if (pos.count(xi)) {
            return i + pos[xi];
        }
        cur_a = cur_a * ablock % p;
    }
    return -1;
}

int32_t main(){_
#ifndef gato
    int t = 1; cin >> t;
    while(t--) {
        int p, a, b, s, g; cin >> p >> a >> b >> s >> g;
        cout << solve(p, a, b, s, g) << endl;
    }
#else
    int t = 1, lim = 10000000;
    vector<bool> primes(lim, 1);
    vector<int> pp;
    for (int i = 2; i < lim; ++i) {
        if (primes[i] == 0) continue;
        pp.pb(i);
        for (int j = i * i; j < lim; j += i) primes[j] = 0;
    }
    while (true) {
        int p, a, b, s, g; p = pp[rnd(0, sz(pp)-1)]; 
        a = rnd(0, p-1), b = rnd(0, p-1), s = rnd(0, p-1), g = rnd(0, p-1);
        int cur = s, ans = -1;
        for (int i = 0; i < p; ++i) {
            if (cur == g) {
                ans = i; break;
            }
            cur = (a * cur + b) % p;
        }
        int my = solve(p, a, b, s, g);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << 1 << endl;
            cout << p << ' ' << a << ' ' << b << ' ' << s << ' ' << g << endl;
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
