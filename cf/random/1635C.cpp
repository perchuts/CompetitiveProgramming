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

//last item will be the biggest and so on
ll v[2*maxn];
void solve(){
    int n;cin>>n;
    for(int i=1;i<=n;++i)cin>>v[i];
    if(v[n-1]>v[n]||v[n]<0){
        bool ok = 1;
        for(int i=1;i<n;++i)if(v[i]>v[i+1])ok=0;
        cout<<(ok ? 0 : -1)<<endl;
        return;
    }
    int m = 0;
    vector<pair<ii,int>>op;
    for(int i=1;i<n-1;++i){
        if(v[i] != v[n-1]-v[n]){
            op.pb({{i,n-1},n});
        }
    }
    cout<<sz(op)<<endl;
    for(auto [a,b]:op){
        auto [x,y] = a;
        cout<<x<<" "<<y<<" "<<b<<endl;
    }
}


int main(){_
    //freopen("in.in", "r", stdin);
    //freopen("out.out", "w", stdout);
    int t;cin>>t;
    while(t--)solve();
}