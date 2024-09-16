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

//dp[bitmask] = best way to arrive at bitmask state.
//if i bits are on in the current bitmask, we have i! possibilities of probabilities
//need to optimize this.
//ans should be dp[2^n-1].
//actually pretty easy one.
//just iterate over all set bits and check best solution recursively with memoization
double prob[21][21],dp[1<<20];
int n;
double solve(int mask){
    if(dp[mask]!=-1)return dp[mask];
    int mission = __builtin_popcount(mask);
    if(!mission)return dp[mask] = 1;
    for(int i=0;i<n;i++){
        if(mask&(1<<i)){
            ckmax(dp[mask],solve(mask&(~(1<<i)))*prob[mission][i+1]);
        }
    }
    return dp[mask];
}


int main(){_
    cin>>n;    
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>prob[i][j];
            prob[i][j]/=100;
        }
    }
    for(int i=0;i<(1<<n);i++)dp[i] = double(-1);
    cout<<fixed<<setprecision(7)<<solve((1<<n)-1)*100<<endl;
}