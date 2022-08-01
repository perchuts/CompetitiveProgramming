#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define int ll
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
 
int cmp[maxn], dp[maxn], bit[maxn], n;
 
void insert(int x,int d){
    for(;x<=n;x+=x&(-x))ckmax(bit[x],d);
}
 
int query(int x){
    int resp = -inf;
    while(x){
        ckmax(resp,bit[x]);
        x-=x&(-x);
    }
    return resp;
}
 
void solve(){
    cin>>n;
    vector<int>a(n+1),pr(n+1);
    vector<ii>v;
    for(int i=1;i<=n;++i){
        cin>>a[i], pr[i] = pr[i-1]+a[i];
        v.pb({pr[i],-i});
    }
    sort(all(v));
    for(int i=0;i<n;++i)cmp[-v[i].second] = i+1, bit[i+1] = -inf;
    for(int i=1;i<=n;++i){
        dp[i] = dp[i-1] + (a[i]<0?-1:a[i]>0);
        ckmax(dp[i],query(cmp[i])+i);
        if(pr[i]>0)dp[i] = i;
        insert(cmp[i],dp[i]-i);
    }
    cout<<dp[n]<<endl;
}
 
 
int32_t main(){_
    //freopen("in.in", "r", stdin);
    //freopen("out.out", "w", stdout);
    int t;cin>>t;
    while(t--)solve();
}