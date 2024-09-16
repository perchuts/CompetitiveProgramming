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
 
ii pairs[maxn];
int bit[maxn];
int n;
// 1 => n, n => 1
void insert(int x,int y){
    for(;x<=n;x+=x&(-x))ckmax(bit[x],y);
}
 
int query(int x){
    int ans = 0;
    while(x){
        ckmax(ans,bit[x]);
        x-=x&(-x);
    }
    return ans;
}
 
vector<ii>origin;
 
int main(){_
    cin>>n;
    vector<int>dest(n);
    for(int i=1;i<=n;i++){
        cin>>pairs[i].first>>pairs[i].second;
        origin.pb(pairs[i]);
    }    
    sort(all(origin));
    iota(all(dest),1);
    sort(all(dest),[](int x,int y){
        return origin[x-1].second<origin[y-1].second;
    });
    ll ans = 0;
    for(int i=0;i<n;i++){
        int cur = dest[i];
        int reversedcur = n+1 - cur;
        insert(reversedcur,query(reversedcur)+1);
    }
    cout<<query(n)<<endl;
    //find size of longest decreasing subsequence
 
}
