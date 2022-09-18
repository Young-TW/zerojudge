#include <iostream>
#include <algorithm>
using namespace std;

int main(){
    int n,d,tt=0,count=0;
    int price[3];
    cin >> n >> d;
    for(int i=0;i<n;i++){
        for(int j=0;j<3;j++){
            cin >> price[j];
        }
        sort(price,price+3);
        if(price[2] - price[0] > d){
            tt += (price[0] + price[1] + price[2]) / 3;
            count++;
        }
    }
    cout << count << " " << tt;
    return 0;
}