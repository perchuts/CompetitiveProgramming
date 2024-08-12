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
int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    int t;cin>>t;
    while(t--){
        int n;cin>>n;
        string s;cin>>s;
        int ok=0;
        for(int i=0;i<n-1;i++){
            if(s[i]=='a'&&s[i+1]=='a'){
                cout<<2<<endl;
                ok=1;
                break;
            }
        }
        if(ok)continue;
        for(int i=0;i<n-2;i++){
            if((s[i]=='a'&&s[i+2]=='a')){
                cout<<3<<endl;
                ok=1;
                break;
            }
        }
        if(ok)continue;
        for(int i=0;i<n-3;i++){
            if(s[i]=='a'&&s[i+3]=='a'&&s[i+1]!=s[i+2]){
                cout<<4<<endl;
                ok=1;
                break;
            }
        }
        if(ok)continue;
        for(int i=0;i<n-6;i++){
            if(s[i]=='a'&&s[i+3]=='a'&&s[i+6]=='a'&&s[i+1]==s[i+2]&&s[i+4]==s[i+5]&&s[i+4]!=s[i+2]){
                cout<<7<<endl;
                ok=1;
                break;
            }
        }
        if(ok)continue;
        cout<<-1<<endl;
    }   
}