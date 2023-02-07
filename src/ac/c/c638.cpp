#include <iostream>
#include <string>
using namespace std;

int main(){
    string t[10] = {"庚","辛","壬","癸","甲","乙","丙","丁","戊","己"};
    string d[12] = {"申","酉","戌","亥","子","丑","寅","卯","辰","巳","午","未"};
    int n;
    while(cin >> n){
        cout << t[n%10] << d[n%12] << endl;
    }
    return 0;
}