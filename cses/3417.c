#include <stdio.h>
#include <stdlib.h>
int dir[3000][3000][4];
int upds[3000][3000];
int ptr[3000];
int bit[3001];
long long ans[26];
char grid[3000][3000];
int lim;
void insert(int x, int k) {
	while (x <= lim) bit[x] += k, x += x & (-x);
}
int query(int x) {
	int ans = 0;
	while (x) {
		ans += bit[x];
		x -= x & (-x);
	}
	return ans;
}
int max(int a, int b) {
	if (a <= b) return b;
	return a;
}
int min(int a, int b) {
	if (a <= b) return a;
	return b;
}
void solve(){
	int n, k;
	scanf("%d %d", &n, &k);
	for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) scanf("%c", &grid[i][j]);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == 0 || grid[i][j] != grid[i-1][j]) dir[i][j][0] = 1;
            else dir[i][j][0] = 1 + dir[i-1][j][0];
            if (j == 0 || grid[i][j] != grid[i][j-1]) dir[i][j][1] = 1;
            else dir[i][j][1] = 1 + dir[i][j-1][1];
        }
    }
    for (int i = n-1; ~i; --i) {
        for (int j = n-1; ~j; --j) {
            if (j == n-1 || grid[i][j] != grid[i][j+1]) dir[i][j][2] = 1;
            else dir[i][j][2] = 1 + dir[i][j+1][2];
            if (i == n-1 || grid[i][j] != grid[i+1][j]) dir[i][j][3] = 1;
            else dir[i][j][3] = 1 + dir[i+1][j][3];
        }
    }
    for (int diag = -n+1; diag < n; ++diag) {
        int pos = 0, alive = 0;
        lim = n-abs(diag);
        for (int i = max(0, diag), j = i - diag; max(i, j) < n; ++i, ++pos, ++j) {
            alive -= ptr[pos] - 1;
            for (int k = 0; k < ptr[pos]; ++k) insert(upds[pos][k], -1);
            insert(pos+1, 1);
            int mx_esq = min(dir[i][j][0], dir[i][j][1]);
            int mx_dir = min(dir[i][j][2], dir[i][j][3]); 
            if (pos+mx_dir <= lim) upds[pos+mx_dir][ptr[pos+mx_dir]++] = (pos+1);
            ans[grid[i][j]-'A'] += alive - query(pos-mx_esq+1);
        }
        for (int i = 0; i <= lim; ++i) ptr[i] = bit[i] = 0;
    }
    for (int i = 0; i < k; ++i) printf("%lld\n", ans[i]);
}

int main(){
	solve();
}
