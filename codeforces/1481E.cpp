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
const int maxn = 5e5+100;
 
template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }
 
int v[maxn],dp[maxn], qnt[maxn], primeira[maxn], ultima[maxn];
 
int main(){_
    int n;cin>>n;
    for(int i=1;i<=n;++i){
        cin>>v[i];
        if(!primeira[v[i]])primeira[v[i]] = i;
        ultima[v[i]] = i;
    }
    for(int i=n;i>=1;--i){
        ++qnt[v[i]];
       if(i!=primeira[v[i]]){
           dp[i] = qnt[v[i]];
       }else dp[i] = qnt[v[i]] + dp[ultima[v[i]]+1];
       ckmax(dp[i],dp[i+1]);
    }   
    cout<<n-dp[1]<<endl; 
}