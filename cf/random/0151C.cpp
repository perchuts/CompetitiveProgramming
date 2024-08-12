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
    long long q;cin>>q;
    ll cpy = q;
    vector<ll>divisors;
    for(ll i=2;i<=1e7&&q!=1;i++){
        while(q%i==0){

            divisors.pb(i);
            q/=i;
        }
    }
    if(q!=1&&divisors.size())divisors.push_back(0);
    if(divisors.size()==2){
        cout<<2<<endl;
        
    }else{
        cout<<1<<endl;
        cout<<(divisors.size()<2 ? 0 : (divisors[0]*divisors[1]))<<endl;
    }
}