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

ll x,fact[20];
int ans; 

int onbits(ll x){
    int resp = 0;
    while(x){
        resp += x&1;
        x>>=1ll;
    }
    return resp;

}
void solve(int i,ll cur,int used){
    if(cur<0||i>16)return;
    ckmin(ans,used+onbits(cur));
    solve(i+1,cur-fact[i],used+1);
    solve(i+1,cur,used);
}

void solve(){
    cin>>x;
    ans = onbits(x);
    solve(1,x,0);
    cout<<ans<<endl;
}


int main(){_
    //freopen("in.in", "r", stdin);
    //freopen("out.out", "w", stdout);
    fact[0] = 1;
    for(ll i=1;i<=17;++i)fact[i] = fact[i-1]*1ll*i;
    int t;cin>>t;
    while(t--)solve();
}