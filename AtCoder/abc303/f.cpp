#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int long long
#define ll __int128_t
//#define gato
using namespace std;

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

struct CHT {
	int32_t it;
	vector<ll> a, b;
	CHT():it(0){}
	ll eval(int i, ll x){
		return a[i]*x + b[i];
	}
	bool useless(){
		int sz = a.size();
		int r = sz-1, m = sz-2, l = sz-3;
		return (b[l] - b[r])*(a[m] - a[l]) <
			(b[l] - b[m])*(a[r] - a[l]);
	}
	void add(ll A, ll B){
		a.push_back(A); b.push_back(B);
		while (!a.empty()){
			if ((a.size() < 3) || !useless()) break;
			a.erase(a.end() - 2);
			b.erase(b.end() - 2);
		}
		it = min(it, int32_t(a.size()) - 1);
	}
	ll get(ll x){
		while (it+1 < a.size()){
			if (eval(it+1, x) >= eval(it, x)) it++;
			else break;
		}
		return eval(it, x);
	}
};
int solve(int n, int h, vector<int> t, vector<int> d){
    vector<int> ord(n); iota(all(ord), 0); sort(all(ord), [&] (int x, int y) { return pair(t[x], d[x]) < pair(t[y], d[y]); });
    vector<int> real;
    for (auto i : ord) {
        while (!real.empty() and (t[real.back()] == t[i] or (t[real.back()] < t[i] and d[real.back()] <= d[i]))) real.pop_back();
        real.pb(i);
    }
    reverse(all(real));
    n = sz(real);
    auto tt = t; auto dd = d;
    for (int i = 0; i < n; ++i) t[i] = tt[real[i]], d[i] = dd[real[i]];
    vector<int> suf(n+1);
    for (int i = n-1; ~i; --i) suf[i] = max(suf[i+1], t[i] * d[i]);
    auto possible = [&] (ll lim) {
        int i = 0; ll tim = 0, dmg = 0;
        CHT seek;
        while (tim < lim) {
#ifndef gato
            //cout << "tempo = " << (int)tim << " i = " << i << " dmg = " << (int)dmg << endl;
#endif
            if (i != n and max<__int128_t>(0, lim-t[i]) <= tim) {
                seek.add(-d[i], lim*d[i]);
                i++;
                continue;
            }
            ll best = 0, prox = lim;
            if (i != n) ckmin(prox, lim-t[i]);
            if (sz(seek.a) > 1) {
                ll A = seek.a[0], B = seek.b[0], C = seek.a[1], D = seek.b[1];
                ckmin(prox, (D - B + A - C - 1) / (A - C));
            }
			if (i != n and !seek.a.empty()){ 
				ll k = seek.get(tim);
				if (k > suf[i]) {
					ll dif = tim+(-seek.a[seek.it]-1+k-suf[i])/(-seek.a[seek.it]);
					ckmin(prox, dif);
				}
			}
            if (seek.it != sz(seek.a)) {
				ll aa = seek.get(tim);
				ll bb = seek.get(prox-1);
#ifndef gato
				//cout << (int) aa << ' ' << (int) bb << endl;
#endif
				ckmax(best, (aa+bb)*(prox-tim)/2);
			}
            ckmax(best, suf[i] * (prox-tim));
            dmg += best;
            tim = prox;
        }
#ifndef gato
       //cout << "tempo = " << (int)tim << " i = " << i << " dmg = " << (int)dmg << endl;
#endif
        return dmg >= h;
    };
#ifndef gato
	//possible(4);
	//exit(0);
#endif
    ll l = 1, r = h, ans = h;
    while (l <= r) {
        int md = l + (r-l+1)/2;
        if (possible(md)) ans = md, r = md-1;
        else l = md+1;
    }
    return (int)ans;
}

int brute(int n, int h, vector<int> t, vector<int> d) {
    int l = 1, r = h, ans = h;
    auto possible = [&] (int x) {
        int tot = 0;
        for (int tt = 0; tt < x; ++tt) {
            int mx = 0;
            for (int i = 0; i < n; ++i) ckmax(mx, min(t[i], (x-tt))*d[i]);
            tot += mx;
        }
        return tot >= h;
    };
    while (l <= r) {
        int md = l + (r-l+1)/2;
        if (possible(md)) ans = md, r = md-1;
        else l = md+1;
    }
    return ans;
}

int32_t main(){_
#ifndef gato
    int n, h; cin >> n >> h;
    vector<int> t(n), d(n);
    for (int i = 0; i < n; ++i) cin >> t[i] >> d[i];
    cout << solve(n, h, t, d) << endl;
#else
    int T = 1;
    while (true) { 
        int n = rnd(1, 5), h = rnd(1, 200);
        vector<int> t(n), d(n);
        for (auto& x : d) x = rnd(1, h);
        for (auto& x : t) x = rnd(1, h);
        int my = solve(n, h, t, d), ans = brute(n, h, t, d);
        if (my != ans) {
            cout << "Wrong answer on test " << T << endl;
            cout << n << ' ' << h << endl;
            for (int i = 0; i < n; ++i) cout << t[i] << ' ' << d[i] << endl;
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << T++ << endl;
    }
#endif
}
