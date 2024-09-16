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

int v[2*maxn],freq[20*maxn];
//VERY NICE! that nested for complexity is O(nlogn)!!
int main(){_
    int n;cin>>n;
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        freq[x]++;
    }
    ll ans = 1LL*n;
    for(int i=2;i<=2e6;i++){
        ll cur = 0;
        for(int j=i;j<=2e6;j+=i){
            cur += freq[j];
        }
        if(cur>1)ckmax(ans,1LL*i*cur);
    }
    cout<<ans<<endl;
}