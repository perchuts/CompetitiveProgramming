#include <bits/stdc++.h>

using namespace std;
string s;
string s1;
vector<pair<string,int>>modificados;
string a = "abcdefghijklmnopqrstuvxz";

int indice(char k){
  for(int i=0;i<a.length();i++){
    if(a[i]==k)return i;
  }
}

int main(int argc, char const *argv[]) {
  cin>>s;
  s1 = s;
  for(int i=0;i<s.length();i++){
    if(s[i]!='a'&&s[i]!='e'&&s[i]!='i'&&s[i]!='o'&&s[i]!='u'){
      string b="";
      b+=s[i];
      int u = indice(s[i]);
      char c1,c2;
      for(int j=1;j<a.length();j++){
        c1 = a[u+j];
        c2 = a[u-j];
        int passou=0;
        if(c1=='a'||c1=='e'||c1=='i'||c1=='o'||c1=='u'){
          passou=1;
        }if(c2=='a'||c2=='e'||c2=='i'||c2=='o'||c2=='u'){
          b+=c2;
          break;
        }
        if(passou){
          b+=c1;
          break;
        }

      }
      if(s[i]=='z'){
        b+='z';
      }else{
        c1 = a[u+1];
        if(c1=='a'||c1=='e'||c1=='i'||c1=='o'||c1=='u')c1=a[u+2];
        b+=c1;
      }
      modificados.push_back({b,i});
    }
  }

  for(int i=0;i<modificados.size();i++){
    s.replace(s.begin()+modificados[i].second+2*i,s.begin()+modificados[i].second+2*i+1,modificados[i].first.begin(),modificados[i].first.end());
  }
  cout<<s;
  return 0;
}
