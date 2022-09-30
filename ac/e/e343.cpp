#include <iostream>
#include <iomanip>
using namespace std;

int main(){
    double h,w,ans;
    cin >> w >> h;
    h = h/100;
    h = h*h;
    ans = w/h;
    cout << fixed << setprecision(1) << ans;
    return 0;
}