#include <bits/stdc++.h>
#define maxn (int)(1e5+51)
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define ll long long
#define ull unsigned long long
#define ii pair<int,int>
#define iii tuple<int,int,int>
#define inf (int)(2e9+1)
#define mod (int)(1e9+7)

using namespace std;
string senha[20010];
unordered_map<string,int>cnt;
int n;
int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>senha[i];
    for(int i=1;i<=n;i++){
        set<string>adicionei;
        for(int j=0;j<senha[i].size();j++){
            string x="";
            for(int k=j;k<senha[i].size();k++){
                x+=senha[i][k];
                if(!adicionei.count(x)){
                    adicionei.insert(x);
                    cnt[x]++;
                }
            }
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        ans+=cnt[senha[i]]-1;
    }
    cout<<ans<<endl;
    
}