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
#define eliminate 1
#define match 0
using namespace std;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

int dp[105][105][5];
bool mark[105][105][5];
vector<int>v;
int n,k;
int solve(int i,int j,int x){
    if(i>n||i>j)return 0;
    x = min(k-1,x);
    if(mark[i][j][x])return dp[i][j][x];
    mark[i][j][x] = 1;
    dp[i][j][x] = inf;
    if(x<k-1)ckmin(dp[i][j][x],solve(i,j,x+1)+1);
    else ckmin(dp[i][j][x],solve(i+1,j,0));
    for(int w=i+1;w<=j;++w){
        if(v[w]!=v[i])continue;
        ckmin(dp[i][j][x],solve(i+1,w-1,0)+solve(w,j,x+1));
    }
    return dp[i][j][x];    
}

int main(){_
    cin>>n>>k;
    v.resize(n+1);
    for(int i=1;i<=n;++i)cin>>v[i];
    cout<<solve(1,n,0)<<endl;
}