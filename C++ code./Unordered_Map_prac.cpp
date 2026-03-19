#include <iostream>
#include <string>
#include <unordered_map>
#include <variant>
using namespace std;

int main(){
  unordered_map<string, variant<string, int, float, double, bool>> list_of_listing = {{"xe", 0}, {"S", "S"}, {"J", 0.2}};
  for (auto[keys, values] : list_of_listing){
    cout << "(" << keys  << ", ";
    visit([](auto var){
      cout << var << ")" << endl;
    }, values); 
  }
}
