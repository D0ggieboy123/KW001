#include <iostream>
#include <string> 
#include <cmath>
#include <list>
#include <vector>
#include <cstdio>
#include <limits>
using namespace std;
template <typename T>
int VSauce(vector<T> v){
  int count = 0;
  //cout << "HEYY VSAUCE, MICHEAL HERE";
  for([[maybe_unused]]T itm : v){
    count += 1;
  }
return count;
}
template <typename T>
void Fugue_Helper_Helper(vector<T> noyes){
  cout << "[";
  for (T itm : noyes){
    cout << " " << itm;
  }
  cout << "]";
}
  

float Fugue_Needs_Help(string John_Lennon){
  [[maybe_unused]]vector<string> ni;
  [[maybe_unused]]int lb = 0;
  [[maybe_unused]]vector<char> op;
  string MichealVS = "";
  bool flg = false;
  float rslt;
  int oin = 0;
   [[maybe_unused]]int fact = 1;
  for(char c : John_Lennon){
    Fugue_Helper_Helper(ni);
    if (c == ' '){
      cout << "DOMAIN ERROR  rule*b0123 was violated {input SPACE was used}";
      exit(0);
    }
    else if (c == ')'){
        flg = false;
        float Goldfish = Fugue_Needs_Help(MichealVS);
        MichealVS = "";
        ni.push_back(to_string(Goldfish));
    }
    else if (c == '('){
      flg = true;
      if (ni.size() > op.size()){
        op.push_back('*');
      }
    }
    else if (c == '!'){
      fact = 1;
      for (float i = 1; i <= stof(ni.back()); i++) {
        fact *= i;
        //cout << fact << "HEY VSAUCE MICHEAL HERE" << i << "ORGAN FUGUE IN G MINOR";
      }
    ni[VSauce(ni)-1] = to_string(fact);
    }
    else if (flg == true){
      MichealVS += c; 
    }
    else if(VSauce(op) == VSauce(ni) && c == '-'){
        string cts(1, c);
        ni.push_back(cts);
    }
    else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
        op.push_back(c);
        lb += 1;
      }
    else{
        if (ni.size() > lb){
          ni[lb] += c;
        }
        else{
          string cts(1, c);
          ni.push_back(cts);
        }
      }  
    }
  rslt = stof(ni[oin]);
  for(char c : op){
    switch(c){
      case '+':
        rslt = rslt + stof(ni[oin+1]);
         break;
      case '-':
        rslt = rslt - stof(ni[oin+1]);
         break;
      case '*':
        rslt = rslt * stof(ni[oin+1]);
         break;
      case '/':
        rslt = rslt / stof(ni[oin+1]);
         break; 
      case '^':
        rslt = pow(rslt,stof(ni[oin+1]));
          break;
  }
  oin += 1;
  }
  //Fugue_Helper_Helper(ni);
  return rslt;
}
float Fugue() {
  string uin = "";
  cout << "Input an Expresion: ";
  getline(cin, uin); 
  return Fugue_Needs_Help(uin);
} 

int main(){
  while (true){
    cout << Fugue() << "\n";
  }
}
