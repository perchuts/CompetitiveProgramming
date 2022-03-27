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
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

using namespace std;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

ll bit[2*maxn],qnt[2*maxn],fact[2*maxn];

const int mx = 2*maxn-1;
const ll mod = 998244353;

void insert(int i,ll d){
    while(i<=mx){
        bit[i]+=d;
        i+=i&(-i);
    }   
}

ll query(int x){
    ll ans = 0;
    while(x){
        ans = (ans+bit[x])%mod;
        x -= x&(-x);
    }
    return ans;
}

ll inv(ll a,ll b){
    return 1<a ? b - inv(b%a,a)*b/a : 1;
}

int main(){_
    int n,m;cin>>n>>m;
    vector<int>s(n),t(m);
    for(auto& x:s){
        cin>>x;
        qnt[x]++;
    }
    for(auto& x: t)cin>>x;
    fact[0] = 1;
    for(ll i=1ll;i<=mx;++i)fact[i]=(fact[i-1]*i)%mod;
    ll prod = 1;
    for(int i=1;i<=mx;++i){
        prod = (prod*fact[qnt[i]])%mod;
        insert(i,qnt[i]);
    }
    ll ans = 0;
    bool ok = 1;
    for(int i=0;i<min(m,n-1);++i){
        ll sum = query(t[i]-1);
        if(sum!=0)ans += (((fact[n-1-i]*inv(prod,mod))%mod)*sum)%mod;
        if(!qnt[t[i]]){
            ok = 0;break;
        }
        prod = (prod*inv(qnt[t[i]]--,mod))%mod;
        insert(t[i],-1);
    }

    if(n<m&&ok&&query(t[n-1]))ans++;
    else if(n==m&&ok&&query(t[n-1]-1))ans++;
    cout<<(ans+mod)%mod<<endl;
    //considerar o caso em que s é substring de t
}