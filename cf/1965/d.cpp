#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
//#define endl '\n'
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

mt19937 rng(69);

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

vector<int> solve(int n, vector<int>& v) {
    map<int, int> freq;
    for (auto x : v) freq[x]++;
    sort(all(v));
    vector<int> odd;
    for (auto [val, p] : freq) {
        //cout << val << " " << p << endl;
        if (p % 2 == 1) odd.pb(val);
    }
    // 2 casos: apaguei alguma soma que eh subarray sum de algum subarray central
    // apaguei alguma soma que nao eh subarray sum de algum subarray central
    // no primeiro caso, vamos ter menos caras impares
    // no segundo caso vamos ter mais caras impares
    auto test = [&] (vector<int> a) {
        auto f2 = freq;
        int bad = 0;
        for (int i = 0; i < n; ++i) for (int j = i, s = 0; j < n; ++j) {
            s += a[j];
            bad += (f2[s] <= 0);
            f2[s]--;
        }
        return (bad == 1);
    };
    reverse(all(odd));
    if (sz(odd) < (n+1)/2) {
        // apaguei subarray sum central
        vector<int> b(n-2);
        for (int i = 0; i < (n-3)/2; ++i) b[i] = b[n-3-i] = (odd[i]-odd[i+1])/2;
        if (n % 2 == 1) b[(n-2)/2] = odd.back();
        else b[(n-2)/2] = b[(n-3)/2] = odd.back()/2;
        auto f = freq;
        for (int i = 0; i < n-2; ++i) {
            int s = 0;
            for (int j = i; j < n-2; ++j) {
                s += b[j];
                f[s]--;
            }
        }
        int missing = -1, big = -1;
        for (auto [val, qt] : f) {
            if (qt != 0 and missing == -1) missing = val;
            if (qt != 0) big = val;
        }
        // we know that the one missing is the first element!
        if (odd[0] != v.back()) {
            vector<int> ans;
            ans.pb(missing);
            for (auto x : b) ans.pb(x);
            ans.pb(missing);
            return ans;
        }
        int S = odd[0], ps = 0;
        //cout << "S = " << S << " big = " << big << " missing = " << missing << endl;
        //cout << "b: ";
        //for (auto x : b) cout << x << " ";
        //cout << endl;
        // smaller comes before
        vector<int> ans;
        for (int i = 0; i < (n-2)/2; ++i) {
            if (max(ps + missing, S - (ps + missing)) == big and b[i] > missing) {
                auto a = b;
                //cout << "i = " << i << endl;
                a.insert(begin(a) + i, missing);
                a.insert(begin(a) + (n-1)-i, missing);
                a[i+1] -= missing;
                a[n-1-i-1] -= missing;
                //cout << "a: ";
                //for (auto x : a) cout << x << " ";
                //cout << endl;
                if (test(a)) ans = a;
            }
            ps += b[i];
        }
        ps = 0;
        for (int i = 0; i < (n-2)/2; ++i) {
            if (b[i] > missing and max(ps + b[i] - missing, S - (ps + b[i] - missing)) == big) {
                auto a = b;
                a.insert(begin(a) + i, b[i] - missing);
                a.insert(begin(a) + (n-1)-i, b[i] - missing);
                a[i+1] = missing;
                a[n-1-i-1] = missing;
                //cout << "testing: ";
                //for (auto x : a) cout << x << " ";
                //cout << endl;
                if (test(a)) ans = a;
            }
            ps += b[i];
        }
        if (n % 2) {
            // can be the central elements as well!
            int z = b[(n-2)/2];
            if (z % 2 == missing % 2 and z > missing) {
                int other = (z-missing)/2;
                vector<int> a(n);
                for (int i = 0; i < (n-2)/2; ++i) a[i] = a[n-1-i] = b[i];
                a[(n-2)/2] = a[n-1-(n-2)/2] = other;
                a[n/2] = missing;
                if (test(a)) ans = a;
            }
            if (2 * missing < z) {
                vector<int> a(n);
                for (int i = 0; i < (n-2)/2; ++i) a[i] = a[n-1-i] = b[i];
                a[(n-2)/2] = a[n-1-(n-2)/2] = missing;
                a[n/2] = z - 2 * missing;
                if (test(a)) ans = a;
            }
        }
        assert(!ans.empty());
        return ans;
    }
    vector<int> ans;
    int S = v.back();
    vector<int> zz(2);
    for (int i = 0; i < sz(odd); ++i) zz[odd[i]&1]++;
    int foi = 0;
    for (int i = 0; i < sz(odd); ++i) {
        if (zz[odd[i]&1] == 1) odd.erase(begin(odd)+i), foi = 1;
    }
    auto build = [&] () {
        int t = n + 2 * (1 - foi);
        vector<int> ans(t);
        for (int i = 0; i < sz(odd)-1; ++i) ans[i] = ans[t-1-i] = (odd[i] - odd[i+1])/2;
        if (n & 1) ans[t/2] = odd.back();
        else ans[t/2] = ans[t/2-1] = odd.back()/2;
        return ans;
    };
    vector<int> b = build();
    if (foi) return b;
    map<int, int> f2;
    for (int i = 0; i < n+2; ++i) {
        int s = 0;
        for (int j = i; j < n+2; ++j) {
            s += b[j];
            f2[s]++;
        }
    }
    for (auto [x, y] : freq) f2[x] -= y;
    int big = -1;
    for (auto [x, y] : f2) {
        assert(y >= 0);
        if (y > 0) big = x;
    }
    int ps = 0;
    //cout << "odd: ";
    //for (auto x : odd) cout << x << " ";
    //cout << endl;
    //cout << "b: ";
    //for (auto x : b) cout << x << " ";
    //cout << endl;
    //cout << "big = " << big << endl;
    for (int i = 0; i < n+2; ++i) {
        if (ps + b[i] > big) {
            //cout << "i = " << i << endl;
            auto a = b;
            //cout << "a = ";
            //for (auto x : a) cout << x << " ";
            //cout << endl;
            a[i-1] += a[i];
            //cout << "a = ";
            //for (auto x : a) cout << x << " ";
            //cout << endl;
            a.erase(begin(a)+max((n+1-i), i)), a.erase(begin(a)+min((n+1-i), i));
            //cout << "a = ";
            //for (auto x : a) cout << x << " ";
            //cout << endl;
            a[n+1-i] = a[i-2];
            //cout << "i = " << i << endl;
            //for (auto x : a) cout << x << ' ';
            //cout << endl;
            if (test(a)) ans = a;
            break;
        }
        ps += b[i];
    }
    if (n % 2) {
        auto a = b;
        a[(n+1)/2] += 2 * a[(n+1)/2-1];
        a.erase(begin(a)+(n+1)/2+1);
        a.erase(begin(a)+(n+1)/2-1);
        if (test(a)) ans = a;
    }
    return ans;
}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<int> v(n*(n+1)/2-1);
        for (auto& x : v) cin >> x;
        auto ans = solve(n, v);
        for (auto x : ans) cout << x << " ";
        cout << endl;
    }
#else
    int t = 1;
    while (true) {
        int n = rnd(3, 80);
        vector<int> a(n);
        for (int i = 0; i < (n+1)/2; ++i) a[i] = a[n-1-i] = rnd(1, 30);
        vector<int> v;
        int X = rnd(0, n-1), Y = rnd(X, n-1);
        for (int i = 0; i < n; ++i) {
            int s = 0;
            for (int j = i; j < n; ++j) {
                s += a[j];
                if (i != X or j != Y) v.pb(s);
            }
        }
        //v.erase(begin(v) + rnd(0, sz(v)-1));
        //cout << "certificate: ";
        //for (auto x : a) cout << x << " ";
        //cout << endl;
        //cout << n << endl;
        //for (auto x : v) cout << x << " ";
        //cout << endl;
        //cout << flush;
        auto my = solve(n, v);
        bool ok = (sz(my) == n);
        if (ok) {
            for (int i = 0; i < n; ++i) ok &= (a[i] == a[n-1-i]);
            map<int, int> f;
            for (auto x : v) f[x]++;
            int qt = 0; 
            for (int i = 0; i < n; ++i) {
                int s = 0;
                for (int j = i; j < n; ++j) {
                    s += my[j];
                    qt += (f[s] <= 0);
                    f[s]--;
                }
            }
            ok &= (qt == 1);
        }
        if (!ok) {
            cout << "Wrong answer on test " << t << endl;
            for (auto x : my) cout << x << " ";
            cout << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
