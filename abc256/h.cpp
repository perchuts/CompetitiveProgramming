#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
//#define gato
#pragma GCC optimize("Ofast")
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

vector<int> solve(int n, int q, vector<int> a, vector<array<int, 4>> queries){
    // o numero de elementos distintos no array eh <= quando updates do tipo 1 sao feitos
    // pra updates de tipo 2, o numero eh <= +1 (caso aaaaaaaa -> aaayyyyyaaaaa) (todos os caras eram iguais no range
    // na verdade, se eu for olhando pra cima nos nodes da segtree, em cada parent node do update, vou somar +1 possivelmente nos valores distintos
    // entao seria um +log^2 de valores distintos?
    set<iii> s;
    int lcur = 0;
    vector<int> bit(n+1);
    auto insert_bit = [&] (int x, int k) {
        x++;
        while (x <= n) bit[x] += k, x += x & (-x);
    };
    auto query_bit = [&] (int x) {
        int ans = 0;
        while (x) ans += bit[x], x -= x & (-x);
        return ans;
    };
    auto Query_bit = [&] (int l, int r) {
        return query_bit(r+1) - query_bit(l);
    };
    auto add = [&] (int r, int l, int x) {
        s.insert({r, l, x});
        insert_bit(l, (r-l+1)*x);
    };
    auto rem = [&] (int r, int l, int x) {
        s.erase({r, l, x});
        insert_bit(l, -(r-l+1)*x);
    };
    for (int i = 1; i < n; ++i) {
        if (a[i] != a[i-1]) add(i-1, lcur, a[i-1]), lcur = i;
    }
    add(n-1, lcur, a[n-1]);
	vector<int> resps;
    for (auto arr : queries) {
		int op = arr[0], l = arr[1], r = arr[2], x = arr[3];
		--l, --r;
		//cout << op << ' ' << l << ' ' << r << ' ' << x << endl;
		//cout.flush();
        //for (auto [x, y, z] : s) cout << y << ' ' << x << ' ' << z << endl;
        //cout << endl;
        //cout.flush();
        if (op == 1) { 
            auto it = s.lower_bound({l, -1, -1});
            auto [rx, lx, val] = *it;
            if (lx != l) add(l-1, lx, val);
            int div = val / x; lcur = l;
            while (true) {
                tie(rx, lx, val) = *it;
                if (lx > r) break;
                it = next(it);
                rem(rx, lx, val);
                if (val / x != div) {
                    add(lx-1, lcur, div);
                    lcur = lx, div = val / x;
                }
                if (r <= rx) {
                    if (r < rx) add(rx, r+1, val);
                    break;
                }
            }
            add(r, lcur, div);
        } else if (op == 2) {
            auto it = s.lower_bound({l, -1, -1});
            auto [rx, lx, val] = *it;
            if (val == x) l = lx;
            if (lx != l) add(l-1, lx, val);
            bool foi = 0;
            while (it != end(s)) {
                tie(rx, lx, val) = *it;
                it = next(it);
                rem(rx, lx, val);
                if (r <= rx) {
                    foi = 1;
                    if (val == x) add(rx, l, x); 
                    else {
                        add(r, l, x);
                        if (rx != r) add(rx, r+1, val); 
                    }
                    break;
                }
            }
            if (!foi) add(r, l, x);
        } else {
            int ans = Query_bit(l, r);
            auto it = s.lower_bound({l, -1, -1});
            {
                auto [rx, lx, X] = *it;
                if (lx != l) ans += (rx-l+1)*X;
            }
            it = s.lower_bound({r+1, -1, -1});
            if (it != end(s)) {
                auto [rx, lx, X] = *it;
                if (lx <= r) ans -= max(0LL, (rx-r)*X);
            }
			resps.pb(ans);
        }
        //for (auto [x, y, z] : s) cout << y << ' ' << x << ' ' << z << endl;
        //for (int i = 0; i < n; ++i) cout << Query_bit(i, i) << ' ';
        //cout << endl;
        //cout << "end of operation" << endl;
    }
	return resps;
}

vector<int> brute(int n, int q, vector<int> a, vector<array<int, 4>> queries){
	vector<int> resps;
    for (auto arr : queries) {
		int op = arr[0], l = arr[1], r = arr[2], x = arr[3];
		--l, --r;
		if (op == 1) {
			for (int i = l; i <= r; ++i) a[i] /= x;
		} 
		if (op == 2) {
			for (int i = l; i <= r; ++i) a[i] = x;
		}
		if (op == 3) { 
			int ans = 0;
			for (int i = l; i <= r; ++i) ans += a[i];
			resps.pb(ans);
		}
	}
	return resps;
}

int32_t main(){_
#ifndef gato
	int n, q; cin >> n >> q;
	vector<int> a(n);
	for (auto& x : a) cin >> x;
	vector<array<int, 4>> queries(q);
	for (auto& arr : queries) {
		cin >> arr[0] >> arr[1] >> arr[2];
		if (arr[0] != 3) cin >> arr[3];
	}
	auto ans = solve(n, q, a, queries);
	for (auto x : ans) cout << x << endl;
#else
	int t = 1;
	while (true) {
		int n = rnd(1, 30), q = rnd(1, 30);
		vector<int> a(n);
		for (auto& x : a) x = rnd(1, 1000);
		vector<array<int, 4>> queries(q);
		for (auto& arr : queries) {
			arr[0] = rnd(1, 3);
			arr[1] = rnd(1, n);
			arr[2] = rnd(arr[1], n);
			arr[3] = rnd(1, 100);
		}
        cout.flush();
		auto my = solve(n, q, a, queries);
		auto ans = brute(n, q, a, queries);
		if (my != ans) {
			cout << "Wrong answer on test " << t << endl;
			cout << n << ' ' << q << endl;
			for (auto x : a) cout << x << ' ';
			cout << endl;
			for (auto arr : queries) {
				cout << arr[0] << ' ' << arr[1] << ' ' << arr[2] << ' ';
				if (arr[0] != 3) cout << arr[3] << endl;
				else cout << endl;
			}
			cout << "Your output: ";
			for (auto x : my) cout << x << ' ';
			cout << endl;
			cout << "Answer: ";
			for (auto x : ans) cout << x << ' ';
			cout << endl;
			exit(0);
		}
		cout << "Accepted on test " << t++ << endl;
	}
#endif
}
