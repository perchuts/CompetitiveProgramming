#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define int ll
#define pb push_back

using namespace std;

using ll = long long;

int ncr[2000][2000], pt[11][2000];

int32_t main() {_
    string s; cin >> s;
	//int N = stoi(s);
	//int real = 0;
	const int mod = 1e9+7;
	//for (int i = 1; i <= N; ++i) {
	//	string z = to_string(i);
	//	sort(begin(z), end(z));
	//	reverse(begin(z), end(z));
	//	while (z.back() == '0') z.pop_back();
	//	reverse(begin(z), end(z));
	//	real += stoi(z);
	//	real %= mod;
	//}
	//cout << real << endl;
    for (int i = 0; i < 2000; ++i) {
        for (int j = 0; j <= i; ++j) {
            if (j == 0 or j == i) ncr[i][j] = 1;
            else ncr[i][j] = (ncr[i-1][j] + ncr[i-1][j-1]) % mod;
        }
    }
    for (int i = 0; i <= 10; ++i) {
        pt[i][0] = 1;
        for (int j = 1; j < 2000; ++j) {
            pt[i][j] = pt[i][j-1] * i % mod;
        }
    }
    int n = s.size(), ans = 0, z = 1;
    vector<int> fixado(10);
    for (int quebra = 0; quebra < n; ++quebra) {
        for (int d = 0; d < s[quebra] - '0'; ++d) {
            fixado[d]++;
            int mn = 0;
            for (int d2 = 9; d2; --d2) {
                mn += fixado[d2];
                int tot = 0;
                for (int i = mn + n - quebra - 1; i >= mn and i; --i) {
                    tot = (tot + ncr[n-quebra-1][i-mn] % mod * pt[10-d2][i-mn] % mod * pt[d2][n-quebra-1-i+mn]) % mod;
                    ans = (ans + pt[10][i-1] * tot % mod) % mod;
                }
                for (int i = 1; i < mn; ++i) ans = (ans + pt[10][i-1] * pt[10][n-quebra-1]) % mod;
            }
            fixado[d]--;
        }
        fixado[s[quebra]-'0']++;
    }
    sort(begin(s), end(s));
    for (int i = n-1; ~i; --i) ans = (ans + (s[i] - '0') * z) % mod, z = 10 * z % mod;
    cout << ans << endl;
}

