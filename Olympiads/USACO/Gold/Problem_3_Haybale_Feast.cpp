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

ll taste[maxn],spice[maxn];
int main(){_
    freopen("hayfeast.in", "r", stdin);
    freopen("hayfeast.out", "w", stdout);
    ll n,m;cin>>n>>m;

    for(int i=1;i<=n;i++)
        cin>>taste[i]>>spice[i];
    
    int ans = inf,r=0;
    ll sum = 0;
    multiset<ll>s;
    for(int l=1;l<=n;l++){
        while(sum<m&&r<n)s.insert(spice[++r]),sum+=taste[r];
        if(sum>=m)ckmin(ans,*s.rbegin());
        s.erase(s.find(spice[l]));
        sum-=taste[l];
    }
    cout<<ans<<endl;

    
}