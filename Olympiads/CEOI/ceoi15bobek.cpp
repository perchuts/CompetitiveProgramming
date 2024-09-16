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
 
int n;
ll m, c[50];    
 
vector<ll>rsums;
 
ll generate(int x,int flag){
    int st = ((n+1)/2)*flag;
    ll sum = 0;
    while(x){
        if(x&1)sum += c[st];
        st++;
        x>>=1;
    }
    return sum;
}
 
int main(){_
    cin>>n>>m;
    for(int i=0;i<n;++i)cin>>c[i];
 
    for(int i=0;i<(1<<(n/2));++i)rsums.pb(generate(i,1));
    sort(all(rsums));
    ll ans = 0;
 
    auto binsearch = [&](ll x){
        int l = 0, r = sz(rsums)-1, ans = -1;
        while(l<=r){
            int md = l + (r-l+1)/2;
            if(rsums[md]<=x)ans = md, l = md + 1;
            else r = md - 1;
        }
        return ans+1;
    };
 
    for(int i=0;i<(1<<((n+1)/2));++i){
        ll lsum = generate(i,0);
        ans += 1LL*binsearch(m-lsum);
    }
 
    cout<<ans<<endl;
}