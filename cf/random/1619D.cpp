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
ii mx[maxn];
vector<ii> v[maxn];
bool counted[maxn];
int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    int t;cin>>t;
    while(t--){
        int m,n;cin>>m>>n;
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                int x;cin>>x;
                if(mx[j].first<x){
                    mx[j]={x,i};
                }
                v[i].pb({x,j});
            }
        }
        for(int i=0;i<m;i++)
            sort(all(v[i]));
        int distinct=0;
        multiset<int>mn;
        for(int i=0;i<n;i++){
            mn.insert(mx[i].first);
            if(counted[mx[i].second]==0){
                distinct++;counted[mx[i].second]=1;
            }
        }
        if(distinct<n){
            cout<<*(begin(mn))<<endl;
        }else{
            int ans=0;
            int mn2 = *(begin(mn));
            for(int i=0;i<m;i++){
                auto maior=v[i][n-1],segmaior=v[i][n-2];
                ans=max({ans,min({maior.first,segmaior.first,mn2})});
            }
            cout<<ans<<endl;
        }
        for(int i=0;i<m;i++){
                counted[i]=0;
                v[i].clear();
            }
            for(int i=0;i<n;i++){
                mx[i]={0,0};
            }
    }   
}