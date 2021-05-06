#include <iostream>
#include <cmath>
using namespace std;

int main(){
    int a,b,c,x1,x2,f,g;
    while (cin >> a >> b >> c){
        f = (b*b)-(4*(a*c));
        g = sqrt(f);
        x1 = ((-b)+g)/(2*a);
        x2 = ((-b)-g)/(2*a);
        if (f > 0){
            cout << "Two different roots x1=" << x1 << " , x2=" << x2 << endl;
        }
        else if (f == 0){
            cout << "Two same roots x=" << x1 << endl;
        }
        else{
            cout << "No real root";
        }
    }
    return 0;
}