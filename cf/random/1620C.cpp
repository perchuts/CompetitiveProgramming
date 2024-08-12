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
vector<ll>intr;
ll mxpos[2100], qnt[2100];
int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    int t;cin>>t;
    while(t--){
        ll n,k,x;cin>>n>>k>>x;
        string s;cin>>s;
        string real="";
        for(int i=0;i<sz(s);i++){
            if(s[i]=='a')real+='a';
            else{
                ll cnt=1;
                while(s[i+1]=='*'&&i<sz(s)){
                    cnt++;
                    i++;
                }
                intr.pb(cnt);
                real+='*';
            }
        }
        mxpos[intr.size()]=1;
        for(int i = intr.size()-1;i>=0;i--){
            mxpos[i] = mxpos[i+1]*(intr[i]*k+1LL);
            if(mxpos[i]>1LL*1e18)break;
        }
        for(int i=intr.size()-1;i>=0;i--){
            if(x<=mxpos[i]||mxpos[i]<=mxpos[i+1]){//i+1 = intervalo mais a direita possivel sendo lexograf. menor
                while(i<intr.size()){
                    ll mx = (x-1)/mxpos[i+1];
                    x-=mxpos[i+1]*mx;
                    qnt[i++]=mx;
                }
                break;
            }
        }
        int cur=0;
        for(int i=0;i<sz(real);i++){
            if(real[i]=='a')cout<<'a';
            else{
                while(qnt[cur]-->0)cout<<'b';
                cur++;
            }
        }
        cout<<endl;
        intr.clear();
        for(int i=0;i<=sz(s);i++)mxpos[i]=0;
    }   
}