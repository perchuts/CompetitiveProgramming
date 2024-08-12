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

int v[2*maxn],dp[2*maxn],msb[2*maxn],reps[2*maxn];

int findmsb(int x){
    int ret=0;
    while((1<<ret)<=x)ret++;
    return ret;
}

map<int,bool>mark;
map<int,int>inicial;

void generate(int x,int source){
    if(x==0||mark[x])return;
    mark[x] = 1;
    if(inicial[x]){
        reps[source]++;
        return;
    }
    if((x%4)==0)generate(x/4,source);
    if(x&1)generate((x-1)/2,source);
}

int main(){_
    int n,p;cin>>n>>p;
    for(int i=1;i<=n;++i)cin>>v[i];    
    for(int i=1;i<=n;++i){
        msb[i] = findmsb(v[i]);
        dp[msb[i]]++;
        inicial[v[i]] = 1;
    }
    for(int i=1;i<=n;++i){
        mark.clear();
        if(v[i]&1)generate((v[i]-1)/2,msb[i]);
        if((v[i]%4)==0)generate(v[i]/4,msb[i]);
    }
    //tenho que tirar repeticoes
    int ans = dp[1]-reps[1];
    // cout<<dp[1]<<" "<<reps[1]<<endl;

    for(int i=2;i<=p;++i){
        dp[i] = (dp[i]+dp[i-2]+dp[i-1]-reps[i])%mod;
        ans=(ans+dp[i])%mod;
        // cout<<dp[i]<<" "<<reps[i]<<endl;
    }
    cout<<(ans+mod)%mod<<endl;
}