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
#define inf (int)(2e9+1)
#define mod (int)(1e9+7)

using namespace std;
ll v[2*maxn],p[2*maxn];

ll rightdiv(ll x,ll y){
    if(x>=0)return x/y;
    return (x-y+1)/y;
}
int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    int t;cin>>t;
    while(t--){
        ll n;cin>>n;
        ll k;cin>>k;
        for(int i=0;i<n;i++){
            cin>>v[i];    
        }
        sort(v,v+n);
        for(int i=0;i<n;i++){
            if(i)p[i]=p[i-1]+v[i];
            else p[i]=v[i];
        }
        if(p[n-1]<=k){
            cout<<0<<endl;continue;
        }
        ll ans = p[n-1]-k;
        for(ll i=0;i<n-1;i++){
            ll l = max(0LL,rightdiv(p[i]-k-v[0]+n-i-1,n-i)+v[0]);
                
            
            l += (n - i - 1LL);
            ans = min(ans, l);
        }
        cout<<endl;
        cout<<ans<<endl;
        
    }   
}