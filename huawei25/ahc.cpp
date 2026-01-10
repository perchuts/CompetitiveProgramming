#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int long long

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ii = pair<int,int>;
using iii = tuple<int,int,int>;

const int inf = 2e9+1;
const int mod = 1e9+7;
const int n = 26;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

int c[n], s[365][n], d;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
      uniform_int_distribution<int> uid(l, r);
      return uid(rng);
}

double rnd_d(double l, double r) {
      uniform_real_distribution<double> uid(l, r);
      return uid(rng);
}

vector<int> random(int d) {
      vector<int> solution(d), lst(n);
      for (int i = 0; i < d; ++i) {
            ii best = {0, -1};
            for (int j = 0; j < n; ++j) ckmax(best, make_pair(c[j] * (i - lst[j]) + s[i][j], j));
            solution[i] = best.second, lst[best.second] = i;
      }
      return solution;
}

const double a = 0.99999;

double last = 1e9;
// double eps = 1e-8;

double temperature(int tries, int limit) { return last *= a; }

int lst[n];

int cost(vector<int> x) {
      int ans = 0, rem = 0, t = 0;
      for (int i = 0; i < n; ++i) lst[i] = 0, t += c[i];
      for (int i = 0; i < d; ++i) ans += s[i][x[i]], rem -= (i - lst[x[i]] - 1) * c[x[i]] - t, ans -= rem, lst[x[i]] = i;
      return ans;
}

vector<int> viz(vector<int>& s) {
      int a = rnd(0, d - 1), b = rnd(0, n - 1);
      vector<int> t = s;
      t[a] = b;
      return t;
}     

bool change(int x, int y, double t) {
      if (y > x) return true;
      double p = exp((y - x) / t), k = rnd_d(0, 1);
      return p >= k;
}

int32_t main(){_
      cin >> d;
      for (int i = 0; i < n; ++i) cin >> c[i];
      for (int i = 0; i < d; ++i) for (int j = 0; j < n; ++j) cin >> s[i][j];
      auto start = chrono::steady_clock::now();
      auto get_time = [&]() {
		auto curr = chrono::steady_clock::now();
		return int32_t(chrono::duration_cast<chrono::milliseconds>(curr - start).count());
	};
      auto solution = random(d); auto s = solution;
      int tries = 0, limit;
      while (get_time() <= 1950) {
            long double t = temperature(tries, limit);
            if (cost(s) > cost(solution)) solution = s;
            auto prox = viz(solution);
            if (change(cost(s), cost(prox), t)) s = prox;
            tries++;
      }
      for (auto x : solution) cout << x + 1 << endl;
}
