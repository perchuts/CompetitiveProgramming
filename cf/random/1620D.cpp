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
int v[1001];
int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    int t;cin>>t;
    while(t--){
        int n;cin>>n;
        for(int i=1;i<=n;i++)
            cin>>v[i];  
        int three=0,two=0,one=0,type=0,mx=0,mn=2e9;
        for(int i=1;i<=n;i++){
            if(v[i]%3==1)one=1;
            if(v[i]%3==2)two=1;
            mn = min(v[i],mn);
            three = max(three,v[i]/3);
            if(v[i]>mx){
                mx=v[i];
                type=v[i]%3;
            }
        }
        if(one&&two){
            if(mn==1){
                cout<<one+two+three-(type==0)<<endl;
            }else if(type==1){
                int ok=1;
                for(int i=1;i<=n;i++)
                    if(v[i]==mx-1)ok=0;
                cout<<one+two+three-ok<<endl;
            }else if(type==0){
                cout<<two+(three-1)+one<<endl;
            }else{
                cout<<one+two+three<<endl;
            }
        }else{
            cout<<three+one+two<<endl;
        }
    }   
}