#include <bits/stdc++.h>

using namespace std;
vector<int>idades;
int main(int argc, char const *argv[]) {
  int a,b,c;
  cin>>a>>b>>c;
  idades.push_back(a);
  idades.push_back(b);
  idades.push_back(c);
  sort(idades.begin(),idades.end());
  cout<<idades[1];
  return 0;
}
