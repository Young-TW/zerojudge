#include <iostream>
using namespace std;

int main(){
    int day;
    int manto;
    long long int tt=0;
    cin >> day;
    for(int i=1;i<=day;i++){
        cin >> manto;
        tt += (i*manto);
    }
    cout << tt << endl;
    return 0;
}