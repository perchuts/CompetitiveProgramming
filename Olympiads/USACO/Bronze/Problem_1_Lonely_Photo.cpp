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
vector<ll>pg,ph;
int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    int n;
    string s;cin>>n>>s;
    ll ans=0;
    ph.pb(-1),pg.pb(-1);
    for(int i=0;i<n;i++){
        if(s[i]=='H')ph.pb(i);
        else pg.pb(i);
    }
    ph.pb(n),pg.pb(n);
    for(int i=1;i<sz(pg)-1;i++){
        ans+=(pg[i]-pg[i-1]-1LL)*(pg[i+1]-pg[i]-1LL);
        ans+=max(0LL,pg[i]-pg[i-1]-2LL)+max(0LL,pg[i+1]-pg[i]-2LL);
    }
    for(int i=1;i<sz(ph)-1;i++){
        ans+=(ph[i]-ph[i-1]-1LL)*(ph[i+1]-ph[i]-1LL);
        ans+=max(0LL,ph[i]-ph[i-1]-2LL)+max(0LL,ph[i+1]-ph[i]-2LL);
    }
    cout<<ans<<endl;

}