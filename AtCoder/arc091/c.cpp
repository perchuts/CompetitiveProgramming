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

void solve() {
    int n, a, b; cin >> n >> a >> b;
    // talvez entender que #LIS = minimum number of partitioning P in decreasing subsequences ajude
    //  >= is trivial. WLOG the subsequence consisting of first elements of each subseq. is an inc. subseq.
    //  how to <=
    //  trivial as well: each number in a list must be in a distinct subsequence.
    //  now LDS = minumum # of inc subseqs to cover array
    //  then LDS * LIS >= n!!
    if (a * b < n) {
        cout << -1 << endl;
        return;
    }
    // LIS and LDS can share at most one element.
    if (a + b > n+1) {
        cout << -1 << endl;
        return;
    }
    // now i claim these conditions are also sufficient for the existence of such permutation.
    // let a >= sqrt(N). suppose the problem is asking only for the existence of a permutation with #LIS = a. 
    // want to do something like 3 2 1 6 5 4 9 8 7 12 11 10 etc
    // each block with size <= x
    // k blocks
    // a blocks
    // first block with size b
    for (int i = b; i >= 1; --i) cout << i << ' ';
    // (n-b)/(a-1) <= b
    // n-b <= ab - b
    // n-b >= a-1 -> nice
    int cur = b+1;
    for (int g = 0; g < a-1; ++g) {
        int st = cur + (n-b)/(a-1) + (g < (n-b) % (a-1)) - 1;
        for (int i = st; i >= cur; --i) cout << i << ' ';
        cur = st+1;
    }
    cout << endl;
}

int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
    while(t--) solve();
#else
    int t = 1;
    while (true) {
        int my = solve(), ans = brute();
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
