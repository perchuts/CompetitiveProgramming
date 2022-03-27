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
 
set<int>res,factors;
int n;
map<int,set<int>>dp;
map<int,bool>mark;
set<int> solve(int x){
    if(mark[x])return dp[x];
    mark[x] = 1;
    dp[x].insert(x-1);
    for(auto y:factors){
        if(y>=x)continue;
        if(x%y==0){
            set<int>cur = solve(x/y);
            for(auto z:cur)dp[x].insert(z+y-1);
        }
    }
    return dp[x];
}
 
int main(){_
    cin>>n;
    int sq = sqrt(n)+1;
    int tmp = n;
    for(int i=2;i<=sq;++i){
        if(n%i==0){
            factors.insert(i);
            factors.insert(n/i);
        }
    }    
    set<int>ans = solve(n);
    cout<<sz(ans)<<endl;
    for(auto x:ans)cout<<x<<" ";
    
}