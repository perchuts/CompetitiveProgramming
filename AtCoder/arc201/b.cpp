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

const int inf = 1e18;
const int mod = 1e9+7;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}
// smawck for max
template<class F>
std::vector<int> smawck(F f, const std::vector<int> &rows, const std::vector<int> &cols) {
    std::vector<int> ans(rows.size(), -1);
    if((int) std::max(rows.size(), cols.size()) <= 2) {
        for(int i = 0; i < (int) rows.size(); i++) {
            for(auto j : cols) {
                if(ans[i] == -1 || f(rows[i], ans[i], j)) {
                    ans[i] = j;
                }
            }
        }
    } else if(rows.size() < cols.size()) {
        // reduce
        std::vector<int> st;
        for(int j : cols) {
            while(1) {
                if(st.empty()) {
                    st.push_back(j);
                    break;
                } else if(f(rows[(int) st.size() - 1], st.back(), j)) {
                    st.pop_back();
                } else if(st.size() < rows.size()) {
                    st.push_back(j);
                    break;
                } else {
                    break;
                }
            }
        }
        ans = smawck(f, rows, st);
    } else {
        std::vector<int> newRows;
        for(int i = 1; i < (int) rows.size(); i += 2) {
            newRows.push_back(rows[i]);
        }
        auto otherAns = smawck(f, newRows, cols);
        for(int i = 0; i < (int) newRows.size(); i++) {
            ans[2*i+1] = otherAns[i];
        }
        for(int i = 0, l = 0, r = 0; i < (int) rows.size(); i += 2) {
            if(i+1 == (int) rows.size()) r = (int) cols.size();
            while(r < (int) cols.size() && cols[r] <= ans[i+1]) r++;
            ans[i] = cols[l++];
            for(; l < r; l++) {
                if(f(rows[i], ans[i], cols[l])) {
                    ans[i] = cols[l];
                }
            }
            l--;
        }
    }
    return ans;
}

// max smawck
// F(i, j, k) checks if M[i][j] <= M[i][k]
// another interpretations is: 
// F(i, j, k) checks if M[i][k] is at least as good as M[i][j]
// higher == better
// when comparing 2 columns as vectors
// for j < k, column j can start better than column k
// as soon as column k is at least as good, it's always at least as good
template<class F>
std::vector<int> smawck(F f, int n, int m) {
    std::vector<int> rows(n), cols(m);
    for(int i = 0; i < n; i++) rows[i] = i;
    for(int i = 0; i < m; i++) cols[i] = i;
    return smawck(f, rows, cols);
}

template<class T>
std::vector<T> MaxConvolutionWithConvexShape(std::vector<T> anyShape, const std::vector<T> &convexShape) {
    if((int) convexShape.size() <= 1) return anyShape;
    if(anyShape.empty()) anyShape.push_back(0);
    int n = (int) anyShape.size(), m = (int) convexShape.size();
    auto function = [&](int i, int j) {
        return anyShape[j] + convexShape[i-j];
    };
    auto comparator = [&](int i, int j, int k) {
        if(i < k) return false;
        if(i - j >= m) return true;
        return function(i, j) <= function(i, k);
    };
    const std::vector<int> best = smawck(comparator, n + m - 1, n);
    std::vector<T> ans(n + m - 1);
    for(int i = 0; i < n + m - 1; i++) {
        ans[i] = function(i, best[i]);
    }
    return ans;
}
void solve() {
    int n, W; cin >> n >> W;
    vector<vector<int>> penis(60);
    for (int i = 0; i < n; ++i) {
        int x, v; cin >> x >> v;
        penis[x].pb(v);
    }
    vector<int> dp(n+1, -inf);
    dp[0] = 0;
    for (int i = 59; ~i; --i) {
        sort(all(penis[i])), penis[i].pb(0); reverse(all(penis[i]));
        for (int j = 1; j < sz(penis[i]); ++j) penis[i][j] += penis[i][j-1]; 
        reverse(all(penis[i]));
        vector<int> ndp(n+1, -inf);
        for (int j = 0; j <= n; ++j) ckmax(ndp[min(n, 2*j)], dp[j]);
        if (W >> i & 1) for (int j = n-1; ~j; --j) ndp[j+1] = ndp[j];
        for (int j = n-1; ~j; --j) ckmax(ndp[j], ndp[j+1]);
        auto z = MaxConvolutionWithConvexShape(ndp, penis[i]);
        for (int j = sz(penis[i])-1; j < sz(z); ++j) ndp[j-sz(penis[i])+1] = z[j];
        swap(dp, ndp);
    }
    cout << *max_element(all(dp)) << endl;
}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
    while(t--) solve();
#else
    int t = 1;
    while (true) {
        int my = solve(), ans = brute();
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
