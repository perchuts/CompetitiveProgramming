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


void solve(){
    int n;cin>>n;
    vector<ll>v(n+1);
    for(int i=1;i<=n;i++)cin>>v[i];
    vector<vector<ll>>sp(n+1,vector<ll>(20));
    for(int j=0;(1<<j)<=n;j++){
        for(int i=1;i<=n;i++){
            if(!j){
                sp[i][j] = v[i];
                continue;
            }
            if(i+(1<<(j-1))>n)break;
            else{
                sp[i][j] = __gcd(sp[i][j-1],sp[i+(1<<(j-1))][j-1]);
            }
        }
    }
    ll ans = 0;
    for(int i=1;i<=n;i++){
        int j = i;
        // cout<<i<<endl;
        ll cur = v[i];
        int salto = 1;
        while(j<=n){
            cur = __gcd(cur,v[j]);
            // cout<<j<<" "<<cur<<endl;
            for(int k = 20;~k;k--){
                if(j+(1<<k)-1>n)continue;
                if(__gcd(cur,sp[j][k])==cur){
                    salto += (1<<k);j += (1<<k);
                    // cout<<"newj "<<j<<" "<<k<<endl;
                }
            }
            ckmax(ans,1LL*(salto-1)*cur);
            // cout<<cur<<" "<<salto<<endl;
        }
    }   
    cout<<ans<<endl;
}


int main(){_
    //freopen("in.in", "r", stdin);
    //freopen("out.out", "w", stdout);
    int t;cin>>t;
    while(t--)solve();
}