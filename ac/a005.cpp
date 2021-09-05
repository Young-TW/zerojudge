#include <iostream>
using namespace std;
int main() {
  int n[5],t;
  cin >> t;
  while (t>0){
    cin >> n[1] >> n[2] >> n[3] >> n[4];
    if (n[4]-n[3]!=n[3]-n[2]){
      n[5] = n[4] * (n[4] / n[3]);
      cout << n[1] << " " << n[2] << " " << n[3] << " " << n[4] << " " << n[5] << "\n";
    }
    else if (n[4]-n[3]==n[3]-n[2]){
      n[5] = n[4] + (n[4]-n[3]);
      cout << n[1] << " " << n[2] << " " << n[3] << " " << n[4] << " " << n[5] << "\n";
    }
    n[1]=n[2]=n[3]=n[4]=n[5]=0;
    t=t-1;
  }
  return 0;
}