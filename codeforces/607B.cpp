#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
 
using namespace std;
 
using ll = long long;
using ull = unsigned long long;
using ii = pair<int,int>;
using iii = tuple<int,int,int>;
 
const int inf = 2e9+1;
const int mod = 1e9+7;
const int maxn = 1e5+100;
 
template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }
 
int dp[505][505], v[505];
int main(){_
    int n;cin>>n;
    for(int i=1;i<=n;++i)cin>>v[i];
    for(int i=n;i>=1;--i){
        for(int j=i;j<=n;++j){
            if(i==j)dp[i][j] = 1;
            else{
                dp[i][j] = min(dp[i+1][j],dp[i][j-1]) + 1;
                //vou combinar o i com o k
                for(int k=i+1;k<=j;++k){
                    if(v[i]==v[k]){
                        ckmin(dp[i][j],max(1,dp[i+1][k-1])+dp[k+1][j]);
                    }
                }
            }
        }
    }
    cout<<dp[1][n]<<endl;
}