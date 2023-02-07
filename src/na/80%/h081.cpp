#include <iostream>
using namespace std;

int main(){
    int n,d,x,tt=0;
    bool status;
    cin >> n >> d;
    int y[n];
    for(int i=0;i<n;i++){
        cin >> y[i];
        if(i==0){
            x = y[i];
            status=1;
        }
        if(y[i]>=x+d && status){
            tt += y[i] - x;
            status=0;
        }
        if(y[i]<=x-d && !status){
            x=y[i];
            status=1;
        }
    }
    cout << tt << endl;
    return 0;
}