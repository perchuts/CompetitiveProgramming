#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

int pot(int a, int b) {
	int ans = 1;
	while (b) {
		if (b & 1) ans = ans * a;
		a = a * a;
		b /= 2;
	}
	return ans;
}

using T = array<ll, 2>;

T operator +(const T& a, const T& b) {
	return T{a[0] + b[0], a[1] + b[1]};
}

T operator *(const T& a, const T& b) {
	return T{a[0] * b[0] - a[1] * b[1],
		a[0] * b[1] + a[1] * b[0] - a[1] * b[1]};
}

T operator /(const T& a, const int& b) {
	return T{a[0] / b, a[1] / b};
}

T val(int x) { return {x, 0}; }

vector<T> FWHT(vector<T> f, int b, T g, bool inv = false) {
	int n = f.size();

	vector<T> w(b);
	w[1] = g;
	for (int i = 2; i < b; i++) w[i] = w[i - 1] * g;
	w[0] = w[b - 1] * g;

	if (inv) reverse(w.begin() + 1, w.end());
	for (int pot = 1; pot < n; pot *= b) {
		for (int i = 0; i < n; i++) if (!(i / pot % b)) {
			vector<T> res(b);
			for (int j = 0; j < b; j++) {
				for (int k = 0; k < b; k++)
					res[j] = res[j] + w[j * k % b] * f[i + k * pot];
				if (inv) res[j] = res[j] / b;
			}
			for (int j = 0; j < b; j++) f[i + j * pot] = res[j];
		}
	}

	return f;
}

T g = {0, 1};
vector<T> conv(vector<T> a, vector<T> b) {
	a = FWHT(a, 3, g, false);
	b = FWHT(b, 3, g, false);
	for (int i = 0; i < a.size(); i++) {
		a[i] = a[i] * b[i];
	}
	a = FWHT(a, 3, g, true);
	return a;
}

int32_t main() {
	fast_io;

	int n, m;
	cin >> n >> m;

	const int M = pot(3, m);

	vector<string> input(n);
	for (int i = 0; i < n; i++) {
		cin >> input[i];
	}

	auto repr = [&] (string s) -> int {
		int x = 0;
		for (int j = 0; j < m; j++) {
			x = x * 3 + (s[j] - '1');
		}
		return x;
	};
	auto op = [&] (string s, string t) {
		string ret(m, '0');
		for (int j = 0; j < m; j++) {
			int u = s[j] - '1';
			int v = t[j] - '1';
			ret[j] = '1' + ((u + v) % 3);
		}
		return ret;
	};

	vector<int> a;
	for (int i = 0; i < n; i++) {
		a.push_back(repr(input[i]));
	}

	//cout << M << endl;
	//cout.flush();

	vector<T> f(M), fl(M), ruim(M);
	for (int i = 0; i < n; i++) {
		assert(a[i] < M);
		f[a[i]] = f[a[i]] + val(1);
		string s2 = op(input[i], input[i]);
		int j = repr(s2);
		fl[j] = fl[j] + val(1);
		int k = repr(op(s2, input[i]));
		ruim[k] = ruim[k] + val(1);
	}


	auto tot = conv(conv(f, f), f);
	//auto convff = conv(f, f);
	//auto ff = conv(fl, f);
	auto ff3 = conv(fl, f);
	for (auto &i : ff3) i = i * val(-3);
	auto ruim2 = ruim;
	for (auto &i : ruim2) i = i * val(2);

	//cout << "a: ";
	//for (int i : a) cout << i << " ";
	//cout << endl;
	//cout << "f: ";
	//for (auto i : f) cout << i[0] << " ";
	//cout << endl;
	//cout << "ff: ";
	//for (auto i : convff) cout << i[0] << " ";
	//cout << endl;
	//cout << "tot: ";
	//for (int j = 0; j < M; j++) {
	//	cout << tot[j][0] << " \n"[j + 1 == M];
	//}
	//cout << "ff: ";
	//for (int j = 0; j < M; j++) {
	//	cout << ff[j][0] << " \n"[j + 1 == M];
	//}
	//cout << "ruim: ";
	//for (int j = 0; j < M; j++) {
	//	cout << ruim[j][0] << " \n"[j + 1 == M];
	//}

	auto ans = (tot[0] + ff3[0] + ruim[0] * val(2));
	int ret = ans[0];
	cout << ret/6 << endl;
}
