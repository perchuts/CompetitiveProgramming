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
int a,b;
vector<int>result(2,0);
int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    cin>>a>>b;
    int factora=1,factorb=1;
    while(a>0||b>0){
        if(a%10>b%10){
            result[0]+=factora*(a%10);
            factora*=10;
        }else if(b%10>a%10){
            result[1]+=factorb*(b%10);
            factorb*=10;
        }else{
            result[1]+=factorb*(a%10);
            result[0]+=factora*(a%10);
            factora*=10;
            factorb*=10;
        }
        a/=10;
        b/=10;
    }
    sort(all(result));
    if(factora>1&&factorb>1){
        cout<<result[0]<<" "<<result[1]<<endl;
    }else{
        cout<<"-1 "<<result[1]<<endl;
    }
}