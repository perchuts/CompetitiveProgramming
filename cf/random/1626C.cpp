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
#define inf 2e18
#define mod 1000000007 //998244353
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
 
using namespace std;
 
template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }
 
ll when[101],mana[101],dp[101];
 
void solve(){
    int n;cin>>n;
    for(int i=1;i<=n;i++){
        cin>>when[i];
    }
    for(int i=1;i<=n;i++){
        cin>>mana[i];
    }
 
    ll cur = 0;
 
    for(int i=1;i<=n;i++){
        if(mana[i]<=cur+when[i]-when[i-1]){
            dp[i] = dp[i-1]+(2LL*cur+1LL+when[i]-when[i-1])*(when[i]-when[i-1])/2;
            cur+=when[i]-when[i-1];
        }else{
            dp[i] = inf;
        } 
        ll st = when[i]-mana[i]+1LL;
        for(int j=i-1;j>=0;j--){
            if(when[j]<st){
                if(ckmin(dp[i],dp[j]+(2LL+when[i]-st)*(when[i]-st+1LL)/2)){
                    cur = when[i]-st+1LL;
                }
                break;
            }else{
                ckmin(st,when[j]-mana[j]+1LL);
            }
        }
    }
 
    cout<<dp[n]<<endl;
 
}
 
 
int main(){_
    //freopen("in.in", "r", stdin);
    //freopen("out.out", "w", stdout);
    int t;cin>>t;
    while(t--)solve();
}