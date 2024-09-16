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
vector<pair<int,ii>>patch;
vector<int>nhoj;
set<pair<int,ii>>bounds;
int used[2*maxn];
int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    int k,m,n;cin>>k>>m>>n;
    for(int i=1;i<=k;i++){
        int p,t;cin>>p>>t;
        patch.pb({p,{t,0}});
    }
    sort(all(patch));
    for(int i=1;i<=m;i++){
        int x;cin>>x;
        nhoj.pb(x);
    }
    sort(all(nhoj));
    int curm=0;
    for(int i=0;i<k;i++){
        auto [pos,random] = patch[i];
        auto [t,mxd] = random;
        while(nhoj[curm]<pos&&curm<m-1)curm++;
        mxd = abs(nhoj[curm]-pos);
        if(curm)mxd=min(mxd,pos-nhoj[curm-1]);
        patch[i].second.second = mxd;
    }
    for(int i=0;i<k;i++){
        auto [pos, random] = patch[i];
        auto [t, mxd] = random;
        ll boundtaste = 1LL*t;
        int start = i;
        while(i+1<k&&patch[i+1].first-pos-mxd+1<=patch[i+1].second.second){
            boundtaste += 1LL * patch[i + 1].second.first;
            i++;
        }
        bounds.insert({boundtaste,{start,i}});
        // if(start!=i)i--;
    }
    ll ans=0;
    int cnt=0;
    while(cnt<n&&!bounds.empty()){
        auto [qnt,interval] = *(prev(end(bounds)));
        if(used[interval.first]){
            bounds.insert({qnt-patch[interval.first].first,{interval.first+1,interval.second}});
        }else{
            used[interval.second]=1;
            ans+=1LL*qnt;
            bounds.erase({qnt,interval});
            cnt++;
        }
    }
    cout<<ans<<endl;

}