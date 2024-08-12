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
int v[5*maxn];
int cnt[10*maxn];
ii pans;
int main(){_
    int n,k;cin>>n>>k;
    for(int i=1;i<=n;i++)
        cin>>v[i];
    int r=0,ans=0;
    int cur=0;
    for(int l=1;l<=n;l++){
        while(cur<=k&&r<n)cnt[v[++r]]++,cur+=cnt[v[r]]==1;
        if(cur>k)cur--,cnt[v[r]]--,r--;
        if(ckmax(ans,r-l+1))pans = {l,r};
        if(cnt[v[l]]==1)cur--;
        cnt[v[l]]--;
    }
    cout<<pans.first<<" "<<pans.second<<endl;
}