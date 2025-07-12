#include <bits/stdc++.h>
//#define gato
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
typedef long long ll;

char f[10][3];

string ask(string a, string b) {
    int n = a.size();
    int carry = 0;
    string result;
    for (int i = n-1; ~i; --i) {
        int x, y;
        for (int j = 0; j < 3; ++j) {
            if (f[n-1-i][j] == a[i]) x = j;
            if (f[n-1-i][j] == b[i]) y = j;
        }
        int z = x + y + carry;
        result += char('0' + (z % 3));
        carry = z / 3;
    }
    if (carry) result += '1';
    else result += '0';
    for (int i = 0; i < n; ++i) result[i] = f[i][result[i]-'0'];
    reverse(begin(result), end(result));
    return result;
}

vector<vector<int>> solve(int n){
#ifndef gato
    cout << "? ";
    for(int i=0;i<n;i++) cout << "0";
    cout << " ";
    for(int i=0;i<n;i++) cout << "1";
    cout << endl;
#endif
    string c;
#ifndef gato
	cin >> c;
#else
    string a(n, '0'), b(n, '1');
    c = ask(a, b);
#endif
    reverse(begin(c), end(c));
    vector<pair<int, int>> vals(n);
    vector<vector<int>> ans(n, vector<int>(3, -1));
    int carry = 0;
    for (int i = 0; i < n; ++i) {
        if (carry == 0) {
            if (c[i] == '2') {
                carry = 1;
                vals[i] = {2, 0};
            } else {
                carry = 0;
                vals[i] = {1-c[i]+'0', 0};
            }
        } else {
            if (c[i] == '2') {
                carry = 0;
                vals[i] = {2, 2};
            } else {
                carry = 1;
                vals[i] = {1-c[i]+'0', 2};
            }
        }
    }
#ifndef gato
    cout << "? ";    
    for (int i = n-1; ~i; --i) cout << (vals[i].first ? 0 : 1);
    cout << ' ';
    for (int i = n-1; ~i; --i) cout << (vals[i].first ? 0 : 1);
    cout << endl;
    cin >> c;
#else
    a = string(n, '0');
    for (int i = 0; i < n; ++i) a[n-1-i] = (vals[i].first ? '0' : '1');
    c = ask(a, a);
#endif
    // carry = 0, descobri o zero
    // A + A = B. tem carry <=> A = 2
    // carry = 1, descobri o zero
    // A + A = 0 se A = 1, A + A = A se A = 2. carry em ambos os casos
    // carry = 0, descobri o dois
    // A + A = 2 se A = 1, A + A = A se A = 0. sem carry em ambos os casos
    // carry = 1, descobri o dois
    // A + A = B. tem carry <=> A = 1
    reverse(begin(c), end(c));
    carry = (c[n] == '1');
    for (int i = n-1; ~i; --i) {
        ans[i][vals[i].first] = vals[i].second;
        char asked = '0' + (vals[i].first ? 0 : 1);
        char know = '0' + vals[i].first;
        int nc = (c[i] != asked and c[i] != know);
        if (vals[i].second == 0) nc ^= 1;
        if (vals[i].second) {
            if (nc) ans[i][asked-'0'] = (carry);
            else ans[i][asked-'0'] = (c[i] == know);
        } else {
            if (!nc) ans[i][asked-'0'] = (carry ? 2 : 1);
            else ans[i][asked-'0'] = (c[i] == know ? 1 : 2);
        }
        int sum = 0;
        for (int j = 0; j < 3; ++j) sum += (ans[i][j] == -1 ? 0 : ans[i][j]);
        for (int j = 0; j < 3; ++j) if (ans[i][j] == -1) ans[i][j] = 3 - sum;
        vector<int> rev(3);
        for (int j = 0; j < 3; ++j) rev[ans[i][j]] = j;
        ans[i] = rev;
        carry = nc;
    }
#ifndef gato
    cout << "! ";
    for (int i = 0; i < n; ++i) cout << ans[i][0] << ans[i][1] << ans[i][2] << " ";
    cout << endl;
#endif
    return ans;
}

mt19937 rng(time(0));

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

int32_t main() {
	fast_io;
#ifndef gato
	int t; cin >> t;
	while(t--) {
        int n; cin >> n;
        solve(n);
    }
#else
    int t = 1;
    while (true) {
        int n = rnd(1, 10);
        vector<char> p = {'0', '1', '2'};
        for (int i = 0; i < n; ++i) {
            shuffle(begin(p), end(p), rng);
            for (int j = 0; j < 3; ++j) f[i][j] = p[j];
        }
        auto my = solve(n);
        bool ok = true;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (char('0' + my[i][j]) != f[i][j]) { ok = 0; break; }
            }
        }
        if (!ok) {
            cout << "Wrong answer on test " << t << endl;
            cout << "Answer: ! ";
            for (int i = 0; i < n; ++i) cout << f[i][0] << f[i][1] << f[i][2] << ' ';
            cout << endl;
            cout << "Your output: ! ";
            for (int i = 0; i < n; ++i) cout << my[i][0] << my[i][1] << my[i][2] << ' ';
            cout << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif

}
