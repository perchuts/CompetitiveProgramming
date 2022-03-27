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

ll pref[51],pw[51];// pref[i] = sum(k^i)
ll n,k,q;

int findlvl(ll x){
    for(int i=0;i<51;i++)if(pref[i]>=x)return i;
    return inf;
}

ll findp(ll x,int lvl){
    int lvlp = lvl-1;
    ll leaf = (x-pref[lvlp]+k-1)/k;
    return pref[lvlp] - pw[lvlp] + leaf;
}

int main(){_
    cin>>n>>k>>q;
    pw[0] = pref[0] = 1;
    if(k!=1)for(int i=1;pw[i-1]<n;i++)pw[i] = k*pw[i-1];
    if(k!=1)for(int i=1;pref[i-1]<n;i++)pref[i] = pref[i-1]+pw[i];
    while(q--){
        ll x,y;cin>>x>>y;
        if(k==1){
            cout<<abs(x-y)<<endl;
            continue;
        }
        int lvlx = findlvl(x), lvly = findlvl(y);
        int ans = 0;
        if(lvlx<lvly){
            swap(x,y);
            swap(lvlx,lvly);
        }
        while(lvlx>lvly){
            ans++;
            x = findp(x,lvlx--);
        }
        while(x!=y){
            ans+=2;
            x = findp(x,lvlx--), y = findp(y,lvly--);
        }
        cout<<ans<<endl;
    }    
}