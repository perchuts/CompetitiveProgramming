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
string a, s;
int zeros;
string backtracking(int ia,int is){
    if(is==-1)return "";
    int cura = (a[ia]-'0');
    int curs1 = (s[is]-'0'); 
    if(zeros>abs(is-ia)&&is!=0){
        int curs = int(s[is]-'0')+10*int(s[is-1]-'0');
        if(curs>9&&curs-cura<10){
            string a = backtracking(ia-1,is-2);
            if(a!="*"){
                char x = char('0'+(curs-cura));
                string b = "";
                b+=a;
                b+=x;
                return b;
            }
        }
    }
    if(curs1<cura)return "*";
    string a = backtracking(ia-1,is-1);
    if(a=="*")return "*";
    char x = char('0'+(curs1-cura));
    string b = "";
    b+=a;
    b+=x;
    return b;
}

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    int t;cin>>t;
    while(t--){
        cin>>a>>s;
        string x="";
        for(int i=0;i<sz(s)-sz(a);i++){
            x+='0';
            zeros++;
        }
        x+=a;
        a = x;
        string ans = backtracking(sz(a)-1,sz(s)-1);
        zeros=0;
        if(ans=="*"){
            cout<<-1<<endl;
        }else{
            int it=0;
            while(ans[it]=='0')it++;
            for(;it<sz(ans);it++)
                cout<<ans[it];
            cout<<endl;
        }
    }   
}