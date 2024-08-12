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
int heaps[2*maxn],temp[2*maxn];
int n;
bool possible(int x){
    for(int i=1;i<=n;i++)
        temp[i]=0;
    for(int i=n;i>=3;i--){
        int mn = (min((heaps[i]+temp[i]-x),heaps[i]))/3;
        if(mn<0)mn=0;
        temp[i-1]+=mn,temp[i-2]+=2*mn;
        temp[i]-=3*mn;
    }
    for(int i=1;i<=n;i++){
        if(temp[i]+heaps[i]<x)return 0;
    }
    return 1;
}


int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    int t;cin>>t;
    while(t--){
        cin>>n;
        for(int i=1;i<=n;i++)
            cin>>heaps[i];
        int l=1,r=1e9;
        while(l<r){
            int md = (l+r)/2;
            if(possible(md)){
                l = md+1;
            }else{
                r= md;
            }
        }
        if(possible(l)){
            cout<<l<<endl;
        }else{
            cout<<l-1<<endl;
        }
    }   

}