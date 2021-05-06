#include <iostream>
using namespace std;
int main() {
  int n1,n2,n3,n4,n5,t;
  cin >> t;
  while (t>0){
    cin >> n1 >> n2 >> n3 >> n4;
    if (n4-n3!=n3-n2){
      n5 = n4 * (n4 / n3);
      cout << n1 << " " << n2 << " " << n3 << " " << n4 << " " << n5 << "\n";
    }
    else if (n4-n3==n3-n2){
      n5 = n4 + (n4-n3);
      cout << n1 << " " << n2 << " " << n3 << " " << n4 << " " << n5 << "\n";
    }
    n1=n2=n3=n4=n5=0;
    t=t-1;
  }
  return 0;
}