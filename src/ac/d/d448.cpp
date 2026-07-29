#include <bits/stdc++.h>
using namespace std;
int main(){
    double t1,t2,t3,x1,x3;
    while(cin>>t1>>t2>>t3>>x1>>x3){
        double x2 = x3 + (t2-t3)*(x1-x3)/(t1-t3);
        printf("%f\n", x2);
    }
    return 0;
}
