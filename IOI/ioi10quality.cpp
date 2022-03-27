#include <bits/stdc++.h>
#define maxn (int)(1e5+51)
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define ll long long
#define pb push_back
#define ull unsigned long long
#define ii pair<int,int>
#define iii tuple<int,int,int>
#define inf 2000000001
#define mod 1000000007 //998244353
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

using namespace std;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }
int ans,n,m,H,W;
int grid[3001][3001],pr[3001][3001];

int rect(int x1,int y1,int x2,int y2){
    return pr[x2][y2] - pr[x1-1][y2] - pr[x2][y1-1] + pr[x1-1][y1-1];
}

bool possible(int x,int q[3001][3001]){
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)grid[i+1][j+1] = (q[i][j]<=x?1:-1);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            pr[i][j] = pr[i-1][j] + pr[i][j-1] - pr[i-1][j-1] + grid[i][j];
    for(int i=0;i+H<=n;i++){
        for(int j=0;j+W<=m;j++){
            if(rect(i+1,j+1,i+H,j+W)>0)return true;
        }
    }
    return false;
}



int rectangle(int r,int c,int h,int w,int q[3001][3001]){
    ans = inf,n=r,m=c,H=h,W=w;
    int le = 1, ri = n*m, ans = 1;
    while(le<=ri){
        int md = le + (ri-le+1)/2;
        if(possible(md, q))ans = md,ri = md - 1;
        else le = md + 1;
    }    
    return ans;
}